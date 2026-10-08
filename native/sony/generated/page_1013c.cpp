// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1013c(ArmState& c){
switch(c.r[15]){
case 0x1013cf28u:goto L1013cf28;
case 0x1013cf2cu:goto L1013cf2c;
case 0x1013cf2eu:goto L1013cf2e;
case 0x1013cf30u:goto L1013cf30;
case 0x1013cf32u:goto L1013cf32;
case 0x1013cf34u:goto L1013cf34;
case 0x1013cf36u:goto L1013cf36;
case 0x1013cf38u:goto L1013cf38;
case 0x1013cf3au:goto L1013cf3a;
case 0x1013cf3cu:goto L1013cf3c;
case 0x1013cf40u:goto L1013cf40;
case 0x1013cf5au:goto L1013cf5a;
case 0x1013cf5eu:goto L1013cf5e;
case 0x1013cf62u:goto L1013cf62;
case 0x1013cf66u:goto L1013cf66;
case 0x1013cf68u:goto L1013cf68;
case 0x1013cf6cu:goto L1013cf6c;
case 0x1013cf70u:goto L1013cf70;
case 0x1013cf72u:goto L1013cf72;
case 0x1013cf76u:goto L1013cf76;
case 0x1013cf78u:goto L1013cf78;
case 0x1013cf7au:goto L1013cf7a;
case 0x1013cf7cu:goto L1013cf7c;
case 0x1013cf80u:goto L1013cf80;
case 0x1013cf84u:goto L1013cf84;
case 0x1013cf88u:goto L1013cf88;
case 0x1013cf8au:goto L1013cf8a;
case 0x1013cf8cu:goto L1013cf8c;
case 0x1013cf90u:goto L1013cf90;
case 0x1013cf94u:goto L1013cf94;
case 0x1013cf96u:goto L1013cf96;
case 0x1013cf98u:goto L1013cf98;
case 0x1013cf9cu:goto L1013cf9c;
case 0x1013cfa0u:goto L1013cfa0;
case 0x1013cfa4u:goto L1013cfa4;
case 0x1013cfc6u:goto L1013cfc6;
case 0x1013cfc8u:goto L1013cfc8;
case 0x1013cfcau:goto L1013cfca;
case 0x1013cfccu:goto L1013cfcc;
case 0x1013cfceu:goto L1013cfce;
case 0x1013cfd0u:goto L1013cfd0;
case 0x1013cfd2u:goto L1013cfd2;
case 0x1013cfd4u:goto L1013cfd4;
case 0x1013cfd6u:goto L1013cfd6;
case 0x1013cfd8u:goto L1013cfd8;
case 0x1013cfe0u:goto L1013cfe0;
case 0x1013cfe4u:goto L1013cfe4;
case 0x1013cfe8u:goto L1013cfe8;
case 0x1013cfeau:goto L1013cfea;
case 0x1013cfeeu:goto L1013cfee;
case 0x1013cff0u:goto L1013cff0;
case 0x1013cff2u:goto L1013cff2;
case 0x1013cff6u:goto L1013cff6;
case 0x1013cff8u:goto L1013cff8;
case 0x1013cffau:goto L1013cffa;
case 0x1013cffcu:goto L1013cffc;
case 0x1013cffeu:goto L1013cffe;
case 0x1013cf42u:goto L1013cf42;
case 0x1013cfa6u:goto L1013cfa6;
case 0x1013cfdcu:goto L1013cfdc;
case 0x1013cf44u:goto L1013cf44;
case 0x1013cfa8u:goto L1013cfa8;
case 0x1013cf46u:goto L1013cf46;
case 0x1013cfaau:goto L1013cfaa;
case 0x1013cf48u:goto L1013cf48;
case 0x1013cfacu:goto L1013cfac;
case 0x1013cf4au:goto L1013cf4a;
case 0x1013cfaeu:goto L1013cfae;
case 0x1013cf4cu:goto L1013cf4c;
case 0x1013cfb0u:goto L1013cfb0;
case 0x1013cf4eu:goto L1013cf4e;
case 0x1013cfb4u:goto L1013cfb4;
case 0x1013cf52u:goto L1013cf52;
case 0x1013cfb6u:goto L1013cfb6;
case 0x1013cf54u:goto L1013cf54;
case 0x1013cfb8u:goto L1013cfb8;
case 0x1013cf58u:goto L1013cf58;
case 0x1013cfbau:goto L1013cfba;
case 0x1013cfbeu:goto L1013cfbe;
case 0x1013cfc0u:goto L1013cfc0;
case 0x1013cfc4u:goto L1013cfc4;
default:throw std::runtime_error("Untranslated instruction");}
L1013cf28:{ // 2de9f047 push.w {r4, r5, r6, r7, r8, sb, sl, lr}
c.r[15]=0x1013cf28u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-32u;c.store<u32>(address+0,c.r[4]);c.store<u32>(address+4,c.r[5]);c.store<u32>(address+8,c.r[6]);c.store<u32>(address+12,c.r[7]);c.store<u32>(address+16,c.r[8]);c.store<u32>(address+20,c.r[9]);c.store<u32>(address+24,c.r[10]);c.store<u32>(address+28,c.r[14]);c.r[13]-=32u;}
goto L1013cf2c;
}
L1013cf2c:{ // 03af add r7, sp, #0xc
c.r[15]=0x1013cf2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0xcu,0u,false);}
goto L1013cf2e;
}
L1013cf2e:{ // 90b0 sub sp, #0x40
c.r[15]=0x1013cf2eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[13]=sum(c,c.r[13],~(0x40u),1u,false);}
goto L1013cf30;
}
L1013cf30:{ // 0446 mov r4, r0
c.r[15]=0x1013cf30u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[0];c.r[4]=x;}
goto L1013cf32;
}
L1013cf32:{ // 5748 ldr r0, [pc, #0x15c]
c.r[15]=0x1013cf32u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cf34u+0x15cu);c.r[0]=u32(c.load<u32>(address));}
goto L1013cf34;
}
L1013cf34:{ // 7844 add r0, pc
c.r[15]=0x1013cf34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x1013cf38u,0u,false);}
goto L1013cf36;
}
L1013cf36:{ // 0068 ldr r0, [r0]
c.r[15]=0x1013cf36u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cf38;
}
L1013cf38:{ // 0068 ldr r0, [r0]
c.r[15]=0x1013cf38u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cf3a;
}
L1013cf3a:{ // 0f90 str r0, [sp, #0x3c]
c.r[15]=0x1013cf3au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x3cu);c.store<u32>(address,c.r[0]);}
goto L1013cf3c;
}
L1013cf3c:{ // b4f83401 ldrh.w r0, [r4, #0x134]
c.r[15]=0x1013cf3cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[4]+0x134u);c.r[0]=u32(c.load<std::uint16_t>(address));}
goto L1013cf40;
}
L1013cf40:{ // 58b1 cbz r0, #0x1013cf5a
c.r[15]=0x1013cf40u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){if(c.r[0]==0){c.r[15]=0x1013cf5au&~1u;return c.r[15];}}
goto L1013cf42;
}
L1013cf42:{ // 564a ldr r2, [pc, #0x158]
c.r[15]=0x1013cf42u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cf44u+0x158u);c.r[2]=u32(c.load<u32>(address));}
goto L1013cf44;
}
L1013cf44:{ // 5349 ldr r1, [pc, #0x14c]
c.r[15]=0x1013cf44u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cf48u+0x14cu);c.r[1]=u32(c.load<u32>(address));}
goto L1013cf46;
}
L1013cf46:{ // 5448 ldr r0, [pc, #0x150]
c.r[15]=0x1013cf46u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cf48u+0x150u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cf48;
}
L1013cf48:{ // 7a44 add r2, pc
c.r[15]=0x1013cf48u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],0x1013cf4cu,0u,false);}
goto L1013cf4a;
}
L1013cf4a:{ // 7944 add r1, pc
c.r[15]=0x1013cf4au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[1],0x1013cf4eu,0u,false);}
goto L1013cf4c;
}
L1013cf4c:{ // 7844 add r0, pc
c.r[15]=0x1013cf4cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x1013cf50u,0u,false);}
goto L1013cf4e;
}
L1013cf4e:{ // cde90002 strd r0, r2, [sp]
c.r[15]=0x1013cf4eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address+0,c.r[0]);c.store<u32>(address+4,c.r[2]);}
goto L1013cf52;
}
L1013cf52:{ // 0320 movs r0, #3
c.r[15]=0x1013cf52u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x3u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013cf54;
}
L1013cf54:{ // 4ff4ab72 mov.w r2, #0x156
c.r[15]=0x1013cf54u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x156u;c.r[2]=x;}
goto L1013cf58;
}
L1013cf58:{ // 31e0 b #0x1013cfbe
c.r[15]=0x1013cf58u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1013cfbeu)&~1u;goto L1013cfbe;}
goto L1013cf5a;
}
L1013cf5a:{ // 41f27070 movw r0, #0x1770
c.r[15]=0x1013cf5au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1770u;c.r[0]=x;}
goto L1013cf5e;
}
L1013cf5e:{ // 4cf29c35 movw r5, #0xc39c
c.r[15]=0x1013cf5eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xc39cu;c.r[5]=x;}
goto L1013cf62;
}
L1013cf62:{ // a4f83401 strh.w r0, [r4, #0x134]
c.r[15]=0x1013cf62u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[4]+0x134u);c.store<std::uint16_t>(address,c.r[0]);}
goto L1013cf66;
}
L1013cf66:{ // 0020 movs r0, #0
c.r[15]=0x1013cf66u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013cf68;
}
L1013cf68:{ // c4e94e00 strd r0, r0, [r4, #0x138]
c.r[15]=0x1013cf68u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[4]+0x138u);c.store<u32>(address+0,c.r[0]);c.store<u32>(address+4,c.r[0]);}
goto L1013cf6c;
}
L1013cf6c:{ // 4ef64c40 movw r0, #0xec4c
c.r[15]=0x1013cf6cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xec4cu;c.r[0]=x;}
goto L1013cf70;
}
L1013cf70:{ // 2618 adds r6, r4, r0
c.r[15]=0x1013cf70u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[6]=sum(c,c.r[4],c.r[0],0u,(!oldIt));}
goto L1013cf72;
}
L1013cf72:{ // c0f20205 movt r5, #2
c.r[15]=0x1013cf72u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[5]=(c.r[5]&65535u)|(0x2u<<16);}
goto L1013cf76;
}
L1013cf76:{ // 0021 movs r1, #0
c.r[15]=0x1013cf76u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[1]=x;if((!oldIt))nz(c,x);}
goto L1013cf78;
}
L1013cf78:{ // 2a46 mov r2, r5
c.r[15]=0x1013cf78u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[5];c.r[2]=x;}
goto L1013cf7a;
}
L1013cf7a:{ // 3046 mov r0, r6
c.r[15]=0x1013cf7au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[6];c.r[0]=x;}
goto L1013cf7c;
}
L1013cf7c:{ // 04f59a79 add.w sb, r4, #0x134
c.r[15]=0x1013cf7cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[9]=sum(c,c.r[4],0x134u,0u,false);}
goto L1013cf80;
}
L1013cf80:{ // 1df780ea blx #0x1005a484
c.r[15]=0x1013cf80u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cf85u;c.r[15]=(0x1005a484u)&~1u;return c.r[15];}
goto L1013cf84;
}
L1013cf84:{ // 4ff48040 mov.w r0, #0x4000
c.r[15]=0x1013cf84u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x4000u;c.r[0]=x;}
goto L1013cf88;
}
L1013cf88:{ // 3146 mov r1, r6
c.r[15]=0x1013cf88u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[6];c.r[1]=x;}
goto L1013cf8a;
}
L1013cf8a:{ // 0090 str r0, [sp]
c.r[15]=0x1013cf8au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address,c.r[0]);}
goto L1013cf8c;
}
L1013cf8c:{ // 04f56a30 add.w r0, r4, #0x3a800
c.r[15]=0x1013cf8cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[4],0x3a800u,0u,false);}
goto L1013cf90;
}
L1013cf90:{ // 00f5fd63 add.w r3, r0, #0x7e8
c.r[15]=0x1013cf90u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[0],0x7e8u,0u,false);}
goto L1013cf94;
}
L1013cf94:{ // 4846 mov r0, sb
c.r[15]=0x1013cf94u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[9];c.r[0]=x;}
goto L1013cf96;
}
L1013cf96:{ // 2a46 mov r2, r5
c.r[15]=0x1013cf96u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[5];c.r[2]=x;}
goto L1013cf98;
}
L1013cf98:{ // 21f7eaea blx #0x1005e570
c.r[15]=0x1013cf98u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cf9du;c.r[15]=(0x1005e570u)&~1u;return c.r[15];}
goto L1013cf9c;
}
L1013cf9c:{ // 4ff6ff7a movw sl, #0xffff
c.r[15]=0x1013cf9cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xffffu;c.r[10]=x;}
goto L1013cfa0;
}
L1013cfa0:{ // 10ea0a0f tst.w r0, sl
c.r[15]=0x1013cfa0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[0]&c.r[10]);nz(c,x);}
goto L1013cfa4;
}
L1013cfa4:{ // 1cd0 beq #0x1013cfe0
c.r[15]=0x1013cfa4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1013cfe0u)&~1u;goto L1013cfe0;}
goto L1013cfa6;
}
L1013cfa6:{ // 404b ldr r3, [pc, #0x100]
c.r[15]=0x1013cfa6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cfa8u+0x100u);c.r[3]=u32(c.load<u32>(address));}
goto L1013cfa8;
}
L1013cfa8:{ // 3e4a ldr r2, [pc, #0xf8]
c.r[15]=0x1013cfa8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cfacu+0xf8u);c.r[2]=u32(c.load<u32>(address));}
goto L1013cfaa;
}
L1013cfaa:{ // 3d49 ldr r1, [pc, #0xf4]
c.r[15]=0x1013cfaau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cfacu+0xf4u);c.r[1]=u32(c.load<u32>(address));}
goto L1013cfac;
}
L1013cfac:{ // 7b44 add r3, pc
c.r[15]=0x1013cfacu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x1013cfb0u,0u,false);}
goto L1013cfae;
}
L1013cfae:{ // 7a44 add r2, pc
c.r[15]=0x1013cfaeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],0x1013cfb2u,0u,false);}
goto L1013cfb0;
}
L1013cfb0:{ // cde90023 strd r2, r3, [sp]
c.r[15]=0x1013cfb0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address+0,c.r[2]);c.store<u32>(address+4,c.r[3]);}
goto L1013cfb4;
}
L1013cfb4:{ // 7944 add r1, pc
c.r[15]=0x1013cfb4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[1],0x1013cfb8u,0u,false);}
goto L1013cfb6;
}
L1013cfb6:{ // 0290 str r0, [sp, #8]
c.r[15]=0x1013cfb6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x8u);c.store<u32>(address,c.r[0]);}
goto L1013cfb8;
}
L1013cfb8:{ // 0320 movs r0, #3
c.r[15]=0x1013cfb8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x3u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013cfba;
}
L1013cfba:{ // 40f26712 movw r2, #0x167
c.r[15]=0x1013cfbau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x167u;c.r[2]=x;}
goto L1013cfbe;
}
L1013cfbe:{ // 0023 movs r3, #0
c.r[15]=0x1013cfbeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1013cfc0;
}
L1013cfc0:{ // 1cf716e8 blx #0x10058ff0
c.r[15]=0x1013cfc0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cfc5u;c.r[15]=(0x10058ff0u)&~1u;return c.r[15];}
goto L1013cfc4;
}
L1013cfc4:{ // 0126 movs r6, #1
c.r[15]=0x1013cfc4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[6]=x;if((!oldIt))nz(c,x);}
goto L1013cfc6;
}
L1013cfc6:{ // 3c48 ldr r0, [pc, #0xf0]
c.r[15]=0x1013cfc6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013cfc8u+0xf0u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cfc8;
}
L1013cfc8:{ // 0f99 ldr r1, [sp, #0x3c]
c.r[15]=0x1013cfc8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x3cu);c.r[1]=u32(c.load<u32>(address));}
goto L1013cfca;
}
L1013cfca:{ // 7844 add r0, pc
c.r[15]=0x1013cfcau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x1013cfceu,0u,false);}
goto L1013cfcc;
}
L1013cfcc:{ // 0068 ldr r0, [r0]
c.r[15]=0x1013cfccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cfce;
}
L1013cfce:{ // 0068 ldr r0, [r0]
c.r[15]=0x1013cfceu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L1013cfd0;
}
L1013cfd0:{ // 401a subs r0, r0, r1
c.r[15]=0x1013cfd0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],~(c.r[1]),1u,(!oldIt));}
goto L1013cfd2;
}
L1013cfd2:{ // 02bf ittt eq
c.r[15]=0x1013cfd2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=2u;}
goto L1013cfd4;
}
L1013cfd4:{ // 3046 moveq r0, r6
c.r[15]=0x1013cfd4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[6];c.r[0]=x;}
goto L1013cfd6;
}
L1013cfd6:{ // 10b0 addeq sp, #0x40
c.r[15]=0x1013cfd6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[13]=sum(c,c.r[13],0x40u,0u,false);}
goto L1013cfd8;
}
L1013cfd8:{ // bde8f087 popeq.w {r4, r5, r6, r7, r8, sb, sl, pc}
c.r[15]=0x1013cfd8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[5]=c.load<u32>(address+4);c.r[6]=c.load<u32>(address+8);c.r[7]=c.load<u32>(address+12);c.r[8]=c.load<u32>(address+16);c.r[9]=c.load<u32>(address+20);c.r[10]=c.load<u32>(address+24);c.r[15]=c.load<u32>(address+28);c.r[13]+=32u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1013cfdc;
}
L1013cfdc:{ // 1bf7aeef blx #0x10058f3c
c.r[15]=0x1013cfdcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cfe1u;c.r[15]=(0x10058f3cu)&~1u;return c.r[15];}
goto L1013cfe0;
}
L1013cfe0:{ // 4ef6a820 movw r0, #0xeaa8
c.r[15]=0x1013cfe0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xeaa8u;c.r[0]=x;}
goto L1013cfe4;
}
L1013cfe4:{ // 1bf7bcef blx #0x10058f60
c.r[15]=0x1013cfe4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cfe9u;c.r[15]=(0x10058f60u)&~1u;return c.r[15];}
goto L1013cfe8;
}
L1013cfe8:{ // 0021 movs r1, #0
c.r[15]=0x1013cfe8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[1]=x;if((!oldIt))nz(c,x);}
goto L1013cfea;
}
L1013cfea:{ // 4ef6a822 movw r2, #0xeaa8
c.r[15]=0x1013cfeau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xeaa8u;c.r[2]=x;}
goto L1013cfee;
}
L1013cfee:{ // 8046 mov r8, r0
c.r[15]=0x1013cfeeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[0];c.r[8]=x;}
goto L1013cff0;
}
L1013cff0:{ // 0026 movs r6, #0
c.r[15]=0x1013cff0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[6]=x;if((!oldIt))nz(c,x);}
goto L1013cff2;
}
L1013cff2:{ // 1df748ea blx #0x1005a484
c.r[15]=0x1013cff2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013cff7u;c.r[15]=(0x1005a484u)&~1u;return c.r[15];}
goto L1013cff6;
}
L1013cff6:{ // 0220 movs r0, #2
c.r[15]=0x1013cff6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x2u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013cff8;
}
L1013cff8:{ // 0ba9 add r1, sp, #0x2c
c.r[15]=0x1013cff8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[13],0x2cu,0u,false);}
goto L1013cffa;
}
L1013cffa:{ // 0e90 str r0, [sp, #0x38]
c.r[15]=0x1013cffau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x38u);c.store<u32>(address,c.r[0]);}
goto L1013cffc;
}
L1013cffc:{ // 0120 movs r0, #1
c.r[15]=0x1013cffcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013cffe;
}
L1013cffe:{ // 4af64445 movw r5, #0xac44
c.r[15]=0x1013cffeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xac44u;c.r[5]=x;}
c.r[15]=0x1013d002u;return c.r[15];
}
}
