const {app,BrowserWindow,ipcMain,dialog,shell}=require('electron');
const path=require('node:path');
const fs=require('node:fs/promises');
const {pathToFileURL}=require('node:url');
const root=path.resolve(__dirname,'..');
const args=process.argv.slice(1),selfTest=args.includes('--self-test');
app.commandLine.appendSwitch('force_high_performance_gpu');
app.setName('Rhine Music');
if(process.env.RHINE_APP_HOME)app.setPath('userData',path.resolve(process.env.RHINE_APP_HOME));
const dataDir=path.resolve(process.env.MUSIC_DATA_DIR||path.join(app.getPath('userData'),'music-data'));
process.env.SONY_WALKMAN_ASSETS=path.join(root,'vendor/sony-walkman');
process.env.SONY_WALKMAN_PYTHON=path.join(root,'runtime/python/python.exe');
process.env.SONY_WALKMAN_X86_DLL=path.join(root,'vendor/sony-walkman-x86/sony-dsp-x86.dll');
process.env.SONY_WALKMAN_NATIVE_DECODER=path.join(root,'vendor/audio/windows-x64/rhine-audio-host.exe');
process.env.RHINE_NATIVE_AUDIO=process.env.SONY_WALKMAN_NATIVE_DECODER;
let service,window,quitting=false,preferences={},saveTail=Promise.resolve();
const preferenceFile=path.join(app.getPath('userData'),'preferences.json');
const preferenceKeys=new Set(['theme','sortMode','quality','reduced','volume','songFade','sony','sonyParallel','sonyStreaming','output','bgm','bgmVolume','sound','soundVolume','renderQuality']);
const selectPreferences=value=>{
 if(!value||typeof value!=='object'||Array.isArray(value))throw new Error('Invalid preferences');
 const text=JSON.stringify(value);if(text.length>8192)throw new Error('Preferences exceed limit');
 return Object.fromEntries(Object.entries(value).filter(([key])=>preferenceKeys.has(key)));
};
async function listen() {
 for(let port=5175;port<5185;port++) {
  try {await new Promise((resolve,reject)=>{const failed=error=>{service.server.off('listening',listening);reject(error)};const listening=()=>{service.server.off('error',failed);resolve()};service.server.once('error',failed);service.server.once('listening',listening);service.server.listen(port,'127.0.0.1')});return `http://127.0.0.1:${port}`}
  catch(error){if(!['EADDRINUSE','EACCES'].includes(error.code))throw error}
 }
 throw new Error('本地播放服务端口均被占用，请关闭多余的播放器实例。');
}
function ownedEvent(event){return window&&!window.isDestroyed()&&event.sender===window.webContents}
ipcMain.on('rhine:preferences:get',event=>{event.returnValue=ownedEvent(event)?preferences:{}});
ipcMain.on('rhine:preferences:save',(event,value)=>{
 if(!ownedEvent(event))return;let selected;try{selected=selectPreferences(value)}catch{return}
 preferences=selected;
 saveTail=saveTail.catch(()=>{}).then(async()=>{await fs.mkdir(path.dirname(preferenceFile),{recursive:true});const temporary=preferenceFile+'.next';await fs.writeFile(temporary,JSON.stringify(selected),{mode:0o600});await fs.rename(temporary,preferenceFile)});
});
if(!selfTest&&!app.requestSingleInstanceLock()){app.quit()}
else {
 app.on('second-instance',()=>{if(window){if(window.isMinimized())window.restore();window.show();window.focus()}});
 app.whenReady().then(async()=>{
  try {
   if(selfTest) {
    const index=args.indexOf('--report');if(index<0||!args[index+1])throw new Error('Self-test requires --report <file>');
    const {runSelfTest}=await import(pathToFileURL(path.join(__dirname,'self-test.mjs')).href);
    const report=await runSelfTest({root,dataDir});const reportFile=path.resolve(args[index+1]);await fs.mkdir(path.dirname(reportFile),{recursive:true});await fs.writeFile(reportFile,JSON.stringify(report,null,2)+'\n');app.exit(report.ok?0:1);return;
   }
   try{preferences=selectPreferences(JSON.parse(await fs.readFile(preferenceFile,'utf8')))}catch{}
   const {createMusicServer}=await import(pathToFileURL(path.join(root,'scripts/music-server.mjs')).href);
   service=await createMusicServer({dataDir});const origin=await listen();
   window=new BrowserWindow({width:1280,height:840,minWidth:700,minHeight:620,title:'Rhine Music',backgroundColor:'#e6e8e3',show:false,autoHideMenuBar:true,icon:path.join(__dirname,'app.ico'),webPreferences:{preload:path.join(__dirname,'preload.cjs'),nodeIntegration:false,contextIsolation:true,sandbox:true,webSecurity:true}});
   // Restore the intended CSS proportions on startup/reload, including profiles
   // with an older saved page zoom. Windows DPI scaling remains under the OS.
   window.webContents.on('dom-ready',()=>{if(window&&!window.isDestroyed())window.webContents.setZoomFactor(1)});
   window.webContents.on('will-navigate',(event,url)=>{if(new URL(url).origin!==origin)event.preventDefault()});
   window.webContents.setWindowOpenHandler(({url})=>{try{const parsed=new URL(url);if(parsed.protocol==='https:')void shell.openExternal(url)}catch{}return {action:'deny'}});
   window.webContents.session.setPermissionRequestHandler((_contents,_permission,callback)=>callback(false));
   window.once('ready-to-show',()=>window.show());window.on('closed',()=>{window=undefined});
   try{await window.loadURL(origin)}catch(error){
    // Reloading or closing the owned window cancels this navigation. Electron
    // reports ERR_ABORTED for that normal cancellation while the next load
    // proceeds; it must not tear down the service or display a startup error.
    if(error.code!=='ERR_ABORTED'&&error.errno!==-3)throw error;
   }
  }catch(error){if(!selfTest)dialog.showErrorBox('Rhine Music 启动失败',error.message);else {const i=args.indexOf('--report');if(i>=0&&args[i+1])await fs.writeFile(path.resolve(args[i+1]),JSON.stringify({ok:false,error:error.stack},null,2)).catch(()=>{})}app.exit(1)}
 });
 app.on('window-all-closed',()=>app.quit());
 app.on('before-quit',event=>{
  if(quitting)return;event.preventDefault();quitting=true;
  const shut=async()=>{if(service){await service.native.stopCurrent().catch(()=>{});service.sony.close();service.ftp.close();service.native.close();service.server.closeAllConnections();await new Promise(resolve=>service.server.close(resolve))}await saveTail.catch(()=>{})};
  void shut().finally(()=>app.quit());
 });
}
