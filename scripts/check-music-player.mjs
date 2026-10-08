import test from 'node:test'
import assert from 'node:assert/strict'
import { MusicPlayer } from '../src/music-player.ts'

const settle = async () => { for (let i = 0; i < 12; i += 1) await Promise.resolve() }

/** No browser, network, real timers, or actual sound is used by these tests. */
function environment(t) {
  let now = 0
  let nextTimer = 1
  const timers = new Map()
  const instances = []
  const document = new EventTarget()
  const previousAudio = Object.getOwnPropertyDescriptor(globalThis, 'Audio')
  const previousDocument = Object.getOwnPropertyDescriptor(globalThis, 'document')
  const previousTimeout = globalThis.setTimeout
  const previousClear = globalThis.clearTimeout
  const previousNow = Object.getOwnPropertyDescriptor(performance, 'now')

  class ControlledAudio extends EventTarget {
    constructor(src = '') {
      super()
      this.src = src
      this.volume = 1
      this.paused = true
      this.ended = false
      this.duration = 120
      this.currentTime = 0
      this.readyState = 1
      this.playCalls = 0
      this.deferred = []
      this.holdPlay = false
      instances.push(this)
    }

    play() {
      this.playCalls += 1
      if (this.holdPlay) {
        this.holdPlay = false
        return new Promise((resolve) => this.deferred.push(() => { this.begin(); resolve() }))
      }
      this.begin()
      return Promise.resolve()
    }

    begin() {
      this.paused = false
      this.dispatchEvent(new Event('playing'))
    }

    resolvePlay() {
      assert.ok(this.deferred.length, 'there must be a held audio play request')
      this.deferred.shift()()
    }

    pause() {
      if (this.paused) return
      this.paused = true
      this.dispatchEvent(new Event('pause'))
    }

    removeAttribute(name) { if (name === 'src') this.src = '' }
    load() {}
  }

  Object.defineProperty(globalThis, 'Audio', { configurable: true, writable: true, value: ControlledAudio })
  Object.defineProperty(globalThis, 'document', { configurable: true, writable: true, value: document })
  Object.defineProperty(performance, 'now', { configurable: true, value: () => now })
  globalThis.setTimeout = (callback, delay = 0) => {
    const id = nextTimer++
    timers.set(id, { callback, at: now + Number(delay) })
    return id
  }
  globalThis.clearTimeout = (id) => timers.delete(id)
  t.after(() => {
    if (previousAudio) Object.defineProperty(globalThis, 'Audio', previousAudio)
    else delete globalThis.Audio
    if (previousDocument) Object.defineProperty(globalThis, 'document', previousDocument)
    else delete globalThis.document
    if (previousNow) Object.defineProperty(performance, 'now', previousNow)
    else delete performance.now
    globalThis.setTimeout = previousTimeout
    globalThis.clearTimeout = previousClear
  })

  return {
    instances,
    gesture: () => document.dispatchEvent(new Event('pointerdown')),
    pendingTimers: () => timers.size,
    async advance(milliseconds) {
      await settle()
      const end = now + milliseconds
      let next
      while ((next = [...timers.entries()].filter(([, timer]) => timer.at <= end).sort((a, b) => a[1].at - b[1].at)[0])) {
        now = next[1].at
        timers.delete(next[0])
        next[1].callback()
        await settle()
      }
      now = end
      await settle()
    },
  }
}

const track = (id) => ({ id, albumId: 'album-test', title: id, artist: 'Test artist', duration: 120, format: 'WAV', browserPlayable: true, relativePath: `${id}.wav`, audioUrl: `/api/audio/${id}` })
const near = (actual, expected) => assert.ok(Math.abs(actual - expected) < 0.0001, `expected ${actual} ≈ ${expected}`)
const sonyJob = (state = 'ready', extra = {}) => ({ id: 'a'.repeat(64), state, progress: state === 'ready' ? 1 : .25,
  sampleRate: 176400, audioUrl: `/api/sony/audio/${'a'.repeat(64)}`, workers: 3, ...extra })
const reply = (value, status = 200) => new Response(JSON.stringify(value), { status, headers: { 'Content-Type': 'application/json' } })

test('the original source URL is preserved for FTP and online tracks when Sony is OFF', async (t) => {
  const env = environment(t)
  const player = new MusicPlayer({ bgmEnabled: false, songFadeEnabled: false })
  const remote = { ...track('remote'), audioUrl: '/api/ftp/audio/ftp-0123456789' }
  await player.play(remote.id,[remote])
  assert.equal(env.instances[1].src,remote.audioUrl)
  assert.equal(player.state.sonyProcessing.state,'off')
  player.dispose()
})

test('Sony starts from a playable growing result, then monitors completion and real failures', async (t) => {
  const env = environment(t)
  let job = sonyJob('processing',{ playable: true })
  const submitted = []
  t.mock.method(globalThis,'fetch',async (url,options) => {
    if (options.body) submitted.push(JSON.parse(options.body))
    return reply(job)
  })
  const player = new MusicPlayer({ bgmEnabled: false, songFadeEnabled: false, sonySettings: { dsee: true, dc: 2, vinyl: 1 } })
  await player.play('first',[track('first')])
  assert.equal(player.state.playing,true,'does not wait for the whole song')
  assert.equal(env.instances[1].src,job.audioUrl)
  assert.equal(player.state.sonyProcessing.streaming,true)
  assert.equal(player.state.sonyProcessing.workers,3)
  assert.equal(submitted[0].parallel,true)
  assert.equal(submitted[0].streaming,true)
  job = sonyJob()
  await env.advance(750)
  assert.equal(player.state.sonyProcessing.progress,1)
  assert.equal(player.state.sonyProcessing.streaming,false)
  player.stop()
  job = sonyJob('processing',{ playable: true })
  await player.play('first')
  job = sonyJob('error',{ error: 'Original DSP failed' })
  await env.advance(750)
  assert.equal(player.state.transport,'error')
  assert.equal(player.state.sonyProcessing.state,'error')
  assert.equal(env.instances[2].paused,true)
  player.dispose()
  assert.equal(env.pendingTimers(),0)
})

test('changing original Sony settings preserves paused position and never plays a cancelled request', async (t) => {
  const env = environment(t)
  let job = sonyJob()
  t.mock.method(globalThis,'fetch',async () => reply(job))
  const player = new MusicPlayer({ bgmEnabled: false, songFadeEnabled: false })
  await player.play('first',[track('first')])
  player.seek(37)
  await player.toggle()
  await player.setSonySettings({ dsee: true, dc: 0, vinyl: 0 })
  assert.equal(player.state.transport,'paused')
  assert.equal(env.instances[2].currentTime,37)
  assert.equal(env.instances[2].playCalls,0,'paused settings changes must stay paused')
  player.stop()
  job = sonyJob('queued',{ audioUrl: undefined })
  const pending = player.play('first')
  await settle()
  assert.equal(player.state.sonyProcessing.state,'preparing')
  await player.toggle()
  job = sonyJob()
  await env.advance(1500)
  await pending
  assert.equal(player.state.playing,false)
  assert.equal(player.state.sonyProcessing.state,'off')
  assert.equal(env.instances.length,3,'cancelled work creates no audio source')
  player.dispose()
  assert.equal(env.pendingTimers(),0)
})

test('BGM has an independent default, live volume, zero-volume gate, and clamped settings', async (t) => {
  const env = environment(t)
  const player = new MusicPlayer({ volume: 0 })
  const bgm = env.instances[0]
  assert.equal(player.state.songFadeEnabled, true)
  assert.equal(player.state.bgmVolume, 0.18)
  assert.equal(bgm.playCalls, 0, 'no autoplay before a gesture')
  env.gesture()
  await env.advance(700)
  near(bgm.volume, 0.18)
  assert.equal(player.state.bgmPlaying, true, 'muted songs do not mute the BGM')
  player.setVolume(1)
  await env.advance(700)
  near(bgm.volume, 0.18)
  player.setBgmVolume(0.42)
  await env.advance(700)
  near(bgm.volume, 0.42)
  assert.equal(player.state.volume, 1)
  player.setBgmVolume(NaN)
  assert.equal(player.state.bgmVolume, 0.42)
  player.setBgmVolume(-1)
  await env.advance(250)
  assert.equal(player.state.bgmVolume, 0)
  assert.equal(bgm.paused, true)
  assert.equal(player.state.bgmEnabled, true, 'zero volume preserves the independent enabled preference')
  player.setBgmVolume(9)
  await env.advance(700)
  assert.equal(player.state.bgmVolume, 1)
  near(bgm.volume, 1)
  player.dispose()
  assert.equal(env.pendingTimers(), 0)
})

test('rapid Sony changes during paused preparation retain pause intent and playhead',async t=>{
 const env=environment(t),pending=[];
 t.mock.method(globalThis,'fetch',async(url,init)=>{
  if(String(url).endsWith('/api/sony/prepare'))return pending.length<2?new Promise(resolve=>pending.push({resolve,body:JSON.parse(init.body)})):reply(sonyJob());
  return reply({ok:true});
 });
 const player=new MusicPlayer({bgmEnabled:false,songFadeEnabled:false});
 await player.play('first',[track('first')]);player.seek(37);await player.toggle();
 const first=player.setSonySettings({dsee:true,dc:2,vinyl:1});await settle();
 assert.equal(player.state.transport,'loading');
 const second=player.setSonySettings({dsee:true,dc:6,vinyl:4});await settle();
 assert.equal(pending.length,2);
 pending[1].resolve(reply(sonyJob()));await second;
 pending[0].resolve(reply(sonyJob()));await first;
 assert.equal(player.state.transport,'paused');assert.equal(player.state.playing,false);assert.equal(player.state.currentTime,37);
 assert.equal(env.instances.at(-1).currentTime,37);assert.equal(env.instances.at(-1).playCalls,0);
 await player.toggle();assert.equal(player.state.transport,'playing');assert.equal(env.instances.at(-1).currentTime,37);
 player.dispose();assert.equal(env.pendingTimers(),0);
});

test('song playback waits for BGM silence despite rapid BGM volume and toggle changes', async (t) => {
  const env = environment(t)
  // Isolate BGM timing from the optional song envelope in this transport check.
  const player = new MusicPlayer({ volume: 0.65, bgmVolume: 0.3, songFadeEnabled: false })
  player.setQueue([track('first')])
  env.gesture()
  await env.advance(700)
  const bgm = env.instances[0]
  const playing = player.play('first')
  const song = env.instances[1]
  await env.advance(96)
  assert.equal(song.playCalls, 0)
  assert.ok(bgm.volume > 0 && bgm.volume < 0.3)
  player.setBgmVolume(0.8)
  player.setBgmEnabled(false)
  player.setBgmEnabled(true)
  player.setVolume(0.25)
  await env.advance(100)
  assert.equal(song.playCalls, 0, 'controls must not bypass the shared fade-out promise')
  await env.advance(60)
  await playing
  assert.equal(song.playCalls, 1)
  assert.equal(song.volume, 0.25)
  assert.equal(bgm.volume, 0)
  assert.equal(bgm.paused, true)
  assert.equal(player.state.playing, true)
  assert.equal(player.state.bgmVolume, 0.8)
  player.setBgmVolume(0.4)
  await env.advance(700)
  assert.equal(song.volume, 0.25, 'BGM volume cannot alter song output')
  assert.equal(bgm.paused, true, 'BGM stays silent while a song plays')
  player.stop()
  await env.advance(700)
  near(bgm.volume, 0.4)
  assert.equal(player.state.bgmPlaying, true)
  player.dispose()
})

test('rapidly cancelling a pending song restores only the latest BGM volume', async (t) => {
  const env = environment(t)
  const player = new MusicPlayer({ bgmVolume: 0.5 })
  player.setQueue([track('first')])
  env.gesture()
  await env.advance(700)
  const bgm = env.instances[0]
  const pending = player.play('first')
  const song = env.instances[1]
  await env.advance(72)
  player.stop()
  player.setBgmVolume(0.2)
  player.setBgmEnabled(false)
  await env.advance(24)
  player.setBgmEnabled(true)
  player.setBgmVolume(0.33)
  await env.advance(700)
  await pending
  assert.equal(song.playCalls, 0, 'cancelled song never starts after the old fade finishes')
  assert.equal(song.paused, true)
  near(bgm.volume, 0.33)
  assert.equal(player.state.bgmPlaying, true)
  assert.equal(player.state.playing, false)
  player.dispose()
  await env.advance(1000)
  assert.equal(bgm.paused, true)
  assert.equal(env.pendingTimers(), 0)
})

test('a late BGM play resolution stays silent when a song has taken over', async (t) => {
  const env = environment(t)
  const player = new MusicPlayer({ bgmVolume: 0.4, songFadeEnabled: false })
  const bgm = env.instances[0]
  bgm.holdPlay = true
  player.setQueue([track('first')])
  env.gesture()
  await settle()
  assert.equal(bgm.playCalls, 1)
  const playing = player.play('first')
  await env.advance(250)
  await playing
  const song = env.instances[1]
  assert.equal(song.paused, false)
  bgm.resolvePlay()
  await settle()
  assert.equal(bgm.paused, true)
  assert.equal(bgm.volume, 0)
  assert.equal(player.state.bgmPlaying, false)
  assert.equal(player.state.playing, true)
  player.dispose()
})

test('native DSD and DoP bypass Sony, browser song audio, fades and digital volume',async t=>{
 const env=environment(t);
 for(const mode of ['native','dop']) {
  const count=env.instances.length,calls=[];
  t.mock.method(globalThis,'fetch',async(url,options)=>{assert.ok(String(url).startsWith('/api/native/'),'direct DSD must never request Sony processing');const value=JSON.parse(options.body);calls.push(value);return reply({session:value.session,duration:120,position:0,paused:value.action!=='play'})});
  const dsd={...track('dsd'),format:'DSF',relativePath:'dsd.dsf',browserPlayable:false};
  const player=new MusicPlayer({outputSettings:{backend:'asio',device:0,channel:0,dsdMode:mode},sonySettings:{dsee:true,dc:2,vinyl:1}});
  env.gesture();await player.play(dsd.id,[dsd]);
  assert.equal(player.state.playing,true);assert.equal(player.state.volumeLocked,true);assert.equal(player.state.sonyProcessing.state,'off');
  assert.equal(env.instances.length,count+1,'only the silent atmosphere placeholder exists');assert.equal(env.instances.at(-1).playCalls,0);
  const volume=player.state.volume;player.setVolume(.1);assert.equal(player.state.volume,volume);
  assert.equal(calls.find(x=>x.trackId).volume,1);assert.ok(!calls.some(x=>x.action==='volume'));
  await player.toggle();assert.equal(player.state.transport,'paused');player.dispose();await settle();assert.equal(env.pendingTimers(),0);
  t.mock.restoreAll();
 }
});
test('native Sony processing honors full-cache mode and hands its result to C++ output',async t=>{
 const env=environment(t),calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=options?.body?JSON.parse(options.body):{};calls.push({url,value});return reply(String(url).startsWith('/api/sony/')?sonyJob():{session:value.session,duration:120,position:value.position??0,paused:value.action!=='play'})});
 const player=new MusicPlayer({songFadeEnabled:false,sonyExecution:{parallel:true,streaming:false},outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'},sonySettings:{dsee:true,dc:0,vinyl:0}});
 await player.play('first',[track('first')]);assert.equal(player.state.playing,true);assert.equal(env.instances.length,1);
 assert.equal(calls.find(x=>x.url==='/api/sony/prepare').value.streaming,false);
 assert.equal(calls.find(x=>x.url==='/api/native/start').value.sonyJobId,'a'.repeat(64));
 await player.toggle();player.seek(37);await settle();
 await player.setOutputSettings({backend:'asio',device:0,channel:2,dsdMode:'pcm'});assert.equal(player.state.transport,'paused');
 await player.toggle();await settle();assert.equal(calls.filter(x=>x.url==='/api/native/start').at(-1).value.settings.channel,2);
 assert.ok(calls.some(x=>x.value.action==='seek'&&x.value.position===37));
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('live Sony changes begin at the current position and backward seeks prepare a new segment',async t=>{
 const env=environment(t),calls=[],positions=new Map();let start=0;
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=options?.body?JSON.parse(options.body):{};calls.push({url,value});
  if(url==='/api/sony/prepare'){start=value.startPosition;return reply(sonyJob('ready',{positionOffset:start,duration:120}))}
  if(String(url).startsWith('/api/sony/'))return reply(sonyJob('ready',{positionOffset:start,duration:120}));
  if(url==='/api/native/start'||value.action==='seek')positions.set(value.session,value.position);
  return reply({session:value.session,duration:120,position:positions.get(value.session)??0,sourceStart:start,paused:value.action!=='play'});
 });
 const player=new MusicPlayer({bgmEnabled:false,songFadeEnabled:false,outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'}});
 await player.play('first',[track('first')]);player.seek(37);await settle();await player.toggle();
 await player.setSonySettings({dsee:true,dc:2,vinyl:1});assert.equal(player.state.transport,'paused');near(player.state.currentTime,37);
 assert.equal(calls.filter(x=>x.url==='/api/sony/prepare').at(-1).value.startPosition,37);
 assert.ok(calls.find(x=>x.value.action==='stop'),'the old native reader is stopped before its replacement');
 await player.toggle();assert.equal(player.state.playing,true);near(player.state.currentTime,37);
 assert.equal(calls.filter(x=>x.url==='/api/native/start').at(-1).value.position,37);
 await player.toggle();player.seek(12);await env.advance(0);
 assert.equal(calls.filter(x=>x.url==='/api/sony/prepare').at(-1).value.startPosition,12);
 assert.equal(player.state.transport,'paused');near(player.state.currentTime,12);
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});
test('DSD to PCM requests conversion even with Sony OFF',async t=>{
 const env=environment(t),calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=options?.body?JSON.parse(options.body):{};calls.push({url,value});return reply(String(url).startsWith('/api/sony/')?sonyJob():{session:value.session,duration:120,position:0,paused:value.action!=='play'})});
 const player=new MusicPlayer({songFadeEnabled:false,outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'}}),dsd={...track('dsd'),format:'DSF',relativePath:'dsd.dsf'};
 await player.play(dsd.id,[dsd]);assert.equal(player.state.playing,true);assert.equal(player.state.volumeLocked,false);assert.equal(player.state.sonyProcessing.state,'off');
 const prepare=calls.find(x=>x.url==='/api/sony/prepare').value;assert.equal(prepare.dsdToPcm,true);assert.deepEqual(prepare.settings,{dsee:false,dc:0,vinyl:0});
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('native pause reports its acknowledged position before preparing changed Sony settings',async t=>{
 const env=environment(t),calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{
  const value=JSON.parse(options.body);calls.push({url,value});
  if(String(url).startsWith('/api/sony/'))return reply(sonyJob('ready',{positionOffset:7.125,duration:120}));
  return reply({session:value.session,duration:120,position:value.action==='pause'?7.125:0,paused:value.action!=='play'});
 });
 const player=new MusicPlayer({bgmEnabled:false,songFadeEnabled:false,outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'}});
 await player.play('first',[track('first')]);await player.toggle();await settle();
 near(player.state.currentTime,7.125);assert.equal(player.state.transport,'paused');
 await player.setSonySettings({dsee:true,dc:2,vinyl:1});
 near(calls.find(x=>x.url==='/api/sony/prepare').value.startPosition,7.125);near(player.state.currentTime,7.125);assert.equal(player.state.transport,'paused');
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});
test('a late native play reply cannot override a newer pause',async t=>{
 const env=environment(t);let release,playing=false;const calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=JSON.parse(options.body);calls.push(value.action||'open');if(value.action==='play')await new Promise(resolve=>release=()=>{playing=true;resolve()});if(value.action==='pause'||value.action==='stop')playing=false;return reply({session:value.session,duration:120,position:0,paused:!playing,playing})});
 const player=new MusicPlayer({songFadeEnabled:false,outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'}});
 const pending=player.play('first',[track('first')]);await settle();assert.equal(typeof release,'function');
 await player.toggle();assert.equal(player.state.transport,'paused');release();await pending;await settle();
 assert.equal(playing,false);assert.equal(player.state.playing,false);assert.ok(calls.filter(x=>x==='pause').length>=2);
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('downloaded tag refresh updates the current title without replacing output or changing a paused position',async t=>{
 const env=environment(t),calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=JSON.parse(options.body);calls.push(value);return reply({session:value.session,duration:120,position:0,paused:value.action!=='play'})});
 const player=new MusicPlayer({songFadeEnabled:false,outputSettings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'}}),first=track('first'),second=track('second');
 await player.play(first.id,[first,second]);await player.toggle();player.seek(37);await settle();const before=calls.length;
 player.updateTrackMetadata([{...first,title:'ID3 中文标题',artist:'标签歌手'}]);
 assert.equal(player.state.currentTrack.title,'ID3 中文标题');assert.equal(player.state.currentTrack.artist,'标签歌手');assert.equal(player.state.transport,'paused');assert.equal(player.state.queue[1].id,second.id);assert.equal(calls.length,before,'Metadata refresh must not reopen, seek or restart output');
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('frontend recovery attaches the native session, queue, preferred volume and Sony state without reopening',async t=>{
 const env=environment(t),calls=[],fx={dsee:true,dc:2,vinyl:1},session=crypto.randomUUID();let position=42.5,playing=true;
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=JSON.parse(options.body);calls.push({url,value});if(value.action==='pause')playing=false;if(value.action==='play')playing=true;if(value.action==='seek')position=value.position;return reply({duration:120,position,playing,paused:!playing,sourceStart:30,sonyProcessing:{state:'active',progress:1,effectiveSettings:fx,workers:3}})});
 const player=new MusicPlayer({bgmEnabled:false,volume:.1});
 const snapshot={session,trackId:'second',settings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'},sonySettings:fx,sonyJobId:'a'.repeat(64),volume:.65,state:{duration:120,position,playing,sourceStart:30},sonyProcessing:{state:'active',progress:.8,effectiveSettings:fx,workers:3}};
 assert.equal(player.restoreNativePlayback(snapshot,[track('first'),track('second')]),true);
 assert.equal(player.state.nativeSessionId,session);assert.equal(player.state.currentIndex,1);assert.equal(player.state.transport,'playing');near(player.state.currentTime,42.5);near(player.state.volume,.65);assert.deepEqual(player.state.sonySettings,fx);assert.equal(env.instances.length,1);
 await env.advance(300);assert.equal(player.state.sonyProcessing.progress,1);assert.equal(calls.some(c=>c.url==='/api/native/start'),false);assert.equal(calls.some(c=>c.url==='/api/sony/prepare'),false);
 assert.equal(calls.find(c=>c.value.action==='volume').value.volume,.65);assert.equal(calls.find(c=>c.value.action==='volume').value.targetVolume,.65);
 await player.toggle();await settle();assert.equal(player.state.transport,'paused');player.seek(50);await settle();near(player.state.currentTime,50);assert.equal(playing,false);
 player.setVolume(.4);await env.advance(50);assert.equal(calls.filter(c=>c.value.action==='volume').at(-1).value.targetVolume,.4);
 assert.ok(calls.every(c=>c.value.session===session));player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('paused native DSD recovery retains a locked DAC volume and rejects an absent track',async t=>{
 const env=environment(t),calls=[],dsd={...track('dsd'),format:'DSF',relativePath:'dsd.dsf'};
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=JSON.parse(options.body);calls.push(value);return reply({duration:120,position:33,playing:false,paused:true})});
 const player=new MusicPlayer({bgmEnabled:false}),snapshot={session:crypto.randomUUID(),trackId:dsd.id,settings:{backend:'asio',device:0,channel:0,dsdMode:'native'},sonySettings:{dsee:false,dc:0,vinyl:0},volume:.2,state:{duration:120,position:33,playing:false},sonyProcessing:{state:'off',progress:0}};
 assert.equal(player.restoreNativePlayback(snapshot,[track('other')]),false);assert.equal(player.state.currentTrack,null);
 assert.equal(player.restoreNativePlayback(snapshot,[dsd]),true);assert.equal(player.state.transport,'paused');assert.equal(player.state.playing,false);assert.equal(player.state.volumeLocked,true);near(player.state.currentTime,33);
 await env.advance(1000);assert.deepEqual(calls,[],'paused recovery sends no start, play, gain or poll commands');player.setVolume(.9);near(player.state.volume,.2);player.seek(60);await settle();assert.equal(calls.at(-1).action,'seek');
 player.dispose();await settle();assert.equal(env.pendingTimers(),0);
});

test('a paused recovered Sony producer updates its buffered progress without resuming or moving the cursor',async t=>{
 const env=environment(t),calls=[];
 t.mock.method(globalThis,'fetch',async(url,options)=>{const value=JSON.parse(options.body);calls.push(value);return reply({position:19,duration:120,playing:false,sonyProcessing:{state:'active',progress:1,streaming:false,bufferedSeconds:120}})});
 const player=new MusicPlayer({bgmEnabled:false});
 assert.equal(player.restoreNativePlayback({session:crypto.randomUUID(),trackId:'first',settings:{backend:'wasapi',device:-1,channel:0,dsdMode:'pcm'},sonySettings:{dsee:true,dc:2,vinyl:1},volume:.4,state:{position:17,duration:120,playing:false},sonyProcessing:{state:'active',progress:.5,streaming:true,bufferedSeconds:60}},[track('first')]),true);
 await env.advance(500);assert.equal(player.state.sonyProcessing.progress,1);near(player.state.currentTime,17);assert.equal(player.state.transport,'paused');assert.equal(calls.filter(c=>c.action==='status').length,1);assert.equal(calls.some(c=>c.action==='play'),false);assert.equal(env.pendingTimers(),0);
 player.dispose();await settle();
});
