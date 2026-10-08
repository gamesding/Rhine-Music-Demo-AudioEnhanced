const {contextBridge,ipcRenderer}=require('electron');
const preferences=ipcRenderer.sendSync('rhine:preferences:get');
try{if(Object.keys(preferences).length)localStorage.setItem('rhine-music-preferences',JSON.stringify(preferences))}catch{}
contextBridge.exposeInMainWorld('rhineDesktop',{native:true,savePreferences:value=>ipcRenderer.send('rhine:preferences:save',value)});
