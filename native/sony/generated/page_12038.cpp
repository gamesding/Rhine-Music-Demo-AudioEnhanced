// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_12038(ArmState& c){
switch(c.r[15]){
case 0x120383d0u:goto L120383d0;
case 0x120383d2u:goto L120383d2;
case 0x12038474u:goto L12038474;
case 0x12038476u:goto L12038476;
case 0x12038478u:goto L12038478;
case 0x1203847au:goto L1203847a;
case 0x1203847cu:goto L1203847c;
case 0x1203847eu:goto L1203847e;
case 0x12038488u:goto L12038488;
case 0x1203848au:goto L1203848a;
case 0x1203848eu:goto L1203848e;
case 0x12038490u:goto L12038490;
case 0x12038492u:goto L12038492;
case 0x120383d6u:goto L120383d6;
case 0x12038480u:goto L12038480;
case 0x12038484u:goto L12038484;
case 0x12038494u:goto L12038494;
case 0x12038486u:goto L12038486;
case 0x12038496u:goto L12038496;
case 0x1203849au:goto L1203849a;
case 0x1203849cu:goto L1203849c;
case 0x120384a0u:goto L120384a0;
case 0x120384a2u:goto L120384a2;
case 0x120384a4u:goto L120384a4;
case 0x120384a6u:goto L120384a6;
case 0x120384a8u:goto L120384a8;
case 0x120384aau:goto L120384aa;
case 0x120384acu:goto L120384ac;
case 0x120384aeu:goto L120384ae;
default:throw std::runtime_error("Untranslated instruction");}
L120383d0:{ // 08b1 cbz r0, #0x120383d6
c.r[15]=0x120383d0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){if(c.r[0]==0){c.r[15]=0x120383d6u&~1u;return c.r[15];}}
goto L120383d2;
}
L120383d2:{ // 2cf0c9b8 b.w #0x12064568
c.r[15]=0x120383d2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x12064568u)&~1u;return c.r[15];}
goto L120383d6;
}
L120383d6:{ // 7047 bx lr
c.r[15]=0x120383d6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
c.r[15]=0x120383d8u;return c.r[15];
}
L12038474:{ // 10b5 push {r4, lr}
c.r[15]=0x12038474u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.r[4]);c.store<u32>(address+4,c.r[14]);c.r[13]-=8u;}
goto L12038476;
}
L12038476:{ // 0028 cmp r0, #0
c.r[15]=0x12038476u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(0x0u),1u,true);}
goto L12038478;
}
L12038478:{ // 14bf ite ne
c.r[15]=0x12038478u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,1);
if(execute){c.it=20u;}
goto L1203847a;
}
L1203847a:{ // 0446 movne r4, r0
c.r[15]=0x1203847au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[0];c.r[4]=x;}
goto L1203847c;
}
L1203847c:{ // 0124 moveq r4, #1
c.r[15]=0x1203847cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[4]=x;}
goto L1203847e;
}
L1203847e:{ // 03e0 b #0x12038488
c.r[15]=0x1203847eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x12038488u)&~1u;goto L12038488;}
goto L12038480;
}
L12038480:{ // f3f70ee9 blx #0x1202b6a0
c.r[15]=0x12038480u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x12038485u;c.r[15]=(0x1202b6a0u)&~1u;return c.r[15];}
goto L12038484;
}
L12038484:{ // 30b1 cbz r0, #0x12038494
c.r[15]=0x12038484u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){if(c.r[0]==0){c.r[15]=0x12038494u&~1u;return c.r[15];}}
goto L12038486;
}
L12038486:{ // 8047 blx r0
c.r[15]=0x12038486u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x12038489u;c.r[15]=(c.r[0])&~1u;return c.r[15];}
goto L12038488;
}
L12038488:{ // 2046 mov r0, r4
c.r[15]=0x12038488u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[4];c.r[0]=x;}
goto L1203848a;
}
L1203848a:{ // f2f720ed blx #0x1202aecc
c.r[15]=0x1203848au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1203848fu;c.r[15]=(0x1202aeccu)&~1u;return c.r[15];}
goto L1203848e;
}
L1203848e:{ // 0028 cmp r0, #0
c.r[15]=0x1203848eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(0x0u),1u,true);}
goto L12038490;
}
L12038490:{ // f6d0 beq #0x12038480
c.r[15]=0x12038490u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x12038480u)&~1u;goto L12038480;}
goto L12038492;
}
L12038492:{ // 10bd pop {r4, pc}
c.r[15]=0x12038492u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[15]=c.load<u32>(address+4);c.r[13]+=8u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L12038494;
}
L12038494:{ // 0420 movs r0, #4
c.r[15]=0x12038494u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x4u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L12038496;
}
L12038496:{ // f2f790ec blx #0x1202adb8
c.r[15]=0x12038496u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1203849bu;c.r[15]=(0x1202adb8u)&~1u;return c.r[15];}
goto L1203849a;
}
L1203849a:{ // 0446 mov r4, r0
c.r[15]=0x1203849au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[0];c.r[4]=x;}
goto L1203849c;
}
L1203849c:{ // f2f71ced blx #0x1202aed8
c.r[15]=0x1203849cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x120384a1u;c.r[15]=(0x1202aed8u)&~1u;return c.r[15];}
goto L120384a0;
}
L120384a0:{ // 0749 ldr r1, [pc, #0x1c]
c.r[15]=0x120384a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x120384a4u+0x1cu);c.r[1]=u32(c.load<u32>(address));}
goto L120384a2;
}
L120384a2:{ // 2046 mov r0, r4
c.r[15]=0x120384a2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[4];c.r[0]=x;}
goto L120384a4;
}
L120384a4:{ // 074a ldr r2, [pc, #0x1c]
c.r[15]=0x120384a4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x120384a8u+0x1cu);c.r[2]=u32(c.load<u32>(address));}
goto L120384a6;
}
L120384a6:{ // 7944 add r1, pc
c.r[15]=0x120384a6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[1],0x120384aau,0u,false);}
goto L120384a8;
}
L120384a8:{ // 0968 ldr r1, [r1]
c.r[15]=0x120384a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[1]+0x0u);c.r[1]=u32(c.load<u32>(address));}
goto L120384aa;
}
L120384aa:{ // 7a44 add r2, pc
c.r[15]=0x120384aau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],0x120384aeu,0u,false);}
goto L120384ac;
}
L120384ac:{ // 1268 ldr r2, [r2]
c.r[15]=0x120384acu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[2]+0x0u);c.r[2]=u32(c.load<u32>(address));}
goto L120384ae;
}
L120384ae:{ // f2f790ec blx #0x1202add0
c.r[15]=0x120384aeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x120384b3u;c.r[15]=(0x1202add0u)&~1u;return c.r[15];}
c.r[15]=0x120384b2u;return c.r[15];
}
}
