"""Research-only ctypes transport for the C++ instruction lift.

No effect math is implemented in this adapter. The original import bridge is
shared with the reference so memory, parameters and ABI stay comparable.
"""
import ctypes, os
# Stable transport register numbers shared with the reference adapter. Native
# playback does not import or initialize the ARM emulator.
class _Ids:pass
ids=_Ids()
_registers={'SP':12,'LR':10,'PC':11,'CPSR':3,'FPSCR':6,'C13_C0_3':113,'C1_C0_2':111,'FPEXC':4}
_registers.update({f'R{i}':66+i for i in range(13)})
_registers.update({f'S{i}':79+i for i in range(32)})
_registers.update({f'D{i}':14+i for i in range(32)})
for name,number in _registers.items():
    setattr(ids,'UC_ARM_REG_'+name,number);globals()['UC_ARM_REG_'+name]=number
UC_ARCH_ARM=1;UC_MODE_ARM=0;UC_HOOK_CODE=4;UC_CPU_ARM_CORTEX_A7=14
__all__=['X86Engine','UC_ARCH_ARM','UC_MODE_ARM','UC_HOOK_CODE','UC_CPU_ARM_CORTEX_A7']+['UC_ARM_REG_'+name for name in _registers]
class X86Engine:
    def __init__(self,*_):
        self.dll=ctypes.CDLL(os.environ['SONY_WALKMAN_X86_DLL'])
        d=self.dll;p=ctypes.c_void_p;u=ctypes.c_uint32;q=ctypes.c_uint64
        d.sony_create.restype=p;d.sony_destroy.argtypes=[p]
        d.sony_map.argtypes=[p,u,u];d.sony_memory.argtypes=[p,u,u];d.sony_memory.restype=p
        d.sony_get.argtypes=[p,u];d.sony_get.restype=q;d.sony_set.argtypes=[p,u,q]
        d.sony_execute.argtypes=[p,u,u,q,ctypes.c_int];d.sony_error.restype=ctypes.c_char_p
        self.state=d.sony_create();self.hook=None
        self.registers={getattr(ids,f'UC_ARM_REG_R{i}'):i for i in range(13)}
        self.registers.update({ids.UC_ARM_REG_SP:13,ids.UC_ARM_REG_LR:14,ids.UC_ARM_REG_PC:15,ids.UC_ARM_REG_CPSR:16,ids.UC_ARM_REG_FPSCR:17,ids.UC_ARM_REG_C13_C0_3:18})
        self.registers.update({getattr(ids,f'UC_ARM_REG_S{i}'):64+i for i in range(32)})
        self.registers.update({getattr(ids,f'UC_ARM_REG_D{i}'):128+i for i in range(32)})
    def __del__(self):
        if getattr(self,'state',None):self.dll.sony_destroy(self.state);self.state=None
    def ctl_set_cpu_model(self,*_):pass
    def mem_map(self,a,n):
        if not self.dll.sony_map(self.state,a,n):raise ValueError('Native ARM ABI memory mapping failed')
    def mem_read(self,a,n):
        p=self.dll.sony_memory(self.state,a,n)
        if not p:raise ValueError(f'Unmapped native read {a:#x}/{n}')
        return ctypes.string_at(p,n)
    def mem_write(self,a,data):
        p=self.dll.sony_memory(self.state,a,len(data))
        if not p:raise ValueError(f'Unmapped native write {a:#x}/{len(data)}')
        ctypes.memmove(p,bytes(data),len(data))
    def reg_read(self,r):return self.dll.sony_get(self.state,self.registers[r]) if r in self.registers else 0
    def reg_write(self,r,value):
        if r in self.registers:self.dll.sony_set(self.state,self.registers[r],value)
    def hook_add(self,_,fn,begin=0,end=0):self.hook=fn
    def emu_start(self,a,stop,timeout=0,count=20_000_000):
        reset=True
        while True:
            result=self.dll.sony_execute(self.state,a,stop,count,reset);reset=False
            if result==0:return
            if result==2:raise ValueError(f'{self.dll.sony_error().decode()} at {self.reg_read(ids.UC_ARM_REG_PC):#x}')
            self.hook(self,self.reg_read(ids.UC_ARM_REG_PC),4,None)
            a=self.reg_read(ids.UC_ARM_REG_LR)
