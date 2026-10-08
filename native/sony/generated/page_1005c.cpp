// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1005c(ArmState& c){
switch(c.r[15]){
case 0x1005ce00u:goto L1005ce00;
case 0x1005ce04u:goto L1005ce04;
case 0x1005ce08u:goto L1005ce08;
case 0x1005cf2cu:goto L1005cf2c;
case 0x1005cf30u:goto L1005cf30;
case 0x1005cf34u:goto L1005cf34;
case 0x1005cf38u:goto L1005cf38;
case 0x1005cf3cu:goto L1005cf3c;
case 0x1005cf40u:goto L1005cf40;
default:throw std::runtime_error("Untranslated instruction");}
L1005ce00:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ce00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ce08u,0x200000u,0u,false);}
goto L1005ce04;
}
L1005ce04:{ // 5eca8ce2 add ip, ip, #0x5e000
c.r[15]=0x1005ce04u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5e000u,0u,false);}
goto L1005ce08;
}
L1005ce08:{ // c4f2bce5 ldr pc, [ip, #0x2c4]!
c.r[15]=0x1005ce08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x2c4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005ce0cu;return c.r[15];
}
L1005cf2c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005cf2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005cf34u,0x200000u,0u,false);}
goto L1005cf30;
}
L1005cf30:{ // 5eca8ce2 add ip, ip, #0x5e000
c.r[15]=0x1005cf30u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5e000u,0u,false);}
goto L1005cf34;
}
L1005cf34:{ // fcf1bce5 ldr pc, [ip, #0x1fc]!
c.r[15]=0x1005cf34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x1fcu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005cf38;
}
L1005cf38:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005cf38u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005cf40u,0x200000u,0u,false);}
goto L1005cf3c;
}
L1005cf3c:{ // 5eca8ce2 add ip, ip, #0x5e000
c.r[15]=0x1005cf3cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5e000u,0u,false);}
goto L1005cf40;
}
L1005cf40:{ // f4f1bce5 ldr pc, [ip, #0x1f4]!
c.r[15]=0x1005cf40u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x1f4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005cf44u;return c.r[15];
}
}
