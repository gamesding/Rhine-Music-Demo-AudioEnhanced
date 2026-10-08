// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10155(ArmState& c){
switch(c.r[15]){
case 0x10155000u:goto L10155000;
case 0x10155004u:goto L10155004;
case 0x10155008u:goto L10155008;
case 0x1015500cu:goto L1015500c;
case 0x10155010u:goto L10155010;
case 0x10155014u:goto L10155014;
case 0x10155018u:goto L10155018;
case 0x1015501cu:goto L1015501c;
case 0x10155020u:goto L10155020;
case 0x10155024u:goto L10155024;
case 0x10155028u:goto L10155028;
case 0x1015502cu:goto L1015502c;
case 0x10155030u:goto L10155030;
case 0x10155034u:goto L10155034;
case 0x10155038u:goto L10155038;
case 0x1015503cu:goto L1015503c;
case 0x10155040u:goto L10155040;
case 0x10155044u:goto L10155044;
case 0x10155048u:goto L10155048;
case 0x1015504cu:goto L1015504c;
case 0x10155050u:goto L10155050;
case 0x10155054u:goto L10155054;
case 0x10155058u:goto L10155058;
case 0x1015505cu:goto L1015505c;
case 0x10155060u:goto L10155060;
case 0x10155064u:goto L10155064;
case 0x10155068u:goto L10155068;
case 0x1015506cu:goto L1015506c;
case 0x10155070u:goto L10155070;
case 0x10155074u:goto L10155074;
case 0x10155078u:goto L10155078;
case 0x1015507cu:goto L1015507c;
case 0x10155080u:goto L10155080;
case 0x10155084u:goto L10155084;
case 0x10155088u:goto L10155088;
case 0x1015508cu:goto L1015508c;
case 0x10155090u:goto L10155090;
case 0x10155094u:goto L10155094;
case 0x10155098u:goto L10155098;
case 0x1015509cu:goto L1015509c;
case 0x101550a0u:goto L101550a0;
case 0x101550a4u:goto L101550a4;
case 0x101550a8u:goto L101550a8;
case 0x101550acu:goto L101550ac;
case 0x101550b0u:goto L101550b0;
case 0x101550b4u:goto L101550b4;
case 0x101550b8u:goto L101550b8;
case 0x101550bcu:goto L101550bc;
case 0x101550c0u:goto L101550c0;
case 0x101550c4u:goto L101550c4;
case 0x101550c8u:goto L101550c8;
case 0x101550ccu:goto L101550cc;
case 0x101550d0u:goto L101550d0;
case 0x101550d4u:goto L101550d4;
case 0x101550d8u:goto L101550d8;
case 0x101550dcu:goto L101550dc;
case 0x101550e0u:goto L101550e0;
case 0x101550e4u:goto L101550e4;
default:throw std::runtime_error("Untranslated instruction");}
L10155000:{ // 2c7f27f2 vmin.f32 d7, d7, d28
c.r[15]=0x10155000u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[14],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[15],c.v[57],5,true);c.v[14]=t0;c.v[15]=t1;}
goto L10155004;
}
L10155004:{ // 438a07ee vmls.f32 s16, s14, s6
c.r[15]=0x10155004u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],fpBinary<float>(c.v[14],c.v[6],2,false),1,false);c.v[16]=t0;}
goto L10155008;
}
L10155008:{ // 2e8f08f2 vmax.f32 d8, d8, d30
c.r[15]=0x10155008u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[17],c.v[61],4,true);c.v[16]=t0;c.v[17]=t1;}
goto L1015500c;
}
L1015500c:{ // 2c8f28f2 vmin.f32 d8, d8, d28
c.r[15]=0x1015500cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[17],c.v[57],5,true);c.v[16]=t0;c.v[17]=t1;}
goto L10155010;
}
L10155010:{ // 439a08ee vmls.f32 s18, s16, s6
c.r[15]=0x10155010u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],fpBinary<float>(c.v[16],c.v[6],2,false),1,false);c.v[18]=t0;}
goto L10155014;
}
L10155014:{ // 043053e2 subs r3, r3, #4
c.r[15]=0x10155014u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[3]=sum(c,c.r[3],~(0x4u),1u,true);}
goto L10155018;
}
L10155018:{ // 2e9f09f2 vmax.f32 d9, d9, d30
c.r[15]=0x10155018u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[19],c.v[61],4,true);c.v[18]=t0;c.v[19]=t1;}
goto L1015501c;
}
L1015501c:{ // 2c9f29f2 vmin.f32 d9, d9, d28
c.r[15]=0x1015501cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[19],c.v[57],5,true);c.v[18]=t0;c.v[19]=t1;}
goto L10155020;
}
L10155020:{ // 5a616af2 vorr q11, q5, q5
c.r[15]=0x10155020u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[20]|c.v[20]);u32 t1=(c.v[21]|c.v[21]);u32 t2=(c.v[22]|c.v[22]);u32 t3=(c.v[23]|c.v[23]);c.v[44]=t0;c.v[45]=t1;c.v[46]=t2;c.v[47]=t3;}
goto L10155024;
}
L10155024:{ // 494af0ee vmov.f32 s9, s18
c.r[15]=0x10155024u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[18];c.v[9]=t0;}
goto L10155028;
}
L10155028:{ // 4861baf3 vuzp.32 q3, q4
c.r[15]=0x10155028u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[12];u32 t1=c.v[14];u32 t2=c.v[16];u32 t3=c.v[18];u32 t4=c.v[13];u32 t5=c.v[15];u32 t6=c.v[17];u32 t7=c.v[19];c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;c.v[16]=t4;c.v[17]=t5;c.v[18]=t6;c.v[19]=t7;}
goto L1015502c;
}
L1015502c:{ // 4667bbf3 vcvt.s32.f32 q3, q3
c.r[15]=0x1015502cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpToInt<float>(c.v[12],true,0u,true);u32 t1=fpToInt<float>(c.v[13],true,0u,true);u32 t2=fpToInt<float>(c.v[14],true,0u,true);u32 t3=fpToInt<float>(c.v[15],true,0u,true);c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;}
goto L10155030;
}
L10155030:{ // 8d6a02f4 vst1.32 {d6, d7}, [r2]!
c.r[15]=0x10155030u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[2];c.store<u32>(address+0,c.v[12]);c.store<u32>(address+4,c.v[13]);c.store<u32>(address+8,c.v[14]);c.store<u32>(address+12,c.v[15]);c.r[2]+=16u;}
goto L10155034;
}
L10155034:{ // d6ffffca bgt #0x10154f94
c.r[15]=0x10155034u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,12);
if(execute){c.r[15]=(0x10154f94u)&~1u;return c.r[15];}
goto L10155038;
}
L10155038:{ // 42a9acf3 vmul.f32 q5, q6, d2[0]
c.r[15]=0x10155038u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[24],c.v[4],2,true);u32 t1=fpBinary<float>(c.v[25],c.v[4],2,true);u32 t2=fpBinary<float>(c.v[26],c.v[4],2,true);u32 t3=fpBinary<float>(c.v[27],c.v[4],2,true);c.v[20]=t0;c.v[21]=t1;c.v[22]=t2;c.v[23]=t3;}
goto L1015503c;
}
L1015503c:{ // cc4cf4f2 vext.32 q10, q10, q6, #3
c.r[15]=0x1015503cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[43];u32 t1=c.v[24];u32 t2=c.v[25];u32 t3=c.v[26];c.v[40]=t0;c.v[41]=t1;c.v[42]=t2;c.v[43]=t3;}
goto L10155040;
}
L10155040:{ // e2a1a4f3 vmla.f32 q5, q10, d2[1]
c.r[15]=0x10155040u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[20],fpBinary<float>(c.v[40],c.v[5],2,true),0,true);u32 t1=fpBinary<float>(c.v[21],fpBinary<float>(c.v[41],c.v[5],2,true),0,true);u32 t2=fpBinary<float>(c.v[22],fpBinary<float>(c.v[42],c.v[5],2,true),0,true);u32 t3=fpBinary<float>(c.v[23],fpBinary<float>(c.v[43],c.v[5],2,true),0,true);c.v[20]=t0;c.v[21]=t1;c.v[22]=t2;c.v[23]=t3;}
goto L10155044;
}
L10155044:{ // 61aa05ee vmls.f32 s20, s10, s3
c.r[15]=0x10155044u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[20],fpBinary<float>(c.v[10],c.v[3],2,false),1,false);c.v[20]=t0;}
goto L10155048;
}
L10155048:{ // 61aa4aee vmls.f32 s21, s20, s3
c.r[15]=0x10155048u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[21],fpBinary<float>(c.v[20],c.v[3],2,false),1,false);c.v[21]=t0;}
goto L1015504c;
}
L1015504c:{ // e1ba0aee vmls.f32 s22, s21, s3
c.r[15]=0x1015504cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[22],fpBinary<float>(c.v[21],c.v[3],2,false),1,false);c.v[22]=t0;}
goto L10155050;
}
L10155050:{ // 61ba4bee vmls.f32 s23, s22, s3
c.r[15]=0x10155050u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[23],fpBinary<float>(c.v[22],c.v[3],2,false),1,false);c.v[23]=t0;}
goto L10155054;
}
L10155054:{ // 5c416cf2 vorr q10, q6, q6
c.r[15]=0x10155054u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[24]|c.v[24]);u32 t1=(c.v[25]|c.v[25]);u32 t2=(c.v[26]|c.v[26]);u32 t3=(c.v[27]|c.v[27]);c.v[40]=t0;c.v[41]=t1;c.v[42]=t2;c.v[43]=t3;}
goto L10155058;
}
L10155058:{ // 6b5ab0ee vmov.f32 s10, s23
c.r[15]=0x10155058u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[23];c.v[10]=t0;}
goto L1015505c;
}
L1015505c:{ // 6369aaf3 vmul.f32 q3, q5, d3[1]
c.r[15]=0x1015505cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[20],c.v[7],2,true);u32 t1=fpBinary<float>(c.v[21],c.v[7],2,true);u32 t2=fpBinary<float>(c.v[22],c.v[7],2,true);u32 t3=fpBinary<float>(c.v[23],c.v[7],2,true);c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;}
goto L10155060;
}
L10155060:{ // ca6cf6f2 vext.32 q11, q11, q5, #3
c.r[15]=0x10155060u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[47];u32 t1=c.v[20];u32 t2=c.v[21];u32 t3=c.v[22];c.v[44]=t0;c.v[45]=t1;c.v[46]=t2;c.v[47]=t3;}
goto L10155064;
}
L10155064:{ // c461a6f3 vmla.f32 q3, q11, d4[0]
c.r[15]=0x10155064u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[12],fpBinary<float>(c.v[44],c.v[8],2,true),0,true);u32 t1=fpBinary<float>(c.v[13],fpBinary<float>(c.v[45],c.v[8],2,true),0,true);u32 t2=fpBinary<float>(c.v[14],fpBinary<float>(c.v[46],c.v[8],2,true),0,true);u32 t3=fpBinary<float>(c.v[15],fpBinary<float>(c.v[47],c.v[8],2,true),0,true);c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;}
goto L10155068;
}
L10155068:{ // c861baf3 vzip.32 q3, q4
c.r[15]=0x10155068u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[12];u32 t1=c.v[16];u32 t2=c.v[13];u32 t3=c.v[17];u32 t4=c.v[14];u32 t5=c.v[18];u32 t6=c.v[15];u32 t7=c.v[19];c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;c.v[16]=t4;c.v[17]=t5;c.v[18]=t6;c.v[19]=t7;}
goto L1015506c;
}
L1015506c:{ // c36a04ee vmls.f32 s12, s9, s6
c.r[15]=0x1015506cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[12],fpBinary<float>(c.v[9],c.v[6],2,false),1,false);c.v[12]=t0;}
goto L10155070;
}
L10155070:{ // 2e6f06f2 vmax.f32 d6, d6, d30
c.r[15]=0x10155070u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[12],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[13],c.v[61],4,true);c.v[12]=t0;c.v[13]=t1;}
goto L10155074;
}
L10155074:{ // 2c6f26f2 vmin.f32 d6, d6, d28
c.r[15]=0x10155074u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[12],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[13],c.v[57],5,true);c.v[12]=t0;c.v[13]=t1;}
goto L10155078;
}
L10155078:{ // 437a06ee vmls.f32 s14, s12, s6
c.r[15]=0x10155078u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[14],fpBinary<float>(c.v[12],c.v[6],2,false),1,false);c.v[14]=t0;}
goto L1015507c;
}
L1015507c:{ // 2e7f07f2 vmax.f32 d7, d7, d30
c.r[15]=0x1015507cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[14],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[15],c.v[61],4,true);c.v[14]=t0;c.v[15]=t1;}
goto L10155080;
}
L10155080:{ // 2c7f27f2 vmin.f32 d7, d7, d28
c.r[15]=0x10155080u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[14],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[15],c.v[57],5,true);c.v[14]=t0;c.v[15]=t1;}
goto L10155084;
}
L10155084:{ // 438a07ee vmls.f32 s16, s14, s6
c.r[15]=0x10155084u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],fpBinary<float>(c.v[14],c.v[6],2,false),1,false);c.v[16]=t0;}
goto L10155088;
}
L10155088:{ // 2e8f08f2 vmax.f32 d8, d8, d30
c.r[15]=0x10155088u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[17],c.v[61],4,true);c.v[16]=t0;c.v[17]=t1;}
goto L1015508c;
}
L1015508c:{ // 2c8f28f2 vmin.f32 d8, d8, d28
c.r[15]=0x1015508cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[16],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[17],c.v[57],5,true);c.v[16]=t0;c.v[17]=t1;}
goto L10155090;
}
L10155090:{ // 439a08ee vmls.f32 s18, s16, s6
c.r[15]=0x10155090u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],fpBinary<float>(c.v[16],c.v[6],2,false),1,false);c.v[18]=t0;}
goto L10155094;
}
L10155094:{ // 043053e2 subs r3, r3, #4
c.r[15]=0x10155094u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[3]=sum(c,c.r[3],~(0x4u),1u,true);}
goto L10155098;
}
L10155098:{ // 2e9f09f2 vmax.f32 d9, d9, d30
c.r[15]=0x10155098u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],c.v[60],4,true);u32 t1=fpBinary<float>(c.v[19],c.v[61],4,true);c.v[18]=t0;c.v[19]=t1;}
goto L1015509c;
}
L1015509c:{ // 2c9f29f2 vmin.f32 d9, d9, d28
c.r[15]=0x1015509cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpBinary<float>(c.v[18],c.v[56],5,true);u32 t1=fpBinary<float>(c.v[19],c.v[57],5,true);c.v[18]=t0;c.v[19]=t1;}
goto L101550a0;
}
L101550a0:{ // 5a616af2 vorr q11, q5, q5
c.r[15]=0x101550a0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[20]|c.v[20]);u32 t1=(c.v[21]|c.v[21]);u32 t2=(c.v[22]|c.v[22]);u32 t3=(c.v[23]|c.v[23]);c.v[44]=t0;c.v[45]=t1;c.v[46]=t2;c.v[47]=t3;}
goto L101550a4;
}
L101550a4:{ // 494af0ee vmov.f32 s9, s18
c.r[15]=0x101550a4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[18];c.v[9]=t0;}
goto L101550a8;
}
L101550a8:{ // 4861baf3 vuzp.32 q3, q4
c.r[15]=0x101550a8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=c.v[12];u32 t1=c.v[14];u32 t2=c.v[16];u32 t3=c.v[18];u32 t4=c.v[13];u32 t5=c.v[15];u32 t6=c.v[17];u32 t7=c.v[19];c.v[12]=t0;c.v[13]=t1;c.v[14]=t2;c.v[15]=t3;c.v[16]=t4;c.v[17]=t5;c.v[18]=t6;c.v[19]=t7;}
goto L101550ac;
}
L101550ac:{ // 4627fbf3 vcvt.s32.f32 q9, q3
c.r[15]=0x101550acu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=fpToInt<float>(c.v[12],true,0u,true);u32 t1=fpToInt<float>(c.v[13],true,0u,true);u32 t2=fpToInt<float>(c.v[14],true,0u,true);u32 t3=fpToInt<float>(c.v[15],true,0u,true);c.v[36]=t0;c.v[37]=t1;c.v[38]=t2;c.v[39]=t3;}
goto L101550b0;
}
L101550b0:{ // 8d2a42f4 vst1.32 {d18, d19}, [r2]!
c.r[15]=0x101550b0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[2];c.store<u32>(address+0,c.v[36]);c.store<u32>(address+4,c.v[37]);c.store<u32>(address+8,c.v[38]);c.store<u32>(address+12,c.v[39]);c.r[2]+=16u;}
goto L101550b4;
}
L101550b4:{ // 0450a0e1 mov r5, r4
c.r[15]=0x101550b4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[4];c.r[5]=x;}
goto L101550b8;
}
L101550b8:{ // f0e120f2 vorr q7, q8, q8
c.r[15]=0x101550b8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[32]|c.v[32]);u32 t1=(c.v[33]|c.v[33]);u32 t2=(c.v[34]|c.v[34]);u32 t3=(c.v[35]|c.v[35]);c.v[28]=t0;c.v[29]=t1;c.v[30]=t2;c.v[31]=t3;}
goto L101550bc;
}
L101550bc:{ // 01fae5ec vstmia r5!, {s31}
c.r[15]=0x101550bcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[31]);c.r[5]+=4u;}
goto L101550c0;
}
L101550c0:{ // 015ae5ec vstmia r5!, {s11}
c.r[15]=0x101550c0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[11]);c.r[5]+=4u;}
goto L101550c4;
}
L101550c4:{ // f4e124f2 vorr q7, q10, q10
c.r[15]=0x101550c4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[40]|c.v[40]);u32 t1=(c.v[41]|c.v[41]);u32 t2=(c.v[42]|c.v[42]);u32 t3=(c.v[43]|c.v[43]);c.v[28]=t0;c.v[29]=t1;c.v[30]=t2;c.v[31]=t3;}
goto L101550c8;
}
L101550c8:{ // 01fae5ec vstmia r5!, {s31}
c.r[15]=0x101550c8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[31]);c.r[5]+=4u;}
goto L101550cc;
}
L101550cc:{ // 015aa5ec vstmia r5!, {s10}
c.r[15]=0x101550ccu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[10]);c.r[5]+=4u;}
goto L101550d0;
}
L101550d0:{ // f6e126f2 vorr q7, q11, q11
c.r[15]=0x101550d0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 t0=(c.v[44]|c.v[44]);u32 t1=(c.v[45]|c.v[45]);u32 t2=(c.v[46]|c.v[46]);u32 t3=(c.v[47]|c.v[47]);c.v[28]=t0;c.v[29]=t1;c.v[30]=t2;c.v[31]=t3;}
goto L101550d4;
}
L101550d4:{ // 01fae5ec vstmia r5!, {s31}
c.r[15]=0x101550d4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[31]);c.r[5]+=4u;}
goto L101550d8;
}
L101550d8:{ // 014ae5ec vstmia r5!, {s9}
c.r[15]=0x101550d8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[5];c.store<u32>(address+0,c.v[9]);c.r[5]+=4u;}
goto L101550dc;
}
L101550dc:{ // 0000a0e3 mov r0, #0
c.r[15]=0x101550dcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=0x0u;c.r[0]=x;}
goto L101550e0;
}
L101550e0:{ // 108bbdec vpop {d8, d9, d10, d11, d12, d13, d14, d15}
c.r[15]=0x101550e0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[13];c.v[16]=c.load<u32>(address+0);c.v[17]=c.load<u32>(address+4);c.v[18]=c.load<u32>(address+8);c.v[19]=c.load<u32>(address+12);c.v[20]=c.load<u32>(address+16);c.v[21]=c.load<u32>(address+20);c.v[22]=c.load<u32>(address+24);c.v[23]=c.load<u32>(address+28);c.v[24]=c.load<u32>(address+32);c.v[25]=c.load<u32>(address+36);c.v[26]=c.load<u32>(address+40);c.v[27]=c.load<u32>(address+44);c.v[28]=c.load<u32>(address+48);c.v[29]=c.load<u32>(address+52);c.v[30]=c.load<u32>(address+56);c.v[31]=c.load<u32>(address+60);c.r[13]+=64u;}
goto L101550e4;
}
L101550e4:{ // f09fbde8 pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
c.r[15]=0x101550e4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[5]=c.load<u32>(address+4);c.r[6]=c.load<u32>(address+8);c.r[7]=c.load<u32>(address+12);c.r[8]=c.load<u32>(address+16);c.r[9]=c.load<u32>(address+20);c.r[10]=c.load<u32>(address+24);c.r[11]=c.load<u32>(address+28);c.r[12]=c.load<u32>(address+32);c.r[15]=c.load<u32>(address+36);c.r[13]+=40u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x101550e8u;return c.r[15];
}
}
