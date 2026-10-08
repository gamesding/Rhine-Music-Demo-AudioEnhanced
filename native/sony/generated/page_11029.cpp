// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_11029(ArmState& c){
switch(c.r[15]){
case 0x11029de8u:goto L11029de8;
case 0x11029deau:goto L11029dea;
case 0x11029deeu:goto L11029dee;
case 0x11029df2u:goto L11029df2;
case 0x11029df4u:goto L11029df4;
case 0x11029df8u:goto L11029df8;
case 0x11029dfcu:goto L11029dfc;
case 0x11029e00u:goto L11029e00;
case 0x11029e04u:goto L11029e04;
case 0x11029e08u:goto L11029e08;
case 0x11029e0cu:goto L11029e0c;
case 0x11029e0eu:goto L11029e0e;
case 0x11029e12u:goto L11029e12;
case 0x11029e16u:goto L11029e16;
case 0x11029e18u:goto L11029e18;
case 0x11029e1au:goto L11029e1a;
case 0x11029e1eu:goto L11029e1e;
case 0x11029e20u:goto L11029e20;
case 0x11029e9eu:goto L11029e9e;
case 0x11029e22u:goto L11029e22;
case 0x11029ea2u:goto L11029ea2;
case 0x11029e24u:goto L11029e24;
case 0x11029ea6u:goto L11029ea6;
case 0x11029e26u:goto L11029e26;
case 0x11029eaau:goto L11029eaa;
case 0x11029e28u:goto L11029e28;
case 0x11029eacu:goto L11029eac;
case 0x11029e2au:goto L11029e2a;
case 0x11029eb0u:goto L11029eb0;
case 0x11029e2cu:goto L11029e2c;
case 0x11029eb4u:goto L11029eb4;
case 0x11029e30u:goto L11029e30;
case 0x11029eb8u:goto L11029eb8;
case 0x11029e34u:goto L11029e34;
case 0x11029ebau:goto L11029eba;
case 0x11029ee4u:goto L11029ee4;
case 0x11029e36u:goto L11029e36;
case 0x11029ebcu:goto L11029ebc;
case 0x11029ee8u:goto L11029ee8;
case 0x11029e3au:goto L11029e3a;
case 0x11029ebeu:goto L11029ebe;
case 0x11029eecu:goto L11029eec;
case 0x11029e3eu:goto L11029e3e;
case 0x11029ec0u:goto L11029ec0;
case 0x11029eeeu:goto L11029eee;
case 0x11029e42u:goto L11029e42;
case 0x11029ec2u:goto L11029ec2;
case 0x11029ef2u:goto L11029ef2;
case 0x11029e44u:goto L11029e44;
case 0x11029ec4u:goto L11029ec4;
case 0x11029ef4u:goto L11029ef4;
case 0x11029e48u:goto L11029e48;
case 0x11029ec6u:goto L11029ec6;
case 0x11029ef6u:goto L11029ef6;
case 0x11029e4cu:goto L11029e4c;
case 0x11029ecau:goto L11029eca;
case 0x11029e8cu:goto L11029e8c;
case 0x11029e50u:goto L11029e50;
case 0x11029eceu:goto L11029ece;
case 0x11029e90u:goto L11029e90;
case 0x11029e52u:goto L11029e52;
case 0x11029ef8u:goto L11029ef8;
case 0x11029ed0u:goto L11029ed0;
case 0x11029e92u:goto L11029e92;
case 0x11029e56u:goto L11029e56;
case 0x11029efcu:goto L11029efc;
case 0x11029ed4u:goto L11029ed4;
case 0x11029e96u:goto L11029e96;
case 0x11029e5au:goto L11029e5a;
case 0x11029efeu:goto L11029efe;
case 0x11029ed8u:goto L11029ed8;
case 0x11029e9au:goto L11029e9a;
case 0x11029e5cu:goto L11029e5c;
case 0x11029edau:goto L11029eda;
case 0x11029e60u:goto L11029e60;
case 0x11029edeu:goto L11029ede;
case 0x11029e62u:goto L11029e62;
case 0x11029ee0u:goto L11029ee0;
case 0x11029e64u:goto L11029e64;
case 0x11029ee2u:goto L11029ee2;
case 0x11029e68u:goto L11029e68;
case 0x11029e6cu:goto L11029e6c;
case 0x11029e70u:goto L11029e70;
case 0x11029e72u:goto L11029e72;
case 0x11029e74u:goto L11029e74;
case 0x11029e76u:goto L11029e76;
case 0x11029e7au:goto L11029e7a;
case 0x11029e7eu:goto L11029e7e;
case 0x11029e80u:goto L11029e80;
case 0x11029e82u:goto L11029e82;
case 0x11029e84u:goto L11029e84;
case 0x11029f00u:goto L11029f00;
case 0x11029e86u:goto L11029e86;
case 0x11029f04u:goto L11029f04;
case 0x11029e8au:goto L11029e8a;
case 0x11029f06u:goto L11029f06;
case 0x11029f18u:goto L11029f18;
case 0x11029f08u:goto L11029f08;
case 0x11029f1au:goto L11029f1a;
case 0x11029f0cu:goto L11029f0c;
case 0x11029f1eu:goto L11029f1e;
case 0x11029f0eu:goto L11029f0e;
case 0x11029f10u:goto L11029f10;
case 0x11029f14u:goto L11029f14;
case 0x11029f16u:goto L11029f16;
default:throw std::runtime_error("Untranslated instruction");}
L11029de8:{ // 80b5 push {r7, lr}
c.r[15]=0x11029de8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.r[7]);c.store<u32>(address+4,c.r[14]);c.r[13]-=8u;}
goto L11029dea;
}
L11029dea:{ // 2ded028b vpush {d8}
c.r[15]=0x11029deau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-8u;c.store<u32>(address+0,c.v[16]);c.store<u32>(address+4,c.v[17]);c.r[13]-=8u;}
goto L11029dee;
}
L11029dee:{ // b0ee408a vmov.f32 s16, s0
c.r[15]=0x11029deeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];c.v[16]=t0;}
goto L11029df2;
}
L11029df2:{ // 00af add r7, sp, #0
c.r[15]=0x11029df2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x0u,0u,false);}
goto L11029df4;
}
L11029df4:{ // f0ee608a vmov.f32 s17, s1
c.r[15]=0x11029df4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[1];c.v[17]=t0;}
goto L11029df8;
}
L11029df8:{ // fbf7bcfe bl #0x11025b74
c.r[15]=0x11029df8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x11029dfdu;c.r[15]=(0x11025b74u)&~1u;return c.r[15];}
goto L11029dfc;
}
L11029dfc:{ // dfed487a vldr s15, [pc, #0x120]
c.r[15]=0x11029dfcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x11029e00u+0x120u);c.v[15]=c.load<u32>(address+0);}
goto L11029e00;
}
L11029e00:{ // b0eec07a vabs.f32 s14, s0
c.r[15]=0x11029e00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=(c.v[0]&0x7fffffffu);c.v[14]=t0;}
goto L11029e04;
}
L11029e04:{ // b4ee677a vcmp.f32 s14, s15
c.r[15]=0x11029e04u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[14],c.v[15]);}
goto L11029e08;
}
L11029e08:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e0c;
}
L11029e0c:{ // 08d8 bhi #0x11029e20
c.r[15]=0x11029e0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e20u)&~1u;goto L11029e20;}
goto L11029e0e;
}
L11029e0e:{ // b5ee400a vcmp.f32 s0, #0
c.r[15]=0x11029e0eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[0],0x0u);}
goto L11029e12;
}
L11029e12:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e12u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e16;
}
L11029e16:{ // 42d0 beq #0x11029e9e
c.r[15]=0x11029e16u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e9eu)&~1u;goto L11029e9e;}
goto L11029e18;
}
L11029e18:{ // bd46 mov sp, r7
c.r[15]=0x11029e18u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L11029e1a;
}
L11029e1a:{ // bdec028b vpop {d8}
c.r[15]=0x11029e1au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L11029e1e;
}
L11029e1e:{ // 80bd pop {r7, pc}
c.r[15]=0x11029e1eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[7]=c.load<u32>(address+0);c.r[15]=c.load<u32>(address+4);c.r[13]+=8u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L11029e20;
}
L11029e20:{ // 404b ldr r3, [pc, #0x100]
c.r[15]=0x11029e20u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x11029e24u+0x100u);c.r[3]=u32(c.load<u32>(address));}
goto L11029e22;
}
L11029e22:{ // 7b44 add r3, pc
c.r[15]=0x11029e22u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x11029e26u,0u,false);}
goto L11029e24;
}
L11029e24:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11029e24u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11029e26;
}
L11029e26:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11029e26u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11029e28;
}
L11029e28:{ // 5a1c adds r2, r3, #1
c.r[15]=0x11029e28u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[3],0x1u,0u,(!oldIt));}
goto L11029e2a;
}
L11029e2a:{ // f5d0 beq #0x11029e18
c.r[15]=0x11029e2au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029e2c;
}
L11029e2c:{ // b4ee488a vcmp.f32 s16, s16
c.r[15]=0x11029e2cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[16],c.v[16]);}
goto L11029e30;
}
L11029e30:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e30u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e34;
}
L11029e34:{ // 56d6 bvs #0x11029ee4
c.r[15]=0x11029e34u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,6);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029ee4u)&~1u;goto L11029ee4;}
goto L11029e36;
}
L11029e36:{ // b0eec87a vabs.f32 s14, s16
c.r[15]=0x11029e36u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=(c.v[16]&0x7fffffffu);c.v[14]=t0;}
goto L11029e3a;
}
L11029e3a:{ // b4ee677a vcmp.f32 s14, s15
c.r[15]=0x11029e3au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[14],c.v[15]);}
goto L11029e3e;
}
L11029e3e:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e3eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e42;
}
L11029e42:{ // e9d8 bhi #0x11029e18
c.r[15]=0x11029e42u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029e44;
}
L11029e44:{ // b0eee87a vabs.f32 s14, s17
c.r[15]=0x11029e44u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=(c.v[17]&0x7fffffffu);c.v[14]=t0;}
goto L11029e48;
}
L11029e48:{ // b4ee677a vcmp.f32 s14, s15
c.r[15]=0x11029e48u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[14],c.v[15]);}
goto L11029e4c;
}
L11029e4c:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e4cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e50;
}
L11029e50:{ // e2d8 bhi #0x11029e18
c.r[15]=0x11029e50u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029e52;
}
L11029e52:{ // b4ee400a vcmp.f32 s0, s0
c.r[15]=0x11029e52u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[0],c.v[0]);}
goto L11029e56;
}
L11029e56:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e56u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e5a;
}
L11029e5a:{ // 64bf itt vs
c.r[15]=0x11029e5au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,6);
if(execute){c.it=100u;}
goto L11029e5c;
}
L11029e5c:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029e5cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029e60;
}
L11029e60:{ // 7c20 movs r0, #0x7c
c.r[15]=0x11029e60u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x7cu;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029e62;
}
L11029e62:{ // 13d6 bvs #0x11029e8c
c.r[15]=0x11029e62u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,6);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
goto L11029e64;
}
L11029e64:{ // b5ee408a vcmp.f32 s16, #0
c.r[15]=0x11029e64u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[16],0x0u);}
goto L11029e68;
}
L11029e68:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e68u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e6c;
}
L11029e6c:{ // f5eec08a vcmpe.f32 s17, #0
c.r[15]=0x11029e6cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[17],0x0u);}
goto L11029e70;
}
L11029e70:{ // 0cbf ite eq
c.r[15]=0x11029e70u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=12u;}
goto L11029e72;
}
L11029e72:{ // 0123 movs r3, #1
c.r[15]=0x11029e72u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L11029e74;
}
L11029e74:{ // 0023 movs r3, #0
c.r[15]=0x11029e74u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L11029e76;
}
L11029e76:{ // 03f00103 and r3, r3, #1
c.r[15]=0x11029e76u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[3]&0x1u);c.r[3]=x;}
goto L11029e7a;
}
L11029e7a:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029e7au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029e7e;
}
L11029e7e:{ // 58bf it pl
c.r[15]=0x11029e7eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,5);
if(execute){c.it=88u;}
goto L11029e80;
}
L11029e80:{ // 0023 movs r3, #0
c.r[15]=0x11029e80u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L11029e82;
}
L11029e82:{ // 002b cmp r3, #0
c.r[15]=0x11029e82u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0x0u),1u,true);}
goto L11029e84;
}
L11029e84:{ // 3cd1 bne #0x11029f00
c.r[15]=0x11029e84u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029f00u)&~1u;goto L11029f00;}
goto L11029e86;
}
L11029e86:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029e86u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029e8a;
}
L11029e8a:{ // 7920 movs r0, #0x79
c.r[15]=0x11029e8au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x79u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029e8c;
}
L11029e8c:{ // f0ee680a vmov.f32 s1, s17
c.r[15]=0x11029e8cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[17];c.v[1]=t0;}
goto L11029e90;
}
L11029e90:{ // bd46 mov sp, r7
c.r[15]=0x11029e90u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L11029e92;
}
L11029e92:{ // bdec028b vpop {d8}
c.r[15]=0x11029e92u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L11029e96;
}
L11029e96:{ // bde88040 pop.w {r7, lr}
c.r[15]=0x11029e96u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13];c.r[7]=c.load<u32>(address+0);c.r[14]=c.load<u32>(address+4);c.r[13]+=8u;}
goto L11029e9a;
}
L11029e9a:{ // 04f0d5ba b.w #0x1102e448
c.r[15]=0x11029e9au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1102e448u)&~1u;return c.r[15];}
goto L11029e9e;
}
L11029e9e:{ // b0eec87a vabs.f32 s14, s16
c.r[15]=0x11029e9eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=(c.v[16]&0x7fffffffu);c.v[14]=t0;}
goto L11029ea2;
}
L11029ea2:{ // b4ee677a vcmp.f32 s14, s15
c.r[15]=0x11029ea2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[14],c.v[15]);}
goto L11029ea6;
}
L11029ea6:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029ea6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029eaa;
}
L11029eaa:{ // b5d8 bhi #0x11029e18
c.r[15]=0x11029eaau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029eac;
}
L11029eac:{ // b0eee87a vabs.f32 s14, s17
c.r[15]=0x11029eacu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=(c.v[17]&0x7fffffffu);c.v[14]=t0;}
goto L11029eb0;
}
L11029eb0:{ // b4ee677a vcmp.f32 s14, s15
c.r[15]=0x11029eb0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[14],c.v[15]);}
goto L11029eb4;
}
L11029eb4:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029eb4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029eb8;
}
L11029eb8:{ // aed8 bhi #0x11029e18
c.r[15]=0x11029eb8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,8);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029eba;
}
L11029eba:{ // 1b4b ldr r3, [pc, #0x6c]
c.r[15]=0x11029ebau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x11029ebcu+0x6cu);c.r[3]=u32(c.load<u32>(address));}
goto L11029ebc;
}
L11029ebc:{ // 7b44 add r3, pc
c.r[15]=0x11029ebcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x11029ec0u,0u,false);}
goto L11029ebe;
}
L11029ebe:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11029ebeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11029ec0;
}
L11029ec0:{ // 1b68 ldr r3, [r3]
c.r[15]=0x11029ec0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[3]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L11029ec2;
}
L11029ec2:{ // 0133 adds r3, #1
c.r[15]=0x11029ec2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x1u,0u,(!oldIt));}
goto L11029ec4;
}
L11029ec4:{ // a8d0 beq #0x11029e18
c.r[15]=0x11029ec4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029ec6;
}
L11029ec6:{ // b5ee408a vcmp.f32 s16, #0
c.r[15]=0x11029ec6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[16],0x0u);}
goto L11029eca;
}
L11029eca:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029ecau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029ece;
}
L11029ece:{ // 13d1 bne #0x11029ef8
c.r[15]=0x11029eceu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029ef8u)&~1u;goto L11029ef8;}
goto L11029ed0;
}
L11029ed0:{ // f5ee408a vcmp.f32 s17, #0
c.r[15]=0x11029ed0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[17],0x0u);}
goto L11029ed4;
}
L11029ed4:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029ed4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029ed8;
}
L11029ed8:{ // 04bf itt eq
c.r[15]=0x11029ed8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=4u;}
goto L11029eda;
}
L11029eda:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029edau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029ede;
}
L11029ede:{ // 7820 movs r0, #0x78
c.r[15]=0x11029edeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x78u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029ee0;
}
L11029ee0:{ // 9ad1 bne #0x11029e18
c.r[15]=0x11029ee0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029ee2;
}
L11029ee2:{ // d3e7 b #0x11029e8c
c.r[15]=0x11029ee2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
goto L11029ee4;
}
L11029ee4:{ // f5ee408a vcmp.f32 s17, #0
c.r[15]=0x11029ee4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){fpCompare<float>(c,c.v[17],0x0u);}
goto L11029ee8;
}
L11029ee8:{ // f1ee10fa vmrs apsr_nzcv, fpscr
c.r[15]=0x11029ee8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);}
goto L11029eec;
}
L11029eec:{ // 04bf itt eq
c.r[15]=0x11029eecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.it=4u;}
goto L11029eee;
}
L11029eee:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029eeeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029ef2;
}
L11029ef2:{ // 8e20 movs r0, #0x8e
c.r[15]=0x11029ef2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x8eu;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029ef4;
}
L11029ef4:{ // 90d1 bne #0x11029e18
c.r[15]=0x11029ef4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,1);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e18u)&~1u;goto L11029e18;}
goto L11029ef6;
}
L11029ef6:{ // c9e7 b #0x11029e8c
c.r[15]=0x11029ef6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
goto L11029ef8;
}
L11029ef8:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029ef8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029efc;
}
L11029efc:{ // 7a20 movs r0, #0x7a
c.r[15]=0x11029efcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x7au;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029efe;
}
L11029efe:{ // c5e7 b #0x11029e8c
c.r[15]=0x11029efeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
goto L11029f00;
}
L11029f00:{ // 18ee103a vmov r3, s16
c.r[15]=0x11029f00u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.r[3]=t0;}
goto L11029f04;
}
L11029f04:{ // 002b cmp r3, #0
c.r[15]=0x11029f04u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0x0u),1u,true);}
goto L11029f06;
}
L11029f06:{ // 07da bge #0x11029f18
c.r[15]=0x11029f06u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,10);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029f18u)&~1u;goto L11029f18;}
goto L11029f08;
}
L11029f08:{ // 10ee103a vmov r3, s0
c.r[15]=0x11029f08u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[0];c.r[3]=t0;}
goto L11029f0c;
}
L11029f0c:{ // 002b cmp r3, #0
c.r[15]=0x11029f0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[3],~(0x0u),1u,true);}
goto L11029f0e;
}
L11029f0e:{ // bcbf itt lt
c.r[15]=0x11029f0eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.it=188u;}
goto L11029f10;
}
L11029f10:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029f10u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029f14;
}
L11029f14:{ // 7b20 movs r0, #0x7b
c.r[15]=0x11029f14u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x7bu;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029f16;
}
L11029f16:{ // b9db blt #0x11029e8c
c.r[15]=0x11029f16u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,11);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
goto L11029f18;
}
L11029f18:{ // 8f20 movs r0, #0x8f
c.r[15]=0x11029f18u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x8fu;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L11029f1a;
}
L11029f1a:{ // b0ee480a vmov.f32 s0, s16
c.r[15]=0x11029f1au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 t0=c.v[16];c.v[0]=t0;}
goto L11029f1e;
}
L11029f1e:{ // b5e7 b #0x11029e8c
c.r[15]=0x11029f1eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x11029e8cu)&~1u;goto L11029e8c;}
c.r[15]=0x11029f20u;return c.r[15];
}
}
