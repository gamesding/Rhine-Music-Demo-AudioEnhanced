// One self-contained Windows executable; no machine-local libraries or credentials.
import {promises as fs,existsSync} from 'node:fs'
import path from 'node:path'
import {fileURLToPath} from 'node:url'
import {prepareRuntime,runtimeRoot,run,digest} from './prepare-desktop-runtime.mjs'
import {npmInvocation} from './platform.mjs'
const project=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..'),release=path.join(project,'release');
const staging=path.join(release,'.desktop-staging'),args=process.argv.slice(2);
const pkg=JSON.parse(await fs.readFile(path.join(project,'package.json'),'utf8'));
if(process.platform!=='win32')throw new Error('The Windows desktop package must be built on Windows.');
const copy=async(from,to)=>{await fs.mkdir(path.dirname(to),{recursive:true});await fs.cp(from,to,{recursive:true,filter:file=>path.basename(file)!=='__pycache__'&&!file.endsWith('.pyc')&&!file.endsWith('.lib')&&path.basename(file)!=='.archive-sha256'})};
const npm=async(values,cwd=project)=>{const invocation=npmInvocation(values);await run(invocation.command,invocation.args,{cwd})};
async function main() {
 if(!args.includes('--skip-build')){await npm(['ci']);await npm(['run','build'])}
 await fs.access(path.join(project,'dist/index.html'));const runtime=await prepareRuntime();
 if(path.resolve(staging)!==path.join(release,'.desktop-staging'))throw new Error('Invalid staging directory');
 await fs.rm(staging,{recursive:true,force:true});await fs.mkdir(staging,{recursive:true});
 await copy(path.join(runtimeRoot,'electron'),staging);
 const appDir=path.join(staging,'resources/app');await fs.mkdir(appDir,{recursive:true});
 await copy(path.join(project,'dist'),path.join(appDir,'dist'));
 for(const file of ['main.cjs','preload.cjs','self-test.mjs','runtime-assets.json'])await copy(path.join(project,'desktop',file),path.join(appDir,'desktop',file));
 await copy(path.join(project,'windows/app.ico'),path.join(appDir,'desktop/app.ico'));
 const scripts=['music-server.mjs','music-library.mjs','read-audio-metadata.mjs','album-introductions.mjs','online-sources.mjs','platform.mjs','sony-walkman.mjs','ftp-library.mjs','native-output.mjs','audio-fixtures.mjs'];
 for(const file of scripts)await copy(path.join(project,'scripts',file),path.join(appDir,'scripts',file));
 await copy(path.join(project,'scripts/sony-walkman'),path.join(appDir,'scripts/sony-walkman'));
 await copy(path.join(project,'vendor/sony-walkman'),path.join(appDir,'vendor/sony-walkman'));
 const x86Manifest=JSON.parse(await fs.readFile(path.join(project,'vendor/sony-walkman-x86/assets.json'),'utf8')),x86SourceHash=(await import('node:crypto')).createHash('sha256');
 if(await digest(path.join(project,'native/sony/instructions.json'))!==x86Manifest.instructionGraphSha256)throw new Error('Sony instruction graph changed: run npm run build:sony first.');
 for(const file of x86Manifest.sourceFiles){if(!file.startsWith('native/sony/')||file.includes('..'))throw new Error('Invalid Sony C++ source entry');x86SourceHash.update(file+'\0');x86SourceHash.update(await fs.readFile(path.join(project,file)));}
 if(x86SourceHash.digest('hex')!==x86Manifest.sourceSha256)throw new Error('Sony C++ source changed: run npm run build:sony first.');
 for(const [file,expected] of Object.entries(x86Manifest.files)){if(!/^[a-z0-9.-]+$/i.test(file)||await digest(path.join(project,'vendor/sony-walkman-x86',file))!==expected)throw new Error('Sony C++ binary SHA-256 mismatch');await copy(path.join(project,'vendor/sony-walkman-x86',file),path.join(appDir,'vendor/sony-walkman-x86',file));}
 await copy(path.join(project,'vendor/sony-walkman-x86/assets.json'),path.join(appDir,'vendor/sony-walkman-x86/assets.json'));
 if(await digest(path.join(project,'vendor/licenses/unicorn/unicorn-2.1.4.tar.gz'))!=='00567a70e323f749b419cd86bee4f9115beab7ebba32194581c090cbb7c59cff')throw new Error('Unicorn corresponding source SHA-256 mismatch.');
 await copy(path.join(project,'vendor/licenses/unicorn'),path.join(appDir,'vendor/licenses/unicorn'));
 const audioManifest=JSON.parse(await fs.readFile(path.join(project,'vendor/audio/windows-x64/assets.json'),'utf8'));
 if(await digest(path.join(project,'native/audio-host.cpp'))!==audioManifest.sourceSha256)throw new Error('Native audio source changed: run npm run build:native first.');
 for(const [file,expected] of Object.entries(audioManifest.files)) {
  const source=path.join(project,'vendor/audio/windows-x64',file);if(await digest(source)!==expected)throw new Error(`Native audio SHA-256 mismatch: ${file}`);
  await copy(source,path.join(appDir,'vendor/audio/windows-x64',file));
 }
 for(const file of ['assets.json','licenses'])await copy(path.join(project,'vendor/audio/windows-x64',file),path.join(appDir,'vendor/audio/windows-x64',file));
 const sonyManifest=JSON.parse(await fs.readFile(path.join(project,'scripts/sony-walkman/assets.json'),'utf8'));
 for(const [file,item] of Object.entries(sonyManifest.files??sonyManifest)){const expected=typeof item==='string'?item:item.sha256;if(expected&&/^[a-f0-9]{64}$/.test(expected)&&await digest(path.join(appDir,'vendor/sony-walkman',file))!==expected)throw new Error(`Sony SHA-256 mismatch: ${file}`)}
 for(const file of ['package.json','package-lock.json','LICENSE','NOTICE.md'])await copy(path.join(project,file),path.join(appDir,file));
 await npm(['ci','--omit=dev','--ignore-scripts','--no-audit','--no-fund'],appDir);
 await fs.writeFile(path.join(appDir,'package.json'),JSON.stringify({name:'rhine-music-desktop',version:pkg.version,private:true,type:'module',main:'desktop/main.cjs'}));
 await copy(path.join(runtimeRoot,'python'),path.join(appDir,'runtime/python'));
 const site=path.join(appDir,'runtime/python/Lib/site-packages');await fs.mkdir(site,{recursive:true});
 for(const file of await fs.readdir(path.join(runtimeRoot,'unicorn')))if(!file.startsWith('.'))await copy(path.join(runtimeRoot,'unicorn',file),path.join(site,file));
 await fs.writeFile(path.join(appDir,'runtime/python/python314._pth'),'python314.zip\n.\nLib/site-packages\n../../scripts/sony-walkman\nimport site\n');
 await fs.writeFile(path.join(appDir,'dist/.music-build.json'),JSON.stringify({prebuilt:true,platform:'win32-x64',version:pkg.version}));
 await fs.writeFile(path.join(appDir,'desktop/build-runtime.json'),JSON.stringify(runtime,null,2)+'\n');
 await copy(path.join(project,'windows/README-Windows.txt'),path.join(staging,'使用说明-Windows.txt'));
 const payload=path.join(release,'Rhine-desktop-payload.zip');await fs.rm(payload,{force:true});
 console.log('Compressing the complete isolated desktop runtime…');
 const psLiteral=value=>"'"+value.replaceAll("'","''")+"'";
 await run(path.join(process.env.SystemRoot??'C:\\Windows','System32/WindowsPowerShell/v1.0/powershell.exe'),['-NoProfile','-Command',`Add-Type -AssemblyName System.IO.Compression.FileSystem; [System.IO.Compression.ZipFile]::CreateFromDirectory(${psLiteral(staging)}, ${psLiteral(payload)}, [System.IO.Compression.CompressionLevel]::Optimal, $false)`]);
 const sha=await digest(payload),shaFile=payload+'.sha256';await fs.writeFile(shaFile,sha+'\n');
 const framework=path.join(process.env.SystemRoot??'C:\\Windows','Microsoft.NET'),compiler=[path.join(framework,'Framework64/v4.0.30319/csc.exe'),path.join(framework,'Framework/v4.0.30319/csc.exe')].find(existsSync);
 if(!compiler)throw new Error('Windows .NET Framework compiler unavailable.');
 const exe=path.join(release,'Rhine Music.exe');
 await run(compiler,['-nologo','-target:winexe','-platform:x64','-optimize+','-codepage:65001','-r:System.Windows.Forms.dll','-r:System.IO.Compression.dll','-r:System.IO.Compression.FileSystem.dll',`-win32icon:${path.join(project,'windows/app.ico')}`,`-win32manifest:${path.join(project,'windows/app.manifest')}`,`-resource:${payload},Rhine.Payload.zip`,`-resource:${shaFile},Rhine.Payload.sha256`,`-out:${exe}`,path.join(project,'windows/Standalone.cs')]);
 const outputSha=await digest(exe);await fs.writeFile(exe+'.sha256',`${outputSha}  Rhine Music.exe\n`);
 await fs.writeFile(path.join(release,'desktop-build.json'),JSON.stringify({version:pkg.version,executable:'Rhine Music.exe',sha256:outputSha,payloadSha256:sha,bytes:(await fs.stat(exe)).size,runtimes:runtime,sonyIncluded:true,externalDecoder:false},null,2)+'\n');
 console.log(`Built ${exe} (${((await fs.stat(exe)).size/1048576).toFixed(1)} MB), SHA-256 ${outputSha}`);
}
await main();
