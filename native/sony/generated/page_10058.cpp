// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10058(ArmState& c){
switch(c.r[15]){
case 0x10058f54u:goto L10058f54;
case 0x10058f58u:goto L10058f58;
case 0x10058f5cu:goto L10058f5c;
case 0x10058f60u:goto L10058f60;
case 0x10058f64u:goto L10058f64;
case 0x10058f68u:goto L10058f68;
case 0x10058f3cu:goto L10058f3c;
case 0x10058f40u:goto L10058f40;
case 0x10058f44u:goto L10058f44;
case 0x10058ff0u:goto L10058ff0;
case 0x10058ff4u:goto L10058ff4;
case 0x10058ff8u:goto L10058ff8;
default:throw std::runtime_error("Untranslated instruction");}
L10058f3c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x10058f3cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x10058f44u,0x200000u,0u,false);}
goto L10058f40;
}
L10058f40:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x10058f40u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L10058f44;
}
L10058f44:{ // 9cfcbce5 ldr pc, [ip, #0xc9c]!
c.r[15]=0x10058f44u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xc9cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x10058f48u;return c.r[15];
}
L10058f54:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x10058f54u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x10058f5cu,0x200000u,0u,false);}
goto L10058f58;
}
L10058f58:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x10058f58u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L10058f5c;
}
L10058f5c:{ // 8cfcbce5 ldr pc, [ip, #0xc8c]!
c.r[15]=0x10058f5cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xc8cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L10058f60;
}
L10058f60:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x10058f60u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x10058f68u,0x200000u,0u,false);}
goto L10058f64;
}
L10058f64:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x10058f64u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L10058f68;
}
L10058f68:{ // 84fcbce5 ldr pc, [ip, #0xc84]!
c.r[15]=0x10058f68u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xc84u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x10058f6cu;return c.r[15];
}
L10058ff0:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x10058ff0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x10058ff8u,0x200000u,0u,false);}
goto L10058ff4;
}
L10058ff4:{ // 60ca8ce2 add ip, ip, #96, #20
c.r[15]=0x10058ff4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x60000u,0u,false);}
goto L10058ff8;
}
L10058ff8:{ // 24fcbce5 ldr pc, [ip, #0xc24]!
c.r[15]=0x10058ff8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xc24u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x10058ffcu;return c.r[15];
}
}
