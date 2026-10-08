"""Compile audited AArch32 instruction sites into native C++ blocks.

Development tool, not an audio implementation or opcode interpreter. The input
records original instruction bytes and addresses. Unsupported semantics abort
generation; untranslated branches abort execution. Never approximate Sony DSP.
"""
import argparse, json, struct, re, collections
from pathlib import Path
project=Path(__file__).resolve().parents[2]
regs={'sb':9,'sl':10,'fp':11,'ip':12,'sp':13,'lr':14,'pc':15}
regs.update({f'r{i}':i for i in range(16)})
def reg(name):return f'c.r[{regs[name]}]'
def words(op):
    name=op['reg'];kind=name[0];index=int(name[1:])
    start=index*{'s':1,'d':2,'q':4}[kind];length={'s':1,'d':2,'q':4}[kind]
    if op.get('lane',-1)>=0:return [f'c.v[{start+op["lane"]}]']
    return [f'c.v[{start+i}]' for i in range(length)]
def fpword(op,double=False,lane=0):
    w=words(op)
    if double:return f'(u64({w[0]})|(u64({w[1]})<<32))'
    return w[lane if len(w)>1 else 0]
def setfp(op,value,double=False):
    w=words(op)
    return f'{{u64 value={value};{w[0]}=u32(value);{w[1]}=u32(value>>32);}}' if double else f'{w[0]}={value};'
def bits(x,double=False):return hex(struct.unpack('<Q' if double else '<I',struct.pack('<d' if double else '<f',x))[0])+('ull' if double else 'u')
def emit(i):
    name=i['id'];o=[dict(x) for x in i['operands']];a=i['address'];thumb=i['thumb'];flags=i['flags'];narrow=thumb and i['size']==2
    if name=='movs':name='mov';flags=True
    pc=a+(4 if thumb else 8);flag='(!oldIt)' if narrow else 'true';flag=flag if flags else 'false'
    # Old Capstone represents rotated ARM immediates as two operands.
    if not thumb and name in ('add','sub','and','orr','eor','bic','mov','mvn','cmp','cmn','rsb','tst') and o and o[-1]['type']==2 and len(o)>({'mov':2,'mvn':2,'cmp':2,'cmn':2,'tst':2}.get(name,3)):
        word=int.from_bytes(bytes.fromhex(i['bytes']),'little');shift=((word>>8)&15)*2;im=word&255
        o[-2]['imm']=((im>>shift)|(im<<(32-shift)))&0xffffffff if shift else im;o.pop()
    def val(op,shflags=False):
        if op['type']==2:return hex(op['imm']&0xffffffff)+'u'
        if op['type']==4:return bits(op['fp'])
        aligned=thumb and name in ('add','sub') and len(o)>=3 and o[1].get('reg')=='pc' and o[2]['type']==2
        r=op['reg'];x=hex(pc&~3 if aligned else pc)+'u' if r=='pc' else reg(r)
        k,n=op['shift']
        if k:x=f'shift(c,{x},{reg(op["shiftReg"])}&255u,{k-5 if k>=6 else k},{"true" if shflags else "false"})' if k>=6 else f'shift(c,{x},{n}u,{k},{"true" if shflags else "false"})'
        return x
    def mem(op,alignment=False):
        m=op['mem'];b=hex((pc&~3) if alignment else pc)+'u' if m['base']=='pc' else reg(m['base']);off=hex(m['disp']&0xffffffff)+'u'
        if m['index']:
            ix=reg(m['index']);k,n=op['shift'];ix=f'shift(c,{ix},{n}u,{k},false)' if k else (f'({ix}<<{m["lshift"]})' if m['lshift'] else ix)
            off=f'({off}{"-" if op["subtracted"] or m["scale"]<0 else "+"}{ix})'
        return f'({b}+{off})'
    control=None;code=''
    if name=='it':code=f'c.it={int.from_bytes(bytes.fromhex(i["bytes"]),"little")&255}u;'
    elif name in ('add','sub','rsb','adc','sbc','rsc','cmp','cmn'):
        dest=None if name in ('cmp','cmn') else o[0];oper=o if dest is None else o[1:];oper=[o[0],*oper] if len(oper)==1 else oper
        x,y=map(val,oper);carry='0u';fl='true' if dest is None else flag
        if name in ('sub','cmp','sbc'):y=f'~({y})';carry='((c.cpsr>>29)&1u)' if name=='sbc' else '1u'
        elif name in ('rsb','rsc'):x,y=y,f'~({x})';carry='((c.cpsr>>29)&1u)' if name=='rsc' else '1u'
        elif name=='adc':carry='((c.cpsr>>29)&1u)'
        value=f'sum(c,{x},{y},{carry},{fl})';code=f'{reg(dest["reg"])}={value};' if dest else f'(void){value};'
        if dest and dest['reg']=='pc':control=reg('pc')
    elif name in ('mov','mvn','and','orr','eor','bic','tst','teq'):
        test=name in ('tst','teq');dest=None if test else o[0];oper=o if test else o[1:];oper=[o[0],*oper] if len(oper)==1 and name not in ('mov','mvn') else oper
        if name in ('mov','mvn'):value=val(oper[0],flags);value=f'~({value})' if name=='mvn' else value
        else:
            x=val(oper[0]);y=val(oper[1],flags or test);value=f'({x}{dict(and_="&",orr="|",eor="^",bic="&",tst="&",teq="^")["and_" if name=="and" else name]}{f"~({y})" if name=="bic" else y})'
        code=f'u32 x={value};'+(f'{reg(dest["reg"])}=x;' if dest else '')+('nz(c,x);' if test else f'if({flag})nz(c,x);' if flags else '')
        if (flags or test) and o[-1]['type']==2:
            w=int.from_bytes(bytes.fromhex(i['bytes']),'little');rotated=bool(w&(1<<25) and (w>>8)&15) if not thumb else False
            if thumb and i['size']==4:
                h1,h2=struct.unpack('<HH',bytes.fromhex(i['bytes']));imm12=((h1>>10)&1)<<11|((h2>>12)&7)<<8|(h2&255);rotated=bool(imm12>>10)
            if rotated:code+=f'c.cpsr=(c.cpsr&~0x20000000)|(({val(o[-1])}&0x80000000)>>2);'
        if dest and dest['reg']=='pc':control=reg('pc')
    elif name in ('lsl','lsr','asr','ror','rrx'):
        if len(o)==2 and o[1]['shift'][0]:
            code=f'u32 x={val(o[1],flags)};{reg(o[0]["reg"])}=x;'+(f'if({flag})nz(c,x);' if flags else '')
            return code,False
        dest=o[0];oper=o[1:];oper=[o[0],*oper] if len(oper)==1 else oper
        x=val(oper[0]);n='1u' if name=='rrx' else val(oper[1]);n=f'({n}&255u)' if len(oper)>1 and oper[1]['type']==1 else n
        code=f'u32 x=shift(c,{x},{n},{dict(lsl=2,lsr=3,asr=1,ror=4,rrx=5)[name]},{flag});{reg(dest["reg"])}=x;'+(f'if({flag})nz(c,x);' if flags else '')
    elif name in ('movw','movt'):code=f'{reg(o[0]["reg"])}='+ (val(o[1]) if name=='movw' else f'({reg(o[0]["reg"])}&65535u)|({val(o[1])}<<16)')+';'
    elif name=='adr':code=f'{reg(o[0]["reg"])}={hex(pc&~3)}u+{val(o[1])};'
    elif name in ('mul','mla','mls','smmul','smull','umull','smlal','umlal','udiv','sdiv'):
        if name in ('smlal','umlal'):
            product=f'i64(i32({val(o[2])}))*i64(i32({val(o[3])}))' if name=='smlal' else f'u64({val(o[2])})*u64({val(o[3])})'
            code=f'u64 x=u64({product})+(u64({reg(o[0]["reg"])})|(u64({reg(o[1]["reg"])})<<32));{reg(o[0]["reg"])}=u32(x);{reg(o[1]["reg"])}=u32(x>>32);'
        elif name in ('smull','umull'):code=f'{"i64" if name=="smull" else "u64"} x={"i64(i32" if name=="smull" else "u64"}({val(o[2])})'+(')' if name=='smull' else '')+f'*{"i32" if name=="smull" else "u64"}({val(o[3])});{reg(o[0]["reg"])}=u32(x);{reg(o[1]["reg"])}=u32(u64(x)>>32);'
        else:
            x,y=(val(p) for p in (o[1:] if len(o)>2 else [o[0],o[1]])[:2]);value=f'({x}*{y})'
            if name=='mla':value+=f'+{val(o[3])}'
            if name=='mls':value=f'({val(o[3])}-{value})'
            if name=='smmul':value=f'u32((i64(i32({x}))*i64(i32({y})))>>32)'
            if name in ('udiv','sdiv'):value=f'({y}?u32({"i64(i32(" if name=="sdiv" else "u64("}{x})'+(')' if name=='sdiv' else '')+f'/{"i64(i32(" if name=="sdiv" else "u64("}{y})'+(')' if name=='sdiv' else '')+'):0u)'
            code=f'{reg(o[0]["reg"])}={value};'
        if flags:code+=f'if({flag})nz(c,{reg(o[0]["reg"])});'
    elif name in ('uxtb','uxth','sxtb','sxth','ubfx','sbfx','bfc','bfi'):
        if name in ('uxtb','uxth','sxtb','sxth'):
            x=val(o[1]);x=f'rotate({x},{val(o[2])})' if len(o)>2 else x;value={'uxtb':f'({x}&255u)','uxth':f'({x}&65535u)','sxtb':f'u32(std::int8_t({x}))','sxth':f'u32(std::int16_t({x}))'}[name]
        elif name in ('ubfx','sbfx'):
            bit,width=o[2]['imm'],o[3]['imm'];value=f'(({val(o[1])}>>{bit})&{hex((1<<width)-1)}u)' if name=='ubfx' else f'u32(i32({val(o[1])}<<{32-width-bit})>>{32-width})'
        else:
            bit,width=(p['imm'] for p in o[-2:]);mask=((1<<width)-1)<<bit;value=f'({reg(o[0]["reg"])}&~{hex(mask)}u)'+(f'|(({val(o[1])}<<{bit})&{hex(mask)}u)' if name=='bfi' else '')
        code=f'{reg(o[0]["reg"])}={value};'
    elif name.startswith(('ldr','str')):
        load=name.startswith('ldr');mi=2 if name.endswith('d') else 1;mp=o[mi];address=mem(mp,True);code=f'u32 address={address};'
        if name.endswith('d'):
            for k in range(2):code+=f'{reg(o[k]["reg"])}=c.load<u32>(address+{k*4});' if load else f'c.store<u32>(address+{k*4},{val(o[k])});'
        else:
            typ={'b':'std::uint8_t','h':'std::uint16_t','sb':'std::int8_t','sh':'std::int16_t'}.get(name[3:],'u32')
            code+=f'{reg(o[0]["reg"])}=u32(c.load<{typ}>(address));' if load else f'c.store<{typ}>(address,{val(o[0])});'
        if i['writeback']:
            base=reg(mp['mem']['base']);code+=f'{base}={base}{"-" if o[-1].get("subtracted") else "+"}{val(o[-1])};' if len(o)>mi+1 else f'{base}=address;'
        if load and o[0]['reg']=='pc':control=reg('pc')
    elif name in ('push','pop','ldm','ldmib','ldmdb','stm','stmib','stmdb','vpush','vpop','vldmia','vstmia'):
        vector=name.startswith('v');push=name.endswith('push');pop=name.endswith('pop');load=pop or 'ldm' in name;base=reg('sp') if push or pop else reg(o[0]['reg']);items=o if push or pop else o[1:]
        itemswords=[word for item in items for word in (words(item) if vector else [reg(item['reg'])])];length=len(itemswords)*4
        code=f'u32 address={base}'+(f'-{length}u' if push or name.endswith('db') else '+4u' if name.endswith('ib') else '')+';'
        for k,w in enumerate(itemswords):code+=f'{w}=c.load<u32>(address+{k*4});' if load else f'c.store<u32>(address+{k*4},{w});'
        if push or pop or i['writeback']:code+=f'{base}{"-=" if push or name.endswith("db") else "+="}{length}u;'
        if load and not vector and any(x['reg']=='pc' for x in items):control=reg('pc')
    elif name in ('tbb','tbh'):
        code=f'c.r[15]={hex(a+4)}u+2u*c.load<{"std::uint8_t" if name=="tbb" else "std::uint16_t"}>({mem(o[0])});return c.r[15];';control=reg('pc')
    elif name in ('b','bl','bx','blx','cbz','cbnz'):
        if name in ('bl','blx'):code=f'c.r[14]={hex((a+i["size"])|(1 if thumb else 0))}u;'
        target=val(o[-1])
        if name.startswith('cb'):code+=f'if({val(o[0])}{"==" if name=="cbz" else "!="}0){{c.r[15]={target}&~1u;return c.r[15];}}'
        else:control=target
    elif name in ('vldr','vstr'):
        code=f'u32 address={mem(o[1],True)};'
        for k,w in enumerate(words(o[0])):code+=f'{w}=c.load<u32>(address+{k*4});' if name=='vldr' else f'c.store<u32>(address+{k*4},{w});'
    elif name in ('vld1','vld2','vld4','vst1','vst2','vst4'):
        mi=next(j for j,p in enumerate(o) if p['type']==3);items=o[:mi];base=reg(o[mi]['mem']['base']);load=name[1:3]=='ld';structures=int(name[-1]);lane_match=re.search(r'\[(\d+)\]',i['text'].split('}')[0]);lane=int(lane_match.group(1)) if lane_match else None
        array=[words({**x,'lane':-1}) for x in items];flat=[w for pair in array for w in pair];count=len(flat) if lane is None else len(items)
        code=f'u32 address={base};'
        if lane is not None:
            for k,p in enumerate(array):code+=f'{p[lane]}=c.load<u32>(address+{k*4});' if load else f'c.store<u32>(address+{k*4},{p[lane]});'
        else:
            width=len(flat)//structures
            for k,w in enumerate(flat):offset=(k//width+k%width*structures)*4 if structures>1 else k*4;code+=f'{w}=c.load<u32>(address+{offset});' if load else f'c.store<u32>(address+{offset},{w});'
        if len(o)>mi+1:code+=f'{base}+={val(o[-1])};'
        elif i['writeback']:code+=f'{base}+={count*4}u;'
    elif name in ('vmov','fmdhr','fconsts','fconstd','vdup'):
        if len(o)==4:
            dw=[reg(p['reg']) if p['reg'] in regs else words(p)[0] for p in o[:2]]
            sw=[val(p) if p['reg'] in regs else words(p)[0] for p in o[2:]]
            code=f'u32 t0={sw[0]},t1={sw[1]};{dw[0]}=t0;{dw[1]}=t1;'
        elif len(o)==3:
            if o[0]['reg'] in regs:
                w=words(o[2]);code=f'{reg(o[0]["reg"])}={w[0]};{reg(o[1]["reg"])}={w[1]};'
            else:
                w=words(o[0]);code=f'{w[0]}={val(o[1])};{w[1]}={val(o[2])};'
        else:
            dest=o[0];src=o[1];dw=[reg(dest['reg'])] if dest['reg'] in regs else words(dest);sw=([val(src)] if src['type']!=1 or src['reg'] in regs else words(src))
            if src['type']==4 and '.f64' in i['mnemonic']:x=struct.unpack('<Q',struct.pack('<d',src['fp']))[0];sw=[hex(x&0xffffffff)+'u',hex(x>>32)+'u']
            lane_match=re.search(r'(?:q|d|s)\d+\[(\d+)\]',i['text'])
            if lane_match and name=='vdup':sw=[words({**src,'lane':int(lane_match.group(1))})[0]]
            code=''.join(f'u32 t{k}={sw[k%len(sw)]};' for k in range(len(dw)))+''.join(f'{w}=t{k};' for k,w in enumerate(dw))
    elif name in ('vadd','vsub','vmul','vdiv','vmin','vmax','vmla','vmls','vnmla','vnmls','vnmul','vfma','vabs','vneg','vcmp','vcmpe','vclt','vcvt','vpadd'):
        double='.f64' in i['mnemonic'];typ='double' if double else 'float';neon=o[0]['reg'].startswith('q') or (o[0]['reg'].startswith('d') and not double);nb='true' if neon else 'false'
        n=1 if double or not neon else len(words(o[0]));ops=dict(vadd=0,vsub=1,vmul=2,vdiv=3,vmax=4,vmin=5)
        def fval(p,k):return bits(p['fp'] if p['type']==4 else float(p['imm']),double) if p['type'] in (2,4) else fpword(p,double,0 if p.get('lane',-1)>=0 else k)
        values=[]
        if name in ('vcmp','vcmpe'):code=f'fpCompare<{typ}>(c,{fval(o[0],0)},{fval(o[1],0)});'
        else:
            for k in range(n):
                x=fval(o[1],k) if name!='vcvt' else None;y=fval(o[2],k) if len(o)>2 and (o[2]['type']!=2 or name=='vclt') else None;acc=fval(o[0],k) if name in ('vmla','vmls','vnmla','vnmls','vfma') else None
                if name in ops:value=f'fpBinary<{typ}>({x},{y},{ops[name]},{nb})'
                elif name in ('vmla','vmls','vnmla','vnmls','vnmul'):
                    product=f'fpBinary<{typ}>({x},{y},2,{nb})'
                    if name in ('vnmla','vnmls'):value=f'fpBinary<{typ}>(({acc}^{hex(0x8000000000000000 if double else 0x80000000)}{"ull" if double else "u"}),{product},{0 if name=="vnmls" else 1},{nb})'
                    elif name=='vnmul':value=f'({product}^{hex(0x8000000000000000 if double else 0x80000000)}{"ull" if double else "u"})'
                    else:value=f'fpBinary<{typ}>({acc},{product},{0 if name=="vmla" else 1},{nb})'
                elif name=='vfma':value=f'fpFma<{typ}>({x},{y},{acc})'
                elif name in ('vneg','vabs'):value=f'({x}{"^" if name=="vneg" else "&"}{hex(0x8000000000000000 if double else 0x80000000) if name=="vneg" else hex(0x7fffffffffffffff if double else 0x7fffffff)}{"ull" if double else "u"})'
                elif name=='vclt':value=f'(fromBits<float>(fpInput<float>({x},true))<fromBits<float>({y})?0xffffffffu:0u)'
                elif name=='vpadd':src=o[1 if k==0 else 2];value=f'fpBinary<float>({fval(src,0)},{fval(src,1)},0,true)'
                elif name=='vcvt':
                    parts=i['mnemonic'].split('.');out,in_=parts[-2:];fractional=o[2]['imm'] if len(o)>2 else 0
                    input_double=in_=='f64';it='double' if input_double else 'float';x=fpword(o[1],input_double,k)
                    if out in ('s32','u32'):value=f'fpToInt<{it}>({x},{str(out=="s32").lower()},{fractional}u,{nb})';double=False
                    elif in_ in ('s32','u32'):value=f'intToFp<{"double" if out=="f64" else "float"}>({fpword(o[1],False,k)},{str(in_=="s32").lower()},{fractional}u,{nb})';double=out=='f64'
                    else:value=f'fpResult<{"double" if out=="f64" else "float"}>({"double" if out=="f64" else "float"}(fromBits<{it}>({x})),false)';double=out=='f64'
                else:raise ValueError(name)
                values.append(value)
            code=''.join(f'{"u64" if double else "u32"} t{k}={v};' for k,v in enumerate(values))
            if double:code+=setfp(o[0],'t0',True)
            else:
                dw=words(o[0]);code+=''.join(f'{dw[k]}=t{k};' for k in range(n))
    elif name in ('vand','vorr','veor','vbic','vext','vrev64','vswp','vtrn','vzip','vuzp','vshl','vshr'):
        dw=words(o[0]);n=len(dw)
        if name in ('vswp','vtrn','vzip','vuzp'):
            aw,bw=words(o[0]),words(o[1]);sources=aw+bw
            if name=='vswp':order=list(range(n,2*n))+list(range(n))
            elif name=='vzip':order=[j for k in range(n) for j in (k,n+k)]
            elif name=='vuzp':order=list(range(0,2*n,2))+list(range(1,2*n,2))
            else:order=[j for k in range(0,n,2) for j in (k,n+k)]+[j for k in range(1,n,2) for j in (k,n+k)]
            values=[sources[k] for k in order];dw=aw+bw
        elif name=='vext':sources=words(o[1])+words(o[2]);start=o[3]['imm'];values=sources[start:start+n]
        elif name=='vrev64':sw=words(o[1]);values=[sw[k^1] for k in range(n)]
        elif name in ('vshr','vshl'):
            sw=words(o[1]);
            if o[2]['type']==1:values=[f'vectorShift({w},{s})' for w,s in zip(sw,words(o[2]))]
            else:
                sh=o[2]['imm'];values=[f'({w}{">>" if name=="vshr" else "<<"}{sh})' if sh<32 else '0u' for w in sw]
        else:
            sw=words(o[1]);bw=words(o[2]);operator={'vand':'&','vorr':'|','veor':'^','vbic':'&'}[name];values=[f'({x}{operator}{"~" if name=="vbic" else ""}{y})' for x,y in zip(sw,bw)]
        code=''.join(f'u32 t{k}={v};' for k,v in enumerate(values))+''.join(f'{w}=t{k};' for k,w in enumerate(dw))
    elif name in ('fmstat','vmrs'):
        code='c.fpscr|=nativeFpFlags();'+('c.cpsr=(c.cpsr&0x0fffffff)|(c.fpscr&0xf0000000);' if name=='fmstat' or o[0].get('reg')=='apsr_nzcv' else f'{reg(o[0]["reg"])}=c.fpscr;')
    elif name=='vmsr':code=f'c.fpscr={val(o[1])};setNativeFp(c);'
    elif name=='mrc' and re.fullmatch(r'p15, #0, r\d+, c13, c0, #3',i['text']):code=f'{reg(o[2]["reg"])}=c.tls;'
    elif name in ('nop','hint'):code=''
    else:raise ValueError(f'{a:#x} {name} {i["text"]}')
    if control is not None:code+=f'c.r[15]=({control})&~1u;return c.r[15];'
    return code,control is not None

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--trace',default=str(project/'native/sony/instructions.json'));parser.add_argument('--output',default=str(project/'native/sony/generated'));args=parser.parse_args()
    trace=json.loads(Path(args.trace).read_text());items=trace['instructions'];pages=collections.defaultdict(list);errors=[]
    for i in items.values():
        try:code,branch=emit(i)
        except Exception as e:errors.append(f'{i["address"]:#x} {i["mnemonic"]} {i["text"]}: {e}');continue
        pages[i['address']>>12].append((i,code,branch))
    if errors:raise ValueError('\n'.join(sorted(set(errors))))
    output=Path(args.output);output.mkdir(parents=True,exist_ok=True);decl=[]
    for page,instructions in sorted(pages.items()):
        name=f'page_{page:x}';decl.append(f'u32 {name}(ArmState& c);');addresses={i['address'] for i,_,_ in instructions}
        lines=['// Generated from pinned Sony ARM instruction bytes. Do not edit.','#include "../arm-state.hpp"',f'u32 {name}(ArmState& c){{','switch(c.r[15]){']
        lines += [f'case {hex(i["address"])}u:goto L{i["address"]:x};' for i,_,_ in instructions];lines+=['default:throw std::runtime_error("Untranslated instruction");}']
        for i,code,branch in sorted(instructions,key=lambda x:x[0]['address']):
            a=i['address'];next_=a+i['size'];thumb=i['thumb'];cond='true' if i['cc'] in (0,15) else f'condition(c,{i["cc"]-1})'
            if i['id'] in ('b','bl','blx') and i['operands'][-1]['type']==2 and i['operands'][-1]['imm']&~1 in addresses:
                code=code.replace('return c.r[15];',f'goto L{i["operands"][-1]["imm"]&~1:x};')
            lines+=[f'L{a:x}:{{ // {i["bytes"]} {i["mnemonic"]} {i["text"]}',f'c.r[15]={hex(a)}u;if(++c.steps>c.limit)throw std::runtime_error("Instruction budget exceeded");']
            if thumb and i['id']!='it':lines+=['u32 oldIt=c.it;bool execute=oldIt?condition(c,oldIt>>4):'+cond+';if(oldIt)c.it=(oldIt&7)?((oldIt&0xe0)|((oldIt<<1)&0x1f)):0;']
            else:lines+=['u32 oldIt=0;bool execute='+cond+';']
            lines+=['if(execute){'+code+'}']
            if next_ in addresses:lines+=[f'goto L{next_:x};']
            else:lines+=[f'c.r[15]={hex(next_)}u;return c.r[15];']
            lines+=['}']
        lines+=['}'];(output/f'{name}.cpp').write_text('\n'.join(lines)+'\n')
    dispatcher=['// Generated from pinned Sony ARM instruction bytes. Do not edit.','#include "../arm-state.hpp"',*decl,'u32 dispatch(ArmState& c){switch(c.r[15]>>12){']
    dispatcher+=[f'case {hex(p)}u:return page_{p:x}(c);' for p in sorted(pages)];dispatcher+=['default:throw std::runtime_error("Untranslated page");}}']
    (output/'dispatch.cpp').write_text('\n'.join(dispatcher)+'\n')
    (output/'manifest.json').write_text(json.dumps({'sourceSha256':trace['sourceSha256'],'instructionSites':len(items),'pages':len(pages),'generator':'scripts/sony-walkman/lift.py','status':'research: full-chain equivalence pending'},indent=2)+'\n')
    print(json.dumps({'instructions':len(items),'pages':len(pages),'generated':True}))
if __name__=='__main__':main()
