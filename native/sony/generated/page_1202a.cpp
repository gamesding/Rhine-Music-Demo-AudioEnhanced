// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1202a(ArmState& c){
switch(c.r[15]){
case 0x1202ae6cu:goto L1202ae6c;
case 0x1202ae70u:goto L1202ae70;
case 0x1202ae74u:goto L1202ae74;
case 0x1202aeccu:goto L1202aecc;
case 0x1202aed0u:goto L1202aed0;
case 0x1202aed4u:goto L1202aed4;
case 0x1202adb8u:goto L1202adb8;
case 0x1202adbcu:goto L1202adbc;
case 0x1202adc0u:goto L1202adc0;
case 0x1202aed8u:goto L1202aed8;
case 0x1202aedcu:goto L1202aedc;
case 0x1202aee0u:goto L1202aee0;
case 0x1202add0u:goto L1202add0;
case 0x1202add4u:goto L1202add4;
case 0x1202add8u:goto L1202add8;
default:throw std::runtime_error("Untranslated instruction");}
L1202adb8:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202adb8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202adc0u,0x0u,0u,false);}
goto L1202adbc;
}
L1202adbc:{ // 46ca8ce2 add ip, ip, #0x46000
c.r[15]=0x1202adbcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x46000u,0u,false);}
goto L1202adc0;
}
L1202adc0:{ // bcf2bce5 ldr pc, [ip, #0x2bc]!
c.r[15]=0x1202adc0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x2bcu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1202adc4u;return c.r[15];
}
L1202add0:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202add0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202add8u,0x0u,0u,false);}
goto L1202add4;
}
L1202add4:{ // 46ca8ce2 add ip, ip, #0x46000
c.r[15]=0x1202add4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x46000u,0u,false);}
goto L1202add8;
}
L1202add8:{ // acf2bce5 ldr pc, [ip, #0x2ac]!
c.r[15]=0x1202add8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x2acu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1202addcu;return c.r[15];
}
L1202ae6c:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202ae6cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202ae74u,0x0u,0u,false);}
goto L1202ae70;
}
L1202ae70:{ // 46ca8ce2 add ip, ip, #0x46000
c.r[15]=0x1202ae70u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x46000u,0u,false);}
goto L1202ae74;
}
L1202ae74:{ // 44f2bce5 ldr pc, [ip, #0x244]!
c.r[15]=0x1202ae74u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x244u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1202ae78u;return c.r[15];
}
L1202aecc:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202aeccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202aed4u,0x0u,0u,false);}
goto L1202aed0;
}
L1202aed0:{ // 46ca8ce2 add ip, ip, #0x46000
c.r[15]=0x1202aed0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x46000u,0u,false);}
goto L1202aed4;
}
L1202aed4:{ // 04f2bce5 ldr pc, [ip, #0x204]!
c.r[15]=0x1202aed4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x204u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1202aed8;
}
L1202aed8:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x1202aed8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1202aee0u,0x0u,0u,false);}
goto L1202aedc;
}
L1202aedc:{ // 46ca8ce2 add ip, ip, #0x46000
c.r[15]=0x1202aedcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x46000u,0u,false);}
goto L1202aee0;
}
L1202aee0:{ // fcf1bce5 ldr pc, [ip, #0x1fc]!
c.r[15]=0x1202aee0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x1fcu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1202aee4u;return c.r[15];
}
}
