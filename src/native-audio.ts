import type { MusicTrack } from './music-types';
import type { SonySettings, SonyProcessing } from './sony-audio';
const frontendId=crypto.randomUUID();
export interface OutputSettings { backend: 'browser'|'wasapi'|'asio'; device: number; channel: number; dsdMode: 'pcm'|'native'|'dop' }
export interface NativeStatus { available: boolean; devices: { id: number; name: string }[]; error?: string }
export const outputDefault: OutputSettings = { backend:'browser', device:-1, channel:0, dsdMode:'pcm' };
export function normalizeOutput(value?: Partial<OutputSettings>): OutputSettings {
 return {backend:['browser','wasapi','asio'].includes(value?.backend??'')?value!.backend!:'browser',
   device:Number.isInteger(value?.device)&&value!.device!>=-1&&value!.device!<=255?value!.device!:-1,
   channel:Number.isInteger(value?.channel)&&value!.channel!>=0&&value!.channel!<=255?value!.channel!:0,
   dsdMode:['pcm','native','dop'].includes(value?.dsdMode??'')?value!.dsdMode!:'pcm'};
}
export const isDsd = (track: MusicTrack) => /^(DSD|DSF|DFF)$/i.test(track.format)||/\.(dsf|dff)$/i.test(track.relativePath);
export const directDsd = (track: MusicTrack,output: OutputSettings) => isDsd(track)&&output.backend==='asio'&&output.dsdMode!=='pcm';
export interface SongAudio extends EventTarget {
 src: string; preload: string; volume: number; currentTime: number; readonly duration: number;
 readonly paused: boolean; readonly ended: boolean; readonly readyState: number; readonly error: { code: number; message?: string }|null;
 play(): Promise<void>; pause(): void; load(): void; removeAttribute(name: string): void;
}
interface NativeState { playing?: boolean; paused?: boolean; ended?: boolean; buffering?: boolean; position?: number; duration?: number; sourceStart?: number; sampleRate?: number; error?: string; stale?: boolean; sonyProcessing?: SonyProcessing }
export interface NativePlaybackSession {
 session: string; trackId: string; settings: OutputSettings; sonySettings: SonySettings;
 sonyJobId?: string; volume: number; state: NativeState; sonyProcessing: SonyProcessing;
}
export async function recoverNativeSession(): Promise<NativePlaybackSession|null> {
 const response=await fetch('/api/native/current',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({clientId:frontendId,clientStartedAt:performance.timeOrigin})});
 const value=await response.json();if(!response.ok)throw new Error(value.error||'无法恢复原生播放会话。');
 if(!value.session)return null;
 if(!/^[a-f0-9-]{36}$/.test(value.session)||typeof value.trackId!=='string'||!value.state||!['wasapi','asio'].includes(value.settings?.backend))throw new Error('原生播放会话无效。');
 return value;
}
export async function discardNativeSession(session: string): Promise<void> {await post('/api/native/control',{session,action:'stop'})}
async function post(route: string,value: unknown,signal?: AbortSignal): Promise<NativeState> {
 const response=await fetch(route,{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({...value as object,clientId:frontendId}),signal});
 const result=await response.json();if(!response.ok)throw new Error(result.error||'原生音频输出失败。');return result;
}
/** Media lifecycle adapter; all song samples go to the C++ host, never HTMLAudio. */
export class NativeAudio extends EventTarget implements SongAudio {
 src='';preload='metadata';paused=true;ended=false;duration=0;readyState=0;error: {code:number;message:string}|null=null;
 private position=0;private gain=1;private readonly session: string;private readonly abort=new AbortController();
 private opened=false;private disposed=false;private desiredPlaying=false;private opening?: Promise<void>;private playingTask?: Promise<void>;
 private tail: Promise<unknown>=Promise.resolve();private pollTimer?: ReturnType<typeof setTimeout>;private gainTimer?: ReturnType<typeof setTimeout>;
 private readonly direct: boolean;
 private readonly track: MusicTrack;
 private readonly output: OutputSettings;
 private readonly sonySettings?: SonySettings;
 preferredVolume: number;
 readonly recovered: boolean;
 sonyProcessing?: SonyProcessing;
 sourceStartTime: number;
 constructor(track: MusicTrack,output: OutputSettings,sourceStartTime=0,options: {sonySettings?:SonySettings;targetVolume?:number;recovered?:NativePlaybackSession}={}){
   super();this.track=track;this.output=output;this.sourceStartTime=sourceStartTime;this.direct=directDsd(track,output);this.sonySettings=options.sonySettings;this.recovered=!!options.recovered;
   this.session=options.recovered?.session??crypto.randomUUID();
   this.preferredVolume=options.targetVolume??options.recovered?.volume??1;
   if(options.recovered){const value=options.recovered;this.opened=true;this.readyState=1;this.accept(value.state);this.gain=value.volume;this.paused=!value.state.playing;this.ended=value.state.ended===true;this.desiredPlaying=!this.paused;this.sonyProcessing=value.sonyProcessing;}
 }
 get sessionId(){return this.session}
 private needsProgress(){return this.recovered&&this.sonyProcessing?.streaming===true&&this.sonyProcessing.progress<1}
 monitor(){if(!this.paused||this.needsProgress())this.poll()}
 get volumeLocked(){return this.direct}
 get volume(){return this.direct?1:this.gain}
 set volume(value: number){if(this.direct||!Number.isFinite(value))return;this.gain=Math.max(0,Math.min(1,value));if(this.opened&&!this.gainTimer&&!this.disposed)this.gainTimer=setTimeout(()=>{this.gainTimer=undefined;void this.control('volume',{volume:this.gain,targetVolume:this.preferredVolume}).catch(error=>this.failure(error))},40)}
 get currentTime(){return this.position}
 set currentTime(value: number){if(!Number.isFinite(value)||value<0)return;this.position=value;if(this.opened&&!this.disposed){this.event('seeking');if(!this.paused)this.event('waiting');void this.control('seek',{position:value}).then(state=>{this.accept(state);this.event('seeked')}).catch(error=>this.failure(error))}}
 private event(name: string){this.dispatchEvent(new Event(name))}
 private control(action: string,extra: object={}): Promise<NativeState> {
   const task=this.tail.catch(()=>{}).then(()=>post('/api/native/control',{session:this.session,action,...extra},this.abort.signal));this.tail=task;return task;
 }
 private accept(value: NativeState){if(this.disposed)return;if(value.stale)throw new Error('音频输出会话已结束，请重新播放。');if(value.error)throw new Error(value.error);if(Number.isFinite(value.duration))this.duration=value.duration!;if(Number.isFinite(value.position))this.position=value.position!;if(Number.isFinite(value.sourceStart))this.sourceStartTime=value.sourceStart!;if(value.sonyProcessing)this.sonyProcessing=value.sonyProcessing}
 private async initialize(){
   if(this.opened)return;if(this.opening)return this.opening;
   this.opening=(async()=>{
     const job=/^\/api\/sony\/audio\/([a-f0-9]{64})$/.exec(this.src)?.[1];
     const state=await post('/api/native/start',{session:this.session,trackId:this.track.id,settings:this.output,volume:this.direct?1:this.gain,targetVolume:this.preferredVolume,position:this.position,sonySettings:this.sonySettings,...(job?{sonyJobId:job}:{})},this.abort.signal);
     if(this.disposed)return;this.accept(state);this.opened=true;this.readyState=1;this.event('loadedmetadata');this.event('durationchange');
   })();return this.opening;
 }
 async play(): Promise<void>{
   if(this.disposed)throw new Error('歌曲已经停止。');this.desiredPlaying=true;if(this.playingTask)return this.playingTask;
   this.playingTask=(async()=>{
    await this.initialize();
    while(!this.disposed){const desired=this.desiredPlaying,state=await this.control(desired?'play':'pause');if(this.disposed)return;this.accept(state);if(desired!==this.desiredPlaying)continue;this.paused=!desired;if(desired){this.ended=false;this.event('playing');this.poll()}return}
   })().finally(()=>{this.playingTask=undefined});
   return this.playingTask;
 }
 pause(): void {this.desiredPlaying=false;this.paused=true;clearTimeout(this.pollTimer);this.pollTimer=undefined;if(this.opened&&!this.disposed)void post('/api/native/control',{session:this.session,action:'pause'},this.abort.signal).then(state=>{if(!this.disposed&&!this.desiredPlaying){this.accept(state);this.event('timeupdate');this.monitor()}}).catch(error=>this.failure(error));this.event('pause')}
 removeAttribute(name: string): void {if(name==='src')this.src=''}
 load(): void {if(this.disposed)return;this.disposed=true;this.desiredPlaying=false;this.abort.abort();clearTimeout(this.pollTimer);clearTimeout(this.gainTimer);this.paused=true;this.readyState=0;
   void post('/api/native/control',{session:this.session,action:'stop'}).catch(()=>{});
 }
 private poll(){
   clearTimeout(this.pollTimer);if(this.disposed||this.paused&&!this.needsProgress())return;
   this.pollTimer=setTimeout(()=>{this.pollTimer=undefined;void this.control('status').then(state=>{
     if(this.disposed)return;
     if(this.paused){if(this.needsProgress()){this.accept({...state,position:undefined});this.event('timeupdate');this.poll()}return}
     this.accept(state);this.event('timeupdate');if(state.buffering)this.event('waiting');else if(!state.ended)this.event('playing');
     if(state.ended){this.ended=true;this.paused=true;this.desiredPlaying=false;this.event('ended')}else this.poll();
   }).catch(error=>this.failure(error))},250);
 }
 private failure(error: unknown){if(this.disposed)return;this.error={code:4,message:error instanceof Error?error.message:'原生输出失败。'};this.paused=true;this.desiredPlaying=false;clearTimeout(this.pollTimer);void post('/api/native/control',{session:this.session,action:'stop'}).catch(()=>{});this.event('error')}
}
