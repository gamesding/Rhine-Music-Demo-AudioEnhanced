"""Full-effect differential checks: original Cortex-A7 versus generated x86 C++.

Run with the 64-bit embedded Python and pinned Unicorn reference. All inputs are
synthetic; compare PCM bytes and every allocated state byte, not spectral shape.
"""
import argparse,array,hashlib,importlib.util,json,math,os,random,struct,sys,time
from pathlib import Path
here=Path(__file__).resolve().parent;project=here.parents[1]
def module(name,file):
    spec=importlib.util.spec_from_file_location(name,here/file);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def main():
    p=argparse.ArgumentParser();p.add_argument('--rate',type=int,default=44100);p.add_argument('--dsee',type=int,default=1);p.add_argument('--dc',type=int,default=2);p.add_argument('--vinyl',type=int,default=1);p.add_argument('--frames',type=int,default=4096);p.add_argument('--pattern',default='mixed');p.add_argument('--pcm-input');p.add_argument('--lockstep',action='store_true');a=p.parse_args()
    os.environ.setdefault('SONY_WALKMAN_ASSETS',str(project/'vendor/sony-walkman'))
    dll=os.environ.pop('SONY_WALKMAN_X86_DLL',str(project/'vendor/sony-walkman-x86/sony-dsp-x86.dll'))
    ref=module('original_reference','arm_runtime.py');os.environ['SONY_WALKMAN_X86_DLL']=dll;nat=module('native_translation','arm_runtime.py')
    sys.modules['arm_runtime']=ref;re=module('reference_effects','effects.py');sys.modules['arm_runtime']=nat;ne=module('translated_effects','effects.py')
    gen=random.Random(20261007);values=array.array('f')
    if a.pcm_input:content=Path(a.pcm_input).read_bytes();a.frames=len(content)//8
    else:
        for i in range(a.frames):
            if a.pattern=='silence':l=r=0
            elif a.pattern=='left':l,r=(.25 if i in (0,63,64,127,128,511,512,2047) else 0),0
            elif a.pattern=='right':l,r=0,(.25 if i in (0,63,64,127,128,511,512,2047) else 0)
            elif a.pattern=='noise':l,r=gen.uniform(-1,1),gen.uniform(-1,1)
            elif a.pattern=='tiny':l,r=(-1 if i%2 else 1)*2**(-130+i%80),2**(-145+i%100)
            else:
                l=.21*math.sin(i*.113)+.14*math.sin(i*.701);r=.17*math.cos(i*.173)-.09*math.sin(i*.917)
                if i%127==0:l,r=(1 if i%2 else -1),(-.999969 if i%2 else .999969)
            values.extend((l,r))
        content=values.tobytes()
    result={'sampleRate':a.rate,'dsee':bool(a.dsee),'dc':a.dc,'vinyl':a.vinyl,'frames':a.frames,'pattern':a.pattern,'bitExact':False,'stateBitExact':False}
    output=[];durations=[]
    def compare_state(stage):
        if ref.top!=nat.top:raise ValueError(f'{stage}: allocation layout differs')
        x=bytes(ref.engine.mem_read(ref.heap,ref.top-ref.heap));y=bytes(nat.engine.mem_read(nat.heap,nat.top-nat.heap))
        if x!=y:
            k=next(i for i,(a,b) in enumerate(zip(x,y)) if a!=b);raise ValueError(f'{stage}: state differs at heap+{k:#x}; original={x[k:k+16].hex()} native={y[k:k+16].hex()}')
    started=time.perf_counter();rc,rr=re.create_chain(a.rate,bool(a.dsee),a.dc,a.vinyl);ref_init=time.perf_counter()-started
    started=time.perf_counter();nc,nr=ne.create_chain(a.rate,bool(a.dsee),a.dc,a.vinyl);nat_init=time.perf_counter()-started
    if rr!=nr:raise ValueError('Output sample rates differ')
    compare_state('initialization')
    if a.lockstep:
        for offset in range(0,len(content),64*8):
            re.feed_chain(rc,content[offset:offset+64*8]);ne.feed_chain(nc,content[offset:offset+64*8]);compare_state(f'block {offset//(64*8)}')
        print(json.dumps({'lockstep':True,'frames':a.frames}));return
    for effects,chain in ((re,rc),(ne,nc)):
        started=time.perf_counter();parts=[];offset=0;pattern=(1,63,7,129,64,511,2,65,8192);index=0
        while offset<len(content):
            size=pattern[index%len(pattern)]*8;parts.append(effects.feed_chain(chain,content[offset:offset+size]));offset+=size;index+=1
        parts.append(effects.finish_chain(chain));output.append(b''.join(parts)[:a.frames*(rr//a.rate)*8]);durations.append(time.perf_counter()-started)
    if output[0]!=output[1]:
        k=next(i for i,(x,y) in enumerate(zip(*output)) if x!=y);raise ValueError(f'PCM differs at byte {k}; original={output[0][k//4*4:k//4*4+16].hex()} native={output[1][k//4*4:k//4*4+16].hex()}')
    compare_state('finished stream')
    result.update(bitExact=True,stateBitExact=True,outputRate=rr,outputValues=len(output[0])//4,pcmSha256=hashlib.sha256(output[0]).hexdigest(),originalSeconds=durations[0],nativeSeconds=durations[1],originalInitSeconds=ref_init,nativeInitSeconds=nat_init,speedup=durations[0]/max(durations[1],1e-9))
    print(json.dumps(result),flush=True)
if __name__=='__main__':
    try:main()
    except Exception as error:print(json.dumps({'bitExact':False,'error':str(error)}),flush=True);sys.exit(1)
