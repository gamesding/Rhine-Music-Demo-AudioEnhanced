import test from 'node:test';
import assert from 'node:assert/strict';
import {promises as fs} from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import {readAudioMetadata,readAlacFormat} from './read-audio-metadata.mjs';
import {MusicLibraryStore} from './music-library.mjs';
import {SonyWalkman,sonyPlaybackPlan} from './sony-walkman.mjs';
import {isHiResAlbum,isHiResTrack} from '../src/hi-res.ts';
import {updateSonyTechIndicators} from '../src/sony-tech-indicators.ts';

async function fixture(t){
 const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-alac-hires-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
 const music=path.join(root,'music');await fs.mkdir(music);const file=path.join(music,'synthetic.m4a');
 const bytes=Buffer.from(await fs.readFile(new URL('./fixtures/alac-192.m4a.b64',import.meta.url),'utf8'),'base64');await fs.writeFile(file,bytes);return {root,music,file,bytes};
}
test('24/192 ALAC reads its codec configuration and repairs the old cached metadata',async t=>{
 const {root,music,file,bytes}=await fixture(t),metadata=await readAudioMetadata(file);
 assert.deepEqual(await readAlacFormat(file),{sampleRate:192000,bitsPerSample:24,numberOfChannels:2,lossless:true});
 assert.equal(metadata.common.title,'Synthetic ALAC');assert.equal(metadata.common.album,'Synthetic Hi-Res');assert.equal(metadata.format.duration,.06);
 assert.equal(isHiResTrack({format:'M4A',...metadata.format}),true);
 const store=await new MusicLibraryStore({dataDir:path.join(root,'data'),defaultRoots:[music]}).init();await store.scan();
 const old=store.index.albums[0].tracks[0];old.sampleRate=1;old.bitsPerSample=16;old._metadataVersion=3;
 await store.scan();const album=store.snapshot().albums[0];assert.equal(album.tracks[0].sampleRate,192000);assert.equal(album.tracks[0].bitsPerSample,24);assert.equal(isHiResAlbum(album),true);
 assert.deepEqual(await fs.readFile(file),bytes);
 await fs.writeFile(file,bytes.subarray(0,bytes.length-1));await assert.rejects(readAlacFormat(file),/MP4/);
 const malformed=Buffer.from(bytes),name=malformed.lastIndexOf(Buffer.from('alac'));assert.ok(name>0);malformed.writeUInt32BE(0,name+28);
 await fs.writeFile(file,malformed);await assert.rejects(readAlacFormat(file),/ALACSpecificConfig/);
});
test('high-rate sources bypass only unsupported original effects and badges follow the actual chain',()=>{
 const requested={dsee:true,dc:2,vinyl:1};
 for(const rate of [44100,48000])assert.deepEqual(sonyPlaybackPlan(requested,{sampleRate:rate,numberOfChannels:2}).effectiveSettings,requested);
 for(const rate of [176400,192000]){const plan=sonyPlaybackPlan(requested,{sampleRate:rate,numberOfChannels:2});assert.deepEqual(plan.effectiveSettings,{dsee:false,dc:2,vinyl:1});assert.deepEqual(plan.bypassed,['dsee']);assert.equal(plan.sourceSampleRate,rate);assert.match(plan.message,/DSEE AI.*旁路/)}
 assert.deepEqual(sonyPlaybackPlan(requested,{sampleRate:96000,numberOfChannels:2}).effectiveSettings,{dsee:false,dc:0,vinyl:0});
 const badges=Object.fromEntries(['dsee','dc','vinyl'].map(name=>[name,{hidden:true}])),host={dataset:{},querySelector:s=>badges[/data-tech="(\w+)"/.exec(s)[1]]};
 updateSonyTechIndicators(host,{sonySettings:requested,sonyProcessing:{state:'active',effectiveSettings:{dsee:false,dc:2,vinyl:1}},currentTrack:{albumId:'high'},playing:true,transport:'playing'},'high');
 assert.equal(badges.dsee.hidden,true);assert.equal(badges.dc.hidden,false);assert.equal(badges.vinyl.hidden,false);assert.equal(host.dataset.count,'2');
});
test('192 kHz ALAC plays with DSEE enabled; serial and parallel DC / Vinyl retain the same original output',{skip:process.platform!=='win32'},async t=>{
 const {root,music,file}=await fixture(t),sony=new SonyWalkman({dataDir:root,store:{trackFile:()=>({path:file,allowedRoot:music})}});t.after(()=>sony.close());
 const direct=await sony.prepare('high',{dsee:true,dc:0,vinyl:0});assert.equal(direct.state,'ready');assert.equal(direct.bypassedAll,true);assert.equal(direct.audioUrl,'/api/audio/high');assert.equal(direct.positionOffset,0);assert.equal(direct.sampleRate,192000);
 let previous;
 for(const parallel of [false,true]){
   let job=await sony.prepare('high',{dsee:true,dc:2,vinyl:1},{streaming:true,parallel});const deadline=Date.now()+30000;
   while(!['ready','error'].includes(job.state)&&Date.now()<deadline){await new Promise(r=>setTimeout(r,30));job=sony.job(job.id)}
   assert.equal(job.state,'ready',job.error);assert.equal(job.sampleRate,192000);assert.deepEqual(job.effectiveSettings,{dsee:false,dc:2,vinyl:1});assert.deepEqual(job.bypassed,['dsee']);assert.ok(job.peak>0);
   const wav=await fs.readFile((await sony.audio(job.id)).path);assert.equal(wav.readUInt32LE(24),192000);assert.equal(wav.length,56+11520*8);
   if(previous)assert.deepEqual(wav,previous);previous=wav;await sony.clearCache();
 }
 await assert.rejects(sony.run(['--input',file,'--output',path.join(root,'unsupported.wav'),'--dsee','1']),/DSEE AI 原版仅支持/);
});
