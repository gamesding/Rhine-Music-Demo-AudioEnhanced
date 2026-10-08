// Research ABI host for generated x86-64 C++ Sony instruction blocks.
#include "arm-state.hpp"
#include <string>
#define API extern "C" __declspec(dllexport)
u32 dispatch(ArmState&);
static thread_local std::string lastError;
API ArmState* sony_create(){return new ArmState;}
API void sony_destroy(ArmState* c){if(c){for(auto p:c->maps)std::free(p);delete c;}}
API int sony_map(ArmState* c,u32 address,u32 bytes){if(address&0xffffff)return 0;for(u32 offset=0;offset<bytes;offset+=0x1000000){u32 page=(address+offset)>>24,size=bytes-offset;if(size>0x1000000)size=0x1000000;if(c->maps[page])return 0;c->maps[page]=static_cast<unsigned char*>(std::calloc(size,1));c->mapSizes[page]=size;if(!c->maps[page])return 0;}return 1;}
API void* sony_memory(ArmState* c,u32 address,u32 bytes){try{return c->ptr(address,bytes);}catch(...){return nullptr;}}
API u64 sony_get(ArmState* c,u32 index){if(index<16)return c->r[index];if(index==16)return c->cpsr;if(index==17)return c->fpscr;if(index==18)return c->tls;if(index==19)return c->steps;if(index>=64&&index<128)return c->v[index-64];if(index>=128&&index<160)return u64(c->v[(index-128)*2])|(u64(c->v[(index-128)*2+1])<<32);return 0;}
API void sony_set(ArmState* c,u32 index,u64 value){if(index<16)c->r[index]=u32(value);else if(index==16)c->cpsr=u32(value);else if(index==17)c->fpscr=u32(value);else if(index==18)c->tls=u32(value);else if(index>=64&&index<128)c->v[index-64]=u32(value);else if(index>=128&&index<160){c->v[(index-128)*2]=u32(value);c->v[(index-128)*2+1]=u32(value>>32);}}
API const char* sony_error(){return lastError.c_str();}
API int sony_execute(ArmState* c,u32 entry,u32 stop,u64 limit,int reset){
 const unsigned mxcsr=_mm_getcsr();setNativeFp(*c);
 c->r[15]=entry&~1u;if(reset){c->steps=0;c->it=0;}c->limit=limit;
 try{while(c->r[15]!=stop){if((c->r[15]&0xff000000)==0x40000000){c->fpscr|=nativeFpFlags();_mm_setcsr(mxcsr);return 1;}dispatch(*c);}c->fpscr|=nativeFpFlags();_mm_setcsr(mxcsr);return 0;}
 catch(const std::exception& e){lastError=e.what();c->fpscr|=nativeFpFlags();_mm_setcsr(mxcsr);return 2;}
}
