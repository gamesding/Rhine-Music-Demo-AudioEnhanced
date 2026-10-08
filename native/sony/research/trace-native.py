import os, sys, json, struct, collections
from pathlib import Path
root=Path(__file__).resolve().parents[3]
os.environ['SONY_WALKMAN_ASSETS']=str(root/'vendor/sony-walkman')
os.environ.pop('SONY_WALKMAN_X86_DLL',None)
reference=root/('.tools/desktop-runtime/unicorn' if sys.maxsize>2**32 else '.tools/walkman/python')
sys.path[:0]=[str(root/'scripts/sony-walkman'),str(root/'.tools/sony-research/python'),str(reference)]
import arm_runtime as arm
import capstone
from effects import create_chain, feed_chain, finish_chain
blocks={}
def block(engine,address,size,_):
    if address<0x20000000: blocks[(address,bool(engine.reg_read(arm.UC_ARM_REG_CPSR)&32))]=size
arm.engine.hook_add(arm.uc.UC_HOOK_BLOCK,block)
cases=[(44100,True,2,1),(48000,True,6,4)]
cases += [(r,False,m,v) for r in (44100,48000,176400,192000) for m,v in ((1,2),(3,3),(4,1),(5,4))]
for rate,dsee,dc,vinyl in cases:
    chain,_=create_chain(rate,dsee,dc,vinyl)
    sample=b''.join(struct.pack('<2f',.3*((i*17)%123-60)/60,.2*((i*13)%113-55)/55) for i in range(4096))
    feed_chain(chain,sample);finish_chain(chain)
    for name in ('EffectGetVersionDSX','EffectGetVersionDCPhaseLinearizer','EffectGetVersionRealVinyl'):arm.call(name)
instructions={};counts=collections.Counter();unsupported_modes=0
for (address,thumb),size in sorted(blocks.items()):
    md=capstone.Cs(capstone.CS_ARCH_ARM,capstone.CS_MODE_THUMB if thumb else capstone.CS_MODE_ARM);md.detail=True
    raw=bytes(arm.engine.mem_read(address,size))
    for i in md.disasm(raw,address):
        operands=[]
        for op in i.operands:
            value={'type':op.type,'shift':[op.shift.type,op.shift.value],'lane':op.neon_lane if op.neon_lane>=0 else op.vector_index,'subtracted':op.subtracted}
            if op.shift.type>=6:value['shiftReg']=i.reg_name(op.shift.value)
            if op.type==capstone.arm.ARM_OP_REG:value['reg']=i.reg_name(op.reg)
            elif op.type==capstone.arm.ARM_OP_IMM:value['imm']=op.imm
            elif op.type==capstone.arm.ARM_OP_FP:value['fp']=op.fp
            elif op.type==capstone.arm.ARM_OP_MEM:value['mem']={'base':i.reg_name(op.mem.base),'index':i.reg_name(op.mem.index),'scale':op.mem.scale,'disp':op.mem.disp,'lshift':op.mem.lshift}
            else:value['value']=op.imm
            operands.append(value)
        instructions[str(i.address)]=dict(address=i.address,size=i.size,thumb=thumb,mnemonic=i.mnemonic,id=i.insn_name(),text=i.op_str,cc=i.cc,flags=i.update_flags,writeback=i.writeback,vectorSize=i.vector_size,vectorData=i.vector_data,operands=operands,bytes=i.bytes.hex())
        counts[(i.insn_name(),i.mnemonic.split('.')[-1] if '.' in i.mnemonic else '',thumb)]+=1
out=root/'.tools/walkman/native-trace.json'
out.parent.mkdir(parents=True,exist_ok=True)
out.write_text(json.dumps({'sourceSha256':'f08934816d91e9e5f7f34230fc0996403bb6a063c58f03a40269476778bbe6f6','instructions':instructions,'blocks':[[a,n,t] for (a,t),n in sorted(blocks.items())]},separators=(',',':')))
print(json.dumps({'instructions':len(instructions),'blocks':len(blocks),'operations':[{'id':k[0],'type':k[1],'thumb':k[2],'count':v} for k,v in sorted(counts.items())]}))
