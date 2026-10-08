// AArch32 instruction semantics used by the source-to-source Sony DSP lift.
// Generated blocks contain native C++ statements; this file never decodes opcodes.
// Retain integer/FP bit patterns and 32-bit guest pointers for the original ABI.
#pragma once
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <immintrin.h>
using u32=std::uint32_t; using u64=std::uint64_t; using i32=std::int32_t; using i64=std::int64_t;
struct ArmState {
 u32 r[16]{};u32 v[64]{};u32 cpsr=0x400001d3,fpscr=0,it=0,tls=0;u64 steps=0,limit=0;
 unsigned char* maps[256]{};u32 mapSizes[256]{};
 unsigned char* ptr(u32 a,u32 n){unsigned page=a>>24,offset=a&0xffffff;if(!maps[page]||u64(offset)+n>mapSizes[page])throw std::runtime_error("Unmapped ARM memory");return maps[page]+offset;}
 template<class T>T load(u32 a){T x;std::memcpy(&x,ptr(a,sizeof(T)),sizeof(T));return x;}
 template<class T>void store(u32 a,T x){std::memcpy(ptr(a,sizeof(T)),&x,sizeof(T));}
};
inline u32 nativeFpFlags(){u32 x=_mm_getcsr();return (x&1)|((x&4)>>1)|((x&8)>>1)|((x&16)>>1)|((x&32)>>1)|((x&2)<<6);}
inline void setNativeFp(const ArmState& c){unsigned r=(c.fpscr>>22)&3;unsigned rounding=r==1?2:r==2?1:r;u32 f=c.fpscr;_mm_setcsr(0x1f80|(rounding<<13)|(f&1)|((f&2)<<1)|((f&4)<<1)|((f&8)<<1)|((f&16)<<1)|((f&128)>>6)|((f&(1u<<24))?0x8040:0));}
inline bool condition(const ArmState& c,unsigned k){bool n=c.cpsr>>31,z=(c.cpsr>>30)&1,a=(c.cpsr>>29)&1,v=(c.cpsr>>28)&1;switch(k){case 0:return z;case 1:return !z;case 2:return a;case 3:return !a;case 4:return n;case 5:return !n;case 6:return v;case 7:return !v;case 8:return a&&!z;case 9:return !a||z;case 10:return n==v;case 11:return n!=v;case 12:return !z&&n==v;case 13:return z||n!=v;default:return true;}}
inline void nz(ArmState& c,u32 x){c.cpsr=(c.cpsr&0x3fffffff)|(x&0x80000000)|(x==0?0x40000000:0);}
inline u32 sum(ArmState& c,u32 a,u32 b,u32 carry,bool flags){u64 x=u64(a)+b+carry;u32 r=u32(x);if(flags){nz(c,r);c.cpsr=(c.cpsr&0xcfffffff)|((x>>32)?0x20000000:0)|((~(a^b)&(a^r)&0x80000000)>>3);}return r;}
inline u32 rotate(u32 x,unsigned n){n&=31;return n?(x>>n)|(x<<(32-n)):x;}
inline u32 vectorShift(u32 x,u32 amount){int n=std::int8_t(amount);return n>=32||n<=-32?0:n<0?x>>(-n):x<<n;}
inline u32 shift(ArmState& c,u32 x,unsigned n,unsigned kind,bool flags){u32 value=x;unsigned carry=(c.cpsr>>29)&1;if(kind==5){value=(carry<<31)|(x>>1);carry=x&1;}else if(n){switch(kind){case 2:carry=n<=32?(x>>(32-n))&1:0;value=n<32?x<<n:0;break;case 3:carry=n<=32?(x>>(n-1))&1:0;value=n<32?x>>n:0;break;case 1:carry=n<32?(x>>(n-1))&1:x>>31;value=n<32?u32(i32(x)>>n):(i32(x)<0?0xffffffff:0);break;case 4:value=rotate(x,n);carry=value>>31;break;default:throw std::runtime_error("Unsupported ARM shift");}}if(flags)c.cpsr=(c.cpsr&~0x20000000)|(carry<<29);return value;}
template<class T,class U>T fromBits(U x){T r;std::memcpy(&r,&x,sizeof(T));return r;}
template<class U,class T>U toBits(T x){U r;std::memcpy(&r,&x,sizeof(T));return r;}
template<class T>struct FpTraits;
template<>struct FpTraits<float>{using U=u32;static constexpr U sign=0x80000000,abs=0x7fffffff,inf=0x7f800000,quiet=0x00400000,nan=0x7fc00000,min=0x00800000;};
template<>struct FpTraits<double>{using U=u64;static constexpr U sign=0x8000000000000000ull,abs=0x7fffffffffffffffull,inf=0x7ff0000000000000ull,quiet=0x0008000000000000ull,nan=0x7ff8000000000000ull,min=0x0010000000000000ull;};
template<class T>inline typename FpTraits<T>::U fpInput(typename FpTraits<T>::U x,bool neon){using F=FpTraits<T>;return neon&&(x&F::abs)<F::min?x&F::sign:x;}
template<class T>inline typename FpTraits<T>::U fpResult(T value,bool neon){using F=FpTraits<T>;auto x=toBits<typename F::U>(value);if((x&F::abs)>F::inf)return F::nan;return fpInput<T>(x,neon);}
template<class T>inline typename FpTraits<T>::U fpNan(typename FpTraits<T>::U a,typename FpTraits<T>::U b,bool neon){using F=FpTraits<T>;if(neon)return F::nan;if((a&F::abs)>F::inf&&!(a&F::quiet))return a|F::quiet;if((b&F::abs)>F::inf&&!(b&F::quiet))return b|F::quiet;return ((a&F::abs)>F::inf?a:b)|F::quiet;}
// VFP arithmetic uses FPSCR defaults; Advanced SIMD always uses default NaN/FZ.
template<class T>inline typename FpTraits<T>::U fpBinary(typename FpTraits<T>::U a,typename FpTraits<T>::U b,int op,bool neon){using F=FpTraits<T>;a=fpInput<T>(a,neon);b=fpInput<T>(b,neon);if((a&F::abs)>F::inf||(b&F::abs)>F::inf)return fpNan<T>(a,b,neon);T x=fromBits<T>(a),y=fromBits<T>(b),r;switch(op){case 0:r=x+y;break;case 1:r=x-y;break;case 2:r=x*y;break;case 3:r=x/y;break;case 4:if(x==y)return a&b;r=x>y?x:y;break;case 5:if(x==y)return a|b;r=x<y?x:y;break;default:throw std::runtime_error("Unsupported ARM FP operation");}return fpResult<T>(r,neon);}
template<class T>inline typename FpTraits<T>::U fpFma(typename FpTraits<T>::U a,typename FpTraits<T>::U b,typename FpTraits<T>::U acc){using F=FpTraits<T>;if((a&F::abs)>F::inf||(b&F::abs)>F::inf)return fpNan<T>(a,b,false);if((acc&F::abs)>F::inf)return acc|F::quiet;return fpResult<T>(std::fma(fromBits<T>(a),fromBits<T>(b),fromBits<T>(acc)),false);}
template<class T>inline u32 fpToInt(typename FpTraits<T>::U bits,bool sign,unsigned fractional,bool neon){T x=fromBits<T>(fpInput<T>(bits,neon));if(std::isnan(x))return 0;double d=std::ldexp(double(x),fractional);if(sign){if(d>=2147483647.0)return 0x7fffffff;if(d<=-2147483648.0)return 0x80000000;return u32(i32(d));}if(d<=0)return 0;if(d>=4294967295.0)return 0xffffffff;return u32(d);}
template<class T>inline typename FpTraits<T>::U intToFp(u32 bits,bool sign,unsigned fractional,bool neon){T x=sign?T(i32(bits)):T(bits);return fpResult<T>(std::ldexp(x,-int(fractional)),neon);}
template<class T>inline void fpCompare(ArmState& c,typename FpTraits<T>::U a,typename FpTraits<T>::U b){T x=fromBits<T>(a),y=fromBits<T>(b);u32 f=std::isnan(x)||std::isnan(y)?0x30000000:x==y?0x60000000:x<y?0x80000000:0x20000000;c.fpscr=(c.fpscr&0x0fffffff)|f;}
