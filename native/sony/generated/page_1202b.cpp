// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1202b(ArmState& c){
switch(c.r[15]){
case 0x1202b6a0u:goto L1202b6a0;
case 0x1202b6a4u:goto L1202b6a4;
case 0x1202b6a8u:goto L1202b6a8;
default:throw std::runtime_error("Untranslated instruction");}
L1202b6a0:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202b6a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202b6a8u,0x0u,0u,false);}
goto L1202b6a4;
}
L1202b6a4:{ // 45ca8ce2 add ip, ip, #0x45000
c.r[15]=0x1202b6a4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x45000u,0u,false);}
goto L1202b6a8;
}
L1202b6a8:{ // ccfcbce5 ldr pc, [ip, #0xccc]!
c.r[15]=0x1202b6a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcccu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1202b6acu;return c.r[15];
}
}
