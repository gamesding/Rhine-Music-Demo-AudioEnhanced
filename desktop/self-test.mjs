import {promises as fs} from 'node:fs'
import path from 'node:path'
import {randomUUID} from 'node:crypto'
import {parseFile} from 'music-metadata'
import {NativeOutput} from '../scripts/native-output.mjs'
import {SonyWalkman} from '../scripts/sony-walkman.mjs'
import {dsdFixture,silentWav,taggedDsf} from '../scripts/audio-fixtures.mjs'
export async function runSelfTest({root,dataDir}) {
 const results=[],report={ok:false,versions:{electron:process.versions.electron,node:process.versions.node},systemPath:process.env.PATH,checks:results};
 const fixtureDir=path.join(dataDir,'self-test');await fs.mkdir(fixtureDir,{recursive:true});
 const host=new NativeOutput(),sony=new SonyWalkman({dataDir,store:{trackFile:id=>id==='synthetic'?{path:path.join(fixtureDir,'synthetic.wav'),allowedRoot:fixtureDir}:undefined}});
 try {
  const native=await host.status();if(!native.available)throw new Error(native.error);results.push({check:'original native DLL hashes / decoder initialization',passed:true,asioDrivers:native.devices.length});
  const dsd=dsdFixture(),file=path.join(fixtureDir,'synthetic.dsf'),picture=await fs.readFile(path.join(root,'dist/icons/icon-192.png'));
  await fs.writeFile(file,taggedDsf(dsd.dsf,{picture}));
  const metadata=await parseFile(file,{duration:true});
  if(metadata.common.title!=='星河之声'||metadata.common.artist!=='测试歌手'||metadata.common.album!=='原生 DSD 专辑'||metadata.common.track.no!==3||metadata.common.disk.no!==1||Buffer.from(metadata.common.picture?.[0]?.data??[]).compare(picture))throw new Error('DSF ID3 tags or embedded artwork differ');
  const raw=await host.command({cmd:'inspect',file,dsd:true,mode:'native',maxBytes:262144});if(Buffer.from(raw.dataHex,'hex').compare(dsd.raw))throw new Error('Raw DSD bytes differ');
  const dop=await host.command({cmd:'inspect',file,dsd:true,mode:'dop',maxBytes:262144}),data=Buffer.from(dop.dataHex,'hex');
  if(data.length!==dsd.raw.length*2)throw new Error('DoP frame length differs');
  for(let i=0;i<data.length/8;i++)for(let ch=0;ch<2;ch++){const value=Math.round(data.readFloatLE((i*2+ch)*4)*8388608)&0xffffff;if(value>>>16!==(i%2?250:5)||((value>>>8)&255)!==dsd.raw[i*4+ch]||(value&255)!==dsd.raw[i*4+2+ch])throw new Error('DoP framing differs')}
  results.push({check:'DSF ID3 Chinese tags / artwork / unmodified raw DSD64 and DoP markers / payload',passed:true,bytes:raw.bytes});
  const status=await sony.status();if(!status.available||status.backend!=='x86-cpp')throw new Error(status.error||'Sony x86 C++ backend is unavailable');results.push({check:'nine Sony hashes / native C++ DLL hash / embedded transport / original AI, DC, Vinyl initialize',passed:true,dseeVersion:status.dseeVersion,backend:status.backend});
  const isolation=await sony.run(['--phase-check']);if(!isolation.ready||isolation.configurations!==24||!isolation.phaseStereoIsolation||!isolation.cases.every(item=>item.originalMonoBitExact&&item.chunkStateBitExact&&item.leftToRightPeak===0&&item.rightToLeftPeak===0))throw new Error('Sony phase isolation regression failed');
  results.push({check:'Sony phase independent stereo histories / 24 presets and rates / bit-exact original mono reference',passed:true,cases:isolation.configurations});
  await fs.writeFile(path.join(fixtureDir,'synthetic.wav'),silentWav(.2));
  let job=await sony.prepare('synthetic',{dsee:true,dc:2,vinyl:1},{parallel:true,streaming:false});const deadline=Date.now()+60000;
  while(!['ready','error'].includes(job.state)&&Date.now()<deadline){await new Promise(resolve=>setTimeout(resolve,100));job=sony.job(job.id)}
  if(job.state!=='ready')throw new Error(job.error||'Sony rendering timed out');
  results.push({check:'three-effect x86 C++ pipeline / bundled streaming native decode',passed:true,sampleRate:job.sampleRate,workers:job.workers});
  const descriptor=await sony.audio(job.id),session=randomUUID();
  await host.command({cmd:'open',file:descriptor.path,backend:'wasapi',mode:'pcm',dsd:false,session,volume:0,position:0});
  await host.command({cmd:'play',session});await new Promise(resolve=>setTimeout(resolve,80));await host.command({cmd:'pause',session});await host.command({cmd:'seek',session,position:.1});await host.command({cmd:'stop',session});
  results.push({check:'silent native WASAPI playback / pause / seek / stop',passed:true});report.ok=true;
 }catch(error){report.error=error.stack}
 finally {host.close();sony.close();await fs.rm(fixtureDir,{recursive:true,force:true}).catch(()=>{})}
 return report;
}
