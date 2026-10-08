// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_10116(ArmState& c){
switch(c.r[15]){
case 0x10116fd0u:goto L10116fd0;
case 0x10116fd2u:goto L10116fd2;
case 0x10116fd4u:goto L10116fd4;
case 0x10116fd6u:goto L10116fd6;
case 0x10116fd8u:goto L10116fd8;
case 0x10116fdau:goto L10116fda;
case 0x10116fdcu:goto L10116fdc;
case 0x10116fdeu:goto L10116fde;
case 0x10116fe0u:goto L10116fe0;
case 0x10116fe2u:goto L10116fe2;
case 0x10116fe4u:goto L10116fe4;
case 0x10116fe6u:goto L10116fe6;
case 0x10116fe8u:goto L10116fe8;
case 0x10116feau:goto L10116fea;
case 0x10116fecu:goto L10116fec;
case 0x10116ff0u:goto L10116ff0;
case 0x10116ff2u:goto L10116ff2;
case 0x10116ff4u:goto L10116ff4;
case 0x10116ff8u:goto L10116ff8;
case 0x10116ffau:goto L10116ffa;
case 0x10116ffcu:goto L10116ffc;
case 0x10116ffeu:goto L10116ffe;
default:throw std::runtime_error("Untranslated instruction");}
L10116fd0:{ // b0b5 push {r4, r5, r7, lr}
c.r[15]=0x10116fd0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-16u;c.store<u32>(address+0,c.r[4]);c.store<u32>(address+4,c.r[5]);c.store<u32>(address+8,c.r[7]);c.store<u32>(address+12,c.r[14]);c.r[13]-=16u;}
goto L10116fd2;
}
L10116fd2:{ // 02af add r7, sp, #8
c.r[15]=0x10116fd2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x8u,0u,false);}
goto L10116fd4;
}
L10116fd4:{ // 82b0 sub sp, #8
c.r[15]=0x10116fd4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[13]=sum(c,c.r[13],~(0x8u),1u,false);}
goto L10116fd6;
}
L10116fd6:{ // 0546 mov r5, r0
c.r[15]=0x10116fd6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[0];c.r[5]=x;}
goto L10116fd8;
}
L10116fd8:{ // 1448 ldr r0, [pc, #0x50]
c.r[15]=0x10116fd8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x10116fdcu+0x50u);c.r[0]=u32(c.load<u32>(address));}
goto L10116fda;
}
L10116fda:{ // 0c46 mov r4, r1
c.r[15]=0x10116fdau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[1];c.r[4]=x;}
goto L10116fdc;
}
L10116fdc:{ // 002c cmp r4, #0
c.r[15]=0x10116fdcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){(void)sum(c,c.r[4],~(0x0u),1u,true);}
goto L10116fde;
}
L10116fde:{ // 7844 add r0, pc
c.r[15]=0x10116fdeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x10116fe2u,0u,false);}
goto L10116fe0;
}
L10116fe0:{ // 0068 ldr r0, [r0]
c.r[15]=0x10116fe0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L10116fe2;
}
L10116fe2:{ // 0068 ldr r0, [r0]
c.r[15]=0x10116fe2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
goto L10116fe4;
}
L10116fe4:{ // 0190 str r0, [sp, #4]
c.r[15]=0x10116fe4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x4u);c.store<u32>(address,c.r[0]);}
goto L10116fe6;
}
L10116fe6:{ // 15d0 beq #0x10117014
c.r[15]=0x10116fe6u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):condition(c,0);if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(0x10117014u)&~1u;return c.r[15];}
goto L10116fe8;
}
L10116fe8:{ // 2168 ldr r1, [r4]
c.r[15]=0x10116fe8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[4]+0x0u);c.r[1]=u32(c.load<u32>(address));}
goto L10116fea;
}
L10116fea:{ // 2846 mov r0, r5
c.r[15]=0x10116feau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[5];c.r[0]=x;}
goto L10116fec;
}
L10116fec:{ // 45f7a4ef blx #0x1005cf38
c.r[15]=0x10116fecu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x10116ff1u;c.r[15]=(0x1005cf38u)&~1u;return c.r[15];}
goto L10116ff0;
}
L10116ff0:{ // 6168 ldr r1, [r4, #4]
c.r[15]=0x10116ff0u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[4]+0x4u);c.r[1]=u32(c.load<u32>(address));}
goto L10116ff2;
}
L10116ff2:{ // 2846 mov r0, r5
c.r[15]=0x10116ff2u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[5];c.r[0]=x;}
goto L10116ff4;
}
L10116ff4:{ // 45f7a0ef blx #0x1005cf38
c.r[15]=0x10116ff4u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[14]=0x10116ff9u;c.r[15]=(0x1005cf38u)&~1u;return c.r[15];}
goto L10116ff8;
}
L10116ff8:{ // 0d48 ldr r0, [pc, #0x34]
c.r[15]=0x10116ff8u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(0x10116ffcu+0x34u);c.r[0]=u32(c.load<u32>(address));}
goto L10116ffa;
}
L10116ffa:{ // 0199 ldr r1, [sp, #4]
c.r[15]=0x10116ffau;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x4u);c.r[1]=u32(c.load<u32>(address));}
goto L10116ffc;
}
L10116ffc:{ // 7844 add r0, pc
c.r[15]=0x10116ffcu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[0]=sum(c,c.r[0],0x10117000u,0u,false);}
goto L10116ffe;
}
L10116ffe:{ // 0068 ldr r0, [r0]
c.r[15]=0x10116ffeu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[0]+0x0u);c.r[0]=u32(c.load<u32>(address));}
c.r[15]=0x10117000u;return c.r[15];
}
}
