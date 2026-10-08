import path from 'node:path'
import { promises as fs,existsSync } from 'node:fs'
import { fileURLToPath } from 'node:url'
import { createHash } from 'node:crypto'
import { spawn } from 'node:child_process'
import { availableParallelism } from 'node:os'
import { StringDecoder } from 'node:string_decoder'
import { readAudioMetadata } from './read-audio-metadata.mjs'
import manifest from './sony-walkman/assets.json' with { type: 'json' }

const PROJECT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')
const RUNNER = path.join(PROJECT, 'scripts/sony-walkman/runner.py')
const fail = (message, status = 400) => Object.assign(new Error(message), { status })
export function sonySettings(value) {
  if (!value || typeof value !== 'object' || Array.isArray(value) ||
      Object.keys(value).some((key) => !['dsee', 'dc', 'vinyl'].includes(key)) ||
      typeof value.dsee !== 'boolean' || !Number.isInteger(value.dc) || value.dc < 0 || value.dc > 6 ||
      !Number.isInteger(value.vinyl) || value.vinyl < 0 || value.vinyl > 4) throw fail('无效的 Sony 音效设置')
  return { dsee: value.dsee, dc: value.dc, vinyl: value.vinyl }
}

export const SONY_SAMPLE_RATES = {dsee:[44100,48000],dc:[44100,48000,176400,192000],vinyl:[44100,48000,176400,192000]}
export function sonyPlaybackPlan(settings,format) {
  const rate=Number(format.sampleRate),stereo=[1,2].includes(format.numberOfChannels),effectiveSettings={...settings},bypassed=[];
  for(const effect of ['dsee','dc','vinyl'])if(settings[effect]&&(!stereo||!SONY_SAMPLE_RATES[effect].includes(rate))){effectiveSettings[effect]=effect==='dsee'?false:0;bypassed.push(effect)}
  const names={dsee:'DSEE AI',dc:'DC 相位线性器',vinyl:'黑胶处理器'};
  return {effectiveSettings,bypassed,sourceSampleRate:rate,
    ...(bypassed.length?{message:`${bypassed.map(name=>names[name]).join('、')} 原版组件不支持此音源参数，已旁路；保留原采样率${Number.isFinite(rate)&&rate>0?` ${rate/1000} kHz`:''}。`}:{})};
}

export async function boundedSource(descriptor) {
  const [source, root] = await Promise.all([fs.realpath(descriptor.path), fs.realpath(descriptor.allowedRoot)])
  const relative = path.relative(root, source)
  if (relative === '..' || relative.startsWith(`..${path.sep}`) || path.isAbsolute(relative)) throw fail('文件已移出配置的音乐目录', 403)
  const stat = await fs.stat(source)
  if (!stat.isFile()) throw fail('音乐文件不存在', 404)
  return { source, signature: `${source}:${stat.size}:${stat.mtimeMs}` }
}

export class SonyWalkman {
  constructor({ dataDir, store, assetsDir = process.env.SONY_WALKMAN_ASSETS ?? path.join(PROJECT, 'vendor/sony-walkman'),
    python = process.env.SONY_WALKMAN_PYTHON ?? (process.platform === 'win32' && existsSync(path.join(PROJECT,'.tools/desktop-runtime/python/python.exe')) ? path.join(PROJECT,'.tools/desktop-runtime/python/python.exe') : process.platform === 'win32' ? 'python' : 'python3') } = {}) {
    this.store = store
    this.assetsDir = path.resolve(assetsDir)
    this.cacheDir = path.resolve(dataDir, 'sony-pcm-cache')
    this.python = python
    this.x86Dll=process.env.SONY_WALKMAN_X86_DLL??(process.platform==='win32'&&existsSync(path.join(PROJECT,'vendor/sony-walkman-x86/sony-dsp-x86.dll'))?path.join(PROJECT,'vendor/sony-walkman-x86/sony-dsp-x86.dll'):undefined)
    this.jobs = new Map()
    this.queue = []
    this.running = false
    this.closed = false
  }
  async environment() {
    const env = { ...process.env, SONY_WALKMAN_ASSETS: this.assetsDir, PYTHONUNBUFFERED: '1', PYTHONIOENCODING:'utf-8' }
    if(this.x86Dll)env.SONY_WALKMAN_X86_DLL=this.x86Dll
    const nativeDecoder=path.join(PROJECT,'vendor/audio/windows-x64/rhine-audio-host.exe')
    if(process.platform==='win32'&&!env.SONY_WALKMAN_NATIVE_DECODER&&existsSync(nativeDecoder))env.SONY_WALKMAN_NATIVE_DECODER=nativeDecoder
    // Optional development installation stays ignored; production uses its Python environment.
    const localPython = path.join(PROJECT, '.tools/walkman/python')
    if (await fs.stat(localPython).then((s) => s.isDirectory()).catch(() => false)) {
      env.PYTHONPATH = [env.PYTHONPATH, localPython].filter(Boolean).join(path.delimiter)
    }
    return env
  }
  terminate(child) {
    if (child?.termination) return child.termination
    if (!child?.pid || child.exitCode !== null || child.killed) return
    if (process.platform === 'win32') {
      // Only the process tree created by this service, including its decoder/workers.
      const terminator = spawn('taskkill.exe',['/PID',String(child.pid),'/T','/F'],{ shell:false,windowsHide:true,stdio:'ignore' })
      child.termination = new Promise((resolve)=>{
        terminator.once('error',()=>{ child.kill(); resolve() })
        terminator.once('close',resolve)
      })
    } else {
      try { process.kill(-child.pid,'SIGTERM') } catch { child.kill() }
    }
    return child.termination
  }
  async run(args, onValue, timeout = 30_000, job) {
    const env = await this.environment()
    if (this.closed) throw fail('本地服务正在关闭',503)
    const bootstrap="import sys,runpy;sys.path[:0]=sys.argv[1:3];sys.argv=sys.argv[3:];runpy.run_path(sys.argv[0],run_name='__main__')"
    const child = spawn(this.python, ['-B','-c',bootstrap,path.dirname(RUNNER),this.x86Dll?path.join(PROJECT,'.tools/desktop-runtime/unicorn'):path.dirname(RUNNER),RUNNER, ...args], { env, shell: false, windowsHide: true, detached:process.platform !== 'win32', stdio: ['ignore', 'pipe', 'pipe'] })
    this.child = child
    if (job?.cancelled) this.terminate(child)
    let text = '', last
    const decoder=new StringDecoder('utf8')
    const timer = setTimeout(() => this.terminate(child), timeout)
    try {
      await new Promise((resolve, reject) => {
        child.once('error', reject)
        child.stdout.on('data', (chunk) => {
          text += decoder.write(chunk)
          if (text.length > 65536) { this.terminate(child); return reject(fail('Sony 处理响应过大')) }
          let end
          while ((end = text.indexOf('\n')) !== -1) {
            const line = text.slice(0, end); text = text.slice(end + 1)
            try { last = JSON.parse(line); onValue?.(last) } catch { /* Diagnostic text is not an audio result. */ }
          }
        })
        child.stderr.resume()
        child.once('close', (code) => code === 0 ? resolve() : reject(fail(last?.error ?? (code === null ? 'Sony 处理已中止或超时。' : 'Sony 音频组件未返回有效结果，请检查组件校验与原生解码器状态。'), 503)))
      })
      if (last?.state === 'error' || !(last?.ready || last?.state === 'ready')) throw fail('Sony 原版处理未产生有效结果', 503)
      return last
    } finally { clearTimeout(timer); await child.termination; if (this.child === child) this.child = undefined }
  }
  async removeIncomplete(job) {
    for (const suffix of ['.partial','.partial.decoded']) {
      for (let attempt=0; ; attempt++) {
        try { await fs.rm(`${job.output}${suffix}`,{ force:true }); break }
        catch (error) {
          if (!['EBUSY','EPERM','EACCES'].includes(error.code) || attempt>=20) throw error
          await new Promise((resolve)=>setTimeout(resolve,100))
        }
      }
    }
  }
  async status() {
    if (!this.statusTask) this.statusTask = (async () => {
      try {
        for (const [name, expected] of Object.entries(manifest.files)) {
          const bytes = await fs.readFile(path.join(this.assetsDir, name))
          if (createHash('sha256').update(bytes).digest('hex') !== expected) throw fail(`Sony 原版文件校验失败：${name}`, 503)
        }
        const probe = await this.run(['--probe'], undefined, 30_000)
        return { available: true, original: true, backend:probe.backend, revision: manifest.revision, dseeVersion: '3.0.7', dcVersion: '1.0.0', vinylVersion: '1.0.0', sampleRates: SONY_SAMPLE_RATES, selfCheck: probe.ready, phaseStereoIsolation:probe.phaseStereoIsolation===true, workers: Math.min(3,availableParallelism()), parallel: true }
      } catch (error) {
        return { available: false, original: false, error: error.code === 'ENOENT' ? '尚未加载 Sony 原版音频组件。' : error.message }
      }
    })()
    return this.statusTask
  }
  view(job) {
    const offset=job.result?.positionOffset??job.stream?.positionOffset??0;
    return { id: job.id, state: job.state, progress: job.progress, settings: job.settings, ...job.plan, workers: job.workers ?? job.result?.workers,
      ...(job.stream?{positionOffset:offset,bufferedSeconds:Math.max(0,(job.producedBytes-56)/(job.stream.sampleRate*8))||0}:{}),
      ...(job.state === 'processing' && this.playable(job) ? { playable: true, streaming: true, audioUrl: `/api/sony/audio/${job.id}`, sampleRate: job.stream.sampleRate, duration: job.stream.duration+offset } : {}),
      ...(job.error ? { error: job.error } : {}),
      ...(job.state === 'ready' ? { audioUrl: `/api/sony/audio/${job.id}`, sampleRate: job.result.sampleRate,
        duration: job.result.duration+offset, positionOffset:offset, pcmSha256: job.result.pcmSha256, peak: job.result.peak } : {}) }
  }
  async prepare(trackId, value, { streaming = true, parallel = true, dsdToPcm = false, startPosition = 0 } = {}) {
    if (typeof streaming !== 'boolean' || typeof parallel !== 'boolean' || typeof dsdToPcm !== 'boolean') throw fail('无效的 Sony 运行设置')
    if (this.closed) throw fail('本地服务正在关闭', 503)
    if(!Number.isFinite(startPosition)||startPosition<0||startPosition>3600)throw fail('无效的 Sony 起播位置')
    const requestedSettings = sonySettings(value)
    if (typeof trackId !== 'string' || !/^[a-zA-Z0-9-]+$/.test(trackId)) throw fail('无效的曲目 ID')
    const descriptor = this.store.trackFile(trackId)
    if (!descriptor) throw fail('本地曲库中没有此音乐；Sony 处理目前用于本地曲目。', 404)
    const { source, signature } = await boundedSource(descriptor)
    const format=dsdToPcm?{sampleRate:44100,numberOfChannels:2}:(await readAudioMetadata(source,{skipCovers:true})).format
    const plan=sonyPlaybackPlan(requestedSettings,format),settings=plan.effectiveSettings
    if (!settings.dsee && !settings.dc && !settings.vinyl && !dsdToPcm) return { state: 'ready', progress: 1, settings, ...plan, bypassedAll:true,positionOffset:0,sampleRate:format.sampleRate,audioUrl: `${trackId.startsWith('ftp-') ? '/api/ftp/audio/' : '/api/audio/'}${trackId}` }
    const status = await this.status()
    if (!status.available) throw fail(status.error, 503)
    const position=Math.floor(startPosition*1000)/1000;
    const id = createHash('sha256').update(JSON.stringify([signature, manifest.revision, requestedSettings, 'rate-policy-v1', ...(dsdToPcm ? ['dsd-pcm-44100'] : []), ...(process.env.SONY_WALKMAN_NATIVE_DECODER ? ['bass-native-pcm-stream-v2'] : []),...(position?[position]:[])])).digest('hex')
    if (this.jobs.has(id) && this.jobs.get(id).state !== 'error') { const existing = this.jobs.get(id); if (streaming) existing.streaming = true; return this.view(existing) }
    // A replaced, unread task must not hold the latest effect change behind a
    // whole old song. Active readers keep ownership until their output stops.
    for(const old of this.jobs.values())if(old.id!==id&&!old.readers&&['queued','processing'].includes(old.state))this.cancel(old.id)
    if (this.queue.length >= 8) throw fail('Sony 处理队列已满，请稍后重试。', 429)
    await fs.mkdir(this.cacheDir, { recursive: true })
    const output = path.join(this.cacheDir, `${id}.wav`)
    const job = { id, trackId, signature, source, output, settings, plan, streaming, parallel, dsdToPcm, startPosition:position, state: 'queued', progress: 0 }
    try {
      const result = JSON.parse(await fs.readFile(`${output}.json`, 'utf8'))
      const stat = await fs.stat(output)
      if (result.state === 'ready' && result.frames*8 + 56 === stat.size) Object.assign(job, { state: 'ready', progress: 1, result })
    } catch {}
    // Limit retained job metadata; completed cache files can be discovered again.
    if (this.jobs.size >= 64) for (const [key, old] of this.jobs) { if (['ready', 'error'].includes(old.state)) { this.jobs.delete(key); break } }
    // Simultaneous clients may both await the cached result. Commit only one job.
    if (this.jobs.has(id) && this.jobs.get(id).state !== 'error') return this.view(this.jobs.get(id))
    this.jobs.set(id, job)
    if (job.state !== 'ready') { this.queue.push(job); void this.drain() }
    return this.view(job)
  }
  async drain() {
    if (this.running || this.closed) return
    this.running = true
    try {
      while (this.queue.length && !this.closed) {
        const job = this.queue.shift()
        if (job.cancelled) continue
        this.activeJob = job
        try {
          const current = this.store.trackFile(job.trackId)
          if (!current || (await boundedSource(current)).signature !== job.signature) throw fail('音乐文件或曲库目录已变化，请重新选择。')
          const cacheBytes = await this.prune()
          if (cacheBytes > 2_000_000_000) throw fail('Sony 音效缓存已满，请重启本地服务后重试。')
          const capacity = await fs.statfs(this.cacheDir)
          if (capacity.bavail * capacity.bsize < 64_000_000) throw fail('本机空间不足，无法准备 Sony 音效缓存。')
          if (job.cancelled) throw fail('Sony 处理请求已取消。')
          job.state = 'processing'
          // Only remove our fixed, incomplete file. No recursive removal or source writes.
          await this.removeIncomplete(job)
          const result = await this.run(['--input', job.source, '--output', `${job.output}.partial`,
            '--dsee', String(Number(job.settings.dsee)), '--dc', String(job.settings.dc), '--vinyl', String(job.settings.vinyl),
            '--workers', String(job.parallel ? Math.min(3,availableParallelism()) : 1), '--progressive', '--start-position',String(job.startPosition), ...(job.dsdToPcm ? ['--dsd-pcm'] : [])],
            (value) => {
              if (value.state === 'processing') {
                job.progress = Math.max(0, Math.min(.99, Number(value.progress) || 0))
                if (value.totalBytes) job.stream = { sampleRate: value.sampleRate, duration: value.duration, totalBytes: value.totalBytes,positionOffset:value.positionOffset??0 }
                if (value.producedBytes) {
                  const now = Date.now()
                  if (job.sample && job.stream && now-job.sample.time > 100 && value.producedBytes > job.sample.bytes) {
                    const speed = (value.producedBytes-job.sample.bytes)/(job.stream.sampleRate*8)/((now-job.sample.time)/1000)
                    job.renderSpeed = job.renderSpeed ? job.renderSpeed*.5+speed*.5 : speed
                  }
                  job.sample = { time: now, bytes: value.producedBytes }
                  job.producedBytes = value.producedBytes
                }
                if (value.workers) job.workers = value.workers
              }
            }, 7_200_000,job)
          if (job.cancelled) throw fail('Sony 处理请求已取消。')
          if ((await boundedSource(this.store.trackFile(job.trackId) ?? {})).signature !== job.signature) throw fail('音乐文件在处理期间发生变化，请重新选择。')
          await fs.rename(`${job.output}.partial`, job.output)
          await fs.writeFile(`${job.output}.json`, JSON.stringify(result))
          Object.assign(job, { result, state: 'ready', progress: 1 })
        } catch (error) {
          job.state = 'error'; job.error = job.cancelled ? 'Sony 处理请求已取消。' : error.message
          await this.removeIncomplete(job).catch(()=>{ job.error += '（临时缓存尚未能清除，请重启服务后清理。）' })
        } finally { if (this.activeJob === job) this.activeJob = undefined }
      }
    } finally { this.running = false }
  }
  async prune() {
    const entries = []
    for (const name of await fs.readdir(this.cacheDir)) {
      if (!/^[a-f0-9]{64}\.wav$/.test(name)) continue
      const stat = await fs.stat(path.join(this.cacheDir, name))
      entries.push({ name, size: stat.size, time: stat.mtimeMs })
    }
    let size = entries.reduce((sum, item) => sum + item.size, 0)
    for (const entry of entries.sort((a,b) => a.time-b.time)) {
      if (size <= 2_000_000_000) break
      const id = entry.name.slice(0,64)
      // Keep files known to this running session so media Range requests remain valid.
      if (this.jobs.has(id)) continue
      await fs.rm(path.join(this.cacheDir, entry.name), { force: true })
      await fs.rm(path.join(this.cacheDir, `${entry.name}.json`), { force: true })
      size -= entry.size
    }
    return size
  }
  job(id) { const job = this.jobs.get(id); if (!job) throw fail('Sony 处理任务不存在', 404); return this.view(job) }
  cancel(id) {
    const job = this.jobs.get(id)
    if (!job) throw fail('Sony 处理任务不存在',404)
    if (['queued','processing'].includes(job.state) && !job.readers) {
      job.cancelled = true; job.state = 'error'; job.error = 'Sony 处理请求已取消。'
      this.queue = this.queue.filter((item)=>item !== job)
      if (this.activeJob === job) this.terminate(this.child)
    }
    return this.view(job)
  }
  async clearCache() {
    if (this.running || this.queue.length || [...this.jobs.values()].some((job)=>job.readers)) throw fail('Sony 音效仍在处理或读取，请完成后再清理缓存。',409)
    const names = await fs.readdir(this.cacheDir).catch((error)=>{ if (error.code === 'ENOENT') return []; throw error })
    for (const name of names) if (/^[a-f0-9]{64}\.wav(?:\.json|\.partial(?:\.decoded)?)?$/.test(name)) await fs.rm(path.join(this.cacheDir,name),{ force:true })
    this.jobs.clear()
    return { cleared:true }
  }
  async audio(id) {
    const job = this.jobs.get(id)
    if (!job || job.state !== 'ready') throw fail('Sony 处理尚未完成', 404)
    const descriptor = this.store.trackFile(job.trackId)
    if (!descriptor || (await boundedSource(descriptor)).signature !== job.signature) throw fail('原曲已移出曲库或发生变化', 403)
    return { path: job.output, allowedRoot: this.cacheDir, mime: 'audio/wav' }
  }
  async growingAudio(id) {
    const job = this.jobs.get(id)
    if (!job || job.state !== 'processing' || !this.playable(job)) throw fail('Sony 音效正在缓冲，请稍后重试。',409)
    const descriptor = this.store.trackFile(job.trackId)
    if (!descriptor || (await boundedSource(descriptor)).signature !== job.signature) throw fail('原曲已移出曲库或发生变化',403)
    return job
  }
  playable(job) {
    if (!job.streaming || !job.stream) return false
    const {duration,sampleRate} = job.stream
    // Live startup is bounded and independent of the remaining track length.
    // The native output reports a real underrun if the CPU cannot keep up; it
    // never silently bypasses Sony or waits for minutes of predicted deficit.
    const buffered = Math.min(duration,.5)
    return job.producedBytes-56 >= buffered*sampleRate*8
  }
  close() { this.closed = true; this.terminate(this.child); this.queue.length = 0 }
}
