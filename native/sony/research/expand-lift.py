import os,sys,json,collections,struct
from pathlib import Path
root=Path(__file__).resolve().parents[3]
os.environ['SONY_WALKMAN_ASSETS']=str(root/'vendor/sony-walkman');os.environ.pop('SONY_WALKMAN_X86_DLL',None)
reference=root/('.tools/desktop-runtime/unicorn' if sys.maxsize>2**32 else '.tools/walkman/python')
sys.path[:0]=[str(root/'scripts/sony-walkman'),str(root/'.tools/sony-research/python'),str(reference)]
import arm_runtime as arm
import capstone
path=root/'.tools/walkman/native-trace.json';record=json.loads(path.read_text());items=record['instructions'];queue=collections.deque()
for i in list(items.values()):queue.append((i['address'],i['thumb']))
for s in arm.symbols:
 if s['index'] and s['name'].startswith('Effect') and any(x in s['name'] for x in ('DCPhaseLinearizer','DSX','RealVinyl')):
  queue.append((arm.base+(s['value']&~1),bool(s['value']&1)))
mds={mode:capstone.Cs(capstone.CS_ARCH_ARM,mode) for mode in (capstone.CS_MODE_ARM,capstone.CS_MODE_THUMB)}
for md in mds.values():md.detail=True
seen=set();extra=0
noreturn=set()
for base,raw,ss,syms in arm.libraries:
 h=struct.unpack_from('<HHIIIIIHHHHHH',raw,16);sn=ss[h[12]];names=raw[sn[4]:sn[4]+sn[5]]
 section=lambda s:names[s[0]:].split(b'\0',1)[0]
 plt=next((s for s in ss if section(s)==b'.plt'),None)
 for s in ss:
  if plt and section(s)==b'.rel.plt':
   for k,pos in enumerate(range(s[4],s[4]+s[5],s[9])):
    info=struct.unpack_from('<I',raw,pos+4)[0];name=syms[info>>8]['name']
    if name in ('__stack_chk_fail','abort','exit','__cxa_throw','_ZSt9terminatev'):noreturn.add(base+plt[3]+20+k*12)
def executable(a):
 for base,raw,ss,syms in arm.libraries:
  for s in ss:
   if s[2]&4 and base+s[3]<=a<base+s[3]+s[5]:return True
 return False
def add(a,t):
 a&=~1
 if a not in seen and executable(a):queue.append((a,t))
while queue:
 a,t=queue.popleft()
 if a in seen:continue
 seen.add(a)
 if str(a) not in items:
  decoded=list(mds[capstone.CS_MODE_THUMB if t else capstone.CS_MODE_ARM].disasm(bytes(arm.engine.mem_read(a,4)),a,count=1))
  if not decoded:continue
  ins=decoded[0];ops=[]
  for op in ins.operands:
   p={'type':op.type,'shift':[op.shift.type,op.shift.value],'lane':op.neon_lane if op.neon_lane>=0 else op.vector_index,'subtracted':op.subtracted}
   if op.shift.type>=6:p['shiftReg']=ins.reg_name(op.shift.value)
   if op.type==1:p['reg']=ins.reg_name(op.reg)
   elif op.type==2:p['imm']=op.imm
   elif op.type==3:p['mem']={'base':ins.reg_name(op.mem.base),'index':ins.reg_name(op.mem.index),'scale':op.mem.scale,'disp':op.mem.disp,'lshift':op.mem.lshift}
   elif op.type==4:p['fp']=op.fp
   else:p['value']=op.imm
   ops.append(p)
  items[str(a)]=dict(address=a,size=ins.size,thumb=t,mnemonic=ins.mnemonic,id=ins.insn_name(),text=ins.op_str,cc=ins.cc,flags=ins.update_flags,writeback=ins.writeback,vectorSize=ins.vector_size,vectorData=ins.vector_data,operands=ops,bytes=ins.bytes.hex());extra+=1
 i=items[str(a)];n=i['id'];o=i['operands']
 if n in ('b','bl','blx','cbz','cbnz') and o[-1]['type']==2:add(o[-1]['imm'],not t if n=='blx' else t)
 returns=n in ('bx','tbh','tbb') or n=='b' or (n in ('pop','ldm','ldmib','ldmdb') and any(p.get('reg')=='pc' for p in o)) or (n in ('ldr','mov','add') and o[0].get('reg')=='pc') or (n in ('bl','blx') and o[-1].get('imm',0)&~1 in noreturn)
 if not returns or i['cc'] not in (0,15):add(a+i['size'],t)
record['instructions']=items;path.write_text(json.dumps(record,separators=(',',':')))
print(json.dumps({'instructions':len(items),'added':extra,'types':dict(collections.Counter(i['id'] for i in items.values()))}))
