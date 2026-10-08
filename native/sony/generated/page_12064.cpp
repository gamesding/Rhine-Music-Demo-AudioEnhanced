// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_12064(ArmState& c){
switch(c.r[15]){
case 0x12064568u:goto L12064568;
case 0x1206456cu:goto L1206456c;
case 0x12064570u:goto L12064570;
default:throw std::runtime_error("Untranslated instruction");}
L12064568:{ // 7847 bx pc
c.r[15]=0x12064568u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1206456cu)&~1u;return c.r[15];}
c.r[15]=0x1206456au;return c.r[15];
}
L1206456c:{ // 00c09fe5 ldr ip, [pc]
c.r[15]=0x1206456cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(0x12064574u+0x0u);c.r[12]=u32(c.load<u32>(address));}
goto L12064570;
}
L12064570:{ // 0ff08ce0 add pc, ip, pc
c.r[15]=0x12064570u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=sum(c,c.r[12],0x12064578u,0u,false);c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x12064574u;return c.r[15];
}
}
