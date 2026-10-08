// Differential release gate for the generated C++ DSP. No real music in reports.
import {promises as fs} from 'node:fs'
import path from 'node:path'
import {spawn} from 'node:child_process'
import {createHash} from 'node:crypto'
import assert from 'node:assert/strict'
import {prepareRuntime,runtimeRoot} from './prepare-desktop-runtime.mjs'
import {validateSonySourceGraph} from './sony-source-graph.mjs'
const project=process.cwd();await prepareRuntime();
const provenance=await validateSonySourceGraph(project);
const nativeManifest=JSON.parse(await fs.readFile('vendor/sony-walkman-x86/assets.json','utf8'));
assert.equal(nativeManifest.instructionGraphSha256,provenance.instructionGraphSha256);
const builtSourceHash=createHash('sha256');
for(const file of nativeManifest.sourceFiles){assert.ok(file.startsWith('native/sony/')&&!file.includes('..'));builtSourceHash.update(file+'\0');builtSourceHash.update(await fs.readFile(file));}
assert.equal(builtSourceHash.digest('hex'),nativeManifest.sourceSha256,'Rebuild modified Sony C++ before comparing');
assert.equal(createHash('sha256').update(await fs.readFile('vendor/sony-walkman-x86/sony-dsp-x86.dll')).digest('hex'),nativeManifest.files['sony-dsp-x86.dll']);
const python=path.join(runtimeRoot,'python/python.exe'),results=[],cases=[];
for(const rate of [44100,48000])for(const dsee of [0,1])for(let dc=0;dc<=6;dc++)for(let vinyl=0;vinyl<=4;vinyl++)if(dsee||dc||vinyl)cases.push({rate,dsee,dc,vinyl,frames:4096,pattern:'mixed'});
for(const rate of [176400,192000])for(let dc=0;dc<=6;dc++)for(let vinyl=0;vinyl<=4;vinyl++)if(dc||vinyl)cases.push({rate,dsee:0,dc,vinyl,frames:4096,pattern:'mixed'});
for(const rate of [44100,48000])for(const pattern of ['silence','left','right','noise','tiny'])for(const settings of [{dsee:1,dc:0,vinyl:0},{dsee:0,dc:2,vinyl:0},{dsee:0,dc:0,vinyl:4},{dsee:1,dc:6,vinyl:4}])cases.push({rate,...settings,pattern,frames:8192});
if(process.argv.includes('--quick'))cases.splice(0,cases.length,{rate:44100,dsee:1,dc:2,vinyl:1,frames:4096,pattern:'mixed'});
const bootstrap="import sys,runpy;sys.path[:0]=sys.argv[1:3];sys.argv=sys.argv[3:];runpy.run_path(sys.argv[0],run_name='__main__')";
async function run(c){const args=Object.entries(c).flatMap(([key,value])=>[`--${key}`,String(value)]),chunks=[];
 const child=spawn(python,['-B','-c',bootstrap,path.join(project,'scripts/sony-walkman'),path.join(runtimeRoot,'unicorn'),path.join(project,'scripts/sony-walkman/verify_x86.py'),...args],{windowsHide:true,env:{...process.env,SONY_WALKMAN_ASSETS:path.join(project,'vendor/sony-walkman'),SONY_WALKMAN_X86_DLL:path.join(project,'vendor/sony-walkman-x86/sony-dsp-x86.dll')},stdio:['ignore','pipe','pipe']});
 child.stdout.on('data',x=>chunks.push(x));child.stderr.on('data',x=>chunks.push(x));
 const timer=setTimeout(()=>child.kill(),120000);const code=await new Promise((resolve,reject)=>{child.once('error',reject);child.once('close',resolve)});clearTimeout(timer);
 const lines=Buffer.concat(chunks).toString().trim().split(/\r?\n/),last=lines.at(-1);let result;try{result=JSON.parse(last)}catch{throw new Error(`DSP differential process failed: ${last}`)}
 assert.equal(code,0,JSON.stringify({case:c,...result}));assert.equal(result.bitExact,true);assert.equal(result.stateBitExact,true);return result;
}
let next=0;const failed=[];
await Promise.all([0,1].map(async()=>{while(next<cases.length){const index=next++;try{results[index]=await run(cases[index])}catch(error){failed.push({case:cases[index],error:error.message})}if((index+1)%20===0)console.log(`Compared ${index+1}/${cases.length} Sony configurations.`)}}));
const report={date:new Date().toISOString(),source:'Sony DMP-Z1 v1.02 DSX 3.0.7',provenance,nativeArchitecture:'x86-64 C++ AOT instruction translation',originalBackend:'Unicorn 2.1.4 Cortex-A7',dllSha256:createHash('sha256').update(await fs.readFile('vendor/sony-walkman-x86/sony-dsp-x86.dll')).digest('hex'),cases:cases.length,passed:results.filter(Boolean).length,outputValues:results.filter(Boolean).reduce((sum,c)=>sum+c.outputValues,0),bitExact:failed.length===0,stateBitExact:failed.length===0,failures:failed,results:results.filter(Boolean)};
const reportPath=process.argv.includes('--quick')?'.tools/walkman/x86-quick-verification.json':'docs/SONY-X86-VERIFICATION.json';
await fs.mkdir(path.dirname(reportPath),{recursive:true});
await fs.writeFile(reportPath,JSON.stringify(report,null,2)+'\n');
console.log(JSON.stringify({cases:report.cases,passed:report.passed,outputValues:report.outputValues,bitExact:report.bitExact,failures:failed.slice(0,8)}));
if(failed.length)process.exitCode=1;
else if(!process.argv.includes('--quick')){
 const file='native/sony/generated/manifest.json',manifest=JSON.parse(await fs.readFile(file,'utf8'));
 Object.assign(manifest,{status:`validated against original ARM: ${report.cases} supported PCM configurations`,verification:'docs/SONY-X86-VERIFICATION.json'});
 await fs.writeFile(file,JSON.stringify(manifest,null,2)+'\n');
}
