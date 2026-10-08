// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1102d(ArmState& c){
switch(c.r[15]){
case 0x1102dbd0u:goto L1102dbd0;
case 0x1102dbd4u:goto L1102dbd4;
case 0x1102dbd6u:goto L1102dbd6;
case 0x1102dbd8u:goto L1102dbd8;
case 0x1102dbdcu:goto L1102dbdc;
case 0x1102dbe0u:goto L1102dbe0;
case 0x1102dbe2u:goto L1102dbe2;
case 0x1102dc78u:goto L1102dc78;
case 0x1102dbe4u:goto L1102dbe4;
case 0x1102dc7cu:goto L1102dc7c;
case 0x1102dbe6u:goto L1102dbe6;
case 0x1102dcb2u:goto L1102dcb2;
case 0x1102dc7eu:goto L1102dc7e;
case 0x1102dbe8u:goto L1102dbe8;
case 0x1102dcb6u:goto L1102dcb6;
case 0x1102dc82u:goto L1102dc82;
case 0x1102dbecu:goto L1102dbec;
case 0x1102dc1cu:goto L1102dc1c;
case 0x1102dc86u:goto L1102dc86;
case 0x1102dbf0u:goto L1102dbf0;
case 0x1102dc20u:goto L1102dc20;
case 0x1102dc8au:goto L1102dc8a;
case 0x1102dbf4u:goto L1102dbf4;
case 0x1102dc22u:goto L1102dc22;
case 0x1102dc8eu:goto L1102dc8e;
case 0x1102dbf6u:goto L1102dbf6;
case 0x1102dc24u:goto L1102dc24;
case 0x1102dc92u:goto L1102dc92;
case 0x1102dbfau:goto L1102dbfa;
case 0x1102dc94u:goto L1102dc94;
case 0x1102dbfeu:goto L1102dbfe;
case 0x1102dc00u:goto L1102dc00;
case 0x1102dc52u:goto L1102dc52;
case 0x1102dc02u:goto L1102dc02;
case 0x1102dc56u:goto L1102dc56;
case 0x1102dc06u:goto L1102dc06;
case 0x1102dc58u:goto L1102dc58;
case 0x1102dc08u:goto L1102dc08;
case 0x1102dc5cu:goto L1102dc5c;
case 0x1102dc26u:goto L1102dc26;
case 0x1102dc0au:goto L1102dc0a;
case 0x1102dc60u:goto L1102dc60;
case 0x1102dc2au:goto L1102dc2a;
case 0x1102dc0cu:goto L1102dc0c;
case 0x1102dc62u:goto L1102dc62;
case 0x1102dc2cu:goto L1102dc2c;
case 0x1102dc0eu:goto L1102dc0e;
case 0x1102dc66u:goto L1102dc66;
case 0x1102dc30u:goto L1102dc30;
case 0x1102dc10u:goto L1102dc10;
case 0x1102dc6au:goto L1102dc6a;
case 0x1102dc34u:goto L1102dc34;
case 0x1102dc12u:goto L1102dc12;
case 0x1102dc6eu:goto L1102dc6e;
case 0x1102dc36u:goto L1102dc36;
case 0x1102dc4cu:goto L1102dc4c;
case 0x1102dc14u:goto L1102dc14;
case 0x1102dc72u:goto L1102dc72;
case 0x1102dc3au:goto L1102dc3a;
case 0x1102dc50u:goto L1102dc50;
case 0x1102dc18u:goto L1102dc18;
case 0x1102dc74u:goto L1102dc74;
case 0x1102dc3eu:goto L1102dc3e;
case 0x1102dc96u:goto L1102dc96;
case 0x1102dc76u:goto L1102dc76;
case 0x1102dc42u:goto L1102dc42;
case 0x1102dc98u:goto L1102dc98;
case 0x1102dc46u:goto L1102dc46;
case 0x1102dc9cu:goto L1102dc9c;
case 0x1102dc48u:goto L1102dc48;
case 0x1102dca0u:goto L1102dca0;
case 0x1102dc4au:goto L1102dc4a;
case 0x1102dca4u:goto L1102dca4;
case 0x1102dca8u:goto L1102dca8;
case 0x1102dcacu:goto L1102dcac;
case 0x1102dcb0u:goto L1102dcb0;
default:throw std::runtime_error("Untranslated instruction");}
L1102dbd0:{ // 10ee101a vmov r1, s0
c.r[15]=0x1102dbd0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];c.r[1]=t0;}
goto L1102dbd4;
}
L1102dbd4:{ // 90b4 push {r4, r7}
c.r[15]=0x1102dbd4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.r[4]);c.store<u32>(address+4,c.r[7]);c.r[13]-=8u;}
goto L1102dbd6;
}
L1102dbd6:{ // 00af add r7, sp, #0
c.r[15]=0x1102dbd6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x0u,0u,false);}
goto L1102dbd8;
}
L1102dbd8:{ // 10ee103a vmov r3, s0
c.r[15]=0x1102dbd8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];c.r[3]=t0;}
goto L1102dbdc;
}
L1102dbdc:{ // c1f3c752 ubfx r2, r1, #0x17, #8
c.r[15]=0x1102dbdcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=((c.r[1]>>23)&0xffu);}
goto L1102dbe0;
}
L1102dbe0:{ // 002a cmp r2, #0
c.r[15]=0x1102dbe0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[2],~(0x0u),1u,true);}
goto L1102dbe2;
}
L1102dbe2:{ // 49d0 beq #0x1102dc78
c.r[15]=0x1102dbe2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc78u)&~1u;goto L1102dc78;}
goto L1102dbe4;
}
L1102dbe4:{ // ff2a cmp r2, #0xff
c.r[15]=0x1102dbe4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[2],~(0xffu),1u,true);}
goto L1102dbe6;
}
L1102dbe6:{ // 02bf ittt eq
c.r[15]=0x1102dbe6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=2u;}
goto L1102dbe8;
}
L1102dbe8:{ // 07ee901a vmov s15, r1
c.r[15]=0x1102dbe8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.r[1];c.v[15]=t0;}
goto L1102dbec;
}
L1102dbec:{ // 77eea77a vadd.f32 s15, s15, s15
c.r[15]=0x1102dbecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=fpBinary<float>(c.v[15],c.v[15],0,false);c.v[15]=t0;}
goto L1102dbf0;
}
L1102dbf0:{ // 17ee900a vmov r0, s15
c.r[15]=0x1102dbf0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[0]=t0;}
goto L1102dbf4;
}
L1102dbf4:{ // 12d0 beq #0x1102dc1c
c.r[15]=0x1102dbf4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc1cu)&~1u;goto L1102dc1c;}
goto L1102dbf6;
}
L1102dbf6:{ // 43f6b044 movw r4, #0x3cb0
c.r[15]=0x1102dbf6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x3cb0u;c.r[4]=x;}
goto L1102dbfa;
}
L1102dbfa:{ // cff6ff74 movt r4, #0xffff
c.r[15]=0x1102dbfau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[4]=(c.r[4]&65535u)|(0xffffu<<16);}
goto L1102dbfe;
}
L1102dbfe:{ // a042 cmp r0, r4
c.r[15]=0x1102dbfeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(c.r[4]),1u,true);}
goto L1102dc00;
}
L1102dc00:{ // 27db blt #0x1102dc52
c.r[15]=0x1102dc00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,11);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc52u)&~1u;goto L1102dc52;}
goto L1102dc02;
}
L1102dc02:{ // 4cf25034 movw r4, #0xc350
c.r[15]=0x1102dc02u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xc350u;c.r[4]=x;}
goto L1102dc06;
}
L1102dc06:{ // a042 cmp r0, r4
c.r[15]=0x1102dc06u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(c.r[4]),1u,true);}
goto L1102dc08;
}
L1102dc08:{ // 0ddc bgt #0x1102dc26
c.r[15]=0x1102dc08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,12);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc26u)&~1u;goto L1102dc26;}
goto L1102dc0a;
}
L1102dc0a:{ // 1044 add r0, r2
c.r[15]=0x1102dc0au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],c.r[2],0u,false);}
goto L1102dc0c;
}
L1102dc0c:{ // fe28 cmp r0, #0xfe
c.r[15]=0x1102dc0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(0xfeu),1u,true);}
goto L1102dc0e;
}
L1102dc0e:{ // 0adc bgt #0x1102dc26
c.r[15]=0x1102dc0eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,12);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc26u)&~1u;goto L1102dc26;}
goto L1102dc10;
}
L1102dc10:{ // 0028 cmp r0, #0
c.r[15]=0x1102dc10u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],~(0x0u),1u,true);}
goto L1102dc12;
}
L1102dc12:{ // 1bdd ble #0x1102dc4c
c.r[15]=0x1102dc12u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,13);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc4cu)&~1u;goto L1102dc4c;}
goto L1102dc14;
}
L1102dc14:{ // 23f0ff43 bic r3, r3, #0x7f800000
c.r[15]=0x1102dc14u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]&~(0x7f800000u));c.r[3]=x;}
goto L1102dc18;
}
L1102dc18:{ // 43eac050 orr.w r0, r3, r0, lsl #23
c.r[15]=0x1102dc18u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]|shift(c,c.r[0],23u,2,false));c.r[0]=x;}
goto L1102dc1c;
}
L1102dc1c:{ // 00ee100a vmov s0, r0
c.r[15]=0x1102dc1cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.r[0];c.v[0]=t0;}
goto L1102dc20;
}
L1102dc20:{ // bd46 mov sp, r7
c.r[15]=0x1102dc20u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L1102dc22;
}
L1102dc22:{ // 90bc pop {r4, r7}
c.r[15]=0x1102dc22u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[7]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L1102dc24;
}
L1102dc24:{ // 7047 bx lr
c.r[15]=0x1102dc24u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
goto L1102dc26;
}
L1102dc26:{ // dfed247a vldr s15, [pc, #0x90]
c.r[15]=0x1102dc26u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dc28u+0x90u);c.v[15]=c.load<u32>(address+0);}
goto L1102dc2a;
}
L1102dc2a:{ // 0029 cmp r1, #0
c.r[15]=0x1102dc2au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[1],~(0x0u),1u,true);}
goto L1102dc2c;
}
L1102dc2c:{ // dfed236a vldr s13, [pc, #0x8c]
c.r[15]=0x1102dc2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dc30u+0x8cu);c.v[13]=c.load<u32>(address+0);}
goto L1102dc30;
}
L1102dc30:{ // b0ee677a vmov.f32 s14, s15
c.r[15]=0x1102dc30u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.v[14]=t0;}
goto L1102dc34;
}
L1102dc34:{ // b8bf it lt
c.r[15]=0x1102dc34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.it=184u;}
goto L1102dc36;
}
L1102dc36:{ // f0ee667a vmov.f32 s15, s13
c.r[15]=0x1102dc36u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[13];c.v[15]=t0;}
goto L1102dc3a;
}
L1102dc3a:{ // 67ee877a vmul.f32 s15, s15, s14
c.r[15]=0x1102dc3au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=fpBinary<float>(c.v[15],c.v[14],2,false);c.v[15]=t0;}
goto L1102dc3e;
}
L1102dc3e:{ // 17ee900a vmov r0, s15
c.r[15]=0x1102dc3eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[0]=t0;}
goto L1102dc42;
}
L1102dc42:{ // 00ee100a vmov s0, r0
c.r[15]=0x1102dc42u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.r[0];c.v[0]=t0;}
goto L1102dc46;
}
L1102dc46:{ // bd46 mov sp, r7
c.r[15]=0x1102dc46u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L1102dc48;
}
L1102dc48:{ // 90bc pop {r4, r7}
c.r[15]=0x1102dc48u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[7]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L1102dc4a;
}
L1102dc4a:{ // 7047 bx lr
c.r[15]=0x1102dc4au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
goto L1102dc4c;
}
L1102dc4c:{ // 10f1180f cmn.w r0, #0x18
c.r[15]=0x1102dc4cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[0],0x18u,0u,true);}
goto L1102dc50;
}
L1102dc50:{ // 21da bge #0x1102dc96
c.r[15]=0x1102dc50u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,10);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc96u)&~1u;goto L1102dc96;}
goto L1102dc52;
}
L1102dc52:{ // dfed1b7a vldr s15, [pc, #0x6c]
c.r[15]=0x1102dc52u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dc54u+0x6cu);c.v[15]=c.load<u32>(address+0);}
goto L1102dc56;
}
L1102dc56:{ // 0029 cmp r1, #0
c.r[15]=0x1102dc56u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[1],~(0x0u),1u,true);}
goto L1102dc58;
}
L1102dc58:{ // dfed1a6a vldr s13, [pc, #0x68]
c.r[15]=0x1102dc58u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dc5cu+0x68u);c.v[13]=c.load<u32>(address+0);}
goto L1102dc5c;
}
L1102dc5c:{ // b0ee677a vmov.f32 s14, s15
c.r[15]=0x1102dc5cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.v[14]=t0;}
goto L1102dc60;
}
L1102dc60:{ // b8bf it lt
c.r[15]=0x1102dc60u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.it=184u;}
goto L1102dc62;
}
L1102dc62:{ // f0ee667a vmov.f32 s15, s13
c.r[15]=0x1102dc62u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[13];c.v[15]=t0;}
goto L1102dc66;
}
L1102dc66:{ // 67ee877a vmul.f32 s15, s15, s14
c.r[15]=0x1102dc66u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=fpBinary<float>(c.v[15],c.v[14],2,false);c.v[15]=t0;}
goto L1102dc6a;
}
L1102dc6a:{ // 17ee900a vmov r0, s15
c.r[15]=0x1102dc6au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[0]=t0;}
goto L1102dc6e;
}
L1102dc6e:{ // 00ee100a vmov s0, r0
c.r[15]=0x1102dc6eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.r[0];c.v[0]=t0;}
goto L1102dc72;
}
L1102dc72:{ // bd46 mov sp, r7
c.r[15]=0x1102dc72u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L1102dc74;
}
L1102dc74:{ // 90bc pop {r4, r7}
c.r[15]=0x1102dc74u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[7]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L1102dc76;
}
L1102dc76:{ // 7047 bx lr
c.r[15]=0x1102dc76u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
goto L1102dc78;
}
L1102dc78:{ // 21f00043 bic r3, r1, #0x80000000
c.r[15]=0x1102dc78u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[1]&~(0x80000000u));c.r[3]=x;}
goto L1102dc7c;
}
L1102dc7c:{ // cbb1 cbz r3, #0x1102dcb2
c.r[15]=0x1102dc7cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){if(c.r[3]==0){c.r[15]=0x1102dcb2u&~1u;return c.r[15];}}
goto L1102dc7e;
}
L1102dc7e:{ // dfed127a vldr s15, [pc, #0x48]
c.r[15]=0x1102dc7eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dc80u+0x48u);c.v[15]=c.load<u32>(address+0);}
goto L1102dc82;
}
L1102dc82:{ // 60ee277a vmul.f32 s15, s0, s15
c.r[15]=0x1102dc82u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[15],2,false);c.v[15]=t0;}
goto L1102dc86;
}
L1102dc86:{ // 17ee901a vmov r1, s15
c.r[15]=0x1102dc86u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[1]=t0;}
goto L1102dc8a;
}
L1102dc8a:{ // 17ee903a vmov r3, s15
c.r[15]=0x1102dc8au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[3]=t0;}
goto L1102dc8e;
}
L1102dc8e:{ // c1f3c752 ubfx r2, r1, #0x17, #8
c.r[15]=0x1102dc8eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=((c.r[1]>>23)&0xffu);}
goto L1102dc92;
}
L1102dc92:{ // 193a subs r2, #0x19
c.r[15]=0x1102dc92u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],~(0x19u),1u,(!oldIt));}
goto L1102dc94;
}
L1102dc94:{ // afe7 b #0x1102dbf6
c.r[15]=0x1102dc94u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dbf6u)&~1u;goto L1102dbf6;}
goto L1102dc96;
}
L1102dc96:{ // 1930 adds r0, #0x19
c.r[15]=0x1102dc96u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x19u,0u,(!oldIt));}
goto L1102dc98;
}
L1102dc98:{ // 23f0ff43 bic r3, r3, #0x7f800000
c.r[15]=0x1102dc98u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]&~(0x7f800000u));c.r[3]=x;}
goto L1102dc9c;
}
L1102dc9c:{ // dfed0b7a vldr s15, [pc, #0x2c]
c.r[15]=0x1102dc9cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1102dca0u+0x2cu);c.v[15]=c.load<u32>(address+0);}
goto L1102dca0;
}
L1102dca0:{ // 43eac050 orr.w r0, r3, r0, lsl #23
c.r[15]=0x1102dca0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]|shift(c,c.r[0],23u,2,false));c.r[0]=x;}
goto L1102dca4;
}
L1102dca4:{ // 07ee100a vmov s14, r0
c.r[15]=0x1102dca4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.r[0];c.v[14]=t0;}
goto L1102dca8;
}
L1102dca8:{ // 67ee277a vmul.f32 s15, s14, s15
c.r[15]=0x1102dca8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=fpBinary<float>(c.v[14],c.v[15],2,false);c.v[15]=t0;}
goto L1102dcac;
}
L1102dcac:{ // 17ee900a vmov r0, s15
c.r[15]=0x1102dcacu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[15];c.r[0]=t0;}
goto L1102dcb0;
}
L1102dcb0:{ // b4e7 b #0x1102dc1c
c.r[15]=0x1102dcb0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc1cu)&~1u;goto L1102dc1c;}
goto L1102dcb2;
}
L1102dcb2:{ // 10ee100a vmov r0, s0
c.r[15]=0x1102dcb2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];c.r[0]=t0;}
goto L1102dcb6;
}
L1102dcb6:{ // b1e7 b #0x1102dc1c
c.r[15]=0x1102dcb6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102dc1cu)&~1u;goto L1102dc1c;}
c.r[15]=0x1102dcb8u;return c.r[15];
}
}
