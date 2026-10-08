// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_11019(ArmState& c){
switch(c.r[15]){
case 0x110193a8u:goto L110193a8;
case 0x110193aau:goto L110193aa;
case 0x110193aeu:goto L110193ae;
case 0x110193b2u:goto L110193b2;
case 0x110193b4u:goto L110193b4;
case 0x110193b8u:goto L110193b8;
case 0x110193bcu:goto L110193bc;
case 0x110193c0u:goto L110193c0;
case 0x110193c4u:goto L110193c4;
case 0x110193c8u:goto L110193c8;
case 0x110193ccu:goto L110193cc;
case 0x110193ceu:goto L110193ce;
case 0x110193d2u:goto L110193d2;
case 0x110193d6u:goto L110193d6;
case 0x110193d8u:goto L110193d8;
case 0x110193dau:goto L110193da;
case 0x110193deu:goto L110193de;
case 0x110193e0u:goto L110193e0;
case 0x11019454u:goto L11019454;
case 0x110193e2u:goto L110193e2;
case 0x11019458u:goto L11019458;
case 0x110193e4u:goto L110193e4;
case 0x1101945cu:goto L1101945c;
case 0x110193e6u:goto L110193e6;
case 0x11019460u:goto L11019460;
case 0x110193e8u:goto L110193e8;
case 0x11019462u:goto L11019462;
case 0x110193eau:goto L110193ea;
case 0x11019466u:goto L11019466;
case 0x110193ecu:goto L110193ec;
case 0x1101946au:goto L1101946a;
case 0x110193f0u:goto L110193f0;
case 0x1101946eu:goto L1101946e;
case 0x110193f4u:goto L110193f4;
case 0x11019470u:goto L11019470;
case 0x11019498u:goto L11019498;
case 0x110193f6u:goto L110193f6;
case 0x11019472u:goto L11019472;
case 0x1101949cu:goto L1101949c;
case 0x110193fau:goto L110193fa;
case 0x11019474u:goto L11019474;
case 0x110194a0u:goto L110194a0;
case 0x110193feu:goto L110193fe;
case 0x11019476u:goto L11019476;
case 0x110194a2u:goto L110194a2;
case 0x11019402u:goto L11019402;
case 0x11019478u:goto L11019478;
case 0x110194a6u:goto L110194a6;
case 0x11019404u:goto L11019404;
case 0x1101947au:goto L1101947a;
case 0x110194a8u:goto L110194a8;
case 0x11019408u:goto L11019408;
case 0x1101947cu:goto L1101947c;
case 0x11019442u:goto L11019442;
case 0x1101940cu:goto L1101940c;
case 0x11019480u:goto L11019480;
case 0x11019446u:goto L11019446;
case 0x11019410u:goto L11019410;
case 0x11019484u:goto L11019484;
case 0x11019448u:goto L11019448;
case 0x11019412u:goto L11019412;
case 0x110194aau:goto L110194aa;
case 0x11019486u:goto L11019486;
case 0x1101944cu:goto L1101944c;
case 0x11019416u:goto L11019416;
case 0x110194aeu:goto L110194ae;
case 0x1101948au:goto L1101948a;
case 0x11019450u:goto L11019450;
case 0x1101941au:goto L1101941a;
case 0x110194b0u:goto L110194b0;
case 0x1101948eu:goto L1101948e;
case 0x110194d0u:goto L110194d0;
case 0x1101941cu:goto L1101941c;
case 0x11019490u:goto L11019490;
case 0x110194d4u:goto L110194d4;
case 0x11019420u:goto L11019420;
case 0x11019494u:goto L11019494;
case 0x110194d6u:goto L110194d6;
case 0x11019424u:goto L11019424;
case 0x11019496u:goto L11019496;
case 0x11019428u:goto L11019428;
case 0x1101942au:goto L1101942a;
case 0x1101942cu:goto L1101942c;
case 0x1101942eu:goto L1101942e;
case 0x11019432u:goto L11019432;
case 0x11019436u:goto L11019436;
case 0x11019438u:goto L11019438;
case 0x1101943au:goto L1101943a;
case 0x110194b2u:goto L110194b2;
case 0x1101943cu:goto L1101943c;
case 0x110194b6u:goto L110194b6;
case 0x11019440u:goto L11019440;
case 0x110194b8u:goto L110194b8;
case 0x110194c8u:goto L110194c8;
case 0x110194bau:goto L110194ba;
case 0x110194ccu:goto L110194cc;
case 0x110194beu:goto L110194be;
case 0x110194ceu:goto L110194ce;
case 0x110194c0u:goto L110194c0;
case 0x110194c4u:goto L110194c4;
case 0x110194c6u:goto L110194c6;
default:throw std::runtime_error("Untranslated instruction");}
L110193a8:{ // 80b5 push {r7, lr}
c.r[15]=0x110193a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.r[7]);c.store<u32>(address+4,c.r[14]);c.r[13]-=8u;}
goto L110193aa;
}
L110193aa:{ // 2ded048b vpush {d8, d9}
c.r[15]=0x110193aau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-16u;c.store<u32>(address+0,c.v[16]);c.store<u32>(address+4,c.v[17]);c.store<u32>(address+8,c.v[18]);c.store<u32>(address+12,c.v[19]);c.r[13]-=16u;}
goto L110193ae;
}
L110193ae:{ // b0ee408b vmov.f64 d8, d0
c.r[15]=0x110193aeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];u32 t1=c.v[1];c.v[16]=t0;c.v[17]=t1;}
goto L110193b2;
}
L110193b2:{ // 00af add r7, sp, #0
c.r[15]=0x110193b2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x0u,0u,false);}
goto L110193b4;
}
L110193b4:{ // b0ee419b vmov.f64 d9, d1
c.r[15]=0x110193b4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[2];u32 t1=c.v[3];c.v[18]=t0;c.v[19]=t1;}
goto L110193b8;
}
L110193b8:{ // f4f73ef8 bl #0x1100d438
c.r[15]=0x110193b8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x110193bdu;c.r[15]=(0x1100d438u)&~1u;return c.r[15];}
goto L110193bc;
}
L110193bc:{ // 9fed467b vldr d7, [pc, #0x118]
c.r[15]=0x110193bcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x110193c0u+0x118u);c.v[14]=c.load<u32>(address+0);c.v[15]=c.load<u32>(address+4);}
goto L110193c0;
}
L110193c0:{ // b0eec06b vabs.f64 d6, d0
c.r[15]=0x110193c0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u64 t0=((u64(c.v[0])|(u64(c.v[1])<<32))&0x7fffffffffffffffull);{u64 value=t0;c.v[12]=u32(value);c.v[13]=u32(value>>32);}}
goto L110193c4;
}
L110193c4:{ // b4ee476b vcmp.f64 d6, d7
c.r[15]=0x110193c4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[12])|(u64(c.v[13])<<32)),(u64(c.v[14])|(u64(c.v[15])<<32)));}
goto L110193c8;
}
L110193c8:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x110193c8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L110193cc;
}
L110193cc:{ // 08d8 bhi #0x110193e0
c.r[15]=0x110193ccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193e0u)&~1u;goto L110193e0;}
goto L110193ce;
}
L110193ce:{ // b5ee400b vcmp.f64 d0, #0
c.r[15]=0x110193ceu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[0])|(u64(c.v[1])<<32)),0x0ull);}
goto L110193d2;
}
L110193d2:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x110193d2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L110193d6;
}
L110193d6:{ // 3dd0 beq #0x11019454
c.r[15]=0x110193d6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019454u)&~1u;goto L11019454;}
goto L110193d8;
}
L110193d8:{ // bd46 mov sp, r7
c.r[15]=0x110193d8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L110193da;
}
L110193da:{ // bdec048b vpop {d8, d9}
c.r[15]=0x110193dau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.v[18]=c.load<u32>(address+8);c.v[19]=c.load<u32>(address+12);c.r[13]+=16u;}
goto L110193de;
}
L110193de:{ // 80bd pop {r7, pc}
c.r[15]=0x110193deu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[7]=c.load<u32>(address+0);c.r[15]=c.load<u32>(address+4);c.r[13]+=8u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L110193e0;
}
L110193e0:{ // 3f4b ldr r3, [pc, #0xfc]
c.r[15]=0x110193e0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x110193e4u+0xfcu);c.r[3]=u32(c.load<u32>(address));}
goto L110193e2;
}
L110193e2:{ // 7b44 add r3, pc
c.r[15]=0x110193e2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x110193e6u,0u,false);}
goto L110193e4;
}
L110193e4:{ // 1b68 ldr r3, [r3]
c.r[15]=0x110193e4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L110193e6;
}
L110193e6:{ // 1b68 ldr r3, [r3]
c.r[15]=0x110193e6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L110193e8;
}
L110193e8:{ // 5a1c adds r2, r3, #1
c.r[15]=0x110193e8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[3],0x1u,0u,(!oldIt));}
goto L110193ea;
}
L110193ea:{ // f5d0 beq #0x110193d8
c.r[15]=0x110193eau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L110193ec;
}
L110193ec:{ // b4ee488b vcmp.f64 d8, d8
c.r[15]=0x110193ecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[16])|(u64(c.v[17])<<32)),(u64(c.v[16])|(u64(c.v[17])<<32)));}
goto L110193f0;
}
L110193f0:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x110193f0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L110193f4;
}
L110193f4:{ // 50d6 bvs #0x11019498
c.r[15]=0x110193f4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,6);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019498u)&~1u;goto L11019498;}
goto L110193f6;
}
L110193f6:{ // b0eec86b vabs.f64 d6, d8
c.r[15]=0x110193f6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u64 t0=((u64(c.v[16])|(u64(c.v[17])<<32))&0x7fffffffffffffffull);{u64 value=t0;c.v[12]=u32(value);c.v[13]=u32(value>>32);}}
goto L110193fa;
}
L110193fa:{ // b4ee476b vcmp.f64 d6, d7
c.r[15]=0x110193fau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[12])|(u64(c.v[13])<<32)),(u64(c.v[14])|(u64(c.v[15])<<32)));}
goto L110193fe;
}
L110193fe:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x110193feu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019402;
}
L11019402:{ // e9d8 bhi #0x110193d8
c.r[15]=0x11019402u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L11019404;
}
L11019404:{ // b0eec96b vabs.f64 d6, d9
c.r[15]=0x11019404u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u64 t0=((u64(c.v[18])|(u64(c.v[19])<<32))&0x7fffffffffffffffull);{u64 value=t0;c.v[12]=u32(value);c.v[13]=u32(value>>32);}}
goto L11019408;
}
L11019408:{ // b4ee476b vcmp.f64 d6, d7
c.r[15]=0x11019408u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[12])|(u64(c.v[13])<<32)),(u64(c.v[14])|(u64(c.v[15])<<32)));}
goto L1101940c;
}
L1101940c:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x1101940cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019410;
}
L11019410:{ // e2d8 bhi #0x110193d8
c.r[15]=0x11019410u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L11019412;
}
L11019412:{ // b4ee400b vcmp.f64 d0, d0
c.r[15]=0x11019412u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[0])|(u64(c.v[1])<<32)),(u64(c.v[0])|(u64(c.v[1])<<32)));}
goto L11019416;
}
L11019416:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11019416u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L1101941a;
}
L1101941a:{ // 59d6 bvs #0x110194d0
c.r[15]=0x1101941au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,6);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110194d0u)&~1u;goto L110194d0;}
goto L1101941c;
}
L1101941c:{ // b5ee408b vcmp.f64 d8, #0
c.r[15]=0x1101941cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[16])|(u64(c.v[17])<<32)),0x0ull);}
goto L11019420;
}
L11019420:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11019420u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019424;
}
L11019424:{ // b5eec09b vcmpe.f64 d9, #0
c.r[15]=0x11019424u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[18])|(u64(c.v[19])<<32)),0x0ull);}
goto L11019428;
}
L11019428:{ // 0cbf ite eq
c.r[15]=0x11019428u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=12u;}
goto L1101942a;
}
L1101942a:{ // 0123 movs r3, #1
c.r[15]=0x1101942au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1101942c;
}
L1101942c:{ // 0023 movs r3, #0
c.r[15]=0x1101942cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1101942e;
}
L1101942e:{ // 03f00103 and r3, r3, #1
c.r[15]=0x1101942eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]&0x1u);c.r[3]=x;}
goto L11019432;
}
L11019432:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11019432u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019436;
}
L11019436:{ // 58bf it pl
c.r[15]=0x11019436u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,5);
if(execute){c.it=88u;}
goto L11019438;
}
L11019438:{ // 0023 movs r3, #0
c.r[15]=0x11019438u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1101943a;
}
L1101943a:{ // d3bb cbnz r3, #0x110194b2
c.r[15]=0x1101943au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){if(c.r[3]!=0){c.r[15]=0x110194b2u&~1u;return c.r[15];}}
goto L1101943c;
}
L1101943c:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x1101943cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L11019440;
}
L11019440:{ // 1520 movs r0, #0x15
c.r[15]=0x11019440u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x15u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11019442;
}
L11019442:{ // b0ee491b vmov.f64 d1, d9
c.r[15]=0x11019442u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[18];u32 t1=c.v[19];c.v[2]=t0;c.v[3]=t1;}
goto L11019446;
}
L11019446:{ // bd46 mov sp, r7
c.r[15]=0x11019446u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L11019448;
}
L11019448:{ // bdec048b vpop {d8, d9}
c.r[15]=0x11019448u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.v[18]=c.load<u32>(address+8);c.v[19]=c.load<u32>(address+12);c.r[13]+=16u;}
goto L1101944c;
}
L1101944c:{ // bde88040 pop.w {r7, lr}
c.r[15]=0x1101944cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[7]=c.load<u32>(address+0);c.r[14]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L11019450;
}
L11019450:{ // 07f006ba b.w #0x11020860
c.r[15]=0x11019450u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11020860u)&~1u;return c.r[15];}
goto L11019454;
}
L11019454:{ // b0eec86b vabs.f64 d6, d8
c.r[15]=0x11019454u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u64 t0=((u64(c.v[16])|(u64(c.v[17])<<32))&0x7fffffffffffffffull);{u64 value=t0;c.v[12]=u32(value);c.v[13]=u32(value>>32);}}
goto L11019458;
}
L11019458:{ // b4ee476b vcmp.f64 d6, d7
c.r[15]=0x11019458u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[12])|(u64(c.v[13])<<32)),(u64(c.v[14])|(u64(c.v[15])<<32)));}
goto L1101945c;
}
L1101945c:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x1101945cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019460;
}
L11019460:{ // bad8 bhi #0x110193d8
c.r[15]=0x11019460u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L11019462;
}
L11019462:{ // b0eec96b vabs.f64 d6, d9
c.r[15]=0x11019462u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u64 t0=((u64(c.v[18])|(u64(c.v[19])<<32))&0x7fffffffffffffffull);{u64 value=t0;c.v[12]=u32(value);c.v[13]=u32(value>>32);}}
goto L11019466;
}
L11019466:{ // b4ee476b vcmp.f64 d6, d7
c.r[15]=0x11019466u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[12])|(u64(c.v[13])<<32)),(u64(c.v[14])|(u64(c.v[15])<<32)));}
goto L1101946a;
}
L1101946a:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x1101946au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L1101946e;
}
L1101946e:{ // b3d8 bhi #0x110193d8
c.r[15]=0x1101946eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L11019470;
}
L11019470:{ // 1c4b ldr r3, [pc, #0x70]
c.r[15]=0x11019470u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x11019474u+0x70u);c.r[3]=u32(c.load<u32>(address));}
goto L11019472;
}
L11019472:{ // 7b44 add r3, pc
c.r[15]=0x11019472u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x11019476u,0u,false);}
goto L11019474;
}
L11019474:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11019474u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11019476;
}
L11019476:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11019476u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11019478;
}
L11019478:{ // 0133 adds r3, #1
c.r[15]=0x11019478u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x1u,0u,(!oldIt));}
goto L1101947a;
}
L1101947a:{ // add0 beq #0x110193d8
c.r[15]=0x1101947au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L1101947c;
}
L1101947c:{ // b5ee408b vcmp.f64 d8, #0
c.r[15]=0x1101947cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[16])|(u64(c.v[17])<<32)),0x0ull);}
goto L11019480;
}
L11019480:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11019480u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11019484;
}
L11019484:{ // 11d1 bne #0x110194aa
c.r[15]=0x11019484u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110194aau)&~1u;goto L110194aa;}
goto L11019486;
}
L11019486:{ // b5ee409b vcmp.f64 d9, #0
c.r[15]=0x11019486u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[18])|(u64(c.v[19])<<32)),0x0ull);}
goto L1101948a;
}
L1101948a:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x1101948au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L1101948e;
}
L1101948e:{ // a3d1 bne #0x110193d8
c.r[15]=0x1101948eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L11019490;
}
L11019490:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x11019490u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L11019494;
}
L11019494:{ // 1420 movs r0, #0x14
c.r[15]=0x11019494u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x14u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11019496;
}
L11019496:{ // d4e7 b #0x11019442
c.r[15]=0x11019496u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
goto L11019498;
}
L11019498:{ // b5ee409b vcmp.f64 d9, #0
c.r[15]=0x11019498u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<double>(c,(u64(c.v[18])|(u64(c.v[19])<<32)),0x0ull);}
goto L1101949c;
}
L1101949c:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x1101949cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L110194a0;
}
L110194a0:{ // 9ad1 bne #0x110193d8
c.r[15]=0x110194a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110193d8u)&~1u;goto L110193d8;}
goto L110194a2;
}
L110194a2:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x110194a2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L110194a6;
}
L110194a6:{ // 2a20 movs r0, #0x2a
c.r[15]=0x110194a6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x2au;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L110194a8;
}
L110194a8:{ // cbe7 b #0x11019442
c.r[15]=0x110194a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
goto L110194aa;
}
L110194aa:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x110194aau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L110194ae;
}
L110194ae:{ // 1620 movs r0, #0x16
c.r[15]=0x110194aeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x16u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L110194b0;
}
L110194b0:{ // c7e7 b #0x11019442
c.r[15]=0x110194b0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
goto L110194b2;
}
L110194b2:{ // 18ee903a vmov r3, s17
c.r[15]=0x110194b2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[17];c.r[3]=t0;}
goto L110194b6;
}
L110194b6:{ // 002b cmp r3, #0
c.r[15]=0x110194b6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0x0u),1u,true);}
goto L110194b8;
}
L110194b8:{ // 06da bge #0x110194c8
c.r[15]=0x110194b8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,10);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x110194c8u)&~1u;goto L110194c8;}
goto L110194ba;
}
L110194ba:{ // 10ee903a vmov r3, s1
c.r[15]=0x110194bau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[1];c.r[3]=t0;}
goto L110194be;
}
L110194be:{ // 1720 movs r0, #0x17
c.r[15]=0x110194beu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x17u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L110194c0;
}
L110194c0:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x110194c0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L110194c4;
}
L110194c4:{ // 002b cmp r3, #0
c.r[15]=0x110194c4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0x0u),1u,true);}
goto L110194c6;
}
L110194c6:{ // bcdb blt #0x11019442
c.r[15]=0x110194c6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,11);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
goto L110194c8;
}
L110194c8:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x110194c8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L110194cc;
}
L110194cc:{ // 2b20 movs r0, #0x2b
c.r[15]=0x110194ccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x2bu;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L110194ce;
}
L110194ce:{ // b8e7 b #0x11019442
c.r[15]=0x110194ceu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
goto L110194d0;
}
L110194d0:{ // b0ee480b vmov.f64 d0, d8
c.r[15]=0x110194d0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];u32 t1=c.v[17];c.v[0]=t0;c.v[1]=t1;}
goto L110194d4;
}
L110194d4:{ // 1820 movs r0, #0x18
c.r[15]=0x110194d4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x18u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L110194d6;
}
L110194d6:{ // b4e7 b #0x11019442
c.r[15]=0x110194d6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11019442u)&~1u;goto L11019442;}
c.r[15]=0x110194d8u;return c.r[15];
}
}
