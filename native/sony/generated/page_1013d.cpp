// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_1013d(ArmState& c){
switch(c.r[15]){
case 0x1013d002u:goto L1013d002;
case 0x1013d004u:goto L1013d004;
case 0x1013d006u:goto L1013d006;
case 0x1013d00au:goto L1013d00a;
case 0x1013d00eu:goto L1013d00e;
case 0x1013d012u:goto L1013d012;
case 0x1013d014u:goto L1013d014;
case 0x1013d018u:goto L1013d018;
case 0x1013d01au:goto L1013d01a;
case 0x1013d01eu:goto L1013d01e;
case 0x1013d022u:goto L1013d022;
case 0x1013d024u:goto L1013d024;
case 0x1013d028u:goto L1013d028;
case 0x1013d02cu:goto L1013d02c;
case 0x1013d030u:goto L1013d030;
case 0x1013d032u:goto L1013d032;
case 0x1013d034u:goto L1013d034;
case 0x1013d036u:goto L1013d036;
case 0x1013d03au:goto L1013d03a;
case 0x1013d03cu:goto L1013d03c;
case 0x1013d040u:goto L1013d040;
case 0x1013d042u:goto L1013d042;
case 0x1013d046u:goto L1013d046;
case 0x1013d048u:goto L1013d048;
case 0x1013d04au:goto L1013d04a;
case 0x1013d04eu:goto L1013d04e;
case 0x1013d052u:goto L1013d052;
case 0x1013d054u:goto L1013d054;
case 0x1013d056u:goto L1013d056;
case 0x1013d05au:goto L1013d05a;
case 0x1013d05cu:goto L1013d05c;
case 0x1013d060u:goto L1013d060;
case 0x1013d064u:goto L1013d064;
case 0x1013d086u:goto L1013d086;
case 0x1013d088u:goto L1013d088;
case 0x1013d08cu:goto L1013d08c;
case 0x1013d066u:goto L1013d066;
case 0x1013d068u:goto L1013d068;
case 0x1013d06au:goto L1013d06a;
case 0x1013d06cu:goto L1013d06c;
case 0x1013d06eu:goto L1013d06e;
case 0x1013d070u:goto L1013d070;
case 0x1013d072u:goto L1013d072;
case 0x1013d076u:goto L1013d076;
case 0x1013d078u:goto L1013d078;
case 0x1013d07au:goto L1013d07a;
case 0x1013d07eu:goto L1013d07e;
case 0x1013d080u:goto L1013d080;
case 0x1013d084u:goto L1013d084;
default:throw std::runtime_error("Untranslated instruction");}
L1013d002:{ // 0b90 str r0, [sp, #0x2c]
c.r[15]=0x1013d002u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x2cu);c.store<u32>(address,c.r[0]);}
goto L1013d004;
}
L1013d004:{ // 0d95 str r5, [sp, #0x34]
c.r[15]=0x1013d004u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x34u);c.store<u32>(address,c.r[5]);}
goto L1013d006;
}
L1013d006:{ // 21f7baea blx #0x1005e57c
c.r[15]=0x1013d006u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013d00bu;c.r[15]=(0x1005e57cu)&~1u;return c.r[15];}
goto L1013d00a;
}
L1013d00a:{ // 04f57a32 add.w r2, r4, #0x3e800
c.r[15]=0x1013d00au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[4],0x3e800u,0u,false);}
goto L1013d00e;
}
L1013d00e:{ // 04f57b31 add.w r1, r4, #0x3ec00
c.r[15]=0x1013d00eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[4],0x3ec00u,0u,false);}
goto L1013d012;
}
L1013d012:{ // 0c90 str r0, [sp, #0x30]
c.r[15]=0x1013d012u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x30u);c.store<u32>(address,c.r[0]);}
goto L1013d014;
}
L1013d014:{ // 4ff0ff30 mov.w r0, #-1
c.r[15]=0x1013d014u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xffffffffu;c.r[0]=x;}
goto L1013d018;
}
L1013d018:{ // 0a95 str r5, [sp, #0x28]
c.r[15]=0x1013d018u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x28u);c.store<u32>(address,c.r[5]);}
goto L1013d01a;
}
L1013d01a:{ // 0df11c0c add.w ip, sp, #0x1c
c.r[15]=0x1013d01au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[12]=sum(c,c.r[13],0x1cu,0u,false);}
goto L1013d01e;
}
L1013d01e:{ // 02f5fd62 add.w r2, r2, #0x7e8
c.r[15]=0x1013d01eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],0x7e8u,0u,false);}
goto L1013d022;
}
L1013d022:{ // 09ad add r5, sp, #0x24
c.r[15]=0x1013d022u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[5]=sum(c,c.r[13],0x24u,0u,false);}
goto L1013d024;
}
L1013d024:{ // cde90800 strd r0, r0, [sp, #0x20]
c.r[15]=0x1013d024u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x20u);c.store<u32>(address+0,c.r[0]);c.store<u32>(address+4,c.r[0]);}
goto L1013d028;
}
L1013d028:{ // 4ef66020 movw r0, #0xea60
c.r[15]=0x1013d028u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xea60u;c.r[0]=x;}
goto L1013d02c;
}
L1013d02c:{ // 01f57f71 add.w r1, r1, #0x3fc
c.r[15]=0x1013d02cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[1],0x3fcu,0u,false);}
goto L1013d030;
}
L1013d030:{ // 08ab add r3, sp, #0x20
c.r[15]=0x1013d030u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[13],0x20u,0u,false);}
goto L1013d032;
}
L1013d032:{ // 0790 str r0, [sp, #0x1c]
c.r[15]=0x1013d032u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x1cu);c.store<u32>(address,c.r[0]);}
goto L1013d034;
}
L1013d034:{ // 0aa8 add r0, sp, #0x28
c.r[15]=0x1013d034u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[13],0x28u,0u,false);}
goto L1013d036;
}
L1013d036:{ // cde90005 strd r0, r5, [sp]
c.r[15]=0x1013d036u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address+0,c.r[0]);c.store<u32>(address+4,c.r[5]);}
goto L1013d03a;
}
L1013d03a:{ // 2046 mov r0, r4
c.r[15]=0x1013d03au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[4];c.r[0]=x;}
goto L1013d03c;
}
L1013d03c:{ // cde90232 strd r3, r2, [sp, #8]
c.r[15]=0x1013d03cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x8u);c.store<u32>(address+0,c.r[3]);c.store<u32>(address+4,c.r[2]);}
goto L1013d040;
}
L1013d040:{ // 0daa add r2, sp, #0x34
c.r[15]=0x1013d040u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[13],0x34u,0u,false);}
goto L1013d042;
}
L1013d042:{ // cde9041c strd r1, ip, [sp, #0x10]
c.r[15]=0x1013d042u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x10u);c.store<u32>(address+0,c.r[1]);c.store<u32>(address+4,c.r[12]);}
goto L1013d046;
}
L1013d046:{ // 0ea9 add r1, sp, #0x38
c.r[15]=0x1013d046u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[13],0x38u,0u,false);}
goto L1013d048;
}
L1013d048:{ // 0cab add r3, sp, #0x30
c.r[15]=0x1013d048u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[13],0x30u,0u,false);}
goto L1013d04a;
}
L1013d04a:{ // cdf81880 str.w r8, [sp, #0x18]
c.r[15]=0x1013d04au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x18u);c.store<u32>(address,c.r[8]);}
goto L1013d04e;
}
L1013d04e:{ // 21f79cea blx #0x1005e588
c.r[15]=0x1013d04eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013d053u;c.r[15]=(0x1005e588u)&~1u;return c.r[15];}
goto L1013d052;
}
L1013d052:{ // 4846 mov r0, sb
c.r[15]=0x1013d052u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[9];c.r[0]=x;}
goto L1013d054;
}
L1013d054:{ // 4146 mov r1, r8
c.r[15]=0x1013d054u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[8];c.r[1]=x;}
goto L1013d056;
}
L1013d056:{ // 4ef6a822 movw r2, #0xeaa8
c.r[15]=0x1013d056u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0xeaa8u;c.r[2]=x;}
goto L1013d05a;
}
L1013d05a:{ // 0123 movs r3, #1
c.r[15]=0x1013d05au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1013d05c;
}
L1013d05c:{ // 21f79aea blx #0x1005e594
c.r[15]=0x1013d05cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013d061u;c.r[15]=(0x1005e594u)&~1u;return c.r[15];}
goto L1013d060;
}
L1013d060:{ // 10ea0a0f tst.w r0, sl
c.r[15]=0x1013d060u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[0]&c.r[10]);nz(c,x);}
goto L1013d064;
}
L1013d064:{ // 0fd0 beq #0x1013d086
c.r[15]=0x1013d064u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1013d086u)&~1u;goto L1013d086;}
goto L1013d066;
}
L1013d066:{ // 134b ldr r3, [pc, #0x4c]
c.r[15]=0x1013d066u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013d068u+0x4cu);c.r[3]=u32(c.load<u32>(address));}
goto L1013d068;
}
L1013d068:{ // 1049 ldr r1, [pc, #0x40]
c.r[15]=0x1013d068u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013d06cu+0x40u);c.r[1]=u32(c.load<u32>(address));}
goto L1013d06a;
}
L1013d06a:{ // 114a ldr r2, [pc, #0x44]
c.r[15]=0x1013d06au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x1013d06cu+0x44u);c.r[2]=u32(c.load<u32>(address));}
goto L1013d06c;
}
L1013d06c:{ // 7b44 add r3, pc
c.r[15]=0x1013d06cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[3]=sum(c,c.r[3],0x1013d070u,0u,false);}
goto L1013d06e;
}
L1013d06e:{ // 7944 add r1, pc
c.r[15]=0x1013d06eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[1]=sum(c,c.r[1],0x1013d072u,0u,false);}
goto L1013d070;
}
L1013d070:{ // 7a44 add r2, pc
c.r[15]=0x1013d070u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[2]=sum(c,c.r[2],0x1013d074u,0u,false);}
goto L1013d072;
}
L1013d072:{ // cde90023 strd r2, r3, [sp]
c.r[15]=0x1013d072u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.store<u32>(address+0,c.r[2]);c.store<u32>(address+4,c.r[3]);}
goto L1013d076;
}
L1013d076:{ // 0290 str r0, [sp, #8]
c.r[15]=0x1013d076u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x8u);c.store<u32>(address,c.r[0]);}
goto L1013d078;
}
L1013d078:{ // 0320 movs r0, #3
c.r[15]=0x1013d078u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x3u;c.r[0]=x;if((!oldIt))nz(c,x);}
goto L1013d07a;
}
L1013d07a:{ // 4ff4c072 mov.w r2, #0x180
c.r[15]=0x1013d07au;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x180u;c.r[2]=x;}
goto L1013d07e;
}
L1013d07e:{ // 0023 movs r3, #0
c.r[15]=0x1013d07eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x0u;c.r[3]=x;if((!oldIt))nz(c,x);}
goto L1013d080;
}
L1013d080:{ // 1bf7b6ef blx #0x10058ff0
c.r[15]=0x1013d080u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013d085u;c.r[15]=(0x10058ff0u)&~1u;return c.r[15];}
goto L1013d084;
}
L1013d084:{ // 0126 movs r6, #1
c.r[15]=0x1013d084u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=0x1u;c.r[6]=x;if((!oldIt))nz(c,x);}
goto L1013d086;
}
L1013d086:{ // 4046 mov r0, r8
c.r[15]=0x1013d086u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[8];c.r[0]=x;}
goto L1013d088;
}
L1013d088:{ // 1bf764ef blx #0x10058f54
c.r[15]=0x1013d088u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x1013d08du;c.r[15]=(0x10058f54u)&~1u;return c.r[15];}
goto L1013d08c;
}
L1013d08c:{ // 9be7 b #0x1013cfc6
c.r[15]=0x1013d08cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x1013cfc6u)&~1u;return c.r[15];}
c.r[15]=0x1013d08eu;return c.r[15];
}
}
