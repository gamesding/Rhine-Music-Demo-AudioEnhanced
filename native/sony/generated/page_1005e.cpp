// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1005e(ArmState& c){
switch(c.r[15]){
case 0x1005e570u:goto L1005e570;
case 0x1005e574u:goto L1005e574;
case 0x1005e578u:goto L1005e578;
case 0x1005e57cu:goto L1005e57c;
case 0x1005e580u:goto L1005e580;
case 0x1005e584u:goto L1005e584;
case 0x1005e588u:goto L1005e588;
case 0x1005e58cu:goto L1005e58c;
case 0x1005e590u:goto L1005e590;
case 0x1005e594u:goto L1005e594;
case 0x1005e598u:goto L1005e598;
case 0x1005e59cu:goto L1005e59c;
case 0x1005eb34u:goto L1005eb34;
case 0x1005eb38u:goto L1005eb38;
case 0x1005eb3cu:goto L1005eb3c;
case 0x1005ec00u:goto L1005ec00;
case 0x1005ec04u:goto L1005ec04;
case 0x1005ec08u:goto L1005ec08;
case 0x1005ec0cu:goto L1005ec0c;
case 0x1005ec10u:goto L1005ec10;
case 0x1005ec14u:goto L1005ec14;
case 0x1005ec18u:goto L1005ec18;
case 0x1005ec1cu:goto L1005ec1c;
case 0x1005ec20u:goto L1005ec20;
case 0x1005eee8u:goto L1005eee8;
case 0x1005eeecu:goto L1005eeec;
case 0x1005eef0u:goto L1005eef0;
case 0x1005eef4u:goto L1005eef4;
case 0x1005eef8u:goto L1005eef8;
case 0x1005eefcu:goto L1005eefc;
case 0x1005ef00u:goto L1005ef00;
case 0x1005ef04u:goto L1005ef04;
case 0x1005ef08u:goto L1005ef08;
case 0x1005ef18u:goto L1005ef18;
case 0x1005ef1cu:goto L1005ef1c;
case 0x1005ef20u:goto L1005ef20;
case 0x1005ef24u:goto L1005ef24;
case 0x1005ef28u:goto L1005ef28;
case 0x1005ef2cu:goto L1005ef2c;
case 0x1005e5e8u:goto L1005e5e8;
case 0x1005e5ecu:goto L1005e5ec;
case 0x1005ef0cu:goto L1005ef0c;
case 0x1005e5f0u:goto L1005e5f0;
case 0x1005ef10u:goto L1005ef10;
case 0x1005ef14u:goto L1005ef14;
case 0x1005ec48u:goto L1005ec48;
case 0x1005ec4cu:goto L1005ec4c;
case 0x1005ec50u:goto L1005ec50;
case 0x1005ec24u:goto L1005ec24;
case 0x1005ec28u:goto L1005ec28;
case 0x1005ec2cu:goto L1005ec2c;
case 0x1005ec30u:goto L1005ec30;
case 0x1005ec34u:goto L1005ec34;
case 0x1005ec38u:goto L1005ec38;
case 0x1005ec54u:goto L1005ec54;
case 0x1005ec58u:goto L1005ec58;
case 0x1005ec5cu:goto L1005ec5c;
case 0x1005ec3cu:goto L1005ec3c;
case 0x1005ec40u:goto L1005ec40;
case 0x1005ec44u:goto L1005ec44;
default:throw std::runtime_error("Untranslated instruction");}
L1005e570:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005e570u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005e578u,0x200000u,0u,false);}
goto L1005e574;
}
L1005e574:{ // 5dca8ce2 add ip, ip, #0x5d000
c.r[15]=0x1005e574u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5d000u,0u,false);}
goto L1005e578;
}
L1005e578:{ // 24f3bce5 ldr pc, [ip, #0x324]!
c.r[15]=0x1005e578u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x324u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005e57c;
}
L1005e57c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005e57cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005e584u,0x200000u,0u,false);}
goto L1005e580;
}
L1005e580:{ // 5dca8ce2 add ip, ip, #0x5d000
c.r[15]=0x1005e580u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5d000u,0u,false);}
goto L1005e584;
}
L1005e584:{ // 1cf3bce5 ldr pc, [ip, #0x31c]!
c.r[15]=0x1005e584u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x31cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005e588;
}
L1005e588:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005e588u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005e590u,0x200000u,0u,false);}
goto L1005e58c;
}
L1005e58c:{ // 5dca8ce2 add ip, ip, #0x5d000
c.r[15]=0x1005e58cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5d000u,0u,false);}
goto L1005e590;
}
L1005e590:{ // 14f3bce5 ldr pc, [ip, #0x314]!
c.r[15]=0x1005e590u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x314u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005e594;
}
L1005e594:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005e594u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005e59cu,0x200000u,0u,false);}
goto L1005e598;
}
L1005e598:{ // 5dca8ce2 add ip, ip, #0x5d000
c.r[15]=0x1005e598u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5d000u,0u,false);}
goto L1005e59c;
}
L1005e59c:{ // 0cf3bce5 ldr pc, [ip, #0x30c]!
c.r[15]=0x1005e59cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x30cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005e5a0u;return c.r[15];
}
L1005e5e8:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005e5e8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005e5f0u,0x200000u,0u,false);}
goto L1005e5ec;
}
L1005e5ec:{ // 5dca8ce2 add ip, ip, #0x5d000
c.r[15]=0x1005e5ecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5d000u,0u,false);}
goto L1005e5f0;
}
L1005e5f0:{ // d4f2bce5 ldr pc, [ip, #0x2d4]!
c.r[15]=0x1005e5f0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x2d4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005e5f4u;return c.r[15];
}
L1005eb34:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005eb34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005eb3cu,0x200000u,0u,false);}
goto L1005eb38;
}
L1005eb38:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005eb38u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005eb3c;
}
L1005eb3c:{ // 4cffbce5 ldr pc, [ip, #0xf4c]!
c.r[15]=0x1005eb3cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xf4cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005eb40u;return c.r[15];
}
L1005ec00:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec08u,0x200000u,0u,false);}
goto L1005ec04;
}
L1005ec04:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec04u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec08;
}
L1005ec08:{ // c4febce5 ldr pc, [ip, #0xec4]!
c.r[15]=0x1005ec08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xec4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec0c;
}
L1005ec0c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec14u,0x200000u,0u,false);}
goto L1005ec10;
}
L1005ec10:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec10u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec14;
}
L1005ec14:{ // bcfebce5 ldr pc, [ip, #0xebc]!
c.r[15]=0x1005ec14u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xebcu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec18;
}
L1005ec18:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec18u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec20u,0x200000u,0u,false);}
goto L1005ec1c;
}
L1005ec1c:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec1cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec20;
}
L1005ec20:{ // b4febce5 ldr pc, [ip, #0xeb4]!
c.r[15]=0x1005ec20u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xeb4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec24;
}
L1005ec24:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec24u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec2cu,0x200000u,0u,false);}
goto L1005ec28;
}
L1005ec28:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec28u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec2c;
}
L1005ec2c:{ // acfebce5 ldr pc, [ip, #0xeac]!
c.r[15]=0x1005ec2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xeacu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec30;
}
L1005ec30:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec30u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec38u,0x200000u,0u,false);}
goto L1005ec34;
}
L1005ec34:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec38;
}
L1005ec38:{ // a4febce5 ldr pc, [ip, #0xea4]!
c.r[15]=0x1005ec38u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xea4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec3c;
}
L1005ec3c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec3cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec44u,0x200000u,0u,false);}
goto L1005ec40;
}
L1005ec40:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec40u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec44;
}
L1005ec44:{ // 9cfebce5 ldr pc, [ip, #0xe9c]!
c.r[15]=0x1005ec44u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xe9cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec48;
}
L1005ec48:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec48u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec50u,0x200000u,0u,false);}
goto L1005ec4c;
}
L1005ec4c:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec4cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec50;
}
L1005ec50:{ // 94febce5 ldr pc, [ip, #0xe94]!
c.r[15]=0x1005ec50u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xe94u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ec54;
}
L1005ec54:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ec54u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ec5cu,0x200000u,0u,false);}
goto L1005ec58;
}
L1005ec58:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ec58u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ec5c;
}
L1005ec5c:{ // 8cfebce5 ldr pc, [ip, #0xe8c]!
c.r[15]=0x1005ec5cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xe8cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005ec60u;return c.r[15];
}
L1005eee8:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005eee8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005eef0u,0x200000u,0u,false);}
goto L1005eeec;
}
L1005eeec:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005eeecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005eef0;
}
L1005eef0:{ // d4fcbce5 ldr pc, [ip, #0xcd4]!
c.r[15]=0x1005eef0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcd4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005eef4;
}
L1005eef4:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005eef4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005eefcu,0x200000u,0u,false);}
goto L1005eef8;
}
L1005eef8:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005eef8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005eefc;
}
L1005eefc:{ // ccfcbce5 ldr pc, [ip, #0xccc]!
c.r[15]=0x1005eefcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcccu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ef00;
}
L1005ef00:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ef00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ef08u,0x200000u,0u,false);}
goto L1005ef04;
}
L1005ef04:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ef04u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ef08;
}
L1005ef08:{ // c4fcbce5 ldr pc, [ip, #0xcc4]!
c.r[15]=0x1005ef08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcc4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ef0c;
}
L1005ef0c:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ef0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ef14u,0x200000u,0u,false);}
goto L1005ef10;
}
L1005ef10:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ef10u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ef14;
}
L1005ef14:{ // bcfcbce5 ldr pc, [ip, #0xcbc]!
c.r[15]=0x1005ef14u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcbcu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ef18;
}
L1005ef18:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ef18u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ef20u,0x200000u,0u,false);}
goto L1005ef1c;
}
L1005ef1c:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ef1cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ef20;
}
L1005ef20:{ // b4fcbce5 ldr pc, [ip, #0xcb4]!
c.r[15]=0x1005ef20u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcb4u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1005ef24;
}
L1005ef24:{ // 02c68fe2 add ip, pc, #0x200000
c.r[15]=0x1005ef24u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x1005ef2cu,0x200000u,0u,false);}
goto L1005ef28;
}
L1005ef28:{ // 5cca8ce2 add ip, ip, #92, #20
c.r[15]=0x1005ef28u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x5c000u,0u,false);}
goto L1005ef2c;
}
L1005ef2c:{ // acfcbce5 ldr pc, [ip, #0xcac]!
c.r[15]=0x1005ef2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0xcacu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x1005ef30u;return c.r[15];
}
}
