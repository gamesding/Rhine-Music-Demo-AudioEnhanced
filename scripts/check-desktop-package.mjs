import assert from 'node:assert/strict'
import {promises as fs} from 'node:fs'
import path from 'node:path'
import {spawn} from 'node:child_process'
import {fileURLToPath} from 'node:url'
const project=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
const executable=path.resolve(process.argv[2]??path.join(project,'release/Rhine Music.exe'));
if(process.platform!=='win32')throw new Error('Windows package validation requires Windows.');
const base=await fs.mkdtemp(path.join(project,'release','独立 EXE 验证 (环境) ')),single=path.join(base,'仅有播放器');
await fs.mkdir(single);const copy=path.join(single,'Rhine Music.exe');await fs.copyFile(executable,copy);
const env=Object.fromEntries(Object.entries(process.env).filter(([key])=>!(/^(path|python.*|sony_walkman.*|rhine_.*|music_.*|electron_run_as_node)$/i.test(key))));
Object.assign(env,{PATH:path.join(process.env.SystemRoot??'C:\\Windows','System32'),RHINE_RUNTIME_ROOT:path.join(base,'自带运行时'),RHINE_APP_HOME:path.join(base,'用户数据'),MUSIC_DATA_DIR:path.join(base,'测试曲库数据')});
const reportFile=path.join(base,'self-test.json');
async function launch(){return new Promise((resolve,reject)=>{const child=spawn(copy,['--self-test','--report',reportFile],{cwd:single,env,windowsHide:true,stdio:'ignore'});const timer=setTimeout(()=>{child.kill();reject(new Error('Self-contained EXE test timed out'))},120000);child.once('error',reject);child.once('close',code=>{clearTimeout(timer);resolve(code)})})}
assert.deepEqual(await fs.readdir(single),['Rhine Music.exe']);
const began=Date.now();assert.equal(await launch(),0,await fs.readFile(reportFile,'utf8').catch(()=>'No report: extraction or desktop startup failed'));
const first=JSON.parse(await fs.readFile(reportFile,'utf8'));assert.equal(first.ok,true,first.error);assert.equal(first.checks.length,6);assert.ok(first.checks.every(item=>item.passed));
const runtimes=await fs.readdir(env.RHINE_RUNTIME_ROOT);assert.equal(runtimes.length,1);
const runtime=path.join(env.RHINE_RUNTIME_ROOT,runtimes[0]),appDir=path.join(runtime,'resources/app');
for(const file of ['electron.exe','LICENSE','LICENSES.chromium.html','resources/app/desktop/main.cjs','resources/app/desktop/preload.cjs','resources/app/runtime/python/python.exe','resources/app/runtime/python/Lib/site-packages/unicorn/lib/unicorn.dll','resources/app/vendor/licenses/unicorn/COPYING','resources/app/vendor/licenses/unicorn/unicorn-2.1.4.tar.gz','resources/app/vendor/sony-walkman/DseeAi.bin','resources/app/vendor/sony-walkman-x86/sony-dsp-x86.dll','resources/app/vendor/audio/windows-x64/bassasio.dll'])await fs.access(path.join(runtime,file));
assert.equal(await fs.access(path.join(appDir,'runtime/node.exe')).then(()=>true,()=>false),false);
const ready=await fs.stat(path.join(runtime,'.ready'));const coldSeconds=(Date.now()-began)/1000;
assert.equal(await launch(),0);assert.equal((await fs.stat(path.join(runtime,'.ready'))).mtimeMs,ready.mtimeMs,'Second run must reuse the extracted runtime');
const report={...first,executableBytes:(await fs.stat(copy)).size,coldSeconds,isolatedExeOnly:true,externalRuntimes:false,secondRunReused:true,base,runtime,appDir};
await fs.writeFile(path.join(project,'release/desktop-package-verification.json'),JSON.stringify(report,null,2)+'\n');
console.log(JSON.stringify({ok:true,checks:report.checks,coldSeconds,executableMB:(report.executableBytes/1048576).toFixed(1),secondRunReused:true}));
// Keep this ignored test runtime for the independent desktop-window / Pad review.
