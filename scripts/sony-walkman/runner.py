"""Process only the source file supplied by the loopback music service."""
import argparse, array, atexit, hashlib, json, math, os, shutil, struct, subprocess, sys, time
from pathlib import Path

class DecodedInput:
    def __init__(self,path): self.stdout = open(path,'rb')
    def wait(self,timeout=None): return 0
    def poll(self): return 0
    def kill(self): self.stdout.close()

def close_decoder(decoder):
    if decoder.poll() is None:
        decoder.kill(); decoder.wait()
    decoder.stdout.close()

def emit(**value):
    # ASCII JSON also preserves Chinese errors in legacy Windows pipe locales.
    print(json.dumps(value, ensure_ascii=True), flush=True)

def validate_assets():
    manifest = json.loads(Path(__file__).with_name('assets.json').read_text())
    root = Path(os.environ['SONY_WALKMAN_ASSETS'])
    for filename, expected in manifest['files'].items():
        if hashlib.sha256((root / filename).read_bytes()).hexdigest() != expected:
            raise ValueError(f'Sony original asset hash mismatch: {filename}')
    if os.environ.get('SONY_WALKMAN_X86_DLL'):
        dll = Path(os.environ['SONY_WALKMAN_X86_DLL'])
        native = json.loads(dll.with_name('assets.json').read_text())
        if hashlib.sha256(dll.read_bytes()).hexdigest() != native['files']['sony-dsp-x86.dll']:
            raise ValueError('Sony C++ component hash mismatch')

def header(rate, data_bytes):
    # IEEE float WAV retains Sony output and any peaks above full scale.
    return struct.pack('<4sI4s4sIHHIIHH4sII4sI', b'RIFF', data_bytes+48, b'WAVE',
                       b'fmt ',16,3,2,rate,rate*8,8,32,b'fact',4,data_bytes//8,b'data',data_bytes)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--probe', action='store_true')
    parser.add_argument('--phase-check', action='store_true')
    parser.add_argument('--input'); parser.add_argument('--output')
    parser.add_argument('--dsee', type=int, default=0, choices=(0,1))
    parser.add_argument('--dc', type=int, default=0, choices=range(7))
    parser.add_argument('--vinyl', type=int, default=0, choices=range(5))
    parser.add_argument('--workers', type=int, default=min(3,os.cpu_count() or 1), choices=(1,2,3))
    parser.add_argument('--progressive', action='store_true')
    parser.add_argument('--dsd-pcm', action='store_true')
    parser.add_argument('--start-position', type=float, default=0)
    args = parser.parse_args()
    validate_assets()
    if not os.environ.get('SONY_WALKMAN_X86_DLL'):
        import unicorn
        if unicorn.__version__ != '2.1.4':
            raise ValueError('This verified reference requires unicorn 2.1.4')
    from effects import create_chain, feed_chain, finish_chain
    import arm_runtime as arm
    native_decoder = os.environ.get('SONY_WALKMAN_NATIVE_DECODER')
    if args.phase_check:
        from phase_checks import run_phase_checks
        emit(**run_phase_checks())
        return
    if args.probe:
        if native_decoder:
            result = subprocess.run([native_decoder],input=b'{"id":1,"cmd":"devices"}\n{"id":2,"cmd":"shutdown"}\n',capture_output=True,check=True,timeout=15)
            if not json.loads(result.stdout.splitlines()[0]).get('available'):
                raise ValueError('Bundled native decoder is unavailable')
        else:
            for name, fallback in [('SONY_WALKMAN_FFMPEG','ffmpeg'),('SONY_WALKMAN_FFPROBE','ffprobe')]:
                subprocess.run([os.environ.get(name,fallback),'-version'],capture_output=True,check=True,timeout=10)
        # The same initialization used for actual playback, not just imports.
        chain, rate = create_chain(44100, True, 2, 1)
        output = feed_chain(chain, bytes(512*8)) + finish_chain(chain)
        if not output:
            raise ValueError('Sony self-check produced no PCM')
        values = array.array('f'); values.frombytes(output)
        if not all(math.isfinite(x) for x in values):
            raise ValueError('Sony self-check produced non-finite PCM')
        versions = [arm.call(name) for name in ('EffectGetVersionDSX','EffectGetVersionDCPhaseLinearizer','EffectGetVersionRealVinyl')]
        if versions != [0x30007, 0x10000, 0x10000]:
            raise ValueError(f'Unexpected Sony DSP versions: {versions}')
        from phase_checks import quick_isolation
        emit(ready=True, versions=versions, sampleRate=rate, phaseStereoIsolation=quick_isolation(),backend='x86-cpp' if os.environ.get('SONY_WALKMAN_X86_DLL') else 'arm-original')
        return
    if not args.input or not args.output:
        raise ValueError('Input and output are required')
    if not math.isfinite(args.start_position) or not 0 <= args.start_position <= 3600:
        raise ValueError('Invalid Sony start position')
    if args.start_position and not native_decoder:
        raise ValueError('从播放位置实时处理需要桌面原生解码器。')
    input_dsd = Path(args.input).suffix.lower() in ('.dsf','.dff')
    decoder = None
    expected_frames = None
    position_offset = 0
    if native_decoder:
        # Decode directly into the bounded pipe while Sony processes its first
        # blocks. No full-track decode or intermediate PCM file comes first.
        decoder = subprocess.Popen([native_decoder,'--decode-stream-json'],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.DEVNULL)
        atexit.register(close_decoder,decoder)
        decoder.stdin.write(json.dumps({'file':args.input,'dsd':input_dsd,'position':args.start_position}).encode('utf-8')+b'\n')
        decoder.stdin.close()
        metadata_line = decoder.stdout.readline(65537)
        try:
            if len(metadata_line)>65536: raise ValueError('Native metadata exceeds limit')
            metadata = json.loads(metadata_line)
            if not metadata.get('ready'): raise ValueError('Native source is unavailable')
        except Exception:
            decoder.kill(); decoder.wait(); decoder.stdout.close()
            raise ValueError('原生流式解码器未返回有效音频信息。')
        info = {'sample_rate':metadata['sampleRate'],'channels':metadata['sourceChannels'],'codec_name':'dsd' if input_dsd else 'pcm'}
        duration = float(metadata['duration'])
        expected_frames = int(metadata['frames'])
        position_offset = float(metadata['positionOffset'])
    else:
        ffprobe = os.environ.get('SONY_WALKMAN_FFPROBE', 'ffprobe')
        probe = subprocess.run([ffprobe,'-v','error','-select_streams','a:0','-show_entries',
                                'stream=sample_rate,channels,codec_name:format=duration','-of','json',args.input],
                               capture_output=True, check=True, timeout=30)
        metadata = json.loads(probe.stdout); info = metadata['streams'][0]
        input_dsd = input_dsd or info['codec_name'].startswith(('dsd','dst'))
        duration = float(metadata['format']['duration'])
    rate = 44100 if input_dsd and args.dsd_pcm else int(info['sample_rate'])
    if rate not in (44100,48000,176400,192000) or int(info['channels']) not in (1,2) or (input_dsd and not args.dsd_pcm):
        raise ValueError('Sony DC／黑胶原版支持 44.1、48、176.4、192 kHz 单声道或双声道 PCM。')
    if args.dsee and rate not in (44100,48000):
        raise ValueError('DSEE AI 原版仅支持 44.1／48 kHz 输入；高采样率音源应保持原采样率并旁路 DSEE AI。')
    if not 0 < duration <= 3600:
        raise ValueError('Sony 处理支持最长一小时的曲目。')
    if duration*rate*8*(4 if args.dsee else 1) > 2_000_000_000:
        raise ValueError('Sony 输出超过 2 GB 单曲上限。')
    needed = duration*rate*8*((4 if args.dsee else 1)+(1 if args.progressive and not native_decoder else 0))+64_000_000
    if shutil.disk_usage(Path(args.output).parent).free < needed:
        raise ValueError('本机空间不足，无法准备 Sony 音效缓存。')
    parallel = args.workers > 1 and sum(bool(x) for x in (args.dsee,args.dc,args.vinyl)) > 1
    if parallel:
        chain = []
        output_rate = rate * (4 if args.dsee else 1)
    else:
        chain, output_rate = create_chain(rate, bool(args.dsee), args.dc, args.vinyl)
    ffmpeg = os.environ.get('SONY_WALKMAN_FFMPEG','ffmpeg')
    # Decoder only: no FFmpeg equalizer, harmonic enhancer, phase or vinyl filter.
    decoder_command = [ffmpeg,'-nostdin','-v','error','-i',args.input,'-map','0:a:0',
                       '-vn','-ac','2','-ar',str(rate),'-f','f32le','-c:a','pcm_f32le','pipe:1']
    decoded_path = args.output+'.decoded'
    if args.progressive and not native_decoder:
        # Decode first to learn the exact gapless frame count. A growing WAV then has
        # an accurate header/Content-Length, including MP3/AAC encoder padding.
        with open(decoded_path,'xb') as decoded:
            subprocess.run(decoder_command,stdout=decoded,stderr=subprocess.DEVNULL,check=True,timeout=300)
        decoded_bytes = Path(decoded_path).stat().st_size
        if decoded_bytes%8: raise ValueError('Incomplete decoded PCM')
        expected_frames = decoded_bytes//8
        if not expected_frames or expected_frames*output_rate//rate*8 > 2_000_000_000:
            raise ValueError('Decoded Sony output exceeded the configured size limit')
        duration = expected_frames/rate
        decoder = DecodedInput(decoded_path)
    elif decoder is None:
        decoder = subprocess.Popen(decoder_command,stdout=subprocess.PIPE,stderr=subprocess.DEVNULL)
    ratio = output_rate // rate
    frames = 0; written = 0; peak = 0.0; digest = hashlib.sha256()
    started = time.monotonic(); last_progress = 0.0
    pending_output = bytearray()
    pipeline = None
    try:
        with open(args.output, 'xb') as target:
            target.write(header(output_rate, (expected_frames or 0)*ratio*8))
            target.flush()
            if expected_frames is not None:
                emit(state='processing',progress=0,sampleRate=output_rate,duration=duration,positionOffset=position_offset,totalBytes=expected_frames*ratio*8+56,producedBytes=56)
            def write_pcm(content, limit):
                nonlocal written, peak
                pending_output.extend(content)
                length = min(len(pending_output), max(0,limit-written)) // 8 * 8
                pcm = bytes(pending_output[:length]); del pending_output[:length]
                values = array.array('f'); values.frombytes(pcm)
                if sys.byteorder != 'little': values.byteswap()
                if not all(math.isfinite(x) for x in values):
                    raise ValueError('Sony DSP produced non-finite audio')
                if values: peak = max(peak,max(abs(x) for x in values))
                target.write(pcm); digest.update(pcm); written += len(pcm)
            def progress():
                nonlocal last_progress
                if frames > rate*3601 or frames*ratio*8 > 2_000_000_000:
                    raise ValueError('Sony output exceeded the configured size limit')
                now = time.monotonic()
                if now-last_progress >= .1:
                    target.flush()
                    emit(state='processing',progress=min(.99,written/(duration*output_rate*8)),workers=len(pipeline.processes) if pipeline else 1,producedBytes=written+56)
                    last_progress = now
            if parallel:
                from parallel import ParallelChain
                pipeline = ParallelChain(decoder,rate,bool(args.dsee),args.dc,args.vinyl,args.workers)
                for content in pipeline:
                    frames = pipeline.frames
                    write_pcm(content,frames*ratio*8); progress()
                frames = pipeline.frames
            else:
                while True:
                    content = decoder.stdout.read(8192*8)
                    if not content: break
                    if len(content) % 8: raise ValueError('Incomplete PCM frame from decoder')
                    frames += len(content)//8
                    write_pcm(feed_chain(chain,content),frames*ratio*8); progress()
                if decoder.wait(timeout=10): raise ValueError('音乐解码失败。')
                write_pcm(finish_chain(chain),frames*ratio*8)
            if written != frames*ratio*8:
                raise ValueError(f'Sony output duration mismatch: {written} != {frames*ratio*8}')
            if expected_frames is not None and frames != expected_frames:
                raise ValueError('Progressive Sony frame count changed')
            target.seek(0); target.write(header(output_rate,written))
        emit(state='ready',progress=1,sampleRate=output_rate,frames=frames*ratio,channels=2,
             duration=frames/rate,positionOffset=position_offset,peak=peak,pcmSha256=digest.hexdigest(),
             renderSeconds=time.monotonic()-started,imports=sorted(pipeline.imports if pipeline else arm.called),workers=len(pipeline.processes) if pipeline else 1,
             dseeVersion=arm.call('EffectGetVersionDSX'),dcVersion=arm.call('EffectGetVersionDCPhaseLinearizer'),
             vinylVersion=arm.call('EffectGetVersionRealVinyl'))
    finally:
        if pipeline: pipeline.close()
        if decoder.poll() is None:
            decoder.kill(); decoder.wait()
        decoder.stdout.close()
        if args.progressive and not native_decoder: Path(decoded_path).unlink(missing_ok=True)

if __name__ == '__main__':
    try:
        main()
    except Exception as error:
        emit(state='error',error=str(error))
        sys.exit(1)
