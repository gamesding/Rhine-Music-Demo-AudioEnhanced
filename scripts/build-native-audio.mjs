import { promises as fs } from 'node:fs'
import path from 'node:path'
import { spawn } from 'node:child_process'
import { fileURLToPath } from 'node:url'
import { createHash } from 'node:crypto'
const project=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..')
const vendor=path.join(project,'vendor/audio/windows-x64'),source=path.join(project,'native/audio-host.cpp')
const compiler=process.env.RHINE_CXX??path.join(project,'.tools/walkman/compiler/zig-x86_64-windows-0.15.2/zig.exe')
await new Promise((resolve,reject)=>{
 const child=spawn(compiler,['c++','-target','x86_64-windows-gnu','-std=c++17','-O2','-fno-fast-math','-static','-I',path.join(vendor,'include'),source,'-o',path.join(vendor,'rhine-audio-host.exe')],{cwd:project,windowsHide:true,stdio:'inherit'})
 child.once('error',reject);child.once('close',code=>code===0?resolve():reject(new Error(`Native audio compilation failed (${code})`)))
})
const manifest=JSON.parse(await fs.readFile(path.join(vendor,'assets.json'),'utf8'))
manifest.files['rhine-audio-host.exe']=createHash('sha256').update(await fs.readFile(path.join(vendor,'rhine-audio-host.exe'))).digest('hex')
manifest.sourceSha256=createHash('sha256').update(await fs.readFile(source)).digest('hex')
await fs.writeFile(path.join(vendor,'assets.json'),JSON.stringify(manifest,null,2)+'\n')
console.log('Built the self-contained C++ ASIO/DSD host and recorded hashes.')
