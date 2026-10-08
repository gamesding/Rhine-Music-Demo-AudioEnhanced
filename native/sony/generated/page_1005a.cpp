// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1005a(ArmState& c){
switch(c.r[15]){
case 0x1005a484u:goto L1005a484;
case 0x1005a488u:goto L1005a488;
case 0x1005a48cu:goto L1005a48c;
default:throw std::runtime_error("Untranslated instruction");}
L1005a484:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005a484u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005a48cu,0x200000u,0u,false);}
goto L1005a488;
}
L1005a488:{ // 5fca8ce2 add ip, ip, #0x5f000
c.r[15]=0x1005a488u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5f000u,0u,false);}
goto L1005a48c;
}
L1005a48c:{ // 6cfebce5 ldr pc, [ip, #0xe6c]!
c.r[15]=0x1005a48cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xe6cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005a490u;return c.r[15];
}
}
