import os,sys,importlib.util,struct,json,math
from pathlib import Path
root=Path(__file__).resolve().parents[3]
sys.path[:0]=[str(root/'scripts/sony-walkman'),str(root/'.tools/sony-research/python'),str(root/'.tools/desktop-runtime/unicorn')]
os.environ['SONY_WALKMAN_ASSETS']=str(root/'vendor/sony-walkman')
os.environ.pop('SONY_WALKMAN_X86_DLL',None)
def module(name):
 s=importlib.util.spec_from_file_location(name,root/'scripts/sony-walkman/arm_runtime.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
ref=module('ref')
os.environ['SONY_WALKMAN_X86_DLL']=str(root/'vendor/sony-walkman-x86/sony-dsp-x86.dll')
nat=module('nat')
name='_ZN3pst8services5sound6mobile6DseeAi10InitEffectEv';args=None
if '--vinyl' in sys.argv or '--ai-block' in sys.argv:
 import effects
 effects.arm=ref;original_call=ref.call
 class Pause(Exception):pass
 def capture(n,*values,**kw):
  global args
  if n==target:args=values;raise Pause()
  return original_call(n,*values,**kw)
 if '--ai-block' in sys.argv:
  chain,_=effects.create_chain(44100,True,0,0)
  samples=[]
  for i in range(256):
   l=.21*math.sin(i*.113)+.14*math.sin(i*.701);r=.17*math.cos(i*.173)-.09*math.sin(i*.917)
   if i%127==0:l,r=(1 if i%2 else -1),(-.999969 if i%2 else .999969)
   samples.append(struct.pack('<2f',l,r))
  content=b''.join(samples);effects.feed_chain(chain,content[:192*8]);target='EffectExecuteDSX'
  ref.call=capture
  try:effects.feed_chain(chain,content[192*8:])
  except Pause:pass
 else:
  target='EffectInitRealVinyl';ref.call=capture
  try:effects.create_chain(44100,True,2,1)
  except Pause:pass
 ref.call=original_call;name=target;nat.top=ref.top
 for base,_,_,_ in ref.libraries:nat.engine.mem_write(base,bytes(ref.engine.mem_read(base,0x500000)))
 for base,length in [(ref.heap,ref.top-ref.heap),(ref.stack,0x100000),(ref.tls,4096)]:nat.engine.mem_write(base,bytes(ref.engine.mem_read(base,length)))
 for k in [getattr(ref,f'UC_ARM_REG_R{i}') for i in range(13)]+[getattr(ref,f'UC_ARM_REG_D{i}') for i in range(32)]:nat.engine.reg_write(k,ref.engine.reg_read(k))
for arm in (ref,nat):
 if args is None:
  obj=arm.allocate(0x50000);arm.engine.mem_write(obj+0x3effc,(arm.root/'DseeAi.bin').read_bytes());arm.engine.mem_write(obj+0x3efe8,(arm.root/'DseeAi.dcfg').read_bytes());values=[obj]
 else:values=args
 arm.engine.reg_write(arm.UC_ARM_REG_SP,arm.stack+0xf0000);arm.engine.reg_write(arm.UC_ARM_REG_LR,arm.stop)
 for k in range(4):arm.engine.reg_write(arm.registers[k],values[k] if k<len(values) else 0)
 for k,v in enumerate(values[4:]):arm.write32(arm.stack+0xf0000+k*4,v)
entry=ref.base+ref.byname[name]['value'];nat.engine.reg_write(nat.UC_ARM_REG_PC,entry&~1)
for key in [ref.UC_ARM_REG_CPSR,ref.UC_ARM_REG_FPSCR]:nat.engine.reg_write(key,ref.engine.reg_read(key))
history=[];count=0
def check(engine,a,size,_):
 global count
 count+=1;history.append(hex(a));history[:]=history[-8:]
 pc=nat.engine.reg_read(nat.UC_ARM_REG_PC)
 for skip in range(4):
  if pc==a:break
  limit=nat.engine.dll.sony_get(nat.engine.state,19)+1
  result=nat.engine.dll.sony_execute(nat.engine.state,pc,ref.stop,limit,False)
  if result==2 and 'Instruction budget' not in nat.engine.dll.sony_error().decode():raise ValueError(nat.engine.dll.sony_error().decode()+f' {nat.engine.reg_read(nat.UC_ARM_REG_PC):#x}')
  pc=nat.engine.reg_read(nat.UC_ARM_REG_PC)
 if a in ref.stubnames:nat.hook(nat.engine,a,size,None)
 ids=[getattr(ref,f'UC_ARM_REG_R{i}') for i in range(13)]+[ref.UC_ARM_REG_SP,ref.UC_ARM_REG_LR]
 ids += [getattr(ref,f'UC_ARM_REG_D{i}') for i in range(32)]
 differences=[]
 if pc!=a:differences.append(['pc',hex(a),hex(pc)])
 for key in ids:
  v,w=ref.engine.reg_read(key),nat.engine.reg_read(key)
  if v!=w:differences.append([key,hex(v),hex(w)])
 for key in [ref.UC_ARM_REG_CPSR,ref.UC_ARM_REG_FPSCR]:
  v,w=ref.engine.reg_read(key)&0xf0000000,nat.engine.reg_read(key)&0xf0000000
  if v!=w:differences.append([key,hex(v),hex(w)])
 if differences:raise ValueError(json.dumps({'count':count,'history':history,'diff':differences[:10]}))
 if a in ref.stubnames:
  nat.engine.reg_write(nat.UC_ARM_REG_PC,nat.engine.reg_read(nat.UC_ARM_REG_LR)&~1);return
 limit=nat.engine.dll.sony_get(nat.engine.state,19)+1
 result=nat.engine.dll.sony_execute(nat.engine.state,a,ref.stop,limit,False)
 if result==2 and 'Instruction budget' not in nat.engine.dll.sony_error().decode():raise ValueError(nat.engine.dll.sony_error().decode()+f' {nat.engine.reg_read(nat.UC_ARM_REG_PC):#x}')
ref.engine.hook_add(ref.uc.UC_HOOK_CODE,check)
try:ref.engine.emu_start(entry,ref.stop,count=20_000_000);print('MATCH',count)
except Exception as e:print(e);print('LAST',history)
