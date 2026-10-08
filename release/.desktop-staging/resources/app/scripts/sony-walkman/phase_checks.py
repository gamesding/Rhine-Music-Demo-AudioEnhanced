"""Regression checks using only the pinned original Sony ARM implementation."""
import array, hashlib, math
from effects import Effect, create_chain, dc_context, feed_chain, finish_chain

def words(content):
    values = array.array('I'); values.frombytes(content)
    return values

def render(content, rate, mode, chunks=None):
    chain, _ = create_chain(rate, False, mode, 0)
    if chunks is None:
        result = feed_chain(chain, content)
    else:
        parts = []; pos = 0; index = 0
        while pos < len(content):
            size = chunks[index % len(chunks)] * 8
            parts.append(feed_chain(chain, content[pos:pos+size]))
            pos += size; index += 1
        result = b''.join(parts)
    return (result + finish_chain(chain))[:len(content)]

def original_mono_reference(content, rate, mode):
    # The packet wrapper and the per-channel kernel both run the ORIGINAL
    # conversion/filter instructions. Its packet is 128 scalar values, with
    # one filter history. This reference deliberately supplies ONE mono stream
    # of 128 consecutive values; it does not claim a hardware stereo reference.
    context, _ = dc_context(rate, mode)
    original = Effect('EffectExecuteDCPhaseLinearizer', context, rate, 64)
    return (original.feed(content) + original.finish())[:len(content)]

def quick_isolation():
    impulse = bytearray(256 * 8)
    array_value = array.array('f', [.25]).tobytes()
    for channel in (0, 1):
        impulse[:] = bytes(len(impulse)); impulse[channel*4:channel*4+4] = array_value
        result = words(render(bytes(impulse), 44100, 2))
        if any(result[1-channel::2]):
            raise ValueError('Sony DC phase channel-isolation self-check failed')
    return True

def run_phase_checks():
    frames = 4096
    impulse = array.array('f', [0]) * (frames * 2); impulse[0] = .25
    left = array.array('f', (0.17*math.sin(i*.113)+.05*math.sin(i*.021) for i in range(frames)))
    right = array.array('f', (0.09*math.cos(i*.073)-.03*math.sin(i*.019) for i in range(frames)))
    for i in (0, 63, 64, 127, 128, 511, 512, 4095):
        left[i] = .32 if i % 2 else -.28
        right[i] = -.13 if i % 2 else .21
    source = words(bytes(frames * 8)); source[::2] = words(left.tobytes()); source[1::2] = words(right.tobytes())
    swapped = source[:]; swapped[::2], swapped[1::2] = source[1::2], source[::2]
    cases = []; legacy_peaks = []
    for rate in (44100, 48000, 176400, 192000):
        mode_hashes = []
        for mode in range(1, 7):
            left_only = render(impulse.tobytes(), rate, mode)
            assert not any(words(left_only)[1::2]), (rate, mode, 'left leaked into right')
            right_impulse = impulse[:]; right_impulse[0] = 0; right_impulse[1] = .25
            right_only = render(right_impulse.tobytes(), rate, mode)
            assert not any(words(right_only)[::2]), (rate, mode, 'right leaked into left')
            assert words(left_only)[::2] == words(right_only)[1::2], (rate, mode, 'asymmetric channels')
            stereo = render(source.tobytes(), rate, mode)
            result = words(stereo)
            assert result[::2].tobytes() == original_mono_reference(left.tobytes(), rate, mode), (rate, mode, 'left reference')
            assert result[1::2].tobytes() == original_mono_reference(right.tobytes(), rate, mode), (rate, mode, 'right reference')
            chunked = render(source.tobytes(), rate, mode, (1, 63, 7, 129, 64, 511, 2, 65))
            assert chunked == stereo, (rate, mode, 'state lost at chunk boundary')
            swap_result = words(render(swapped.tobytes(), rate, mode))
            assert result[::2] == swap_result[1::2] and result[1::2] == swap_result[::2], (rate, mode, 'channel swap')
            floating = array.array('f'); floating.frombytes(stereo)
            assert all(math.isfinite(value) for value in floating), (rate, mode, 'non-finite')
            assert stereo != source.tobytes(), (rate, mode, 'effect was bypassed')
            digest = hashlib.sha256(stereo).hexdigest(); mode_hashes.append(digest)
            cases.append(dict(sampleRate=rate,mode=mode,frames=frames,leftToRightPeak=0.0,rightToLeftPeak=0.0,
                              originalMonoBitExact=True,chunkStateBitExact=True,channelSwapBitExact=True,finite=True,pcmSha256=digest))
            if rate == 44100:
                context, _ = dc_context(rate, mode)
                legacy = Effect('EffectExecuteDCPhaseLinearizer', context, rate, 64)
                raw = legacy.feed(impulse.tobytes()) + legacy.finish()
                values = array.array('f'); values.frombytes(raw)
                legacy_peaks.append(max(abs(x) for x in values[1::2]))
        assert len(set(mode_hashes)) == 6, 'Sony phase presets lost their distinct responses'
        assert render(source.tobytes(), rate, 0) == source.tobytes(), 'OFF changed source bits'
    return dict(ready=True,phaseStereoIsolation=True,originalKernelUnmodified=True,configurations=len(cases),
                originalReference='pinned ARM packet wrapper processing one consecutive mono stream',
                legacyLeftToRightPeaks44100=legacy_peaks,cases=cases)
