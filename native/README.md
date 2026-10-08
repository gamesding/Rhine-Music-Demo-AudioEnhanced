# Native audio and Sony translation research

`audio-host.cpp` is the Windows C++ audio service. It decodes music through the
pinned original BASS components and outputs through WASAPI or the selected ASIO
driver. The DSF virtual view preserves the DSD samples while presenting DSDIFF
framing to the decoder; it avoids the tested end-block loss in BASSDSD 2.4.2.
DSF ID3 tags remain in the original file and are read by the library metadata
parser. Native DSD and DoP bypass all PCM effects and digital volume changes.

Build with `npm run build:native`, then run `npm run check:native`. The executable
and its source hash are recorded in `vendor/audio/windows-x64/assets.json`.
Changing the source without rebuilding causes desktop packaging to fail.

`sony-crelu-reference.cpp` is the limited ARM CReLU kernel translation proof.
It is Sony-derived private research, subject to the Sony component restrictions
in `NOTICE.md`; it is not used by the player or a translation of the entire
DSEE AI system. Its recorded 36 cases / 8,912 values compare bit for bit with
the original kernel, including special floating-point values. The complete
evidence is in `docs/SONY-CRELU-VERIFICATION.json` and the firmware research copy.
The complete supported Sony effect chain now runs the generated x86-64 C++
instruction translation in `sony/`. Original model, coefficients and parameters
remain pinned. See [Sony C++ source and validation](sony/README.md) and
`docs/SONY-WALKMAN.md`; the CReLU file above remains an earlier isolated proof.
