"""ARM ABI bridge for pinned, unmodified Sony DSP and original runtime libraries.

No effect equations are implemented here. Unknown imports fail closed.
"""
import sys
import os
from pathlib import Path
root = Path(os.environ['SONY_WALKMAN_ASSETS']).resolve()
import struct
import time
import re
if os.environ.get('SONY_WALKMAN_X86_DLL'):
    import x86_runtime as uc
    from x86_runtime import *
else:
    import unicorn as uc
    from unicorn.arm_const import *

data = (root / 'libSoundServiceFw.so').read_bytes()
header = struct.unpack_from('<HHIIIIIHHHHHH', data, 16)
sections = [struct.unpack_from('<IIIIIIIIII', data, header[5] + n * header[10]) for n in range(header[11])]
names = data[sections[header[12]][4]:sections[header[12]][4] + sections[header[12]][5]]
sectionname = lambda s: names[s[0]:].split(b'\0',1)[0].decode()
symsection = next(s for s in sections if s[1] == 11)
strsection = sections[symsection[6]]
strings = data[strsection[4]:strsection[4]+strsection[5]]
symbols = []
for pos in range(symsection[4],symsection[4]+symsection[5],symsection[9]):
    name, value, size, info, other, index = struct.unpack_from('<IIIBBH', data, pos)
    symbols.append(dict(name=strings[name:].split(b'\0',1)[0].decode(), value=value, size=size, index=index))
byname = {s['name']:s for s in symbols}
if os.environ.get('SONY_WALKMAN_X86_DLL'):
    engine = X86Engine()
else:
    engine = uc.Uc(uc.UC_ARCH_ARM,uc.UC_MODE_ARM)
engine.ctl_set_cpu_model(UC_CPU_ARM_CORTEX_A7)
engine.reg_write(UC_ARM_REG_C1_C0_2,0xF00000)
engine.reg_write(UC_ARM_REG_FPEXC,0x40000000)
base = 0x10000000
engine.mem_map(base,0x500000)
for pos in range(header[4],header[4]+header[8]*header[9],header[8]):
    kind,offset,address,_,filesize,memsize,flags,align = struct.unpack_from('<IIIIIIII',data,pos)
    if kind == 1:
        engine.mem_write(base+address,data[offset:offset+filesize])
stack = 0x20000000
engine.mem_map(stack,0x100000)
heap = 0x30000000
engine.mem_map(heap,0x4000000)
top = heap
imports = 0x40000000
engine.mem_map(imports,0x100000)
stop = 0x50000000
engine.mem_map(stop,4096)
tls = 0x60000000
engine.mem_map(tls,4096)
engine.reg_write(UC_ARM_REG_C13_C0_3,tls)
stubs = {}
stubnames = {}
def allocate(length):
    global top
    result = top
    top += (length + 15) & ~15
    if top > heap+0x4000000:
        raise ValueError('heap exhausted')
    return result
def read32(address):
    return struct.unpack('<I',engine.mem_read(address,4))[0]
def write32(address,value):
    engine.mem_write(address,struct.pack('<I',value & 0xffffffff))
def cstring(address):
    out=bytearray()
    for i in range(65536):
        value=engine.mem_read(address+i,1)[0]
        if not value:
            return bytes(out)
        out.append(value)
    raise ValueError('unterminated runtime string')
def stub(name):
    if name not in stubs:
        address = imports + len(stubs) * 16
        stubs[name] = address
        stubnames[address] = name
        engine.mem_write(address,bytes.fromhex('1eff2fe1'))
    return stubs[name]
libraries = [(base,data,sections,symbols)]
if True:
    for libbase,filename in [(0x11000000,'libm-2.23.so'),(0x12000000,'libc++.so.1.0')]:
        raw=(root/filename).read_bytes()
        h=struct.unpack_from('<HHIIIIIHHHHHH',raw,16)
        ss=[struct.unpack_from('<IIIIIIIIII',raw,h[5]+i*h[10]) for i in range(h[11])]
        symsec=next(s for s in ss if s[1]==11)
        strsec=ss[symsec[6]]
        stringdata=raw[strsec[4]:strsec[4]+strsec[5]]
        syms=[]
        for pos in range(symsec[4],symsec[4]+symsec[5],symsec[9]):
            n,v,sz,info,other,idx=struct.unpack_from('<IIIBBH',raw,pos)
            syms.append(dict(name=stringdata[n:].split(b'\0',1)[0].decode(),value=v,size=sz,index=idx))
        engine.mem_map(libbase,0x500000)
        for pos in range(h[4],h[4]+h[8]*h[9],h[8]):
            kind,offset,address,_,filesize,memsize,flags,align=struct.unpack_from('<IIIIIIII',raw,pos)
            if kind==1:
                engine.mem_write(libbase+address,raw[offset:offset+filesize])
        libraries.append((libbase,raw,ss,syms))
defined={s['name']:b+s['value'] for b,_,_,syms in libraries for s in syms if s['index'] and s['index']<0xff00}
for libbase,raw,ss,syms in libraries:
    for s in ss:
        if s[1] != 9:
            continue
        for pos in range(s[4],s[4]+s[5],s[9]):
            address,info = struct.unpack_from('<II',raw,pos)
            kind = info & 255
            symbol = syms[info >> 8]
            target = libbase+address
            addend = read32(target)
            resolved = libbase+symbol['value'] if symbol['index'] and symbol['index']<0xff00 else defined.get(symbol['name'])
            if resolved is None:
                resolved=stub(symbol['name'])
            if kind == 23:
                write32(target,libbase+addend)
            elif kind in (21,22):
                write32(target,resolved)
            elif kind == 2:
                write32(target,resolved+addend)
            elif kind == 19 and symbol['name'] == 'errno':
                write32(target,0x100+addend)
            elif kind not in (0,17):
                raise ValueError(f'unsupported relocation {kind} in library {libbase:#x}')
if '__stack_chk_guard' in stubs:
    write32(stubs['__stack_chk_guard'],0x1234abcd)
registers = [UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3]
called = set()
def hook(engine,address,size,userdata):
    name = stubnames.get(address)
    if not name:
        raise ValueError(f'unknown stub address {address:#x}')
    called.add(name)
    args = [engine.reg_read(r) for r in registers]
    if os.environ.get('WALKMAN_TRACE_IMPORTS'):
        print('IMPORT',name,hex(address),args,'LR',hex(engine.reg_read(UC_ARM_REG_LR)),flush=True)
    result = 0
    if name in ('memcpy','memmove','__aeabi_memcpy','__aeabi_memcpy4','__aeabi_memcpy8'):
        engine.mem_write(args[0],bytes(engine.mem_read(args[1],args[2])))
        result = args[0]
    elif name in ('memset','__aeabi_memset','__aeabi_memset4','__aeabi_memclr','__aeabi_memclr4'):
        value,length = (args[1],args[2]) if name == 'memset' else (args[2],args[1])
        if 'memclr' in name:
            value = 0
        engine.mem_write(args[0],bytes([value & 255]) * length)
        result = args[0]
    elif name in ('malloc','calloc'):
        result = allocate(args[0] * args[1] if name == 'calloc' else args[0])
    elif name == 'free':
        result = 0
    elif name == '__aeabi_read_tp':
        result = tls
    elif name == 'snprintf':
        fmt=cstring(args[2])
        if fmt not in (b'%u',b'%d',b'%lu',b'%ld'):
            raise ValueError(f'unsupported runtime snprintf format {fmt!r}')
        value=args[3]
        if fmt in (b'%d',b'%ld') and value >= 2**31:
            value-=2**32
        rendered=str(value).encode()
        result=len(rendered)
        if args[1]:
            engine.mem_write(args[0],rendered[:args[1]-1]+b'\0')
    elif name == 'strlen':
        result=len(cstring(args[0]))
    elif name == '__errno_location':
        result=tls+0x100
    elif name in ('strtol','strtoul','strtof','strtod'):
        source=cstring(args[0]).decode('ascii')
        floating=name in ('strtof','strtod')
        if not floating and args[2] != 10:
            raise ValueError('Only decimal conversion is permitted by this runtime adapter')
        pattern=r'\s*[+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?' if floating else r'\s*[+-]?\d+'
        match=re.match(pattern,source)
        end=match.end() if match else 0
        if args[1]:
            write32(args[1],args[0]+end)
        value=(float(match.group()) if floating else int(match.group())) if match else 0
        if floating:
            fmt,integer,reg=('<f','<I',UC_ARM_REG_S0) if name=='strtof' else ('<d','<Q',UC_ARM_REG_D0)
            engine.reg_write(reg,struct.unpack(integer,struct.pack(fmt,value))[0])
        else:
            lo,hi=(-(2**31),2**31-1) if name=='strtol' else (0,2**32-1)
            if not lo<=value<=hi:
                write32(tls+0x100,34)
            result=max(lo,min(hi,value))&0xffffffff
    elif name == 'memcmp':
        a=bytes(engine.mem_read(args[0],args[2]))
        b=bytes(engine.mem_read(args[1],args[2]))
        result=(a>b)-(a<b)
    elif name in ('__cxa_guard_acquire','__cxa_guard_release','__cxa_guard_abort'):
        if name.endswith('acquire'):
            result=int(engine.mem_read(args[0],1)[0]==0)
        elif name.endswith('release'):
            engine.mem_write(args[0],b'\1')
    elif name in ('__android_log_print','__android_log_vprint','printf','fprintf','puts','__cxa_atexit','__aeabi_atexit') or name.startswith('_ZN3pst3log5Print'):
        result = 0
    else:
        raise ValueError(f'unimplemented import {name}, args {args}')
    engine.reg_write(UC_ARM_REG_R0,result)
engine.hook_add(uc.UC_HOOK_CODE,hook,begin=imports,end=imports+0x100000-1)
def call(name,*args,verbose=False):
    engine.reg_write(UC_ARM_REG_SP,stack+0xF0000)
    engine.reg_write(UC_ARM_REG_LR,stop)
    for i in range(4):
        engine.reg_write(registers[i],args[i] if i < len(args) else 0)
    for i,arg in enumerate(args[4:]):
        write32(stack+0xF0000+i*4,arg)
    value = byname[name]['value'] if isinstance(name,str) else name
    started = time.perf_counter()
    try:
        engine.emu_start(base+value,stop,timeout=0,count=20_000_000)
    except Exception as error:
        print('FAILED',name,'PC',hex(engine.reg_read(UC_ARM_REG_PC)),error)
        raise
    if engine.reg_read(UC_ARM_REG_PC) != stop:
        raise ValueError('DSP instruction budget exceeded')
    result = engine.reg_read(UC_ARM_REG_R0)
    if verbose:
        print('CALL',name,'result',result if result < 2**31 else result-2**32,'ms',round((time.perf_counter()-started)*1000,3),flush=True)
    return result
