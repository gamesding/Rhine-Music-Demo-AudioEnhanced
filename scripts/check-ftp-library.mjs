import test from 'node:test'
import assert from 'node:assert/strict'
import net from 'node:net'
import path from 'node:path'
import os from 'node:os'
import { promises as fs } from 'node:fs'
import { FtpLibrary, ftpConfig } from './ftp-library.mjs'
import { sonySettings, boundedSource } from './sony-walkman.mjs'
import { createMusicServer } from './music-server.mjs'
import { dsdFixture, taggedDsf, silentWav } from './audio-fixtures.mjs'

test('FTP configuration validates commands, remote boundaries, TLS and password retention', () => {
  const valid = { host: 'music.example.test', port: 21, user: 'listener', password: 'private', root: '/Music', secure: true }
  const prior = ftpConfig(valid)
  assert.equal(ftpConfig({ ...valid, password: undefined }, prior).password, 'private')
  assert.equal(ftpConfig({ ...valid, host: 'other.example.test', password: undefined }, prior).password, '')
  for (const value of [{ ...valid, root: '/Music/../private' }, { ...valid, user: 'x\r\nDELE music' }, { ...valid, host: 'ftp://host' }, { ...valid, port: 0 }, { ...valid, secure: 'no' }]) assert.throws(() => ftpConfig(value))
})
test('Sony accepts only original exposed mode ranges', () => {
  assert.deepEqual(sonySettings({ dsee: true, dc: 6, vinyl: 4 }), { dsee: true, dc: 6, vinyl: 4 })
  for (const value of [{ dsee: 'true', dc: 0, vinyl: 0 }, { dsee: true, dc: 7, vinyl: 0 }, { dsee: false, dc: 0, vinyl: 5 }, { dsee: false, dc: 0, vinyl: 0, path: '/tmp' }]) assert.throws(() => sonySettings(value))
})

// Real passive FTP protocol over isolated loopback sockets. The fixture implements reads only.
async function fixtureFtp(bytes,filename='01. Test.wav',additional={}) {
  const files=new Map([[filename,bytes],...Object.entries(additional)])
  const commands = [], sockets = new Set()
  const server = net.createServer((socket) => {
    sockets.add(socket); socket.on('close', () => sockets.delete(socket))
    socket.on('error', () => {})
    let input = '', directory = '/', dataServer, dataReady, loggedIn = false
    const reply = (message) => socket.write(`${message}\r\n`)
    const list = (location) => location === '/' ? 'type=dir; Music\r\n' : location === '/Music' ? 'type=dir; Artist\r\n' : location === '/Music/Artist' ? 'type=dir; Album\r\n' : [...files].map(([name,data])=>`type=file;size=${data.length};modify=20261007000000; ${name}\r\n`).join('')
    async function passive() {
      dataServer = net.createServer()
      dataReady = new Promise((resolve) => dataServer.once('connection', (data) => { sockets.add(data); data.on('error', () => {}); data.once('close', () => sockets.delete(data)); resolve(data) }))
      await new Promise((resolve) => dataServer.listen(0,'127.0.0.1',resolve))
      reply(`229 Entering Extended Passive Mode (|||${dataServer.address().port}|)`)
    }
    async function command(line) {
      const [verb, ...parts] = line.split(' '), arg = parts.join(' ')
      commands.push(verb)
      if (verb === 'USER') return reply('331 Password required')
      if (verb === 'PASS') { loggedIn = arg === 'private'; return reply(loggedIn ? '230 Logged in' : '530 Login incorrect') }
      if (verb === 'QUIT') { reply('221 Goodbye'); socket.end(); return }
      if (!loggedIn) return reply('530 Login required')
      if (['TYPE','STRU','OPTS'].includes(verb)) return reply('200 OK')
      if (verb === 'FEAT') return reply('211-Features\r\n MLST type*;size*;modify*;\r\n UTF8\r\n EPSV\r\n211 End')
      if (verb === 'SYST') return reply('215 UNIX Type: L8')
      if (verb === 'PWD') return reply(`257 "${directory}"`)
      if (verb === 'CWD') { directory = arg; return reply('250 Directory changed') }
      if (verb === 'EPSV') return passive()
      if (verb === 'SIZE') return reply(`213 ${files.get(path.posix.basename(arg))?.length??bytes.length}`)
      if (verb === 'MLSD' || verb === 'LIST' || verb === 'RETR') {
        reply('150 Opening data connection')
        const data = await dataReady
        await new Promise((resolve) => data.end(verb === 'RETR' ? files.get(path.posix.basename(arg))??bytes : list(arg || directory),resolve))
        await new Promise((resolve) => dataServer.close(resolve))
        return reply('226 Transfer complete')
      }
      reply('502 Unsupported')
    }
    let chain = Promise.resolve()
    socket.on('data', (chunk) => {
      input += chunk.toString()
      let end
      while ((end = input.indexOf('\r\n')) !== -1) { const line = input.slice(0,end); input = input.slice(end+2); chain = chain.then(() => command(line)).catch(() => socket.destroy()) }
    })
    reply('220 Test FTP')
  })
  await new Promise((resolve) => server.listen(0,'127.0.0.1',resolve))
  return { port: server.address().port, commands, close: async () => { for (const socket of sockets) socket.destroy(); await new Promise((resolve) => server.close(resolve)) } }
}

test('FTP logs in, scans nested albums without downloading songs, masks credentials, caches exact bytes and serves Range', async (t) => {
  const root = await fs.mkdtemp(path.join(os.tmpdir(),'rhine-ftp-'))
  t.after(() => fs.rm(root,{ recursive: true, force: true }))
  const bytes = Buffer.alloc(1024,17)
  const fixture = await fixtureFtp(bytes)
  t.after(() => fixture.close())
  const ftp = await new FtpLibrary({ dataDir: root }).init()
  const config = { host: '127.0.0.1', port: fixture.port, user: 'listener', password: 'private', root: '/Music', secure: false }
  await assert.rejects(ftp.test({ ...config, password: 'wrong' }), /连接失败/)
  await ftp.configure(config); await ftp.scanTask
  assert.equal(fixture.commands.includes('RETR'),false, 'scan must list only')
  const status = ftp.status()
  assert.equal(status.tracks,1); assert.equal(status.albums,1)
  assert.equal(JSON.stringify(status).includes('private'),false)
  const track = ftp.snapshot()[0].tracks[0]
  assert.equal(track.title,'01. Test')
  assert.equal('_remote' in track,false)
  const source = await ftp.ensure(track.id)
  assert.deepEqual(await fs.readFile(source.path),bytes)
  const downloads = fixture.commands.filter((x) => x === 'RETR').length
  await ftp.ensure(track.id)
  assert.equal(fixture.commands.filter((x) => x === 'RETR').length,downloads)
  const restarted = await new FtpLibrary({ dataDir: root }).init()
  assert.equal(restarted.snapshot()[0].tracks[0].id,track.id)
  const store = { dataDir: root, config: {}, reloadRules: async () => {}, trackFile: () => null,
    snapshot: () => ({ version: 1, albums: [], genres: [], roots: [], scan: { running: false } }) }
  const { server } = await createMusicServer({ dataDir: root, store, ftp, autoScan: false })
  await new Promise((resolve) => server.listen(0,'127.0.0.1',resolve))
  t.after(() => new Promise((resolve) => server.close(resolve)))
  const base = `http://127.0.0.1:${server.address().port}`
  const response = await fetch(`${base}${track.audioUrl}`,{ headers: { Range: 'bytes=10-19' } })
  assert.equal(response.status,206); assert.deepEqual(Buffer.from(await response.arrayBuffer()),bytes.subarray(10,20))
  assert.equal((await (await fetch(`${base}/api/library`)).json()).albums.length,1)
  assert.equal((await fetch(`${base}/api/ftp/status`,{ headers: { Origin: 'https://untrusted.test' } })).status,403)
  const outside = path.join(root,'outside.wav'); await fs.writeFile(outside,bytes)
  await assert.rejects(boundedSource({ path: outside, allowedRoot: ftp.cacheDir }), /移出/)
  assert.ok(fixture.commands.every((cmd) => !['STOR','DELE','RMD','MKD','RNFR','RNTO'].includes(cmd)))
  await fs.writeFile(path.join(ftp.cacheDir,'keep.txt'),'not an audio cache')
  await ftp.clearCache()
  assert.equal(await fs.stat(source.path).catch(()=>null),null)
  assert.equal(await fs.readFile(path.join(ftp.cacheDir,'keep.txt'),'utf8'),'not an audio cache')
  assert.equal(ftp.snapshot().length,1,'clearing audio keeps the connection and index')
  await ftp.ensure(track.id)
  assert.deepEqual(await fs.readFile(source.path),bytes)
  await ftp.disconnect(); assert.equal(ftp.snapshot().length,0)
  ftp.close(); restarted.close()
})

test('FTP cached PCM exposes original Hi-Res metadata without downloading songs during scan',async t=>{
 const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-ftp-hires-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
 const bytes=silentWav(.05,96000,24),fixture=await fixtureFtp(bytes,'01 Hi-Res.wav');t.after(()=>fixture.close());
 const ftp=await new FtpLibrary({dataDir:root}).init();t.after(()=>ftp.close());
 await ftp.configure({host:'127.0.0.1',port:fixture.port,user:'listener',password:'private',root:'/Music',secure:false});await ftp.scanTask;
 const before=ftp.snapshot()[0].tracks[0];assert.equal(before.sampleRate,undefined);assert.ok(!fixture.commands.includes('RETR'));
 const file=await ftp.ensure(before.id),track=ftp.snapshot()[0].tracks[0];assert.deepEqual(await fs.readFile(file.path),bytes);
 assert.equal(track.sampleRate,96000);assert.equal(track.bitsPerSample,24);assert.equal(track.lossless,true);
 await ftp.scan();assert.deepEqual(ftp.snapshot()[0].tracks[0],track);
 const restarted=await new FtpLibrary({dataDir:root}).init();t.after(()=>restarted.close());assert.deepEqual(restarted.snapshot()[0].tracks[0],track);
 await restarted.ensure(track.id);assert.equal(fixture.commands.filter(command=>command==='RETR').length,1);
});
test('an untagged first FTP track cannot hide album tags provided by a later DSF',async t=>{
 const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-ftp-mixed-tags-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
 const pcm=silentWav(.05,96000,24),dsf=taggedDsf(dsdFixture().dsf),fixture=await fixtureFtp(pcm,'01 Untagged.wav',{'02 Tagged.dsf':dsf});t.after(()=>fixture.close());
 const ftp=await new FtpLibrary({dataDir:root}).init();t.after(()=>ftp.close());await ftp.configure({host:'127.0.0.1',port:fixture.port,user:'listener',password:'private',root:'/Music',secure:false});await ftp.scanTask;
 const ids=ftp.snapshot()[0].tracks.map(track=>track.id);await ftp.ensure(ids[0]);assert.equal(ftp.snapshot()[0].title,'Album');
 await ftp.ensure(ids[1]);const album=ftp.snapshot()[0];assert.equal(album.title,'原生 DSD 专辑');assert.equal(album.artist,'测试乐团');assert.equal(album.tracks[0].sampleRate,96000);assert.ok(album.coverUrl);
 await ftp.scan();assert.deepEqual(ftp.snapshot()[0],album);assert.equal(fixture.commands.filter(cmd=>cmd==='RETR').length,2);
});
test('FTP DSF reads ID3 only after selecting a song, preserves tags and cover across rescan/restart/cache clearing',async t=>{
 const root=await fs.mkdtemp(path.join(os.tmpdir(),'rhine-ftp-id3-'));t.after(()=>fs.rm(root,{recursive:true,force:true}));
 const picture=await fs.readFile(new URL('../public/icons/icon-192.png',import.meta.url)),bytes=taggedDsf(dsdFixture().dsf,{picture});
 const fixture=await fixtureFtp(bytes,'远端文件名.dsf');t.after(()=>fixture.close());
 const ftp=await new FtpLibrary({dataDir:root}).init();t.after(()=>ftp.close());
 await ftp.configure({host:'127.0.0.1',port:fixture.port,user:'listener',password:'private',root:'/Music',secure:false});await ftp.scanTask;
 assert.ok(!fixture.commands.includes('RETR'));const id=ftp.snapshot()[0].tracks[0].id;
 const file=await ftp.ensure(id);assert.deepEqual(await fs.readFile(file.path),bytes);
 const album=ftp.snapshot()[0];assert.equal(album.title,'原生 DSD 专辑');assert.equal(album.artist,'测试乐团');assert.equal(album.tracks[0].title,'星河之声');assert.equal(album.tracks[0].artist,'测试歌手');assert.equal(album.tracks[0].trackNumber,3);assert.equal(album.tracks[0].discNumber,1);assert.equal(album.tracks[0].sampleRate,2822400);
 assert.deepEqual(await fs.readFile(ftp.artworkFile(album.id).path),picture);assert.ok(!('_metadata' in album.tracks[0]));assert.ok(!('_cover' in album));
 await ftp.scan();assert.deepEqual(ftp.snapshot()[0],album);
 const restarted=await new FtpLibrary({dataDir:root}).init();t.after(()=>restarted.close());assert.deepEqual(restarted.snapshot()[0],album);
 const store={dataDir:root,config:{},reloadRules:async()=>{},trackFile:()=>null,snapshot:()=>({version:1,albums:[],genres:[],roots:[],scan:{running:false}})};
 const {server}=await createMusicServer({dataDir:root,store,ftp,autoScan:false});await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));t.after(()=>{server.closeAllConnections();return new Promise(resolve=>server.close(resolve))});
 const response=await fetch(`http://127.0.0.1:${server.address().port}${album.coverUrl}`);assert.equal(response.status,200);assert.match(response.headers.get('content-type'),/^image\/png/);assert.deepEqual(Buffer.from(await response.arrayBuffer()),picture);
 await ftp.clearCache();assert.equal(ftp.artworkFile(album.id),null);assert.equal(ftp.snapshot()[0].tracks[0].title,'星河之声');await ftp.scan();assert.equal(ftp.snapshot()[0].title,'原生 DSD 专辑');
 await ftp.ensure(id);assert.deepEqual(await fs.readFile(ftp.artworkFile(album.id).path),picture);assert.deepEqual(await fs.readFile(file.path),bytes);
 assert.equal(fixture.commands.filter(cmd=>cmd==='RETR').length,2);assert.ok(!fixture.commands.some(cmd=>['STOR','DELE','RNFR','RNTO'].includes(cmd)));
});
