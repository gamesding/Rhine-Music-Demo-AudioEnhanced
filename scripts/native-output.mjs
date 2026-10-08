import path from 'node:path'
import { promises as fs } from 'node:fs'
import { spawn } from 'node:child_process'
import { StringDecoder } from 'node:string_decoder'
import { createHash } from 'node:crypto'
import { fileURLToPath } from 'node:url'
import { boundedSource,sonySettings } from './sony-walkman.mjs'
const project=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..')
const fail=(message,status=400)=>Object.assign(new Error(message),{status})
const token=value=>typeof value==='string'&&/^[a-f0-9-]{36}$/.test(value)
export function outputSettings(value) {
 if(!value||!['wasapi','asio'].includes(value.backend)||!Number.isInteger(value.device)||value.device< -1||value.device>255||
   !Number.isInteger(value.channel)||value.channel<0||value.channel>255||!['pcm','native','dop'].includes(value.dsdMode))throw fail('无效的原生输出设置')
 if(value.backend==='asio'&&value.device<0)throw fail('请先选择已安装的 ASIO 驱动')
 return {backend:value.backend,device:value.device,channel:value.channel,dsdMode:value.dsdMode}
}
export class NativeOutput {
 constructor({store,ftp,sony,executable=process.env.RHINE_NATIVE_AUDIO??path.join(project,'vendor/audio/windows-x64/rhine-audio-host.exe')}={}) {
   this.store=store;this.ftp=ftp;this.sony=sony;this.executable=path.resolve(executable);this.pending=new Map();this.counter=0;this.generation=0;this.tail=Promise.resolve();this.startTail=Promise.resolve();this.closed=false
   this.cancelledSessions=new Set()
 }
 async verify() {
   if(process.platform!=='win32')throw fail('ASIO / Windows 原生输出仅用于 Windows 桌面版',503)
   const manifest=JSON.parse(await fs.readFile(path.join(path.dirname(this.executable),'assets.json'),'utf8'))
   for(const [name,expected] of Object.entries(manifest.files)) {
     if(!/^[a-z0-9.-]+$/i.test(name))throw fail('原生组件清单无效',503)
     if(createHash('sha256').update(await fs.readFile(path.join(path.dirname(this.executable),name))).digest('hex')!==expected)throw fail(`原生音频组件校验失败：${name}`,503)
   }
 }
 async connect() {
   if(this.closed)throw fail('播放器正在退出',503)
   if(this.child)return
   if(this.connecting)return this.connecting
   this.connecting=(async()=>{
     await this.verify();if(this.closed)throw fail('播放器正在退出',503)
     const child=this.child=spawn(this.executable,[],{windowsHide:true,shell:false,stdio:['pipe','pipe','pipe']})
     let buffer='';const decoder=new StringDecoder('utf8');child.stderr.on('data',()=>{})
     child.stdout.on('data',chunk=>{
       buffer+=decoder.write(chunk);if(buffer.length>1_200_000){child.kill();return}
       let end;while((end=buffer.indexOf('\n'))>=0){const line=buffer.slice(0,end);buffer=buffer.slice(end+1);let value;try{value=JSON.parse(line)}catch{child.kill();return}
         if(value.fatal){child.kill();continue}
         const pending=this.pending.get(value.id);if(!pending)continue;this.pending.delete(value.id);clearTimeout(pending.timer)
         value.ok?pending.resolve(value):pending.reject(fail(value.error||'原生输出失败',503))
       }
     })
     const disconnected=()=>{if(this.child!==child)return;this.child=undefined;this.releaseLease();for(const request of this.pending.values()){clearTimeout(request.timer);request.reject(fail('原生音频进程已退出，请重新选择输出设备',503))}this.pending.clear()}
     child.once('error',disconnected);child.once('close',disconnected)
   })().finally(()=>{this.connecting=undefined})
   return this.connecting
 }
 command(value) {
   const task=this.tail.catch(()=>{}).then(async()=>{
     await this.connect();const child=this.child,id=++this.counter
     return new Promise((resolve,reject)=>{
       const timer=setTimeout(()=>{this.pending.delete(id);child.kill();reject(fail('音频驱动响应超时，已停止原生输出',503))},20_000)
       this.pending.set(id,{resolve,reject,timer});child.stdin.write(JSON.stringify({...value,id})+'\n',error=>{if(error){clearTimeout(timer);this.pending.delete(id);reject(fail('原生音频进程无法接收请求',503))}})
     })
   });this.tail=task;return task
 }
 async status() {
   try {const result=await this.command({cmd:'devices'});return {available:true,devices:result.devices,backends:['wasapi','asio'],dsdModes:['pcm','native','dop']}}
   catch(error){return {available:false,devices:[],error:error.message}}
 }
 async refresh() {
   await this.stopCurrent();const child=this.child;
   if(child)await new Promise(resolve=>{const timer=setTimeout(()=>child.kill(),2000);child.once('close',()=>{clearTimeout(timer);resolve()});child.stdin.end()});
   return this.status()
 }
 processing() {
   const job=this.lease;if(!job)return {state:'off',progress:0};
   const view=this.sony.view(job),enabled=job.settings.dsee||job.settings.dc||job.settings.vinyl;
   return {state:view.state==='error'?'error':enabled?'active':'off',progress:view.progress??0,
     effectiveSettings:{...job.settings},bypassed:view.bypassed,message:view.message,sampleRate:view.sampleRate,
     streaming:view.streaming===true,bufferedSeconds:view.bufferedSeconds,positionOffset:view.positionOffset,workers:view.workers};
 }
 async current(value) {
   if(!token(value?.clientId))throw fail('无效的前端播放会话');
   if(value.clientStartedAt!==undefined&&(!Number.isFinite(value.clientStartedAt)||value.clientStartedAt<0))throw fail('无效的前端时间标识');
   const epoch=value.clientStartedAt??Date.now();
   if(this.frontendEpoch!==undefined&&epoch<this.frontendEpoch)return {session:null,stale:true};
   // A new document adopts the existing stream. Older documents cannot later
   // reopen a track or stop the stream that has just been adopted.
   this.frontendOwner=value.clientId;this.frontendEpoch=epoch;
   if(this.reserved&&this.reserved!==this.active?.session){++this.generation;this.reserved=this.active?.session;await this.startTail.catch(()=>{})}
   const active=this.active;
   if(!active){for(const job of this.sony?.jobs?.values()??[])if(!job.readers&&['queued','processing'].includes(job.state))this.sony.cancel(job.id);return {session:null}}
   if(this.lease?.state==='error'){await this.stopCurrent();return {session:null,error:'Sony 处理已失败，原生播放已停止。'}}
   try {
     const state=this.timeline(await this.command({cmd:'status',session:active.session}));
     if(this.active!==active||this.frontendOwner!==value.clientId)return {session:null};
     if(state.stale){this.active=undefined;this.releaseLease();return {session:null}}
     return {session:active.session,trackId:active.trackId,settings:{...active.settings},sonySettings:{...active.sonySettings},
       sonyJobId:active.sonyJobId,volume:active.targetVolume,sonyProcessing:this.processing(),
       state:{...state,playing:active.desiredPlaying&&!state.ended,paused:!active.desiredPlaying||!!state.ended,...(active.seeking?{buffering:true}:{})}};
   }catch(error){if(this.active===active&&this.frontendOwner===value.clientId)await this.stopCurrent().catch(()=>{});throw error}
 }
 releaseLease(keep) {if(this.lease){const old=this.lease;old.readers=Math.max(0,(old.readers??1)-1);this.lease=undefined;if(old!==keep&&!old.readers&&old.state==='processing')this.sony?.cancel?.(old.id)}}
 timeline(value,lease=this.lease) {
   if(!lease)return value;
   const metadata=lease.result??lease.stream;if(!metadata)return value;
   const offset=metadata.positionOffset??0,duration=metadata.duration+offset;
   return {...value,duration,sourceStart:offset,...(Number.isFinite(value.position)?{position:Math.min(duration,value.position+offset)}:{})};
 }
 async stopCurrent() {
   ++this.generation;this.reserved=undefined
   await this.startTail.catch(()=>{})
   const current=this.active;this.active=undefined
   try{if(current&&this.child)await this.command({cmd:'stop',session:current.session})}finally{this.releaseLease()}
   return {stopped:true}
 }
 async start(value) {
   if(this.frontendOwner&&value.clientId!==this.frontendOwner)throw fail('前端已经刷新，此播放请求已取消',409)
   const settings=outputSettings(value.settings)
   const requestedSony=value.sonySettings===undefined?{dsee:false,dc:0,vinyl:0}:sonySettings(value.sonySettings)
   if(!token(value.session)||typeof value.trackId!=='string'||!/^[-a-zA-Z0-9]+$/.test(value.trackId))throw fail('无效的原生播放请求')
   if(this.cancelledSessions.has(value.session))throw fail('此播放请求已取消',409)
   if(!Number.isFinite(value.volume)||value.volume<0||value.volume>1||!Number.isFinite(value.position)||value.position<0)throw fail('无效的音量或播放位置')
   if(value.targetVolume!==undefined&&(!Number.isFinite(value.targetVolume)||value.targetVolume<0||value.targetVolume>1))throw fail('无效的歌曲音量')
   if(value.sonyJobId!==undefined&&!/^[a-f0-9]{64}$/.test(value.sonyJobId))throw fail('无效的音效缓存 ID')
   const generation=++this.generation;this.reserved=value.session
   let descriptor,lease,growingBytes
   if(value.trackId.startsWith('ftp-'))await this.ftp.ensure(value.trackId)
   if(value.sonyJobId) {
     const job=this.sony.jobs.get(value.sonyJobId)
     if(!job||job.trackId!==value.trackId)throw fail('音效缓存与所选歌曲不一致',403)
     if(job.state==='processing'){await this.sony.growingAudio(value.sonyJobId);descriptor={path:job.output+'.partial',allowedRoot:this.sony.cacheDir};growingBytes=job.stream.totalBytes}
     else descriptor=await this.sony.audio(value.sonyJobId);lease=job
   }else descriptor=this.store.trackFile(value.trackId)??this.ftp.trackFile(value.trackId)
   if(!descriptor)throw fail('原生输出用于本地与 FTP 曲目，请选择曲库中的歌曲',404)
   let source;
   try{({source}=await boundedSource(descriptor))}catch(error){if(lease?.state==='ready'&&growingBytes){({source}=await boundedSource(await this.sony.audio(value.sonyJobId)));growingBytes=undefined}else throw error}
   if(generation!==this.generation||this.closed)throw fail('此播放请求已取消',409)
   const dsd=/\.(dsf|dff)$/i.test(source),mode=dsd&&settings.backend==='asio'?settings.dsdMode:'pcm'
   const commit=this.startTail.catch(()=>{}).then(async()=>{
    if(generation!==this.generation||this.closed)throw fail('此播放请求已取消',409)
    const offset=lease?.result?.positionOffset??lease?.stream?.positionOffset??0;
    if(value.position+1e-6<offset)throw fail('此位置早于当前音效片段，请重新准备所选位置',409);
    const position=Math.max(0,value.position-offset);
    if(lease?.state==='processing'&&position>0){const target=Math.min(lease.stream.duration,position+.5)*lease.stream.sampleRate*8+56;while(lease.state==='processing'&&lease.producedBytes<target){if(generation!==this.generation||this.closed)throw fail('此播放请求已取消',409);await new Promise(resolve=>setTimeout(resolve,100))}if(lease.state==='error')throw fail(lease.error||'Sony 处理失败',503)}
    this.releaseLease(lease);this.active=undefined
    if(lease){lease.readers=(lease.readers??0)+1;this.lease=lease}
    try {
     const open={cmd:'open',file:source,dsd,mode,session:value.session,backend:settings.backend,device:settings.device,channel:settings.channel,volume:mode==='pcm'?value.volume:1,position,...(growingBytes?{growingBytes}:{})};
     let result;
     try{result=await this.command(open)}catch(error){
      // A completed worker atomically renames the same file while we acquire it.
      if(!growingBytes||!/progressive PCM is not available/.test(error.message))throw error;
      const completed=await boundedSource({path:lease.output,allowedRoot:this.sony.cacheDir});
      if((await fs.stat(completed.source)).size!==growingBytes)throw error;
      result=await this.command({...open,file:completed.source});
     }
     if(generation!==this.generation||this.closed){await this.command({cmd:'stop',session:value.session});throw fail('此播放请求已取消',409)}
     if(this.frontendOwner&&value.clientId!==this.frontendOwner){await this.command({cmd:'stop',session:value.session});throw fail('前端已经刷新，此播放请求已取消',409)}
     this.active={session:value.session,generation,desiredPlaying:false,trackId:value.trackId,settings,sonySettings:requestedSony,sonyJobId:value.sonyJobId,volume:value.volume,targetVolume:value.targetVolume??value.volume};return this.timeline(result)
    }catch(error){this.releaseLease();throw error}
   });this.startTail=commit;return commit
 }
 async control(value) {
   if(!token(value.session)||!['status','play','pause','stop','seek','volume'].includes(value.action))throw fail('无效的原生控制请求')
   if(this.frontendOwner&&value.clientId!==this.frontendOwner)return {stale:true}
   if(value.action==='stop'){this.cancelledSessions.add(value.session);if(this.cancelledSessions.size>512)this.cancelledSessions.delete(this.cancelledSessions.values().next().value)}
   if(value.action==='stop'&&this.reserved===value.session) {++this.generation;this.reserved=undefined}
   if(this.active?.session!==value.session)return {stopped:true,session:value.session,stale:true}
   if(value.action==='stop') {
     try{await this.command({cmd:'stop',session:value.session})}catch(error){if(this.active?.session===value.session)throw error}
     if(this.active?.session===value.session){this.active=undefined;this.releaseLease()}
     return {stopped:true,session:value.session}
   }
   if(value.action==='seek'&&(!Number.isFinite(value.position)||value.position<0))throw fail('无效的播放位置')
   if(value.action==='volume'&&(!Number.isFinite(value.volume)||value.volume<0||value.volume>1))throw fail('无效的歌曲音量')
   if(value.action==='volume'&&value.targetVolume!==undefined&&(!Number.isFinite(value.targetVolume)||value.targetVolume<0||value.targetVolume>1))throw fail('无效的歌曲音量')
   if(this.lease?.state==='error')throw fail(this.lease.error||'Sony 实时处理失败',503);
   const offset=this.lease?.result?.positionOffset??this.lease?.stream?.positionOffset??0;
   if(value.action==='seek'&&value.position+1e-6<offset)throw fail('此位置早于当前音效片段，请重新准备所选位置',409);
   const position=value.action==='seek'?Math.max(0,value.position-offset):undefined;
   const active=this.active;
   if(value.action==='play'||value.action==='pause'){active.desiredPlaying=value.action==='play';if(active.seeking&&value.action==='play')return {...this.timeline(await this.command({cmd:'status',session:value.session})),buffering:true}}
   if(value.action==='seek'&&this.lease?.state==='processing') {
     const job=this.lease,target=Math.min(job.stream.duration,position+.5)*job.stream.sampleRate*8+56;
     if(job.producedBytes<target) {
      active.seeking=true;
      try {
       await this.command({cmd:'pause',session:value.session});
       while(job.state==='processing'&&job.producedBytes<target){if(this.active!==active||this.cancelledSessions.has(value.session)||this.closed)return {stale:true};await new Promise(resolve=>setTimeout(resolve,100))}
       if(job.state==='error')throw fail(job.error||'Sony 处理失败',503);
       if(this.active!==active||this.cancelledSessions.has(value.session)||this.closed)return {stale:true};
       const seeked=await this.command({cmd:'seek',session:value.session,position});
       return this.timeline(active.desiredPlaying?await this.command({cmd:'play',session:value.session}):seeked);
      }finally{active.seeking=false}
     }
   }
   if(this.active?.session!==value.session||this.cancelledSessions.has(value.session))return {stale:true};
   const result=this.timeline(await this.command({cmd:value.action,session:value.session,...(value.action==='seek'?{position}:{}),...(value.action==='volume'?{volume:value.volume}:{})}));
   if(value.action==='volume'&&this.active===active){active.volume=value.volume;active.targetVolume=value.targetVolume??value.volume}
   const reported=value.action==='status'?{...result,sonyProcessing:this.processing()}:result;
   return active.seeking?{...reported,buffering:true}:reported;
 }
 close(){this.closed=true;++this.generation;this.child?.stdin.end();this.releaseLease();const child=this.child;if(child){const timer=setTimeout(()=>child.kill(),2000);timer.unref();child.once('close',()=>clearTimeout(timer))}}
}
