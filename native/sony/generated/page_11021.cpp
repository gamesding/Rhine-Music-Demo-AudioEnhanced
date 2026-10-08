// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_11021(ArmState& c){
switch(c.r[15]){
case 0x11021e78u:goto L11021e78;
case 0x11021e7cu:goto L11021e7c;
default:throw std::runtime_error("Untranslated instruction");}
L11021e78:{ // 97ed067b vldr d7, [r7, #0x18]
c.r[15]=0x11021e78u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[7]+0x18u);c.v[14]=c.load<u32>(address+0);c.v[15]=c.load<u32>(address+4);}
goto L11021e7c;
}
L11021e7c:{ // fef72dbe b.w #0x11020ada
c.r[15]=0x11021e7cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11020adau)&~1u;return c.r[15];}
c.r[15]=0x11021e80u;return c.r[15];
}
}
