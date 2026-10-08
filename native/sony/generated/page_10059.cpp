// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10059(ArmState& c){
switch(c.r[15]){
case 0x10059164u:goto L10059164;
case 0x10059168u:goto L10059168;
case 0x1005916cu:goto L1005916c;
case 0x100591b8u:goto L100591b8;
case 0x100591bcu:goto L100591bc;
case 0x100591c0u:goto L100591c0;
case 0x100591d0u:goto L100591d0;
case 0x100591d4u:goto L100591d4;
case 0x100591d8u:goto L100591d8;
default:throw std::runtime_error("Untranslated instruction");}
L10059164:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x10059164u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005916cu,0x200000u,0u,false);}
goto L10059168;
}
L10059168:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x10059168u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L1005916c;
}
L1005916c:{ // 2cfbbce5 ldr pc, [ip, #0xb2c]!
c.r[15]=0x1005916cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xb2cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x10059170u;return c.r[15];
}
L100591b8:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x100591b8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x100591c0u,0x200000u,0u,false);}
goto L100591bc;
}
L100591bc:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x100591bcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L100591c0;
}
L100591c0:{ // f4fabce5 ldr pc, [ip, #0xaf4]!
c.r[15]=0x100591c0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xaf4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x100591c4u;return c.r[15];
}
L100591d0:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x100591d0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x100591d8u,0x200000u,0u,false);}
goto L100591d4;
}
L100591d4:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x100591d4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L100591d8;
}
L100591d8:{ // e4fabce5 ldr pc, [ip, #0xae4]!
c.r[15]=0x100591d8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xae4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x100591dcu;return c.r[15];
}
}
