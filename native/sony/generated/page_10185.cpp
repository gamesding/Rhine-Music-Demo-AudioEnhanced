// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10185(ArmState& c){
switch(c.r[15]){
case 0x10185018u:goto L10185018;
case 0x1018501cu:goto L1018501c;
case 0x10185020u:goto L10185020;
case 0x10185024u:goto L10185024;
case 0x10185028u:goto L10185028;
case 0x1018502cu:goto L1018502c;
case 0x10185030u:goto L10185030;
case 0x101851a0u:goto L101851a0;
case 0x101851a4u:goto L101851a4;
case 0x101856fcu:goto L101856fc;
case 0x10185700u:goto L10185700;
case 0x10185704u:goto L10185704;
case 0x10185098u:goto L10185098;
case 0x10185034u:goto L10185034;
case 0x1018509cu:goto L1018509c;
case 0x10185038u:goto L10185038;
case 0x101850a0u:goto L101850a0;
case 0x1018503cu:goto L1018503c;
case 0x10185138u:goto L10185138;
case 0x101850a4u:goto L101850a4;
case 0x10185040u:goto L10185040;
case 0x1018513cu:goto L1018513c;
case 0x101850a8u:goto L101850a8;
case 0x10185044u:goto L10185044;
case 0x10185140u:goto L10185140;
case 0x101850acu:goto L101850ac;
case 0x1018506cu:goto L1018506c;
case 0x10185048u:goto L10185048;
case 0x10185144u:goto L10185144;
case 0x101850b0u:goto L101850b0;
case 0x10185000u:goto L10185000;
case 0x10185070u:goto L10185070;
case 0x1018504cu:goto L1018504c;
case 0x10185148u:goto L10185148;
case 0x101850b4u:goto L101850b4;
case 0x10185004u:goto L10185004;
case 0x10185074u:goto L10185074;
case 0x10185050u:goto L10185050;
case 0x1018514cu:goto L1018514c;
case 0x101850b8u:goto L101850b8;
case 0x10185008u:goto L10185008;
case 0x10185078u:goto L10185078;
case 0x10185054u:goto L10185054;
case 0x10185150u:goto L10185150;
case 0x101850bcu:goto L101850bc;
case 0x1018500cu:goto L1018500c;
case 0x1018507cu:goto L1018507c;
case 0x10185058u:goto L10185058;
case 0x10185154u:goto L10185154;
case 0x101850f4u:goto L101850f4;
case 0x101850c0u:goto L101850c0;
case 0x10185010u:goto L10185010;
case 0x10185080u:goto L10185080;
case 0x1018505cu:goto L1018505c;
case 0x10185158u:goto L10185158;
case 0x101850f8u:goto L101850f8;
case 0x101850c4u:goto L101850c4;
case 0x10185014u:goto L10185014;
case 0x10185084u:goto L10185084;
case 0x10185060u:goto L10185060;
case 0x10185178u:goto L10185178;
case 0x1018515cu:goto L1018515c;
case 0x101850fcu:goto L101850fc;
case 0x101850c8u:goto L101850c8;
case 0x10185088u:goto L10185088;
case 0x10185064u:goto L10185064;
case 0x1018517cu:goto L1018517c;
case 0x10185160u:goto L10185160;
case 0x1018512cu:goto L1018512c;
case 0x10185100u:goto L10185100;
case 0x101850ccu:goto L101850cc;
case 0x1018508cu:goto L1018508c;
case 0x10185068u:goto L10185068;
case 0x10185180u:goto L10185180;
case 0x10185164u:goto L10185164;
case 0x10185130u:goto L10185130;
case 0x10185104u:goto L10185104;
case 0x101850d0u:goto L101850d0;
case 0x10185090u:goto L10185090;
case 0x10185184u:goto L10185184;
case 0x10185168u:goto L10185168;
case 0x10185134u:goto L10185134;
case 0x10185108u:goto L10185108;
case 0x101850d4u:goto L101850d4;
case 0x10185094u:goto L10185094;
case 0x10185188u:goto L10185188;
case 0x1018516cu:goto L1018516c;
case 0x1018510cu:goto L1018510c;
case 0x101850d8u:goto L101850d8;
case 0x1018518cu:goto L1018518c;
case 0x10185170u:goto L10185170;
case 0x10185110u:goto L10185110;
case 0x101850dcu:goto L101850dc;
case 0x10185190u:goto L10185190;
case 0x10185174u:goto L10185174;
case 0x10185114u:goto L10185114;
case 0x101850e0u:goto L101850e0;
case 0x10185194u:goto L10185194;
case 0x10185118u:goto L10185118;
case 0x101850e4u:goto L101850e4;
case 0x10185198u:goto L10185198;
case 0x1018511cu:goto L1018511c;
case 0x101850e8u:goto L101850e8;
case 0x1018519cu:goto L1018519c;
case 0x10185120u:goto L10185120;
case 0x101850ecu:goto L101850ec;
case 0x10185124u:goto L10185124;
case 0x101850f0u:goto L101850f0;
case 0x10185128u:goto L10185128;
case 0x10185f6cu:goto L10185f6c;
default:throw std::runtime_error("Untranslated instruction");}
L10185000:{ // 210a20ee vmul.f32 s0, s0, s3
c.r[15]=0x10185000u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[3],2,false);c.v[0]=t0;}
goto L10185004;
}
L10185004:{ // a10a60ee vmul.f32 s1, s1, s3
c.r[15]=0x10185004u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[1],c.v[3],2,false);c.v[1]=t0;}
goto L10185008;
}
L10185008:{ // 0d0880f4 vst1.32 {d0[0]}, [r0]!
c.r[15]=0x10185008u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[0]);c.r[0]+=4u;}
goto L1018500c;
}
L1018500c:{ // 8d088af4 vst1.32 {d0[1]}, [sl]!
c.r[15]=0x1018500cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[10];c.store<u32>(address+0,c.v[1]);c.r[10]+=4u;}
goto L10185010;
}
L10185010:{ // 018058e2 subs r8, r8, #1
c.r[15]=0x10185010u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x1u),1u,true);}
goto L10185014;
}
L10185014:{ // f3ffffca bgt #0x10184fe8
c.r[15]=0x10185014u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,12);
if(execute){c.r[15]=(0x10184fe8u)&~1u;return c.r[15];}
goto L10185018;
}
L10185018:{ // 0910a0e1 mov r1, sb
c.r[15]=0x10185018u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[9];c.r[1]=x;}
goto L1018501c;
}
L1018501c:{ // 0a00a0e1 mov r0, sl
c.r[15]=0x1018501cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[10];c.r[0]=x;}
goto L10185020;
}
L10185020:{ // d5ffffea b #0x10184f7c
c.r[15]=0x10185020u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x10184f7cu)&~1u;return c.r[15];}
goto L10185024;
}
L10185024:{ // 20709de5 ldr r7, [sp, #0x20]
c.r[15]=0x10185024u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[13]+0x20u);c.r[7]=u32(c.load<u32>(address));}
goto L10185028;
}
L10185028:{ // 017007e2 and r7, r7, #1
c.r[15]=0x10185028u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=(c.r[7]&0x1u);c.r[7]=x;}
goto L1018502c;
}
L1018502c:{ // 017057e2 subs r7, r7, #1
c.r[15]=0x1018502cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[7]=sum(c,c.r[7],~(0x1u),1u,true);}
goto L10185030;
}
L10185030:{ // 5a0000ba blt #0x101851a0
c.r[15]=0x10185030u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x101851a0u)&~1u;goto L101851a0;}
goto L10185034;
}
L10185034:{ // 0250a0e1 mov r5, r2
c.r[15]=0x10185034u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[2];c.r[5]=x;}
goto L10185038;
}
L10185038:{ // 0360a0e1 mov r6, r3
c.r[15]=0x10185038u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[3];c.r[6]=x;}
goto L1018503c;
}
L1018503c:{ // 0480a0e1 mov r8, r4
c.r[15]=0x1018503cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L10185040;
}
L10185040:{ // 088058e2 subs r8, r8, #8
c.r[15]=0x10185040u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x8u),1u,true);}
goto L10185044;
}
L10185044:{ // 080000ba blt #0x1018506c
c.r[15]=0x10185044u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x1018506cu)&~1u;goto L1018506c;}
goto L10185048;
}
L10185048:{ // 8d0221f4 vld1.32 {d0, d1, d2, d3}, [r1]!
c.r[15]=0x10185048u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.v[1]=c.load<u32>(address+4);c.v[2]=c.load<u32>(address+8);c.v[3]=c.load<u32>(address+12);c.v[4]=c.load<u32>(address+16);c.v[5]=c.load<u32>(address+20);c.v[6]=c.load<u32>(address+24);c.v[7]=c.load<u32>(address+28);c.r[1]+=32u;}
goto L1018504c;
}
L1018504c:{ // 8d0265f4 vld1.32 {d16, d17, d18, d19}, [r5]!
c.r[15]=0x1018504cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[32]=c.load<u32>(address+0);c.v[33]=c.load<u32>(address+4);c.v[34]=c.load<u32>(address+8);c.v[35]=c.load<u32>(address+12);c.v[36]=c.load<u32>(address+16);c.v[37]=c.load<u32>(address+20);c.v[38]=c.load<u32>(address+24);c.v[39]=c.load<u32>(address+28);c.r[5]+=32u;}
goto L10185050;
}
L10185050:{ // 8d4266f4 vld1.32 {d20, d21, d22, d23}, [r6]!
c.r[15]=0x10185050u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[40]=c.load<u32>(address+0);c.v[41]=c.load<u32>(address+4);c.v[42]=c.load<u32>(address+8);c.v[43]=c.load<u32>(address+12);c.v[44]=c.load<u32>(address+16);c.v[45]=c.load<u32>(address+20);c.v[46]=c.load<u32>(address+24);c.v[47]=c.load<u32>(address+28);c.r[6]+=32u;}
goto L10185054;
}
L10185054:{ // 600d20f2 vsub.f32 q0, q0, q8
c.r[15]=0x10185054u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[32],1,true);u32 t1=fpBinary<float>(c.v[1],c.v[33],1,true);u32 t2=fpBinary<float>(c.v[2],c.v[34],1,true);u32 t3=fpBinary<float>(c.v[3],c.v[35],1,true);c.v[0]=t0;c.v[1]=t1;c.v[2]=t2;c.v[3]=t3;}
goto L10185058;
}
L10185058:{ // 622d22f2 vsub.f32 q1, q1, q9
c.r[15]=0x10185058u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[4],c.v[36],1,true);u32 t1=fpBinary<float>(c.v[5],c.v[37],1,true);u32 t2=fpBinary<float>(c.v[6],c.v[38],1,true);u32 t3=fpBinary<float>(c.v[7],c.v[39],1,true);c.v[4]=t0;c.v[5]=t1;c.v[6]=t2;c.v[7]=t3;}
goto L1018505c;
}
L1018505c:{ // 740d00f3 vmul.f32 q0, q0, q10
c.r[15]=0x1018505cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[40],2,true);u32 t1=fpBinary<float>(c.v[1],c.v[41],2,true);u32 t2=fpBinary<float>(c.v[2],c.v[42],2,true);u32 t3=fpBinary<float>(c.v[3],c.v[43],2,true);c.v[0]=t0;c.v[1]=t1;c.v[2]=t2;c.v[3]=t3;}
goto L10185060;
}
L10185060:{ // 762d02f3 vmul.f32 q1, q1, q11
c.r[15]=0x10185060u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[4],c.v[44],2,true);u32 t1=fpBinary<float>(c.v[5],c.v[45],2,true);u32 t2=fpBinary<float>(c.v[6],c.v[46],2,true);u32 t3=fpBinary<float>(c.v[7],c.v[47],2,true);c.v[4]=t0;c.v[5]=t1;c.v[6]=t2;c.v[7]=t3;}
goto L10185064;
}
L10185064:{ // 8d0200f4 vst1.32 {d0, d1, d2, d3}, [r0]!
c.r[15]=0x10185064u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[0]);c.store<u32>(address+4,c.v[1]);c.store<u32>(address+8,c.v[2]);c.store<u32>(address+12,c.v[3]);c.store<u32>(address+16,c.v[4]);c.store<u32>(address+20,c.v[5]);c.store<u32>(address+24,c.v[6]);c.store<u32>(address+28,c.v[7]);c.r[0]+=32u;}
goto L10185068;
}
L10185068:{ // f4ffffea b #0x10185040
c.r[15]=0x10185068u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x10185040u)&~1u;goto L10185040;}
goto L1018506c;
}
L1018506c:{ // 0480a0e1 mov r8, r4
c.r[15]=0x1018506cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L10185070;
}
L10185070:{ // 078008e2 and r8, r8, #7
c.r[15]=0x10185070u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=(c.r[8]&0x7u);c.r[8]=x;}
goto L10185074;
}
L10185074:{ // 018058e2 subs r8, r8, #1
c.r[15]=0x10185074u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x1u),1u,true);}
goto L10185078;
}
L10185078:{ // ebffffba blt #0x1018502c
c.r[15]=0x10185078u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x1018502cu)&~1u;goto L1018502c;}
goto L1018507c;
}
L1018507c:{ // 0d08a1f4 vld1.32 {d0[0]}, [r1]!
c.r[15]=0x1018507cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.r[1]+=4u;}
goto L10185080;
}
L10185080:{ // 0d18a5f4 vld1.32 {d1[0]}, [r5]!
c.r[15]=0x10185080u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[2]=c.load<u32>(address+0);c.r[5]+=4u;}
goto L10185084;
}
L10185084:{ // 8d18a6f4 vld1.32 {d1[1]}, [r6]!
c.r[15]=0x10185084u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[3]=c.load<u32>(address+0);c.r[6]+=4u;}
goto L10185088;
}
L10185088:{ // 410a30ee vsub.f32 s0, s0, s2
c.r[15]=0x10185088u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[2],1,false);c.v[0]=t0;}
goto L1018508c;
}
L1018508c:{ // 210a20ee vmul.f32 s0, s0, s3
c.r[15]=0x1018508cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[0],c.v[3],2,false);c.v[0]=t0;}
goto L10185090;
}
L10185090:{ // 0d0880f4 vst1.32 {d0[0]}, [r0]!
c.r[15]=0x10185090u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[0]);c.r[0]+=4u;}
goto L10185094;
}
L10185094:{ // f6ffffea b #0x10185074
c.r[15]=0x10185094u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x10185074u)&~1u;goto L10185074;}
goto L10185098;
}
L10185098:{ // c770a0e1 asr r7, r7, #1
c.r[15]=0x10185098u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=shift(c,c.r[7],1u,1,false);c.r[7]=x;}
goto L1018509c;
}
L1018509c:{ // 017057e2 subs r7, r7, #1
c.r[15]=0x1018509cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[7]=sum(c,c.r[7],~(0x1u),1u,true);}
goto L101850a0;
}
L101850a0:{ // 240000ba blt #0x10185138
c.r[15]=0x101850a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x10185138u)&~1u;goto L10185138;}
goto L101850a4;
}
L101850a4:{ // 0250a0e1 mov r5, r2
c.r[15]=0x101850a4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[2];c.r[5]=x;}
goto L101850a8;
}
L101850a8:{ // 0360a0e1 mov r6, r3
c.r[15]=0x101850a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[3];c.r[6]=x;}
goto L101850ac;
}
L101850ac:{ // 049181e0 add sb, r1, r4, lsl #2
c.r[15]=0x101850acu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[9]=sum(c,c.r[1],shift(c,c.r[4],2u,2,false),0u,false);}
goto L101850b0;
}
L101850b0:{ // 04a180e0 add sl, r0, r4, lsl #2
c.r[15]=0x101850b0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[10]=sum(c,c.r[0],shift(c,c.r[4],2u,2,false),0u,false);}
goto L101850b4;
}
L101850b4:{ // 0480a0e1 mov r8, r4
c.r[15]=0x101850b4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L101850b8;
}
L101850b8:{ // 088058e2 subs r8, r8, #8
c.r[15]=0x101850b8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x8u),1u,true);}
goto L101850bc;
}
L101850bc:{ // 0c0000ba blt #0x101850f4
c.r[15]=0x101850bcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x101850f4u)&~1u;goto L101850f4;}
goto L101850c0;
}
L101850c0:{ // 8d0221f4 vld1.32 {d0, d1, d2, d3}, [r1]!
c.r[15]=0x101850c0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.v[1]=c.load<u32>(address+4);c.v[2]=c.load<u32>(address+8);c.v[3]=c.load<u32>(address+12);c.v[4]=c.load<u32>(address+16);c.v[5]=c.load<u32>(address+20);c.v[6]=c.load<u32>(address+24);c.v[7]=c.load<u32>(address+28);c.r[1]+=32u;}
goto L101850c4;
}
L101850c4:{ // 8d4229f4 vld1.32 {d4, d5, d6, d7}, [sb]!
c.r[15]=0x101850c4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[9];c.v[8]=c.load<u32>(address+0);c.v[9]=c.load<u32>(address+4);c.v[10]=c.load<u32>(address+8);c.v[11]=c.load<u32>(address+12);c.v[12]=c.load<u32>(address+16);c.v[13]=c.load<u32>(address+20);c.v[14]=c.load<u32>(address+24);c.v[15]=c.load<u32>(address+28);c.r[9]+=32u;}
goto L101850c8;
}
L101850c8:{ // 8d0265f4 vld1.32 {d16, d17, d18, d19}, [r5]!
c.r[15]=0x101850c8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[32]=c.load<u32>(address+0);c.v[33]=c.load<u32>(address+4);c.v[34]=c.load<u32>(address+8);c.v[35]=c.load<u32>(address+12);c.v[36]=c.load<u32>(address+16);c.v[37]=c.load<u32>(address+20);c.v[38]=c.load<u32>(address+24);c.v[39]=c.load<u32>(address+28);c.r[5]+=32u;}
goto L101850cc;
}
L101850cc:{ // 8d4266f4 vld1.32 {d20, d21, d22, d23}, [r6]!
c.r[15]=0x101850ccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[40]=c.load<u32>(address+0);c.v[41]=c.load<u32>(address+4);c.v[42]=c.load<u32>(address+8);c.v[43]=c.load<u32>(address+12);c.v[44]=c.load<u32>(address+16);c.v[45]=c.load<u32>(address+20);c.v[46]=c.load<u32>(address+24);c.v[47]=c.load<u32>(address+28);c.r[6]+=32u;}
goto L101850d0;
}
L101850d0:{ // f08160f2 vorr q12, q8, q8
c.r[15]=0x101850d0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[32]|c.v[32]);u32 t1=(c.v[33]|c.v[33]);u32 t2=(c.v[34]|c.v[34]);u32 t3=(c.v[35]|c.v[35]);c.v[48]=t0;c.v[49]=t1;c.v[50]=t2;c.v[51]=t3;}
goto L101850d4;
}
L101850d4:{ // f2a162f2 vorr q13, q9, q9
c.r[15]=0x101850d4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[36]|c.v[36]);u32 t1=(c.v[37]|c.v[37]);u32 t2=(c.v[38]|c.v[38]);u32 t3=(c.v[39]|c.v[39]);c.v[52]=t0;c.v[53]=t1;c.v[54]=t2;c.v[55]=t3;}
goto L101850d8;
}
L101850d8:{ // 740d40f2 vmla.f32 q8, q0, q10
c.r[15]=0x101850d8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[32],fpBinary<float>(c.v[0],c.v[40],2,true),0,true);u32 t1=fpBinary<float>(c.v[33],fpBinary<float>(c.v[1],c.v[41],2,true),0,true);u32 t2=fpBinary<float>(c.v[34],fpBinary<float>(c.v[2],c.v[42],2,true),0,true);u32 t3=fpBinary<float>(c.v[35],fpBinary<float>(c.v[3],c.v[43],2,true),0,true);c.v[32]=t0;c.v[33]=t1;c.v[34]=t2;c.v[35]=t3;}
goto L101850dc;
}
L101850dc:{ // 762d42f2 vmla.f32 q9, q1, q11
c.r[15]=0x101850dcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[36],fpBinary<float>(c.v[4],c.v[44],2,true),0,true);u32 t1=fpBinary<float>(c.v[37],fpBinary<float>(c.v[5],c.v[45],2,true),0,true);u32 t2=fpBinary<float>(c.v[38],fpBinary<float>(c.v[6],c.v[46],2,true),0,true);u32 t3=fpBinary<float>(c.v[39],fpBinary<float>(c.v[7],c.v[47],2,true),0,true);c.v[36]=t0;c.v[37]=t1;c.v[38]=t2;c.v[39]=t3;}
goto L101850e0;
}
L101850e0:{ // 748d44f2 vmla.f32 q12, q2, q10
c.r[15]=0x101850e0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[48],fpBinary<float>(c.v[8],c.v[40],2,true),0,true);u32 t1=fpBinary<float>(c.v[49],fpBinary<float>(c.v[9],c.v[41],2,true),0,true);u32 t2=fpBinary<float>(c.v[50],fpBinary<float>(c.v[10],c.v[42],2,true),0,true);u32 t3=fpBinary<float>(c.v[51],fpBinary<float>(c.v[11],c.v[43],2,true),0,true);c.v[48]=t0;c.v[49]=t1;c.v[50]=t2;c.v[51]=t3;}
goto L101850e4;
}
L101850e4:{ // 76ad46f2 vmla.f32 q13, q3, q11
c.r[15]=0x101850e4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[52],fpBinary<float>(c.v[12],c.v[44],2,true),0,true);u32 t1=fpBinary<float>(c.v[53],fpBinary<float>(c.v[13],c.v[45],2,true),0,true);u32 t2=fpBinary<float>(c.v[54],fpBinary<float>(c.v[14],c.v[46],2,true),0,true);u32 t3=fpBinary<float>(c.v[55],fpBinary<float>(c.v[15],c.v[47],2,true),0,true);c.v[52]=t0;c.v[53]=t1;c.v[54]=t2;c.v[55]=t3;}
goto L101850e8;
}
L101850e8:{ // 8d0240f4 vst1.32 {d16, d17, d18, d19}, [r0]!
c.r[15]=0x101850e8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[32]);c.store<u32>(address+4,c.v[33]);c.store<u32>(address+8,c.v[34]);c.store<u32>(address+12,c.v[35]);c.store<u32>(address+16,c.v[36]);c.store<u32>(address+20,c.v[37]);c.store<u32>(address+24,c.v[38]);c.store<u32>(address+28,c.v[39]);c.r[0]+=32u;}
goto L101850ec;
}
L101850ec:{ // 8d824af4 vst1.32 {d24, d25, d26, d27}, [sl]!
c.r[15]=0x101850ecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[10];c.store<u32>(address+0,c.v[48]);c.store<u32>(address+4,c.v[49]);c.store<u32>(address+8,c.v[50]);c.store<u32>(address+12,c.v[51]);c.store<u32>(address+16,c.v[52]);c.store<u32>(address+20,c.v[53]);c.store<u32>(address+24,c.v[54]);c.store<u32>(address+28,c.v[55]);c.r[10]+=32u;}
goto L101850f0;
}
L101850f0:{ // f0ffffea b #0x101850b8
c.r[15]=0x101850f0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x101850b8u)&~1u;goto L101850b8;}
goto L101850f4;
}
L101850f4:{ // 0480a0e1 mov r8, r4
c.r[15]=0x101850f4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L101850f8;
}
L101850f8:{ // 078018e2 ands r8, r8, #7
c.r[15]=0x101850f8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=(c.r[8]&0x7u);c.r[8]=x;if(true)nz(c,x);}
goto L101850fc;
}
L101850fc:{ // 0a00000a beq #0x1018512c
c.r[15]=0x101850fcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,0);
if(execute){c.r[15]=(0x1018512cu)&~1u;goto L1018512c;}
goto L10185100;
}
L10185100:{ // 0d08a1f4 vld1.32 {d0[0]}, [r1]!
c.r[15]=0x10185100u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.r[1]+=4u;}
goto L10185104;
}
L10185104:{ // 8d08a9f4 vld1.32 {d0[1]}, [sb]!
c.r[15]=0x10185104u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[9];c.v[1]=c.load<u32>(address+0);c.r[9]+=4u;}
goto L10185108;
}
L10185108:{ // 0d28a5f4 vld1.32 {d2[0]}, [r5]!
c.r[15]=0x10185108u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[4]=c.load<u32>(address+0);c.r[5]+=4u;}
goto L1018510c;
}
L1018510c:{ // 0d18a6f4 vld1.32 {d1[0]}, [r6]!
c.r[15]=0x1018510cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[2]=c.load<u32>(address+0);c.r[6]+=4u;}
goto L10185110;
}
L10185110:{ // 422af0ee vmov.f32 s5, s4
c.r[15]=0x10185110u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[4];c.v[5]=t0;}
goto L10185114;
}
L10185114:{ // 411af0ee vmov.f32 s3, s2
c.r[15]=0x10185114u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[2];c.v[3]=t0;}
goto L10185118;
}
L10185118:{ // 112d00f2 vmla.f32 d2, d0, d1
c.r[15]=0x10185118u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[4],fpBinary<float>(c.v[0],c.v[2],2,true),0,true);u32 t1=fpBinary<float>(c.v[5],fpBinary<float>(c.v[1],c.v[3],2,true),0,true);c.v[4]=t0;c.v[5]=t1;}
goto L1018511c;
}
L1018511c:{ // 0d2880f4 vst1.32 {d2[0]}, [r0]!
c.r[15]=0x1018511cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[4]);c.r[0]+=4u;}
goto L10185120;
}
L10185120:{ // 8d288af4 vst1.32 {d2[1]}, [sl]!
c.r[15]=0x10185120u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[10];c.store<u32>(address+0,c.v[5]);c.r[10]+=4u;}
goto L10185124;
}
L10185124:{ // 018058e2 subs r8, r8, #1
c.r[15]=0x10185124u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x1u),1u,true);}
goto L10185128;
}
L10185128:{ // f4ffffca bgt #0x10185100
c.r[15]=0x10185128u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,12);
if(execute){c.r[15]=(0x10185100u)&~1u;goto L10185100;}
goto L1018512c;
}
L1018512c:{ // 0910a0e1 mov r1, sb
c.r[15]=0x1018512cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[9];c.r[1]=x;}
goto L10185130;
}
L10185130:{ // 0a00a0e1 mov r0, sl
c.r[15]=0x10185130u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[10];c.r[0]=x;}
goto L10185134;
}
L10185134:{ // d8ffffea b #0x1018509c
c.r[15]=0x10185134u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x1018509cu)&~1u;goto L1018509c;}
goto L10185138;
}
L10185138:{ // 20709de5 ldr r7, [sp, #0x20]
c.r[15]=0x10185138u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[13]+0x20u);c.r[7]=u32(c.load<u32>(address));}
goto L1018513c;
}
L1018513c:{ // 017007e2 and r7, r7, #1
c.r[15]=0x1018513cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=(c.r[7]&0x1u);c.r[7]=x;}
goto L10185140;
}
L10185140:{ // 017057e2 subs r7, r7, #1
c.r[15]=0x10185140u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[7]=sum(c,c.r[7],~(0x1u),1u,true);}
goto L10185144;
}
L10185144:{ // 150000ba blt #0x101851a0
c.r[15]=0x10185144u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x101851a0u)&~1u;goto L101851a0;}
goto L10185148;
}
L10185148:{ // 0250a0e1 mov r5, r2
c.r[15]=0x10185148u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[2];c.r[5]=x;}
goto L1018514c;
}
L1018514c:{ // 0360a0e1 mov r6, r3
c.r[15]=0x1018514cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[3];c.r[6]=x;}
goto L10185150;
}
L10185150:{ // 0480a0e1 mov r8, r4
c.r[15]=0x10185150u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L10185154;
}
L10185154:{ // 088058e2 subs r8, r8, #8
c.r[15]=0x10185154u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x8u),1u,true);}
goto L10185158;
}
L10185158:{ // 060000ba blt #0x10185178
c.r[15]=0x10185158u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x10185178u)&~1u;goto L10185178;}
goto L1018515c;
}
L1018515c:{ // 8d0221f4 vld1.32 {d0, d1, d2, d3}, [r1]!
c.r[15]=0x1018515cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.v[1]=c.load<u32>(address+4);c.v[2]=c.load<u32>(address+8);c.v[3]=c.load<u32>(address+12);c.v[4]=c.load<u32>(address+16);c.v[5]=c.load<u32>(address+20);c.v[6]=c.load<u32>(address+24);c.v[7]=c.load<u32>(address+28);c.r[1]+=32u;}
goto L10185160;
}
L10185160:{ // 8d0265f4 vld1.32 {d16, d17, d18, d19}, [r5]!
c.r[15]=0x10185160u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[32]=c.load<u32>(address+0);c.v[33]=c.load<u32>(address+4);c.v[34]=c.load<u32>(address+8);c.v[35]=c.load<u32>(address+12);c.v[36]=c.load<u32>(address+16);c.v[37]=c.load<u32>(address+20);c.v[38]=c.load<u32>(address+24);c.v[39]=c.load<u32>(address+28);c.r[5]+=32u;}
goto L10185164;
}
L10185164:{ // 8d4266f4 vld1.32 {d20, d21, d22, d23}, [r6]!
c.r[15]=0x10185164u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[40]=c.load<u32>(address+0);c.v[41]=c.load<u32>(address+4);c.v[42]=c.load<u32>(address+8);c.v[43]=c.load<u32>(address+12);c.v[44]=c.load<u32>(address+16);c.v[45]=c.load<u32>(address+20);c.v[46]=c.load<u32>(address+24);c.v[47]=c.load<u32>(address+28);c.r[6]+=32u;}
goto L10185168;
}
L10185168:{ // 740d40f2 vmla.f32 q8, q0, q10
c.r[15]=0x10185168u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[32],fpBinary<float>(c.v[0],c.v[40],2,true),0,true);u32 t1=fpBinary<float>(c.v[33],fpBinary<float>(c.v[1],c.v[41],2,true),0,true);u32 t2=fpBinary<float>(c.v[34],fpBinary<float>(c.v[2],c.v[42],2,true),0,true);u32 t3=fpBinary<float>(c.v[35],fpBinary<float>(c.v[3],c.v[43],2,true),0,true);c.v[32]=t0;c.v[33]=t1;c.v[34]=t2;c.v[35]=t3;}
goto L1018516c;
}
L1018516c:{ // 762d42f2 vmla.f32 q9, q1, q11
c.r[15]=0x1018516cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[36],fpBinary<float>(c.v[4],c.v[44],2,true),0,true);u32 t1=fpBinary<float>(c.v[37],fpBinary<float>(c.v[5],c.v[45],2,true),0,true);u32 t2=fpBinary<float>(c.v[38],fpBinary<float>(c.v[6],c.v[46],2,true),0,true);u32 t3=fpBinary<float>(c.v[39],fpBinary<float>(c.v[7],c.v[47],2,true),0,true);c.v[36]=t0;c.v[37]=t1;c.v[38]=t2;c.v[39]=t3;}
goto L10185170;
}
L10185170:{ // 8d0240f4 vst1.32 {d16, d17, d18, d19}, [r0]!
c.r[15]=0x10185170u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[32]);c.store<u32>(address+4,c.v[33]);c.store<u32>(address+8,c.v[34]);c.store<u32>(address+12,c.v[35]);c.store<u32>(address+16,c.v[36]);c.store<u32>(address+20,c.v[37]);c.store<u32>(address+24,c.v[38]);c.store<u32>(address+28,c.v[39]);c.r[0]+=32u;}
goto L10185174;
}
L10185174:{ // f6ffffea b #0x10185154
c.r[15]=0x10185174u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x10185154u)&~1u;goto L10185154;}
goto L10185178;
}
L10185178:{ // 0480a0e1 mov r8, r4
c.r[15]=0x10185178u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[8]=x;}
goto L1018517c;
}
L1018517c:{ // 078008e2 and r8, r8, #7
c.r[15]=0x1018517cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=(c.r[8]&0x7u);c.r[8]=x;}
goto L10185180;
}
L10185180:{ // 018058e2 subs r8, r8, #1
c.r[15]=0x10185180u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[8]=sum(c,c.r[8],~(0x1u),1u,true);}
goto L10185184;
}
L10185184:{ // edffffba blt #0x10185140
c.r[15]=0x10185184u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,11);
if(execute){c.r[15]=(0x10185140u)&~1u;goto L10185140;}
goto L10185188;
}
L10185188:{ // 0d08a1f4 vld1.32 {d0[0]}, [r1]!
c.r[15]=0x10185188u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[1];c.v[0]=c.load<u32>(address+0);c.r[1]+=4u;}
goto L1018518c;
}
L1018518c:{ // 0d18a5f4 vld1.32 {d1[0]}, [r5]!
c.r[15]=0x1018518cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.v[2]=c.load<u32>(address+0);c.r[5]+=4u;}
goto L10185190;
}
L10185190:{ // 8d18a6f4 vld1.32 {d1[1]}, [r6]!
c.r[15]=0x10185190u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[6];c.v[3]=c.load<u32>(address+0);c.r[6]+=4u;}
goto L10185194;
}
L10185194:{ // 211a00ee vmla.f32 s2, s0, s3
c.r[15]=0x10185194u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[2],fpBinary<float>(c.v[0],c.v[3],2,false),0,false);c.v[2]=t0;}
goto L10185198;
}
L10185198:{ // 0d1880f4 vst1.32 {d1[0]}, [r0]!
c.r[15]=0x10185198u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[0];c.store<u32>(address+0,c.v[2]);c.r[0]+=4u;}
goto L1018519c;
}
L1018519c:{ // f7ffffea b #0x10185180
c.r[15]=0x1018519cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(0x10185180u)&~1u;goto L10185180;}
goto L101851a0;
}
L101851a0:{ // f00fbde8 pop {r4, r5, r6, r7, r8, sb, sl, fp}
c.r[15]=0x101851a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[5]=c.load<u32>(address+4);c.r[6]=c.load<u32>(address+8);c.r[7]=c.load<u32>(address+12);c.r[8]=c.load<u32>(address+16);c.r[9]=c.load<u32>(address+20);c.r[10]=c.load<u32>(address+24);c.r[11]=c.load<u32>(address+28);c.r[13]+=32u;}
goto L101851a4;
}
L101851a4:{ // 1eff2fe1 bx lr
c.r[15]=0x101851a4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
c.r[15]=0x101851a8u;return c.r[15];
}
L101856fc:{ // 7847 bx pc
c.r[15]=0x101856fcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x10185700u)&~1u;return c.r[15];}
c.r[15]=0x101856feu;return c.r[15];
}
L10185700:{ // 00c09fe5 ldr ip, [pc]
c.r[15]=0x10185700u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(0x10185708u+0x0u);c.r[12]=u32(c.load<u32>(address));}
goto L10185704;
}
L10185704:{ // 0ff08ce0 add pc, ip, pc
c.r[15]=0x10185704u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[15]=sum(c,c.r[12],0x1018570cu,0u,false);c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x10185708u;return c.r[15];
}
L10185f6c:{ // 7847 bx pc
c.r[15]=0x10185f6cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x10185f70u)&~1u;return c.r[15];}
c.r[15]=0x10185f6eu;return c.r[15];
}
}
