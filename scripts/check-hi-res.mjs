import test from 'node:test';
import assert from 'node:assert/strict';
import {promises as fs} from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import {parseBuffer} from 'music-metadata';
import {isDsdAlbum,isDsdTrack,isHiResAlbum,isHiResTrack} from '../src/hi-res.ts';
import {silentWav,dsdFixture} from './audio-fixtures.mjs';
import {readAudioMetadata,readDffMetadata} from './read-audio-metadata.mjs';

test('JAS / JEITA source boundaries and unknown or lossy metadata',()=>{
  for(const [rate,bits,expected] of [[44100,16,false],[48000,16,false],[44100,24,true],[48000,24,true],[96000,16,true],[96000,24,true],[96000,12,false],[32000,24,false],[44100,32,true],[88200,16,true]])
    assert.equal(isHiResTrack({format:'WAV',sampleRate:rate,bitsPerSample:bits,lossless:true}),expected,`${bits} bit / ${rate} Hz`);
  for(const track of [
    {format:'FLAC'}, {format:'FLAC',sampleRate:96000,bitsPerSample:24},
    {format:'AAC',sampleRate:96000,bitsPerSample:24,lossless:false},
    {format:'WAV',sampleRate:NaN,bitsPerSample:24,lossless:true},
    {format:'WAV',sampleRate:96000,bitsPerSample:Infinity,lossless:true},
    {format:'WAV',sampleRate:96000,lossless:true},
    {format:'DSF',sampleRate:2822400,lossless:false},
  ])assert.equal(isHiResTrack(track),false,JSON.stringify(track));
});
test('actual PCM / DSD metadata is classified before playback, without inferring from file names',async t=>{
  for(const [rate,bits,expected] of [[44100,16,false],[48000,16,false],[44100,24,true],[48000,24,true],[96000,16,true],[96000,24,true]]){
    const bytes=silentWav(.05,rate,bits),metadata=await parseBuffer(bytes,{mimeType:'audio/wav'});
    assert.equal(isHiResTrack({format:'WAV',...metadata.format}),expected);
  }
  const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-hires-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
  for(const [format,bytes] of [['DSF',dsdFixture().dsf],['DFF',dsdFixture(5644800).dff]]){
    const filename=path.join(root,`fixture.${format.toLowerCase()}`);await fs.writeFile(filename,bytes);
    const metadata=await readAudioMetadata(filename);
    assert.equal(metadata.format.lossless,true);assert.equal(isHiResTrack({format,...metadata.format}),true);
    assert.equal(isDsdTrack({format,...metadata.format}),true);
  }
});
test('DFF pad alignment is preserved and malformed chunk bounds cannot produce Hi-Res metadata',async t=>{
  const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-dff-tags-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
  const fixture=dsdFixture(2822400,8111),filename=path.join(root,'padding.dff');await fs.writeFile(filename,fixture.dff);
  const metadata=await readDffMetadata(filename);assert.equal(metadata.format.duration,fixture.duration);assert.equal(metadata.format.sampleRate,fixture.rate);
  assert.deepEqual(await fs.readFile(filename),fixture.dff);
  for(const bytes of [fixture.dff.subarray(0,fixture.dff.length-1),Buffer.from(fixture.dff)]){
    if(bytes.length===fixture.dff.length)bytes.writeBigUInt64BE(0xffffffffffffffffn,20);
    await fs.writeFile(filename,bytes);await assert.rejects(readDffMetadata(filename),/DFF/);
  }
});
test('album requires every source track, including unknown FTP metadata; processed output never changes its source label',()=>{
  const cd={format:'FLAC',sampleRate:44100,bitsPerSample:16,lossless:true};
  const high={...cd,bitsPerSample:24};
  assert.equal(isHiResAlbum(),false);assert.equal(isHiResAlbum({tracks:[]}),false);
  assert.equal(isHiResAlbum({tracks:[high,high]}),true);
  assert.equal(isHiResAlbum({tracks:[high,cd]}),false);
  assert.equal(isHiResAlbum({tracks:[high,{format:'FLAC'}]}),false);
  const source=structuredClone(cd),output={sampleRate:176400,bitsPerSample:32};
  assert.equal(isHiResTrack(source),false);assert.equal(output.sampleRate,176400);assert.deepEqual(source,cd);
});
test('DSD badges require the original parsed source, and full-album badges require every track',()=>{
  const dsd={format:'DSF',codec:'DSD',sampleRate:2822400,bitsPerSample:1,lossless:true};
  const pcm={format:'FLAC',codec:'FLAC',sampleRate:192000,bitsPerSample:24,lossless:true};
  for(const rate of [2822400,5644800,11289600,22579200]) {
    assert.equal(isDsdTrack({...dsd,sampleRate:rate}),true);
    assert.equal(isHiResTrack({...dsd,sampleRate:rate}),true);
  }
  for(const unknown of [{format:'DSF'}, {...dsd,lossless:false}, {...dsd,sampleRate:NaN}, {...dsd,sampleRate:0}, pcm])
    assert.equal(isDsdTrack(unknown),false);
  assert.equal(isDsdAlbum(),false);assert.equal(isDsdAlbum({tracks:[]}),false);
  assert.equal(isDsdAlbum({tracks:[dsd,{...dsd,format:'DFF'}]}),true);
  assert.equal(isDsdAlbum({tracks:[dsd,pcm]}),false);
  assert.equal(isHiResAlbum({tracks:[dsd,pcm]}),true);
  assert.equal(isDsdAlbum({tracks:[dsd,{format:'DSF'}]}),false);
  const source=structuredClone(dsd),output={sampleRate:176400,bitsPerSample:32};
  assert.equal(isDsdTrack(source),true);assert.equal(output.sampleRate,176400);assert.deepEqual(source,dsd);
});
test('the distributed badges are the user SVGs unchanged',async()=>{
  assert.deepEqual(await fs.readFile(new URL('../public/audio-tech/hi-res.svg',import.meta.url)),await fs.readFile(new URL('../art/Hi-Res_Audio_(logo).svg',import.meta.url)));
  assert.deepEqual(await fs.readFile(new URL('../public/audio-tech/dsd.svg',import.meta.url)),await fs.readFile(new URL('../art/DSDlogo.svg',import.meta.url)));
});
