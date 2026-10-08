// Research translation of Sony DMP-Z1 DSX 3.0.7 ARM instructions at 0x184c3c.
// This is not recovered Sony source. Not used in the player until full-chain validation.
// vneg.f32 and vmax.f32 (Advanced SIMD): default NaN and flush-to-zero semantics.
using u32 = unsigned int;
static u32 vmax_zero(u32 bits) {
    const u32 absolute = bits & 0x7fffffffu;
    if (absolute > 0x7f800000u) return 0x7fc00000u;
    if (absolute < 0x00800000u || (bits & 0x80000000u)) return 0;
    return bits;
}
#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif
extern "C" EXPORT void sony_crelu_translated(u32* output, const u32* input, int width, int rows) {
    // Each original row emits width positives followed by width negated positives.
    for (int row = 0; row < rows; ++row) {
        for (int x = 0; x < width; ++x) {
            const u32 bits = input[row*width+x];
            output[row*width*2+x] = vmax_zero(bits);
            output[row*width*2+width+x] = vmax_zero(bits ^ 0x80000000u);
        }
    }
}
