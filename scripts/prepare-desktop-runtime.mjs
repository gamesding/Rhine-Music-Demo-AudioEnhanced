import {createHash} from 'node:crypto'
import {createReadStream,promises as fs} from 'node:fs'
import path from 'node:path'
import {fileURLToPath} from 'node:url'
import {spawn} from 'node:child_process'
const project=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
export const runtimeRoot=path.join(project,'.tools/desktop-runtime');
export async function digest(file){const hash=createHash('sha256');for await(const chunk of createReadStream(file))hash.update(chunk);return hash.digest('hex')}
export function run(command,args,{cwd=project,env=process.env}={}){return new Promise((resolve,reject)=>{const child=spawn(command,args,{cwd,env,windowsHide:true,stdio:'inherit'});child.once('error',reject);child.once('close',code=>code===0?resolve():reject(new Error(`${path.basename(command)} exited ${code}`)))})}
export async function prepareRuntime() {
 const manifest=JSON.parse(await fs.readFile(path.join(project,'desktop/runtime-assets.json'),'utf8'));
 await fs.mkdir(runtimeRoot,{recursive:true});
 for(const [kind,item] of Object.entries(manifest)) {
  const archive=path.join(runtimeRoot,item.name);
  if(await digest(archive).catch(()=>undefined)!==item.sha256) {
   console.log(`Downloading pinned ${kind} ${item.version}…`);
   const response=await fetch(item.url);if(!response.ok)throw new Error(`Download failed: ${item.url}`);
   await fs.writeFile(archive,Buffer.from(await response.arrayBuffer()));
   if(await digest(archive)!==item.sha256)throw new Error(`${kind}: official archive SHA-256 mismatch`);
  }
  const destination=path.join(runtimeRoot,kind),marker=path.join(destination,'.archive-sha256');
  if(await fs.readFile(marker,'utf8').catch(()=>undefined)!==item.sha256) {
   if(!destination.startsWith(runtimeRoot+path.sep))throw new Error('Invalid build-cache directory');
   await fs.rm(destination,{recursive:true,force:true});await fs.mkdir(destination,{recursive:true});
   await run(path.join(process.env.SystemRoot??'C:\\Windows','System32/tar.exe'),['-xf',archive,'-C',destination]);
   await fs.writeFile(marker,item.sha256);
  }
 }
 return manifest;
}
if(process.argv[1]&&path.resolve(process.argv[1])===fileURLToPath(import.meta.url))await prepareRuntime();
