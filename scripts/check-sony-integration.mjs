import test from 'node:test'
import assert from 'node:assert/strict'
import { promises as fs } from 'node:fs'
import os from 'node:os'
import path from 'node:path'
import { SonyWalkman } from './sony-walkman.mjs'
import { updateSonyTechIndicators } from '../src/sony-tech-indicators.ts'

test('technology marks follow actual attached Sony audio, selected album and transport',()=>{
  const badges=Object.fromEntries(['dsee','dc','vinyl'].map(key=>[key,{ hidden:true }]))
  const host={ dataset:{},querySelector:selector=>badges[/data-tech="(\w+)"/.exec(selector)[1]] }
  const state={currentTrack:{albumId:'playing-album'},sonyProcessing:{state:'active'},sonySettings:{dsee:true,dc:2,vinyl:1},playing:true,loading:false,transport:'playing'}
  for(let bits=0;bits<8;bits++) {
    state.sonySettings={dsee:!!(bits&1),dc:bits&2?2:0,vinyl:bits&4?1:0}
    updateSonyTechIndicators(host,state,'playing-album')
    assert.equal(host.dataset.count,String(Number(!!(bits&1))+Number(!!(bits&2))+Number(!!(bits&4))))
    assert.equal(badges.dsee.hidden,!(bits&1));assert.equal(badges.dc.hidden,!(bits&2));assert.equal(badges.vinyl.hidden,!(bits&4))
  }
  for(const process of ['off','preparing','error']) {
    state.sonyProcessing.state=process;updateSonyTechIndicators(host,state,'playing-album');assert.equal(host.dataset.count,'0')
  }
  state.sonyProcessing.state='active';state.playing=false;state.transport='paused'
  updateSonyTechIndicators(host,state,'playing-album');assert.equal(host.dataset.count,'3');assert.equal(host.dataset.playing,'false')
  updateSonyTechIndicators(host,state,'different-album');assert.equal(host.dataset.count,'0')
  state.transport='idle';updateSonyTechIndicators(host,state,'playing-album');assert.equal(host.dataset.count,'0')
})

test('missing original components stay unavailable; cache clearing only removes generated files',async(t)=>{
  const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-sony-'))
  t.after(()=>fs.rm(root,{recursive:true,force:true}))
  const sony=new SonyWalkman({dataDir:root,assetsDir:path.join(root,'missing-assets'),store:{trackFile:()=>null}})
  t.after(()=>sony.close())
  assert.equal((await sony.status()).available,false)
  await fs.mkdir(sony.cacheDir,{recursive:true})
  const generated=`${'a'.repeat(64)}.wav`
  await fs.writeFile(path.join(sony.cacheDir,generated),'generated audio')
  await fs.writeFile(path.join(sony.cacheDir,`${generated}.json`),'{}')
  await fs.writeFile(path.join(sony.cacheDir,'keep.wav'),'user file')
  sony.running=true;await assert.rejects(sony.clearCache(),/仍在处理/);sony.running=false
  await sony.clearCache()
  assert.equal(await fs.stat(path.join(sony.cacheDir,generated)).catch(()=>null),null)
  assert.equal(await fs.readFile(path.join(sony.cacheDir,'keep.wav'),'utf8'),'user file')
})

test('live Sony playback needs a short buffer even for a long track on a slow CPU',()=>{
 const sony=new SonyWalkman({dataDir:os.tmpdir(),store:{trackFile:()=>null}}),rate=176400;
 const job={streaming:true,stream:{duration:3500,sampleRate:rate},producedBytes:rate*8*.5+56,renderSpeed:.2};
 assert.equal(sony.playable(job),true);job.producedBytes-=8;assert.equal(sony.playable(job),false);
 job.stream.duration=.2;job.producedBytes=Math.round(rate*8*.2)+56;assert.equal(sony.playable(job),true);
 job.streaming=false;assert.equal(sony.playable(job),false);sony.close();
})
