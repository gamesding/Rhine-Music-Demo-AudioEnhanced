// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10182(ArmState& c){
switch(c.r[15]){
case 0x10182000u:goto L10182000;
case 0x10182004u:goto L10182004;
case 0x10182008u:goto L10182008;
case 0x1018200cu:goto L1018200c;
case 0x10182010u:goto L10182010;
case 0x10182014u:goto L10182014;
case 0x10182018u:goto L10182018;
case 0x1018201cu:goto L1018201c;
case 0x10182020u:goto L10182020;
case 0x10182024u:goto L10182024;
case 0x10182028u:goto L10182028;
case 0x1018202cu:goto L1018202c;
case 0x10182030u:goto L10182030;
case 0x10182034u:goto L10182034;
case 0x10182038u:goto L10182038;
case 0x1018203cu:goto L1018203c;
default:throw std::runtime_error("Untranslated instruction");}
L10182000:{ // 0c2084e5 str r2, [r4, #0xc]
c.r[15]=0x10182000u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0xcu);c.store<u32>(address,c.r[2]);}
goto L10182004;
}
L10182004:{ // 140094e5 ldr r0, [r4, #0x14]
c.r[15]=0x10182004u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0x14u);c.r[0]=u32(c.load<u32>(address));}
goto L10182008;
}
L10182008:{ // 0520a0e1 mov r2, r5
c.r[15]=0x10182008u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 x=c.r[5];c.r[2]=x;}
goto L1018200c;
}
L1018200c:{ // 441094e5 ldr r1, [r4, #0x44]
c.r[15]=0x1018200cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0x44u);c.r[1]=u32(c.load<u32>(address));}
goto L10182010;
}
L10182010:{ // 185084e5 str r5, [r4, #0x18]
c.r[15]=0x10182010u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0x18u);c.store<u32>(address,c.r[5]);}
goto L10182014;
}
L10182014:{ // 1ce084e5 str lr, [r4, #0x1c]
c.r[15]=0x10182014u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0x1cu);c.store<u32>(address,c.r[14]);}
goto L10182018;
}
L10182018:{ // 20c084e5 str ip, [r4, #0x20]
c.r[15]=0x10182018u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[4]+0x20u);c.store<u32>(address,c.r[12]);}
goto L1018201c;
}
L1018201c:{ // 00608de5 str r6, [sp]
c.r[15]=0x1018201cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address,c.r[6]);}
goto L10182020;
}
L10182020:{ // bf76fbeb bl #0x1005fb24
c.r[15]=0x10182020u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[14]=0x10182024u;c.r[15]=(0x1005fb24u)&~1u;return c.r[15];}
goto L10182024;
}
L10182024:{ // 0c209de5 ldr r2, [sp, #0xc]
c.r[15]=0x10182024u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[13]+0xcu);c.r[2]=u32(c.load<u32>(address));}
goto L10182028;
}
L10182028:{ // 003097e5 ldr r3, [r7]
c.r[15]=0x10182028u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[7]+0x0u);c.r[3]=u32(c.load<u32>(address));}
goto L1018202c;
}
L1018202c:{ // 030052e1 cmp r2, r3
c.r[15]=0x1018202cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){(void)sum(c,c.r[2],~(c.r[3]),1u,true);}
goto L10182030;
}
L10182030:{ // 0100001a bne #0x1018203c
c.r[15]=0x10182030u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=condition(c,1);
if(execute){c.r[15]=(0x1018203cu)&~1u;goto L1018203c;}
goto L10182034;
}
L10182034:{ // 14d08de2 add sp, sp, #0x14
c.r[15]=0x10182034u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[13]=sum(c,c.r[13],0x14u,0u,false);}
goto L10182038;
}
L10182038:{ // f080bde8 pop {r4, r5, r6, r7, pc}
c.r[15]=0x10182038u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=c.r[13];c.r[4]=c.load<u32>(address+0);c.r[5]=c.load<u32>(address+4);c.r[6]=c.load<u32>(address+8);c.r[7]=c.load<u32>(address+12);c.r[15]=c.load<u32>(address+16);c.r[13]+=20u;c.r[15]=(c.r[15])&~1u;return c.r[15];}
goto L1018203c;
}
L1018203c:{ // be5bfbeb bl #0x10058f3c
c.r[15]=0x1018203cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[14]=0x10182040u;c.r[15]=(0x10058f3cu)&~1u;return c.r[15];}
c.r[15]=0x10182040u;return c.r[15];
}
}
