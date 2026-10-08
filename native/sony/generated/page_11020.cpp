// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_11020(ArmState& c){
switch(c.r[15]){
case 0x11020860u:goto L11020860;
case 0x11020862u:goto L11020862;
case 0x11020864u:goto L11020864;
case 0x11020868u:goto L11020868;
case 0x1102086cu:goto L1102086c;
case 0x1102086eu:goto L1102086e;
case 0x11020870u:goto L11020870;
case 0x11020872u:goto L11020872;
case 0x11020876u:goto L11020876;
case 0x1102087au:goto L1102087a;
case 0x1102087cu:goto L1102087c;
case 0x11020880u:goto L11020880;
case 0x11020adau:goto L11020ada;
case 0x11020adeu:goto L11020ade;
case 0x11020ae0u:goto L11020ae0;
case 0x11020ae2u:goto L11020ae2;
case 0x11020ae6u:goto L11020ae6;
default:throw std::runtime_error("Untranslated instruction");}
L11020860:{ // b0b5 push {r4, r5, r7, lr}
c.r[15]=0x11020860u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-16u;c.store<u32>(address+0,c.r[4]);c.store<u32>(address+4,c.r[5]);c.store<u32>(address+8,c.r[7]);c.store<u32>(address+12,c.r[14]);c.r[13]-=16u;}
goto L11020862;
}
L11020862:{ // 431e subs r3, r0, #1
c.r[15]=0x11020862u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[0],~(0x1u),1u,(!oldIt));}
goto L11020864;
}
L11020864:{ // 2ded028b vpush {d8}
c.r[15]=0x11020864u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.v[16]);c.store<u32>(address+4,c.v[17]);c.r[13]-=8u;}
goto L11020868;
}
L11020868:{ // dff80845 ldr.w r4, [pc, #0x508]
c.r[15]=0x11020868u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102086cu+0x508u);c.r[4]=u32(c.load<u32>(address));}
goto L1102086c;
}
L1102086c:{ // 7c44 add r4, pc
c.r[15]=0x1102086cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[4]=sum(c,c.r[4],0x11020870u,0u,false);}
goto L1102086e;
}
L1102086e:{ // 88b0 sub sp, #0x20
c.r[15]=0x1102086eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[13]=sum(c,c.r[13],~(0x20u),1u,false);}
goto L11020870;
}
L11020870:{ // 00af add r7, sp, #0
c.r[15]=0x11020870u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x0u,0u,false);}
goto L11020872;
}
L11020872:{ // 87ed020b vstr d0, [r7, #8]
c.r[15]=0x11020872u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[7]+0x8u);c.store<u32>(address+0,c.v[0]);c.store<u32>(address+4,c.v[1]);}
goto L11020876;
}
L11020876:{ // 87ed041b vstr d1, [r7, #0x10]
c.r[15]=0x11020876u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[7]+0x10u);c.store<u32>(address+0,c.v[2]);c.store<u32>(address+4,c.v[3]);}
goto L1102087a;
}
L1102087a:{ // f92b cmp r3, #0xf9
c.r[15]=0x1102087au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0xf9u),1u,true);}
goto L1102087c;
}
L1102087c:{ // 01f2fc82 bhi.w #0x11021e78
c.r[15]=0x1102087cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11021e78u)&~1u;return c.r[15];}
goto L11020880;
}
L11020880:{ // dfe813f0 tbh [pc, r3, lsl #1]
c.r[15]=0x11020880u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=0x11020884u+2u*c.load<std::uint16_t>((0x11020884u+(0x0u+shift(c,c.r[3],1u,2,false))));return c.r[15];c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x11020884u;return c.r[15];
}
L11020ada:{ // b0ee470b vmov.f64 d0, d7
c.r[15]=0x11020adau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[14];u32 t1=c.v[15];c.v[0]=t0;c.v[1]=t1;}
goto L11020ade;
}
L11020ade:{ // 2037 adds r7, #0x20
c.r[15]=0x11020adeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[7],0x20u,0u,(!oldIt));}
goto L11020ae0;
}
L11020ae0:{ // bd46 mov sp, r7
c.r[15]=0x11020ae0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L11020ae2;
}
L11020ae2:{ // bdec028b vpop {d8}
c.r[15]=0x11020ae2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L11020ae6;
}
L11020ae6:{ // b0bd pop {r4, r5, r7, pc}
c.r[15]=0x11020ae6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[5]=c.load<u32>(address+4);c.r[7]=c.load<u32>(address+8);c.r[15]=c.load<u32>(address+12);c.r[13]+=16u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x11020ae8u;return c.r[15];
}
}
