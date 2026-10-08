import test from 'node:test'
import assert from 'node:assert/strict'
import { promises as fs } from 'node:fs'
import path from 'node:path'
import os from 'node:os'
import { randomUUID } from 'node:crypto'
import { spawn } from 'node:child_process'
import { NativeOutput,outputSettings } from './native-output.mjs'
import { dsdFixture,silentWav,taggedDsf } from './audio-fixtures.mjs'
const settings={backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'};
const request=(session,trackId='first')=>({session,trackId,settings,volume:0,position:0});
const sleep=ms=>new Promise(resolve=>setTimeout(resolve,ms));
async function decodeCli(executable,request,stream=true,pauseReader=0){
 const child=spawn(executable,[stream?'--decode-stream-json':'--decode-json'],{windowsHide:true,stdio:['pipe','pipe','pipe']}),chunks=[],errors=[];
 child.stdout.on('data',chunk=>chunks.push(chunk));child.stderr.on('data',chunk=>errors.push(chunk));child.stdin.end(JSON.stringify(request)+'\n');
 if(pauseReader){child.stdout.pause();setTimeout(()=>child.stdout.resume(),pauseReader)}
 const code=await new Promise((resolve,reject)=>{child.once('error',reject);child.once('close',resolve)}),data=Buffer.concat(chunks);
 assert.equal(code,0,Buffer.concat(errors).toString());
 if(!stream)return JSON.parse(data.toString());
 const end=data.indexOf(10),metadata=JSON.parse(data.subarray(0,end).toString());assert.equal(metadata.ready,true);const pcm=data.subarray(end+1);
 assert.equal(pcm.length,metadata.frames*8,'stream must retain its advertised exact frame count');return {metadata,pcm};
}
async function fixture(t) {
 const directory=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-native-'));
 const file=path.join(directory,'合成 (静音).wav');await fs.writeFile(file,silentWav());
 t.after(()=>fs.rm(directory,{recursive:true,force:true}));return {directory,file};
}
test('native settings reject invalid routes and require an explicitly selected ASIO driver',()=>{
 assert.deepEqual(outputSettings(settings),settings);
 for(const value of [{...settings,backend:'browser'},{...settings,backend:'asio'},{...settings,channel:256},{...settings,dsdMode:'fake'}])assert.throws(()=>outputSettings(value));
});

test('native streaming decode matches file decode and preserves the seek timeline', {skip:process.platform!=='win32'},async t=>{
 const {directory,file}=await fixture(t),host=new NativeOutput();
 const full=await decodeCli(host.executable,{file,dsd:false,position:0});
 const output=path.join(directory,'decoded.f32'),decoded=await decodeCli(host.executable,{file,dsd:false,output},false);
 assert.equal(decoded.frames,full.metadata.frames);assert.deepEqual(full.pcm,await fs.readFile(output));
 const tail=await decodeCli(host.executable,{file,dsd:false,position:.713});
 const skipped=Math.round(tail.metadata.positionOffset*full.metadata.sampleRate);
 assert.ok(Math.abs(tail.metadata.positionOffset-.713)<1/44100);
 assert.deepEqual(tail.pcm,full.pcm.subarray(skipped*8));
 assert.equal(tail.metadata.frames+skipped,full.metadata.frames);
 // A generated 0.237 s AAC container has a partial final codec frame.
 // Media Foundation may decode its padding past the declared 11,376 frames.
 const aac=path.join(directory,'codec-padding.m4a');
 await fs.writeFile(aac,Buffer.from(await fs.readFile(new URL('./fixtures/aac-padding.m4a.b64',import.meta.url),'utf8'),'base64'));
 const aacFull=await decodeCli(host.executable,{file:aac,dsd:false});
 assert.equal(aacFull.metadata.sampleRate,48000);assert.equal(aacFull.metadata.frames,11376);
 const aacOutput=path.join(directory,'aac-decoded.f32'),aacDisk=await decodeCli(host.executable,{file:aac,dsd:false,output:aacOutput},false);
 assert.equal(aacDisk.frames,11376);assert.deepEqual(aacFull.pcm,await fs.readFile(aacOutput));
 const aacTail=await decodeCli(host.executable,{file:aac,dsd:false,position:.1});
 assert.equal(aacTail.metadata.frames+Math.round(aacTail.metadata.positionOffset*48000),11376);
 for(const rate of [2822400,5644800,11289600])for(const count of [4098,8192,32768])for(const format of ['dsf','dff']){
  const generated=dsdFixture(rate,count),source=path.join(directory,`stream-${rate}-${count}.${format}`);await fs.writeFile(source,generated[format]);
  const pcm=await decodeCli(host.executable,{file:source,dsd:true});assert.equal(pcm.metadata.sampleRate,44100);
  for(let i=0;i<pcm.pcm.length;i+=4)assert.ok(Number.isFinite(pcm.pcm.readFloatLE(i)));
 }
});

test('Windows PCM pipe backpressure retains every frame without a decoder error',{skip:process.platform!=='win32'},async t=>{
 const {directory}=await fixture(t),file=path.join(directory,'backpressure.wav'),host=new NativeOutput();
 await fs.writeFile(file,silentWav(12,192000,24));
 const decoded=await decodeCli(host.executable,{file,dsd:false},true,300);
 assert.equal(decoded.metadata.sampleRate,192000);assert.equal(decoded.metadata.frames,2304000);assert.equal(decoded.pcm.length,2304000*8);assert.ok(decoded.pcm.every(byte=>byte===0));
});

test('Sony segments expose full-track positions and release obsolete producers',async t=>{
 const {directory,file}=await fixture(t),id='c'.repeat(64),job={trackId:'first',output:file,state:'ready',readers:0,result:{duration:90,positionOffset:30}},cancelled=[];
 const sony={cacheDir:directory,jobs:new Map([[id,job]]),audio:async()=>({path:file,allowedRoot:directory}),cancel:key=>cancelled.push(key)};
 const host=new NativeOutput({sony,store:{trackFile:()=>({path:file,allowedRoot:directory})}});job.id=id;
 const calls=[];host.command=async value=>{calls.push(value);return {position:value.position??0,duration:90,paused:true}};
 const session=randomUUID(),opened=await host.start({...request(session),position:30,sonyJobId:id});
 assert.equal(calls[0].position,0);assert.equal(opened.position,30);assert.equal(opened.duration,120);assert.equal(opened.sourceStart,30);
 const sought=await host.control({session,action:'seek',position:45});assert.equal(calls.at(-1).position,15);assert.equal(sought.position,45);
 await assert.rejects(host.control({session,action:'seek',position:29}),/早于/);
 job.state='processing';await host.control({session,action:'stop'});assert.equal(job.readers,0);assert.deepEqual(cancelled,[id]);
});
test('late cancellation cannot replace a newer track; stop before start is fenced',async t=>{
 const {directory,file}=await fixture(t);let release;
 const host=new NativeOutput({store:{trackFile:()=>({path:file,allowedRoot:directory})},ftp:{ensure:()=>new Promise(resolve=>release=resolve),trackFile:()=>({path:file,allowedRoot:directory})}});
 const commands=[];host.command=async value=>{commands.push(value);return {session:value.session,paused:true}};
 const old=randomUUID(),latest=randomUUID(),cancelled=randomUUID();
 const pending=host.start(request(old,'ftp-first'));await sleep(5);
 await host.start(request(latest));await host.control({session:old,action:'stop'});release();
 await assert.rejects(pending,/取消/);assert.equal(host.active.session,latest);assert.deepEqual(commands.map(x=>x.cmd),['open']);
 await host.control({session:cancelled,action:'stop'});await assert.rejects(host.start(request(cancelled)),/取消/);
 await host.stopCurrent();assert.equal(host.active,undefined);
});

test('a refreshed frontend adopts playing and paused Sony output without reopening or losing the full timeline',async t=>{
 const {directory,file}=await fixture(t),id='d'.repeat(64),fx={dsee:true,dc:2,vinyl:1},commands=[];
 const job={id,trackId:'first',output:file,state:'ready',readers:0,settings:fx,result:{duration:90,positionOffset:30}};
 const sony={cacheDir:directory,jobs:new Map([[id,job]]),audio:async()=>({path:file,allowedRoot:directory}),view:()=>({state:'ready',progress:1,sampleRate:176400,positionOffset:30,duration:90,workers:3})};
 const host=new NativeOutput({sony});let playing=false;
 host.command=async value=>{commands.push(value);if(value.cmd==='play')playing=true;if(value.cmd==='pause')playing=false;return {position:12.5,duration:90,playing,paused:!playing,sampleRate:176400}};
 const first=randomUUID(),second=randomUUID(),third=randomUUID(),session=randomUUID();
 assert.deepEqual(await host.current({clientId:first,clientStartedAt:100}),{session:null});
 await host.start({...request(session),clientId:first,sonyJobId:id,sonySettings:fx,position:30,volume:.1,targetVolume:.65});
 await host.control({session,clientId:first,action:'play'});
 await host.control({session,clientId:first,action:'volume',volume:.3,targetVolume:.65});
 const recovered=await host.current({clientId:second,clientStartedAt:101});
 assert.equal(recovered.session,session);assert.equal(recovered.state.playing,true);assert.equal(recovered.state.position,42.5);assert.equal(recovered.state.duration,120);assert.equal(recovered.state.sourceStart,30);
 assert.equal(recovered.volume,.65,'a reload during a fade restores the preferred gain');assert.deepEqual(recovered.sonySettings,fx);assert.deepEqual(recovered.sonyProcessing.effectiveSettings,fx);assert.equal(job.readers,1);
 assert.deepEqual(await host.control({session,clientId:first,action:'stop'}),{stale:true});
 await assert.rejects(host.start({...request(randomUUID()),clientId:first}),/前端已经刷新/);
 assert.deepEqual(await host.current({clientId:first,clientStartedAt:100}),{session:null,stale:true});assert.equal(host.frontendOwner,second);
 await host.control({session,clientId:second,action:'pause'});
 const paused=await host.current({clientId:third,clientStartedAt:102});assert.equal(paused.state.playing,false);assert.equal(paused.state.paused,true);assert.equal(paused.state.position,42.5);
 assert.equal(commands.filter(c=>c.cmd==='open').length,1);assert.equal(commands.filter(c=>c.cmd==='stop').length,0);
 await host.control({session,clientId:third,action:'stop'});assert.equal(host.active,undefined);assert.equal(job.readers,0);
});

test('frontend adoption cancels an old pending open and stops an invalid driver session',async t=>{
 const {directory,file}=await fixture(t),first=randomUUID(),second=randomUUID(),session=randomUUID(),commands=[];
 const host=new NativeOutput({store:{trackFile:()=>({path:file,allowedRoot:directory})}});let release;
 host.command=async value=>{commands.push(value.cmd);if(value.cmd==='open')await new Promise(resolve=>release=resolve);return {session:value.session,paused:true}};
 await host.current({clientId:first,clientStartedAt:200});
 const opening=host.start({...request(session),clientId:first});while(!release)await sleep(1);
 const rejected=assert.rejects(opening,/取消/),adopting=host.current({clientId:second,clientStartedAt:201});release();
 await rejected;assert.deepEqual(await adopting,{session:null});assert.deepEqual(commands,['open','stop']);assert.equal(host.active,undefined);
 host.command=async value=>{commands.push(value.cmd);return {session:value.session,stale:value.cmd==='status'}};
 await host.start({...request(randomUUID()),clientId:second});assert.deepEqual(await host.current({clientId:second,clientStartedAt:201}),{session:null});assert.equal(host.active,undefined);
});
test('serialized native opens retain only the active Sony cache lease',async t=>{
 const {directory,file}=await fixture(t),job={trackId:'first',readers:0},id='a'.repeat(64);
 const host=new NativeOutput({store:{trackFile:()=>({path:file,allowedRoot:directory})},ftp:{trackFile:()=>null},sony:{jobs:new Map([[id,job]]),audio:async()=>({path:file,allowedRoot:directory})}});
 let release;const calls=[];
 host.command=async value=>{calls.push(value);if(value.cmd==='open'&&calls.length===1)await new Promise(resolve=>release=resolve);return {session:value.session,paused:true}};
 const first=randomUUID(),second=randomUUID();
 const opening=host.start({...request(first),sonyJobId:id});while(!release)await sleep(1);
 const next=host.start({...request(second),sonyJobId:id});await sleep(5);release();
 await assert.rejects(opening,/取消/);await next;
 assert.deepEqual(calls.map(x=>x.cmd),['open','stop','open']);assert.equal(job.readers,1);
 await host.control({session:first,action:'stop'});assert.equal(job.readers,1);assert.equal(host.active.session,second);
 await host.stopCurrent();assert.equal(job.readers,0);
});
test('actual native decoder preserves DSF/DFF raw DSD and DoP payloads', {skip:process.platform!=='win32'},async t=>{
 const {directory}=await fixture(t),host=new NativeOutput();t.after(()=>host.close());
 const status=await host.status();assert.equal(status.available,true,status.error);
 for(const rate of [2822400,5644800,11289600]) for(const count of [4098,8192,32768]) {
  const generated=dsdFixture(rate,count);
  for(const format of ['dsf','dff']) {
   const file=path.join(directory,`位序 (${rate}).${format}`);await fs.writeFile(file,generated[format]);
   const raw=await host.command({cmd:'inspect',file,dsd:true,mode:'native',maxBytes:262144});
   assert.equal(raw.dsdRate,rate);assert.equal(raw.channels,2);assert.equal(raw.bytes,generated.raw.length);
   assert.deepEqual(Buffer.from(raw.dataHex,'hex'),generated.raw,`${format} ${rate} raw MSB bytes`);
   const dop=await host.command({cmd:'inspect',file,dsd:true,mode:'dop',maxBytes:262144});
   const data=Buffer.from(dop.dataHex,'hex');assert.equal(dop.sampleRate,rate/16);assert.equal(data.length,generated.raw.length*2);
   for(let frame=0;frame<generated.raw.length/4;frame++)for(let channel=0;channel<2;channel++) {
    const value=Math.round(data.readFloatLE((frame*2+channel)*4)*8388608)&0xffffff;
    assert.equal(value>>>16,frame%2?0xfa:0x05,`${format} DoP marker at ${frame}/${channel}`);
    // DoP v1.1: the oldest DSD bit is slot t0 (bit 15), so the older byte is bits 8..15.
    assert.equal((value>>>8)&255,generated.raw[frame*4+channel],`${format} first payload byte`);
    assert.equal(value&255,generated.raw[frame*4+2+channel],`${format} second payload byte`);
   }
   const pcm=await host.command({cmd:'inspect',file,dsd:true,mode:'pcm',maxBytes:262144});assert.equal(pcm.sampleRate,44100);
   const floats=Buffer.from(pcm.dataHex,'hex');assert.ok(floats.length>0);
   for(let i=0;i<floats.length;i+=4)assert.ok(Number.isFinite(floats.readFloatLE(i)));
  }
 }
});
test('seeking into unfinished Sony output buffers and a newer pause prevents automatic resume',async t=>{
 const {directory,file}=await fixture(t);const output=file.slice(0,-4);await fs.rename(file,output+'.partial');
 const job={trackId:'first',output,state:'processing',readers:0,producedBytes:44100*8+56,stream:{duration:10,sampleRate:44100,totalBytes:44100*80+56}},id='b'.repeat(64);
 const host=new NativeOutput({store:{trackFile:()=>null},ftp:{trackFile:()=>null},sony:{cacheDir:directory,jobs:new Map([[id,job]]),growingAudio:async()=>job}});
 let playing=false;const commands=[];host.command=async value=>{commands.push(value.cmd);if(value.cmd==='play')playing=true;if(value.cmd==='pause')playing=false;return {paused:!playing,playing,duration:10,position:value.position??0}};
 const session=randomUUID();await host.start({...request(session),sonyJobId:id});await host.control({session,action:'play'});
 const seek=host.control({session,action:'seek',position:7});await sleep(10);assert.equal(host.active.seeking,true);assert.equal(playing,false);
 await host.control({session,action:'pause'});job.producedBytes=job.stream.totalBytes;
 const result=await seek;assert.equal(result.paused,true);assert.equal(playing,false);assert.equal(commands.filter(cmd=>cmd==='play').length,1);
 await host.stopCurrent();assert.equal(job.readers,0);
});

test('trailing DSF ID3v2.3/v2.4 do not change native DSD or DoP payloads', {skip:process.platform!=='win32'},async t=>{
 const {directory}=await fixture(t),host=new NativeOutput();t.after(()=>host.close());const generated=dsdFixture();
 const plain=path.join(directory,'without-tags.dsf');await fs.writeFile(plain,generated.dsf);
 const expectedDop=await host.command({cmd:'inspect',file:plain,dsd:true,mode:'dop',maxBytes:262144});
 for(const version of [3,4]) {
  const file=path.join(directory,`中文 ID3v2.${version}.dsf`),bytes=taggedDsf(generated.dsf,{version});await fs.writeFile(file,bytes);
  const raw=await host.command({cmd:'inspect',file,dsd:true,mode:'native',maxBytes:262144});assert.equal(raw.bytes,generated.raw.length);
  assert.deepEqual(Buffer.from(raw.dataHex,'hex'),generated.raw);
  const dop=await host.command({cmd:'inspect',file,dsd:true,mode:'dop',maxBytes:262144});assert.equal(dop.dataHex,expectedDop.dataHex);
  assert.deepEqual(await fs.readFile(file),bytes,'Native playback must leave the ID3 tag and source file intact');
 }
});
test('actual silent WASAPI playback supports pause, seek, end and missing-ASIO errors', {skip:process.platform!=='win32'},async t=>{
 const {file}=await fixture(t),host=new NativeOutput();t.after(()=>host.close());const session=randomUUID();
 const devices=await host.command({cmd:'devices'});
 const opened=await host.command({cmd:'open',file,dsd:false,mode:'pcm',backend:'wasapi',volume:0,position:0,session});assert.equal(opened.paused,true);
 await host.command({cmd:'play',session});let playing;const startedDeadline=Date.now()+1500;
 do{await sleep(50);playing=await host.command({cmd:'status',session})}while(playing.position<=0&&Date.now()<startedDeadline);
 assert.ok(playing.position>0,'the physical system output must advance after its startup latency');assert.equal(playing.playing,true);
 const paused=await host.command({cmd:'pause',session});await sleep(100);const still=await host.command({cmd:'status',session});assert.ok(Math.abs(paused.position-still.position)<.03);
 await host.command({cmd:'seek',position:1.8,session});const seeked=await host.command({cmd:'status',session});assert.ok(Math.abs(seeked.position-1.8)<.01);
 await host.command({cmd:'play',session});await sleep(700);const ended=await host.command({cmd:'status',session});assert.equal(ended.ended,true);
 await host.command({cmd:'stop',session});
 if(!devices.devices.length)await assert.rejects(host.command({cmd:'open',file,dsd:false,mode:'pcm',backend:'asio',device:0,channel:0,volume:0,position:0,session}),/ASIO driver unavailable/);
});
test('native asynchronous PCM playback starts before file completion and cancels a waiting read', {skip:process.platform!=='win32'},async t=>{
 const {directory}=await fixture(t),host=new NativeOutput();t.after(()=>host.close());const session=randomUUID(),wav=silentWav(4),file=path.join(directory,'增长.wav.partial');
 const writer=await fs.open(file,'w');t.after(()=>writer.close());const initial=44+44100*4;
 await writer.write(wav.subarray(0,initial),0,initial,0);
 let completed=false;const completion=sleep(1500).then(async()=>{await writer.write(wav.subarray(initial),0,wav.length-initial,initial);completed=true});
 const began=Date.now();const open=await host.command({cmd:'open',file,growingBytes:wav.length,dsd:false,mode:'pcm',backend:'wasapi',volume:0,position:0,session});
 assert.equal(completed,false,'must open before the remaining PCM is produced');assert.ok(Date.now()-began<900);assert.equal(open.duration,4);
 await host.command({cmd:'play',session});await sleep(200);assert.equal((await host.command({cmd:'status',session})).playing,true);
 await fs.rename(file,path.join(directory,'增长.wav'));
 await completion;await host.command({cmd:'seek',position:3.6,session});await sleep(700);assert.equal((await host.command({cmd:'status',session})).ended,true);
 await host.command({cmd:'stop',session});
 const incomplete=path.join(directory,'取消.wav.partial'),long=silentWav(20);await fs.writeFile(incomplete,long.subarray(0,initial));
 await host.command({cmd:'open',file:incomplete,growingBytes:long.length,dsd:false,mode:'pcm',backend:'wasapi',volume:0,position:0,session});await host.command({cmd:'play',session});
 const stopping=Date.now();await host.command({cmd:'stop',session});assert.ok(Date.now()-stopping<1000,'waiting file thread must exit promptly');
 assert.equal((await host.command({cmd:'devices'})).ok,true,'native process remains usable after cancellation');
});
