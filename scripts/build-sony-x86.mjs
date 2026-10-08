import {promises as fs} from 'node:fs'
import path from 'node:path'
import {spawn} from 'node:child_process'
import {createHash} from 'node:crypto'
import {validateSonySourceGraph} from './sony-source-graph.mjs'
const project=process.cwd(),directory=path.join(project,'native/sony/generated'),target=path.join(project,'vendor/sony-walkman-x86');
const provenance=await validateSonySourceGraph(project);
console.log(`Verified ${provenance.instructionSites} original instruction sites across ${provenance.pages} C++ pages.`);
await fs.mkdir(target,{recursive:true});
const sources=(await fs.readdir(directory)).filter(name=>name.endsWith('.cpp')).map(name=>path.join(directory,name));
const compiler=process.env.RHINE_CXX??path.join(project,'.tools/windows-build/zig/zig-x86_64-windows-0.15.2/zig.exe');
await new Promise((resolve,reject)=>{const child=spawn(compiler,['c++','-target','x86_64-windows-gnu','-std=c++17','-O2','-fno-fast-math','-ffp-contract=off','-shared',path.join(project,'native/sony/lift-host.cpp'),...sources,'-o',path.join(target,'sony-dsp-x86.dll')],{stdio:'inherit',windowsHide:true});child.once('error',reject);child.once('close',code=>code===0?resolve():reject(new Error(`Sony x86 compilation failed (${code})`)))});
const sha=value=>createHash('sha256').update(value).digest('hex'),sourceFiles=['native/sony/arm-state.hpp','native/sony/lift-host.cpp',...(await fs.readdir(directory)).filter(name=>name.endsWith('.cpp')).sort().map(name=>'native/sony/generated/'+name)],sourcesHash=createHash('sha256');
for(const file of sourceFiles){sourcesHash.update(file+'\0');sourcesHash.update(await fs.readFile(path.join(project,file)));}
await fs.writeFile(path.join(target,'assets.json'),JSON.stringify({revision:'dmp-z1-dsx-3.0.7-x86-aot-v1',architecture:'x86_64-windows',...provenance,originalSourceSha256:provenance.sourceSha256,sourceSha256:sourcesHash.digest('hex'),sourceFiles,files:{'sony-dsp-x86.dll':sha(await fs.readFile(path.join(target,'sony-dsp-x86.dll')))}},null,2)+'\n');
console.log('Compiled native C++ instruction lift and recorded its source and binary hashes.');
