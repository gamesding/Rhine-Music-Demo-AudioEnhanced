import path from 'node:path'
import { promises as fs } from 'node:fs'
import { createHash } from 'node:crypto'
import { Writable } from 'node:stream'
import { Client } from 'basic-ftp'
import { readAudioMetadata as parseFile, AUDIO_METADATA_VERSION } from './read-audio-metadata.mjs'

const AUDIO = new Set(['.mp3','.flac','.m4a','.aac','.alac','.wav','.aiff','.aif','.ogg','.opus','.dsf','.dff'])
const PLAYABLE = new Set(['.mp3','.flac','.m4a','.aac','.wav','.ogg','.opus'])
const CACHE_FILE = /^[a-f0-9]{64}\.(mp3|flac|m4a|aac|alac|wav|aiff|aif|ogg|opus|dsf|dff)$/
const CACHE_COVER = /^[a-f0-9]{64}\.(png|jpg|webp)$/
const CACHE_LIMIT = 4_000_000_000
const hash = (...values) => createHash('sha256').update(values.join('\0')).digest('hex')
const bad = (message, status=400) => Object.assign(new Error(message), { status })
const text = (value, name, max=1024) => {
  if (typeof value !== 'string' || value.length > max || /[\u0000-\u001f\u007f]/.test(value)) throw bad(`${name} 无效`)
  return value
}
export function ftpConfig(value, previous = {}) {
  const host = text(value.host, '服务器', 253).trim()
  if (!host || /[\s/\\@?#]/.test(host) || host.includes('://')) throw bad('服务器请填写主机名或 IP，端口和目录分别填写。')
  const port = value.port ?? 21
  if (!Number.isInteger(port) || port<1 || port>65535) throw bad('FTP 端口必须为 1–65535')
  const user = text(value.user ?? 'anonymous','用户名',256) || 'anonymous'
  const secure = value.secure ?? false
  if (![false,true,'implicit'].includes(secure)) throw bad('无效的 FTP 加密方式')
  const rawRoot = text(value.root ?? '/','音乐目录')
  if (!rawRoot.startsWith('/') || rawRoot.includes('\\') || rawRoot.split('/').includes('..')) throw bad('音乐目录须为绝对路径，且不能包含 ..')
  const root = path.posix.normalize(rawRoot)
  const password = value.password === undefined ? (previous.host === host && previous.port === port && previous.user === user ? previous.password : '') : text(value.password, '密码',1024)
  return { host, port, user, password: password ?? '', secure, root }
}

export class FtpLibrary {
  constructor({ dataDir }) {
    this.dataDir = path.resolve(dataDir, 'ftp-library')
    this.cacheDir = path.join(this.dataDir, 'audio-cache')
    this.config = null; this.index = []; this.clients = new Set(); this.downloads = new Map()
    this.scanStatus = { running: false }; this.connected = false
    this.reservedBytes = 0
    this.metadataReads = new Map(); this.indexWrites = Promise.resolve()
  }
  async init() {
    await fs.mkdir(this.dataDir, { recursive: true })
    try { this.config = ftpConfig(JSON.parse(await fs.readFile(path.join(this.dataDir,'connection.json'),'utf8'))) } catch {}
    try { const index = JSON.parse(await fs.readFile(path.join(this.dataDir,'index.json'),'utf8')); if (index.source === this.sourceKey()) this.index = index.albums } catch {}
    return this
  }
  sourceKey(config = this.config) { return config ? hash(config.host,String(config.port),config.user,config.root,String(config.secure)) : '' }
  status() {
    const { password, ...config } = this.config ?? {}
    return { configured: !!this.config, connected: this.connected, config, passwordSet: !!password, scan: { ...this.scanStatus },
      albums: this.index.length, tracks: this.index.reduce((n,a) => n+a.tracks.length,0) }
  }
  async client(config = this.config) {
    if (!config) throw bad('FTP 尚未配置',503)
    const client = new Client(20_000, { maxListingBytes: 8*1024*1024, allowSeparateTransferHost: false })
    this.clients.add(client)
    try { await client.access(config); return client }
    catch (error) { this.release(client); throw bad(`FTP 连接失败（${Number(error.code) || '网络或证书错误'}）。`,502) }
  }
  release(client) { client.close(); this.clients.delete(client) }
  async test(value) {
    const config = ftpConfig(value,this.config ?? {})
    const client = await this.client(config)
    try { await client.cd(config.root); await client.list(); return { connected: true } }
    finally { this.release(client) }
  }
  async configure(value) {
    if (this.scanTask || this.downloads.size || this.metadataReads.size) throw bad('FTP 正在扫描或读取歌曲，请完成后再更改连接。',409)
    const config = ftpConfig(value,this.config ?? {})
    await this.test(config)
    const changed = this.sourceKey(config) !== this.sourceKey()
    const file = path.join(this.dataDir,'connection.json')
    await fs.writeFile(`${file}.tmp`,JSON.stringify(config),{ mode: 0o600 }); await fs.rename(`${file}.tmp`,file)
    this.config = config; this.connected = true
    if (changed) this.index = []
    void this.scan().catch(() => {})
    return this.status()
  }
  async disconnect() {
    if (this.scanTask || this.downloads.size || this.metadataReads.size) throw bad('FTP 正在读取，请稍后断开。',409)
    await this.indexWrites.catch(() => {})
    this.config = null; this.index = []; this.connected = false; this.scanStatus = { running: false }
    await fs.rm(path.join(this.dataDir,'connection.json'),{ force: true })
    await fs.rm(path.join(this.dataDir,'index.json'),{ force: true })
    return this.status()
  }
  async scan() {
    if (this.scanTask) return this.scanTask
    if (!this.config) throw bad('FTP 尚未配置',503)
    this.scanStatus = { running: true, directories: 0, tracks: 0 }
    this.scanTask = (async () => {
      const client = await this.client()
      const queue = [{ directory: this.config.root, depth: 0 }], albums = []
      const previousTracks = new Map(this.index.flatMap(album => album.tracks).map(track => [track.id, track]))
      let total = 0
      try {
        while (queue.length) {
          const { directory, depth } = queue.shift()
          if (++this.scanStatus.directories > 5000 || depth > 20) throw bad('FTP 目录数量或深度超过扫描上限。')
          const list = await client.list(directory)
          const files = []
          for (const entry of list) {
            // Skip symlinks and unsafe names; every path stays under the selected remote directory.
            if (entry.isSymbolicLink || !entry.name || ['.','..'].includes(entry.name) || /[\u0000-\u001f\u007f/\\]/.test(entry.name)) continue
            const remotePath = path.posix.join(directory,entry.name)
            if (entry.isDirectory) queue.push({ directory: remotePath, depth: depth+1 })
            else if (entry.isFile && AUDIO.has(path.posix.extname(entry.name).toLowerCase())) files.push({ ...entry, remotePath })
          }
          const groups = directory === this.config.root ? files.map((file) => [file]) : files.length ? [files] : []
          for (const group of groups) {
            const albumId = `ftp-album-${hash(this.sourceKey(),directory,group.length === 1 && directory === this.config.root ? group[0].name : '').slice(0,32)}`
            const artist = path.posix.basename(path.posix.dirname(directory)) || 'FTP'
            const title = directory === this.config.root ? path.posix.parse(group[0].name).name : path.posix.basename(directory)
            const tracks = group.sort((a,b) => a.name.localeCompare(b.name, 'zh-Hans-CN', { numeric: true })).map((file,i) => {
              if (++total > 50000) throw bad('FTP 歌曲超过 50,000 首扫描上限。')
              const extension = path.posix.extname(file.name).toLowerCase()
              const id = `ftp-${hash(this.sourceKey(),file.remotePath).slice(0,40)}`
              const track = { id, albumId, title: path.posix.parse(file.name).name, artist, trackNumber: i+1, duration: 0,
                format: extension.slice(1).toUpperCase(), browserPlayable: PLAYABLE.has(extension), audioUrl: `/api/ftp/audio/${id}`,
                relativePath: path.posix.relative(this.config.root,file.remotePath), _remote: file.remotePath, _size: file.size,
                _modified: file.modifiedAt?.toISOString() ?? file.rawModifiedAt ?? '' }
              const previous = previousTracks.get(id)
              if(previous?._metadata && previous._size === track._size && previous._modified === track._modified) {
                track._metadata = previous._metadata; Object.assign(track, previous._metadata.track)
              }
              return track
            })
            const album = { id: albumId, title, artist, genreId: 'ftp-library', rawGenres: [], folder: path.posix.relative(this.config.root,directory) || '/',
              tracks, producers: [], offline: false, _singleFile: directory === this.config.root }
            this.applyMetadata(album); albums.push(album)
          }
          this.scanStatus.tracks = total
        }
        this.index = albums; this.connected = true
        await this.saveIndex()
        this.scanStatus = { ...this.scanStatus, running: false }
        return this.status()
      } finally { this.release(client) }
    })().catch((error) => { this.connected = false; this.scanStatus = { ...this.scanStatus, running: false, error: error.message }; throw error })
      .finally(() => { this.scanTask = undefined })
    return this.scanTask
  }
  snapshot() {
    return this.index.map(({_cover,_singleFile,...album}) => ({ ...album, ...(_cover?{coverUrl:`/api/ftp/artwork/${album.id}?v=${_cover.file}`} : {}), tracks: album.tracks.map(({ _remote,_size,_modified,_metadata,...track }) => track) }))
  }
  saveIndex() {
    const bytes=JSON.stringify({source:this.sourceKey(),albums:this.index}),file=path.join(this.dataDir,'index.json')
    const write=this.indexWrites.catch(()=>{}).then(async()=>{await fs.writeFile(`${file}.tmp`,bytes);await fs.rename(`${file}.tmp`,file)})
    this.indexWrites=write;return write
  }
  applyMetadata(album) {
    const metadata=album.tracks.map(track=>track._metadata).filter(Boolean)
    if(!metadata.length)return
    const title=metadata.map(item=>album._singleFile?item.track.title:item.album).find(Boolean)
    const artist=metadata.map(item=>album._singleFile?item.track.artist:item.albumArtist).find(Boolean)
    album.title=title||album.title
    album.artist=artist||album.artist
    album._cover=album.tracks.find(track=>track._metadata?.cover)?._metadata.cover
    const discs=album.tracks.map(track=>track.discNumber??1);album.discCount=Math.max(1,...discs)
  }
  artworkFile(id) {
    const cover=this.index.find(album=>album.id===id)?._cover
    return this.config&&cover&&CACHE_COVER.test(cover.file)?{path:path.join(this.cacheDir,cover.file),allowedRoot:this.cacheDir,mime:cover.mime,embedded:true}:null
  }
  async readMetadata(id,file) {
    const track=this.track(id)
    if(!track||(track._metadata?.version===AUDIO_METADATA_VERSION&&!track._metadata.needsCover))return
    if(this.metadataReads.has(id))return this.metadataReads.get(id)
    const task=(async()=>{
      let metadata;try{metadata=await parseFile(file.path,{duration:true})}catch{return}
      const current=this.track(id)
      if(!current||this.trackFile(id)?.path!==file.path)return
      const common=metadata.common??{},format=metadata.format??{},parsed={track:{},version:AUDIO_METADATA_VERSION}
      const clean=value=>typeof value==='string'&&value.trim()?value.trim().slice(0,8192):undefined
      for(const [key,value] of Object.entries({title:clean(common.title),artist:clean(common.artist)||clean(common.albumartist),trackNumber:common.track?.no,discNumber:common.disk?.no,duration:format.duration,codec:clean(format.codec),sampleRate:format.sampleRate,bitsPerSample:format.bitsPerSample,bitrate:format.bitrate,numberOfChannels:format.numberOfChannels,lossless:format.lossless}))if(value!==undefined&&(typeof value!=='number'||Number.isFinite(value)))parsed.track[key]=value
      parsed.album=clean(common.album);parsed.albumArtist=clean(common.albumartist)||clean(common.artist)
      const picture=common.picture?.find(image=>/front/i.test(image.type??''))??common.picture?.[0]
      const mime=picture?.format==='image/jpg'?'image/jpeg':picture?.format,extension=({'image/jpeg':'.jpg','image/png':'.png','image/webp':'.webp'})[mime]
      if(extension&&picture.data?.length&&picture.data.length<30*1024*1024) {
        const name=createHash('sha256').update(picture.data).digest('hex')+extension,target=path.join(this.cacheDir,name)
        if(await fs.stat(target).then(stat=>stat.isFile()&&stat.size===picture.data.length).catch(()=>false))parsed.cover={file:name,mime}
        else if(await this.cacheBytes()+this.reservedBytes+picture.data.length<=CACHE_LIMIT){await fs.writeFile(target,picture.data,{mode:0o600,flag:'wx'}).catch(error=>{if(error.code!=='EEXIST')throw error});parsed.cover={file:name,mime}}
      }
      current._metadata=parsed;Object.assign(current,parsed.track)
      const album=this.index.find(album=>album.id===current.albumId);if(album)this.applyMetadata(album)
      await this.saveIndex()
    })().finally(()=>this.metadataReads.delete(id))
    this.metadataReads.set(id,task);return task
  }
  track(id) { return this.config && this.index.flatMap((a) => a.tracks).find((t) => t.id === id) }
  trackFile(id) {
    const track = this.track(id)
    if (!track) return null
    const filename = `${hash(this.sourceKey(),track._remote,String(track._size),track._modified)}${path.posix.extname(track._remote).toLowerCase()}`
    return { path: path.join(this.cacheDir, filename), allowedRoot: this.cacheDir }
  }
  async ensure(id) {
    const track = this.track(id), file = this.trackFile(id)
    if (!track || !file) throw bad('FTP 索引中没有此歌曲',404)
    if (!Number.isSafeInteger(track._size) || track._size < 0 || track._size > 1_000_000_000) throw bad('FTP 单曲大小无效或超过 1 GB 读取上限。',413)
    if (await fs.stat(file.path).then((s) => s.isFile() && s.size === track._size).catch(() => false)) {await this.readMetadata(id,file);return file}
    if (this.downloads.has(id)) return this.downloads.get(id)
    if (this.downloads.size >= 2) throw bad('FTP 正在读取其他歌曲，请稍后重试。',429)
    let reserved = false
    const task = (async () => {
      await fs.mkdir(this.cacheDir,{ recursive: true })
      const cached = await this.cacheBytes()
      if (cached+track._size+this.reservedBytes > CACHE_LIMIT) throw bad('FTP 缓存已达 4 GB 上限，请在设置中清理缓存后重试。',413)
      this.reservedBytes += track._size
      reserved = true
      const capacity = await fs.statfs(this.cacheDir)
      if (capacity.bavail*capacity.bsize < track._size+100_000_000) throw bad('本机空间不足，无法缓存 FTP 歌曲。')
      const client = await this.client()
      let target
      try {
        if (await client.size(track._remote) !== track._size) throw bad('FTP 歌曲已变化，请重新扫描曲库。',409)
        await fs.rm(`${file.path}.partial`,{ force: true })
        target = await fs.open(`${file.path}.partial`,'wx',0o600)
        let bytes = 0
        const stream = new Writable({ write(chunk,encoding,callback) {
          bytes += chunk.length
          if (bytes > track._size || bytes > 1_000_000_000) return callback(bad('FTP 下载大小与索引不一致。'))
          void (async () => {
            let offset = 0
            while (offset < chunk.length) {
              const { bytesWritten } = await target.write(chunk,offset,chunk.length-offset)
              if (!bytesWritten) throw bad('FTP 缓存写入失败。',502)
              offset += bytesWritten
            }
          })().then(() => callback(),callback)
        } })
        await client.downloadTo(stream,track._remote)
        if (bytes !== track._size) throw bad('FTP 歌曲读取不完整。',502)
        await target.close(); target = undefined
        await fs.rename(`${file.path}.partial`,file.path)
        this.connected = true
        await this.readMetadata(id,file)
        return file
      } catch (error) { this.connected = false; throw bad(`FTP 歌曲读取失败：${error.status ? error.message : '请检查连接、读取权限或证书。'}`,error.status ?? 502) }
      finally { this.release(client); await target?.close(); await fs.rm(`${file.path}.partial`,{ force: true }).catch(() => {}) }
    })().finally(() => { this.downloads.delete(id); if (reserved) this.reservedBytes = Math.max(0,this.reservedBytes-track._size) })
    this.downloads.set(id,task)
    return task
  }
  async cacheBytes() {
    const names = await fs.readdir(this.cacheDir).catch((error) => { if (error.code === 'ENOENT') return []; throw error })
    let size = 0
    for (const name of names) if (CACHE_FILE.test(name)||CACHE_COVER.test(name)) size += (await fs.stat(path.join(this.cacheDir,name))).size
    return size
  }
  async clearCache() {
    if (this.downloads.size||this.metadataReads.size) throw bad('FTP 正在读取歌曲，请完成后再清理缓存。',409)
    for (const name of await fs.readdir(this.cacheDir).catch((error) => { if (error.code === 'ENOENT') return []; throw error })) {
      if (CACHE_FILE.test(name)||CACHE_COVER.test(name)) await fs.rm(path.join(this.cacheDir,name),{ force: true })
    }
    for(const album of this.index){delete album._cover;for(const track of album.tracks)if(track._metadata){delete track._metadata.cover;track._metadata.needsCover=true}}
    await this.saveIndex()
    return this.status()
  }
  close() { for (const client of this.clients) client.close(); this.clients.clear() }
}
