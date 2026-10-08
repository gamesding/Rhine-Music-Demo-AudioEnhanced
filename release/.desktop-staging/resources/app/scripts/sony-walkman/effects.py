"""Run Sony's original exported effects on interleaved float PCM.

Only transport, packet layout, buffering and latency compensation live here.
All signal processing, coefficients and AI inference run in the original ARM code.
"""
import array, struct
from pathlib import Path
import arm_runtime as arm

DC_PRESETS = ((0, 0, 0), (1, 2, 2), (2, 2, 2), (3, 2, 2),
              (1, 3, 3), (2, 3, 3), (3, 3, 3))

def checked(name, *args):
    result = arm.call(name, *args)
    if result:
        raise ValueError(f'Sony {name} failed: {result:#x}')

class Effect:
    def __init__(self, name, context, rate, frames, ratio=1, delay=0):
        self.name, self.context, self.rate = name, context, rate
        self.frames, self.ratio, self.delay = frames, ratio, delay
        self.packet = arm.allocate(128)
        self.input = arm.allocate(frames * 8)
        self.output = arm.allocate(frames * 8 * ratio)
        self.pending = bytearray()
        self.drop = delay * 8

    def feed(self, content):
        self.pending.extend(content)
        block_bytes = self.frames * 8
        outputs = []
        count = len(self.pending) // block_bytes
        for pos in range(count):
            outputs.append(self.execute_block(bytes(self.pending[pos*block_bytes:(pos+1)*block_bytes])))
        del self.pending[:count * block_bytes]
        output = b''.join(outputs)
        skip = min(self.drop, len(output)); self.drop -= skip
        return output[skip:]

    def execute_block(self, content):
        # RealVinyl mutates packet fields, so reset the format every call.
        arm.write32(self.packet, self.input)
        arm.write32(self.packet + 0x28, self.output)
        arm.engine.mem_write(self.packet + 0x50, struct.pack('<HHHH', 2, 0, 4, self.frames))
        arm.engine.mem_write(self.packet + 0x5b, b'\1')
        arm.engine.mem_write(self.packet + 0x5c, struct.pack('<H', 1))
        arm.write32(self.packet + 0x60, self.rate)
        arm.engine.mem_write(self.input, content)
        checked(self.name, self.context, self.packet)
        return bytes(arm.engine.mem_read(self.output, self.frames * 8 * self.ratio))

    def finish(self):
        # Emit the partial block and enough silence to drain the original latency.
        needed = (-len(self.pending)) % (self.frames * 8)
        if self.delay:
            needed += ((self.delay + self.ratio - 1) // self.ratio + self.frames - 1) // self.frames * self.frames * 8
        return self.feed(bytes(needed))

def dc_context(rate, mode):
    ctx, work, shared, param = (arm.allocate(x) for x in (64, 96, 1024, 16))
    checked('EffectInitDCPhaseLinearizer', ctx, work, 96, shared, 1024)
    arm.engine.mem_write(param, struct.pack('<4I', rate, *DC_PRESETS[mode]))
    checked('EffectSetParamDCPhaseLinearizer', ctx, param, 16, 1)
    return ctx, work

class DCPhaseEffect(Effect):
    """Route two independent histories through the unchanged Sony mono kernel.

    The exported packet wrapper feeds 128 scalar samples through ONE history.
    Passing L,R,L,R through it therefore couples the channels. Its ARM kernel
    processes 2*r3 scalar samples; use r3=32 for each 64-sample mono block.
    Sony performs every conversion, coefficient update and filtering operation.
    Only the word-preserving channel split/join and state ownership live here.
    """
    def __init__(self, rate, mode):
        self.channels = [dc_context(rate, mode) for _ in range(2)]
        super().__init__('EffectExecuteDCPhaseLinearizer', self.channels[0][0], rate, 64)
        self.fixed = arm.allocate(self.frames * 4)

    def execute_block(self, content):
        # Unsigned words preserve the PCM bit patterns without extra FP math.
        words = array.array('I'); words.frombytes(content)
        result = array.array('I', [0]) * len(words)
        for channel, (_, work) in enumerate(self.channels):
            arm.engine.mem_write(self.input, words[channel::2].tobytes())
            arm.call('dc_phase_linearizer_Float2Fixed', self.input, self.fixed, self.frames)
            checked('dc_phase_linearizer_proc_CortexA7_ASM', work, self.fixed, self.fixed, self.frames // 2)
            arm.call('dc_phase_linearizer_Fixed2Float', self.fixed, self.output, self.frames)
            mono = array.array('I'); mono.frombytes(bytes(arm.engine.mem_read(self.output, self.frames * 4)))
            result[channel::2] = mono
        return result.tobytes()

def create_chain(rate, dsee, dc, vinyl):
    if rate not in (44100, 48000, 176400, 192000) or (dsee and rate not in (44100,48000)):
        raise ValueError('Sony bridge sample rate is unsupported')
    chain = []
    if dsee:
        obj = arm.allocate(0x50000)
        arm.engine.mem_write(obj + 0x3effc, (arm.root / 'DseeAi.bin').read_bytes())
        arm.engine.mem_write(obj + 0x3efe8, (arm.root / 'DseeAi.dcfg').read_bytes())
        checked('_ZN3pst8services5sound6mobile6DseeAi10InitEffectEv', obj)
        ctx = obj + 0x134
        param = arm.allocate(0xeaa8)
        checked('EffectGetParamDSX', ctx, param, 0xeaa8)
        arm.write32(param + 8, rate); arm.write32(param + 12, rate * 4)
        arm.write32(param + 20, rate)  # The bridge input is decoded PCM (Sony codec 16).
        checked('EffectSetParamDSX', ctx, param, 0xeaa8, 1)
        delay = arm.call('EffectGetDelaySizeDSX', ctx)
        chain.append(Effect('EffectExecuteDSX', ctx, rate, 64, 4, delay))
        rate *= 4
    if dc:
        chain.append(DCPhaseEffect(rate, dc))
    if vinyl:
        ctx, work, shared, param = (arm.allocate(x) for x in (128, 0xc340+32, 0x14010+32, 0x1048))
        arm.engine.mem_write(param, (arm.root / f'vinyl-preset-{vinyl}.bin').read_bytes())
        checked('EffectInitRealVinyl', ctx, work, 0xc340, shared, 0x14010)
        checked('EffectSetParamRealVinyl', ctx, param, 0x1048, 1)
        chain.append(Effect('EffectExecuteRealVinyl', ctx, rate, 512))
    return chain, rate

def feed_chain(chain, content):
    for effect in chain:
        content = effect.feed(content)
    return content

def finish_chain(chain):
    output = []
    for i, effect in enumerate(chain):
        content = effect.finish()
        for downstream in chain[i+1:]:
            content = downstream.feed(content)
        output.append(content)
    return b''.join(output)
