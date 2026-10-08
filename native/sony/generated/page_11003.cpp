// Generated from pinned Sony ARM instruction bytes. Do not edit.
#include "../arm-state.hpp"
u32 page_11003(ArmState& c){
switch(c.r[15]){
case 0x11003c0cu:goto L11003c0c;
case 0x11003c10u:goto L11003c10;
case 0x11003c14u:goto L11003c14;
case 0x11003e70u:goto L11003e70;
case 0x11003e72u:goto L11003e72;
case 0x11003e74u:goto L11003e74;
case 0x11003c4cu:goto L11003c4c;
case 0x11003e78u:goto L11003e78;
case 0x11003c50u:goto L11003c50;
case 0x11003e7cu:goto L11003e7c;
case 0x11003c54u:goto L11003c54;
case 0x11003e7eu:goto L11003e7e;
case 0x11003e82u:goto L11003e82;
default:throw std::runtime_error("Untranslated instruction");}
L11003c0c:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x11003c0cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x11003c14u,0x0u,0u,false);}
goto L11003c10;
}
L11003c10:{ // 6dca8ce2 add ip, ip, #0x6d000
c.r[15]=0x11003c10u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x6d000u,0u,false);}
goto L11003c14;
}
L11003c14:{ // 9cf3bce5 ldr pc, [ip, #0x39c]!
c.r[15]=0x11003c14u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x39cu);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x11003c18u;return c.r[15];
}
L11003c4c:{ // 00c68fe2 add ip, pc, #0, #12
c.r[15]=0x11003c4cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,0x11003c54u,0x0u,0u,false);}
goto L11003c50;
}
L11003c50:{ // 6dca8ce2 add ip, ip, #0x6d000
c.r[15]=0x11003c50u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){c.r[12]=sum(c,c.r[12],0x6d000u,0u,false);}
goto L11003c54;
}
L11003c54:{ // 70f3bce5 ldr pc, [ip, #0x370]!
c.r[15]=0x11003c54u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=0;bool execute=true;
if(execute){u32 address=(c.r[12]+0x370u);c.r[15]=u32(c.load<u32>(address));c.r[12]=address;c.r[15]=(c.r[15])&~1u;return c.r[15];}
c.r[15]=0x11003c58u;return c.r[15];
}
L11003e70:{ // 80b4 push {r7}
c.r[15]=0x11003e70u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=c.r[13]-4u;c.store<u32>(address+0,c.r[7]);c.r[13]-=4u;}
goto L11003e72;
}
L11003e72:{ // 00af add r7, sp, #0
c.r[15]=0x11003e72u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[7]=sum(c,c.r[13],0x0u,0u,false);}
goto L11003e74;
}
L11003e74:{ // f1ee100a vmrs r0, fpscr
c.r[15]=0x11003e74u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.fpscr|=nativeFpFlags();c.r[0]=c.fpscr;}
goto L11003e78;
}
L11003e78:{ // 00f44000 and r0, r0, #0xc00000
c.r[15]=0x11003e78u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=(c.r[0]&0xc00000u);c.r[0]=x;}
goto L11003e7c;
}
L11003e7c:{ // bd46 mov sp, r7
c.r[15]=0x11003e7cu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 x=c.r[7];c.r[13]=x;}
goto L11003e7e;
}
L11003e7e:{ // 5df8047b ldr r7, [sp], #4
c.r[15]=0x11003e7eu;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){u32 address=(c.r[13]+0x0u);c.r[7]=u32(c.load<u32>(address));c.r[13]=c.r[13]+0x4u;}
goto L11003e82;
}
L11003e82:{ // 7047 bx lr
c.r[15]=0x11003e82u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");
u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):true;if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;
if(execute){c.r[15]=(c.r[14])&~1u;return c.r[15];}
c.r[15]=0x11003e84u;return c.r[15];
}
}
