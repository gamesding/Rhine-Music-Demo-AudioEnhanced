// Windows ASIO host. Sony processing stays in the original ARM bridge.
// Only file decoding / DSD framing / device output are handled here.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"
#define BASSDEF(f) (WINAPI *f)
#define BASSASIODEF(f) (WINAPI *f)
#define BASSDSDDEF(f) (WINAPI *f)
#include "bass.h"
#include "bassasio.h"
#include "bassdsd.h"
using json=nlohmann::json;
using Clock=std::chrono::steady_clock;
static HSTREAM stream=0;
static bool asio=false,paused=true,ended=false;
static std::string mode="pcm",session,error,backend="asio";
static int systemDevice=-1;
static DWORD outputChannel=0;
static double outputRate=0;
static double pausedPosition=0;
static std::atomic<int> driverEvent{0};
static std::atomic<bool> dsdReadFailed{false};
static Clock::time_point endSince{};
static std::wstring directory;
struct GrowingFile {
 HANDLE handle=INVALID_HANDLE_VALUE;QWORD length=0,position=0;
 std::atomic<bool> cancelled{false},failed{false};std::mutex mutex;
};
static std::unique_ptr<GrowingFile> growing;
// Present DSF as a seekable DSDIFF byte view. BASSDSD 2.4.2 drops the final
// complete DSF block when sampleCount/8 is a multiple of 4096. This view keeps
// every source bit, changes only container framing / specified bit order, and
// avoids rewriting or copying the song. Its two-channel cache is only 8192 bytes.
struct DsfView {
 HANDLE handle=INVALID_HANDLE_VALUE;QWORD position=0,dataOffset=0,bytesPerChannel=0,length=0,cachedBlock=static_cast<QWORD>(-1);
 DWORD channels=0,rate=0;bool lsb=false;std::vector<unsigned char> header,cache;std::mutex mutex;
 ~DsfView(){if(handle!=INVALID_HANDLE_VALUE)CloseHandle(handle);}
};
static std::unordered_map<HSTREAM,std::unique_ptr<DsfView>> dsfViews;
static QWORD little64(const unsigned char* value){QWORD n=0;for(int i=7;i>=0;i--)n=(n<<8)|value[i];return n;}
static DWORD little32(const unsigned char* value){return static_cast<DWORD>(little64(std::array<unsigned char,8>{value[0],value[1],value[2],value[3],0,0,0,0}.data()));}
static bool readAt(HANDLE handle,QWORD offset,void* destination,DWORD count) {
 LARGE_INTEGER where{};where.QuadPart=offset;DWORD received=0;
 return SetFilePointerEx(handle,where,nullptr,FILE_BEGIN)&&ReadFile(handle,destination,count,&received,nullptr)&&received==count;
}
static void appendBig(std::vector<unsigned char>& result,QWORD value,int bytes){for(int i=bytes-1;i>=0;i--)result.push_back(static_cast<unsigned char>(value>>(i*8)));}
static std::vector<unsigned char> dffChunk(const char* id,const std::vector<unsigned char>& data) {
 std::vector<unsigned char> result(id,id+4);appendBig(result,data.size(),8);result.insert(result.end(),data.begin(),data.end());if(data.size()%2)result.push_back(0);return result;
}
static std::unique_ptr<DsfView> dsfView(const std::wstring& file) {
 auto view=std::make_unique<DsfView>();view->handle=CreateFileW(file.c_str(),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
 if(view->handle==INVALID_HANDLE_VALUE)throw std::runtime_error("DSD file could not be opened");
 std::array<unsigned char,80> head{};
 if(!readAt(view->handle,0,head.data(),4))throw std::runtime_error("Incomplete DSD header");
 if(std::string(reinterpret_cast<char*>(head.data()),4)!="DSD ")return nullptr;
 if(!readAt(view->handle,0,head.data(),80)||little64(head.data()+4)!=28||std::string(reinterpret_cast<char*>(head.data()+28),4)!="fmt ")throw std::runtime_error("Invalid DSF header");
 const QWORD fmtBytes=little64(head.data()+32),samples=little64(head.data()+64);
 view->channels=little32(head.data()+52);view->rate=little32(head.data()+56);const DWORD bits=little32(head.data()+60);
 if(fmtBytes<52||fmtBytes>1048576||little32(head.data()+40)!=1||little32(head.data()+44)!=0||view->channels<1||view->channels>2||!view->rate||(bits!=1&&bits!=8)||little32(head.data()+72)!=4096||!samples||samples>static_cast<QWORD>(-1)-7)throw std::runtime_error("Unsupported DSF layout; mono/stereo uncompressed 4096-byte blocks required");
 std::array<unsigned char,12> data{};if(!readAt(view->handle,28+fmtBytes,data.data(),12)||std::string(reinterpret_cast<char*>(data.data()),4)!="data")throw std::runtime_error("Missing DSF data chunk");
 view->dataOffset=40+fmtBytes;view->bytesPerChannel=(samples+7)/8;view->lsb=bits==1;LARGE_INTEGER size{};
 const QWORD blocks=(view->bytesPerChannel+4095)/4096,declared=little64(data.data()+4);
 if(!GetFileSizeEx(view->handle,&size)||view->bytesPerChannel>static_cast<QWORD>(size.QuadPart)||blocks>static_cast<QWORD>(size.QuadPart)/(4096*view->channels)||declared<12||declared-12<blocks*4096*view->channels||view->dataOffset>static_cast<QWORD>(size.QuadPart)||blocks*4096*view->channels>static_cast<QWORD>(size.QuadPart)-view->dataOffset)throw std::runtime_error("Truncated DSF audio blocks");
 std::vector<unsigned char> frequency;appendBig(frequency,view->rate,4);
 std::vector<unsigned char> channels;appendBig(channels,view->channels,2);const std::string names=view->channels==2?"SLFTSRGT":"C   ";channels.insert(channels.end(),names.begin(),names.end());
 const std::string compression="DSD ";std::vector<unsigned char> cmpr(compression.begin(),compression.end());cmpr.push_back(14);const std::string label="not compressed";cmpr.insert(cmpr.end(),label.begin(),label.end());
 std::vector<unsigned char> properties={'S','N','D',' '};for(const auto& chunk:{dffChunk("FS  ",frequency),dffChunk("CHNL",channels),dffChunk("CMPR",cmpr)})properties.insert(properties.end(),chunk.begin(),chunk.end());
 const auto version=dffChunk("FVER",{1,5,0,0}),prop=dffChunk("PROP",properties);const QWORD bytes=view->bytesPerChannel*view->channels;
 const QWORD formBytes=4+version.size()+prop.size()+12+bytes+(bytes%2);
 view->header={'F','R','M','8'};appendBig(view->header,formBytes,8);view->header.insert(view->header.end(),{'D','S','D',' '});view->header.insert(view->header.end(),version.begin(),version.end());view->header.insert(view->header.end(),prop.begin(),prop.end());view->header.insert(view->header.end(),{'D','S','D',' '});appendBig(view->header,bytes,8);
 view->length=view->header.size()+bytes+(bytes%2);view->cache.resize(4096*view->channels);return view;
}
static void CALLBACK dsfClose(void* user){auto& view=*static_cast<DsfView*>(user);std::lock_guard<std::mutex> lock(view.mutex);if(view.handle!=INVALID_HANDLE_VALUE){CloseHandle(view.handle);view.handle=INVALID_HANDLE_VALUE;}}
static QWORD CALLBACK dsfLength(void* user){return static_cast<DsfView*>(user)->length;}
static BOOL CALLBACK dsfSeek(QWORD offset,void* user){auto& view=*static_cast<DsfView*>(user);std::lock_guard<std::mutex> lock(view.mutex);if(offset>view.length)return FALSE;view.position=offset;return TRUE;}
static DWORD CALLBACK dsfRead(void* destination,DWORD count,void* user) {
 auto& view=*static_cast<DsfView*>(user);std::lock_guard<std::mutex> lock(view.mutex);DWORD written=0;auto buffer=static_cast<unsigned char*>(destination);
 while(written<count&&view.position<view.length) {
  if(view.position<view.header.size())buffer[written]=view.header[view.position];
  else {
   const QWORD index=view.position-view.header.size(),byte=index/view.channels;
   if(byte>=view.bytesPerChannel)buffer[written]=0;
   else {
    const QWORD block=byte/4096;if(block!=view.cachedBlock){if(!readAt(view.handle,view.dataOffset+block*4096*view.channels,view.cache.data(),static_cast<DWORD>(view.cache.size())))return static_cast<DWORD>(-1);view.cachedBlock=block;}
    unsigned char value=view.cache[(index%view.channels)*4096+byte%4096];
    if(view.lsb){value=(value>>4)|(value<<4);value=((value&0xcc)>>2)|((value&0x33)<<2);value=((value&0xaa)>>1)|((value&0x55)<<1);}
    buffer[written]=value;
   }
  }
  written++;view.position++;
 }
 return written?written:static_cast<DWORD>(-1);
}
static void freeStream(HSTREAM handle){BASS_StreamFree(handle);dsfViews.erase(handle);}
static void CALLBACK growingClose(void* user) {
 auto& file=*static_cast<GrowingFile*>(user);std::lock_guard<std::mutex> lock(file.mutex);
 if(file.handle!=INVALID_HANDLE_VALUE){CloseHandle(file.handle);file.handle=INVALID_HANDLE_VALUE;}
}
static QWORD CALLBACK growingLength(void* user){return static_cast<GrowingFile*>(user)->length;}
static BOOL CALLBACK growingSeek(QWORD offset,void* user) {
 auto& file=*static_cast<GrowingFile*>(user);std::lock_guard<std::mutex> lock(file.mutex);
 if(offset>file.length||file.cancelled)return FALSE;file.position=offset;return TRUE;
}
static DWORD CALLBACK growingRead(void* buffer,DWORD count,void* user) {
 auto& file=*static_cast<GrowingFile*>(user);std::lock_guard<std::mutex> lock(file.mutex);
 // NOBUFFER: zero means temporarily unavailable, -1 means actual EOF.
 // Never wait inside this callback: metadata probes and the audio thread must finish.
 if(file.cancelled||file.position>=file.length)return static_cast<DWORD>(-1);
 LARGE_INTEGER size{};if(file.handle==INVALID_HANDLE_VALUE||!GetFileSizeEx(file.handle,&size)){file.failed=true;return static_cast<DWORD>(-1);}
 if(static_cast<QWORD>(size.QuadPart)<=file.position)return 0;
 const DWORD available=static_cast<DWORD>(std::min<QWORD>(count,std::min<QWORD>(size.QuadPart-file.position,file.length-file.position)));
 LARGE_INTEGER offset{};offset.QuadPart=file.position;DWORD read=0;
 if(!SetFilePointerEx(file.handle,offset,nullptr,FILE_BEGIN)||!ReadFile(file.handle,buffer,available,&read,nullptr)||!read){file.failed=true;return static_cast<DWORD>(-1);}
 file.position+=read;return read;
}

static std::wstring wide(const std::string& value) {
 if(value.find('\0')!=std::string::npos)throw std::runtime_error("Invalid path");
 const int size=MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,value.data(),static_cast<int>(value.size()),nullptr,0);
 if(!size)throw std::runtime_error("Invalid UTF-8");
 std::wstring result(size,L'\0');MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,value.data(),static_cast<int>(value.size()),result.data(),size);return result;
}
static std::string utf8(const wchar_t* value) {
 if(!value)return "";int n=WideCharToMultiByte(CP_UTF8,0,value,-1,nullptr,0,nullptr,nullptr);
 std::string result(n,'\0');WideCharToMultiByte(CP_UTF8,0,value,-1,result.data(),n,nullptr,nullptr);result.pop_back();return result;
}
static HMODULE library(const wchar_t* name) {
 const auto file=directory+L"\\"+name;
 HMODULE dll=LoadLibraryExW(file.c_str(),nullptr,LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR|LOAD_LIBRARY_SEARCH_SYSTEM32);
 if(!dll)throw std::runtime_error("Missing native audio library");return dll;
}
#define LOAD(dll,name) name=reinterpret_cast<decltype(name)>(GetProcAddress(dll,#name)); if(!name)throw std::runtime_error("Missing API: " #name)
static void initialize() {
 wchar_t file[32768];DWORD n=GetModuleFileNameW(nullptr,file,32768);if(!n||n>=32768)throw std::runtime_error("Executable path unavailable");
 directory=std::wstring(file,n);directory.resize(directory.find_last_of(L"\\/"));
 SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32|LOAD_LIBRARY_SEARCH_USER_DIRS);
 const auto bass=library(L"bass.dll"),asiodll=library(L"bassasio.dll"),dsd=library(L"bassdsd.dll");
 LOAD(bass,BASS_Init);LOAD(bass,BASS_Free);LOAD(bass,BASS_GetVersion);LOAD(bass,BASS_ErrorGetCode);LOAD(bass,BASS_SetConfig);
 LOAD(bass,BASS_PluginLoad);LOAD(bass,BASS_StreamCreateFile);LOAD(bass,BASS_StreamCreateFileUser);LOAD(bass,BASS_StreamFree);LOAD(bass,BASS_ChannelGetInfo);
 LOAD(bass,BASS_ChannelGetLength);LOAD(bass,BASS_ChannelGetPosition);LOAD(bass,BASS_ChannelSetPosition);LOAD(bass,BASS_ChannelBytes2Seconds);LOAD(bass,BASS_ChannelSeconds2Bytes);
 LOAD(bass,BASS_ChannelGetData);LOAD(bass,BASS_ChannelIsActive);LOAD(bass,BASS_ChannelGetAttribute);LOAD(bass,BASS_ChannelSetAttribute);
 LOAD(bass,BASS_GetDevice);LOAD(bass,BASS_SetDevice);LOAD(bass,BASS_ChannelPlay);LOAD(bass,BASS_ChannelPause);LOAD(bass,BASS_ChannelStop);
 LOAD(asiodll,BASS_ASIO_GetVersion);LOAD(asiodll,BASS_ASIO_SetUnicode);LOAD(asiodll,BASS_ASIO_GetDeviceInfo);LOAD(asiodll,BASS_ASIO_Init);LOAD(asiodll,BASS_ASIO_Free);
 LOAD(asiodll,BASS_ASIO_ErrorGetCode);LOAD(asiodll,BASS_ASIO_GetInfo);LOAD(asiodll,BASS_ASIO_CheckRate);LOAD(asiodll,BASS_ASIO_SetRate);LOAD(asiodll,BASS_ASIO_GetRate);
 LOAD(asiodll,BASS_ASIO_SetDSD);LOAD(asiodll,BASS_ASIO_ChannelGetInfo);LOAD(asiodll,BASS_ASIO_ChannelEnableBASS);LOAD(asiodll,BASS_ASIO_ChannelSetRate);LOAD(asiodll,BASS_ASIO_ChannelSetVolume);
 LOAD(asiodll,BASS_ASIO_Start);LOAD(asiodll,BASS_ASIO_Stop);LOAD(asiodll,BASS_ASIO_IsStarted);LOAD(asiodll,BASS_ASIO_GetLatency);LOAD(asiodll,BASS_ASIO_SetNotify);
 LOAD(asiodll,BASS_ASIO_ChannelEnable);LOAD(asiodll,BASS_ASIO_ChannelJoin);LOAD(asiodll,BASS_ASIO_ChannelSetFormat);
 LOAD(dsd,BASS_DSD_StreamCreateFile);LOAD(dsd,BASS_DSD_StreamCreateFileUser);
 if(HIWORD(BASS_GetVersion())!=0x204)throw std::runtime_error("Unexpected BASS version");
 if(!BASS_Init(0,44100,0,nullptr,nullptr))throw std::runtime_error("Decoder initialization failed");
 BASS_SetConfig(BASS_CONFIG_DSD_GAIN,0);BASS_ASIO_SetUnicode(TRUE);
 for(const wchar_t* name:{L"bassflac.dll",L"bassopus.dll"}) {
   const auto plugin=directory+L"\\"+name;
   if(!BASS_PluginLoad(reinterpret_cast<const char*>(plugin.c_str()),BASS_UNICODE))throw std::runtime_error("Decoder plugin unavailable");
 }
}
static void stop() {
 if(growing)growing->cancelled=true;
 if(asio){BASS_ASIO_Stop();BASS_ASIO_Free();asio=false;}
 if(stream){if(backend=="wasapi")BASS_ChannelStop(stream);freeStream(stream);stream=0;}
 if(growing){growingClose(growing.get());growing.reset();}
 paused=true;ended=false;pausedPosition=0;session.clear();mode="pcm";driverEvent=0;dsdReadFailed=false;endSince={};error.clear();
}
static void check(bool ok,const char* message,bool driver=false) {
 if(!ok)throw std::runtime_error(std::string(message)+" ("+std::to_string(driver?BASS_ASIO_ErrorGetCode():BASS_ErrorGetCode())+")");
}
static HSTREAM openFile(const json& request,const std::string& requested,bool systemOutput=false) {
 const std::wstring file=wide(request.at("file").get<std::string>());
 DWORD flags=BASS_UNICODE|(request.value("dsd",false)?0:BASS_ASYNCFILE)|(systemOutput?0:BASS_STREAM_DECODE);
 if(requested=="native")flags|=BASS_DSD_RAW;
 else {flags|=BASS_SAMPLE_FLOAT;if(requested=="dop")flags|=BASS_DSD_DOP;}
 if(request.value("accurate",false)&&!request.value("dsd",false))flags|=BASS_STREAM_PRESCAN;
 HSTREAM result;
 if(request.contains("growingBytes")) {
   if(requested!="pcm"||request.value("dsd",false)||growing)throw std::runtime_error("Invalid progressive PCM input");
   auto state=std::make_unique<GrowingFile>();state->length=request.at("growingBytes").get<QWORD>();
   if(state->length<56||state->length>2000000056ULL)throw std::runtime_error("Invalid progressive PCM length");
   state->handle=CreateFileW(file.c_str(),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
   if(state->handle==INVALID_HANDLE_VALUE)throw std::runtime_error("Sony progressive PCM is not available");
   growing=std::move(state);const BASS_FILEPROCS callbacks={growingClose,growingLength,growingRead,growingSeek};
   result=BASS_StreamCreateFileUser(STREAMFILE_NOBUFFER,flags&~BASS_UNICODE,&callbacks,growing.get());
 }else if(request.value("dsd",false)) {
   auto view=dsfView(file);
   if(view){const BASS_FILEPROCS callbacks={dsfClose,dsfLength,dsfRead,dsfSeek};result=BASS_DSD_StreamCreateFileUser(STREAMFILE_NOBUFFER,flags&~BASS_UNICODE,&callbacks,view.get(),44100);if(result)dsfViews.emplace(result,std::move(view));}
   else result=BASS_DSD_StreamCreateFile(BASS_FILE_NAME,file.c_str(),0,0,flags,44100);
 }
 else {
   if(requested!="pcm")throw std::runtime_error("DSD output requires a DSD file");
   result=BASS_StreamCreateFile(BASS_FILE_NAME,file.c_str(),0,0,flags);
 }
 check(result!=0,"File cannot be decoded; uncompressed DSF/DFF required for DSD direct output");return result;
}
static json devices() {
 json list=json::array();BASS_ASIO_DEVICEINFO info{};
 for(DWORD i=0;i<256 && BASS_ASIO_GetDeviceInfo(i,&info);i++)
   list.push_back({{"id",i},{"name",utf8(reinterpret_cast<const wchar_t*>(info.name))}});
 return {{"available",true},{"devices",list},{"bassVersion",BASS_GetVersion()},{"asioVersion",BASS_ASIO_GetVersion()}};
}
static void CALLBACK notify(DWORD event,void*){driverEvent.store(static_cast<int>(event));}
static DWORD CALLBACK dsdOutput(BOOL,DWORD,void* buffer,DWORD length,void* user) {
 const auto handle=static_cast<HSTREAM>(reinterpret_cast<uintptr_t>(user));
 DWORD read=BASS_ChannelGetData(handle,buffer,length);
 if(read==static_cast<DWORD>(-1)){if(BASS_ErrorGetCode()!=BASS_ERROR_ENDED)dsdReadFailed=true;read=0;}
 if(read>length){dsdReadFailed=true;read=0;}
 // Original interleaved MSB-first bits. A partial final hardware buffer uses
 // balanced DSD silence (0x69); zero bytes are not DSD silence.
 if(read<length)std::memset(static_cast<unsigned char*>(buffer)+read,0x69,length-read);
 return length;
}
static json capabilities(const json& request) {
 if(stream||asio)throw std::runtime_error("Stop playback before querying ASIO capabilities");
 const int device=request.at("device").get<int>();if(device<0||device>255)throw std::runtime_error("Invalid ASIO device");
 check(BASS_ASIO_Init(device,BASS_ASIO_THREAD),"ASIO driver unavailable",true);
 try {
   BASS_ASIO_INFO info{};check(BASS_ASIO_GetInfo(&info),"ASIO information unavailable",true);
   json pcm=json::array(),dsd=json::array(),channels=json::array();
   BASS_ASIO_SetDSD(FALSE);
   for(double rate:{44100.,48000.,88200.,96000.,176400.,192000.,352800.,384000.})if(BASS_ASIO_CheckRate(rate))pcm.push_back(rate);
   for(DWORD i=0;i<std::min<DWORD>(info.outputs,32);i++){BASS_ASIO_CHANNELINFO channel{};check(BASS_ASIO_ChannelGetInfo(FALSE,i,&channel),"ASIO channel information unavailable",true);channels.push_back({{"id",i},{"format",channel.format}});}
   const bool nativeDsd=BASS_ASIO_SetDSD(TRUE)!=FALSE;
   if(nativeDsd)for(double rate:{2822400.,5644800.,11289600.,22579200.})if(BASS_ASIO_CheckRate(rate))dsd.push_back(rate);
   BASS_ASIO_SetDSD(FALSE);BASS_ASIO_Free();
   return {{"device",device},{"outputs",info.outputs},{"pcmRates",pcm},{"nativeDsd",nativeDsd},{"dsdRates",dsd},{"channels",channels}};
 }catch(...){BASS_ASIO_SetDSD(FALSE);BASS_ASIO_Free();throw;}
}
static json status() {
 if(!stream)return {{"session",session},{"playing",false},{"paused",true},{"ended",ended},{"position",0},{"duration",0}};
 BASS_CHANNELINFO info{};check(BASS_ChannelGetInfo(stream,&info),"Stream information unavailable");
 const double duration=BASS_ChannelBytes2Seconds(stream,BASS_ChannelGetLength(stream,BASS_POS_BYTE));
 const auto bytes=BASS_ChannelGetPosition(stream,BASS_POS_BYTE);
 const double position=ended?duration:paused?pausedPosition:std::clamp(BASS_ChannelBytes2Seconds(stream,bytes),0.0,duration);
 if(driverEvent.exchange(0)) {error="ASIO device changed or requested reset; select the device again";BASS_ASIO_Stop();pausedPosition=position;paused=true;}
 if(growing&&growing->failed)error="Sony progressive PCM cache could not be read";
 if(dsdReadFailed)error="Native DSD source could not be read";
 if(!paused&&!ended&&BASS_ChannelIsActive(stream)==BASS_ACTIVE_STOPPED) {
   const auto now=Clock::now();if(endSince==Clock::time_point{})endSince=now;
   // Give the last hardware buffers time to drain before ending the transport.
   const double dataRate=mode=="native"?outputRate/8:outputRate;
   const double waitMs=asio?std::clamp(50+2000*BASS_ASIO_GetLatency(FALSE)/std::max(1.0,dataRate),50.0,1500.0):0;
   if(std::chrono::duration<double,std::milli>(now-endSince).count()>=waitMs){ended=true;paused=true;if(asio)BASS_ASIO_Stop();}
 }
 return {{"session",session},{"playing",!paused&&!ended},{"paused",paused},{"ended",ended},{"buffering",!paused&&BASS_ChannelIsActive(stream)==BASS_ACTIVE_STALLED},{"position",position},{"duration",duration},{"mode",mode},{"backend",backend},{"sampleRate",outputRate},{"channels",info.chans},{"volumeLocked",mode!="pcm"},{"error",error}};
}
static json open(const json& request) {
 stop();mode=request.value("mode",std::string("pcm"));
 backend=request.value("backend",std::string("asio"));if(backend!="asio"&&backend!="wasapi")throw std::runtime_error("Invalid native output backend");
 if(mode!="pcm"&&mode!="native"&&mode!="dop")throw std::runtime_error("Invalid output mode");
 try {
   if(backend=="wasapi") {
     if(mode!="pcm")throw std::runtime_error("DSD direct output requires ASIO; system output uses PCM");
     if(systemDevice<0){check(BASS_Init(-1,44100,0,nullptr,nullptr),"System audio device unavailable");systemDevice=static_cast<int>(BASS_GetDevice());}
     else check(BASS_SetDevice(systemDevice),"System audio device unavailable");
   }else check(BASS_SetDevice(0),"Decoder device unavailable");
   stream=openFile(request,mode,backend=="wasapi");
   BASS_CHANNELINFO info{};check(BASS_ChannelGetInfo(stream,&info),"Stream information unavailable");
   if(info.chans<1||info.chans>2)throw std::runtime_error("Native output currently supports mono/stereo");
   if(backend=="wasapi") {
     outputRate=info.freq;check(BASS_ChannelSetAttribute(stream,BASS_ATTRIB_VOL,request.value("volume",1.0f)),"System volume failed");
     const double position=request.value("position",0.0);if(!std::isfinite(position)||position<0)throw std::runtime_error("Invalid seek position");
     if(position>0)check(BASS_ChannelSetPosition(stream,BASS_ChannelSeconds2Bytes(stream,position),BASS_POS_BYTE),"Seek failed");
     session=request.at("session").get<std::string>();pausedPosition=position;paused=true;ended=false;return status();
   }
   const int device=request.at("device").get<int>();outputChannel=request.value("channel",0u);
   if(device<0||device>255||outputChannel>255)throw std::runtime_error("Invalid ASIO device/channel");
   check(BASS_ASIO_Init(device,BASS_ASIO_THREAD),"ASIO driver unavailable",true);asio=true;
   BASS_ASIO_INFO driver{};check(BASS_ASIO_GetInfo(&driver),"ASIO information unavailable",true);
   if(outputChannel+info.chans>driver.outputs)throw std::runtime_error("ASIO output channel pair unavailable");
   if(mode=="native") {
     check(BASS_ASIO_SetDSD(TRUE),"Device/driver does not support native DSD",true);
     float rate=0;check(BASS_ChannelGetAttribute(stream,BASS_ATTRIB_DSD_RATE,&rate),"DSD rate unavailable");outputRate=rate;
   } else {BASS_ASIO_SetDSD(FALSE);outputRate=info.freq;}
   if(mode=="dop")for(DWORD i=0;i<info.chans;i++) {
     BASS_ASIO_CHANNELINFO format{};check(BASS_ASIO_ChannelGetInfo(FALSE,outputChannel+i,&format),"Output format unavailable",true);
     if(format.format!=BASS_ASIO_FORMAT_24BIT&&format.format!=BASS_ASIO_FORMAT_32BIT&&format.format!=BASS_ASIO_FORMAT_32BIT24&&format.format!=BASS_ASIO_FORMAT_FLOAT)
       throw std::runtime_error("DoP requires an output with at least 24 bits; no conversion to 16-bit is allowed");
   }
   check(BASS_ASIO_CheckRate(outputRate),"Device does not support the exact output rate",true);
   check(BASS_ASIO_SetRate(outputRate),"Device could not set the exact output rate",true);
   if(std::abs(BASS_ASIO_GetRate()-outputRate)>.1)throw std::runtime_error("Device changed the requested rate; resampling is disabled");
   if(mode=="native") {
     // Explicit raw DSD format avoids the helper's rejected 8-bit setup on
     // vendor ASIO drivers. Stereo is joined before transferring source bits.
     check(BASS_ASIO_ChannelEnable(FALSE,outputChannel,dsdOutput,reinterpret_cast<void*>(static_cast<uintptr_t>(stream))),"Native DSD channel setup failed",true);
     for(DWORD i=1;i<info.chans;i++)check(BASS_ASIO_ChannelJoin(FALSE,outputChannel+i,outputChannel),"Native DSD stereo setup failed",true);
     check(BASS_ASIO_ChannelSetFormat(FALSE,outputChannel,BASS_ASIO_FORMAT_DSD_MSB),"Native DSD format unavailable",true);
   }else check(BASS_ASIO_ChannelEnableBASS(FALSE,outputChannel,stream,TRUE),"ASIO channel setup failed",true);
   if(mode!="native")check(BASS_ASIO_ChannelSetRate(FALSE,outputChannel,outputRate),"ASIO sample rate setup failed",true);
   check(BASS_ASIO_ChannelSetVolume(FALSE,-1,mode=="pcm"?request.value("volume",1.0f):1.0f),"ASIO volume setup failed",true);
   BASS_ASIO_SetNotify(notify,nullptr);driverEvent=0;
   const double position=request.value("position",0.0);
   if(!std::isfinite(position)||position<0)throw std::runtime_error("Invalid seek position");
   if(position>0)check(BASS_ChannelSetPosition(stream,BASS_ChannelSeconds2Bytes(stream,position),BASS_POS_BYTE),"Seek failed");
   session=request.at("session").get<std::string>();pausedPosition=position;paused=true;ended=false;error.clear();return status();
 }catch(...){stop();throw;}
}
static json inspect(const json& request) {
 if(stream)throw std::runtime_error("Stop output before inspection");
 const auto requested=request.value("mode",std::string("pcm"));
 HSTREAM handle=openFile(request,requested);
 try {
   BASS_CHANNELINFO info{};check(BASS_ChannelGetInfo(handle,&info),"Stream information unavailable");
   const double duration=BASS_ChannelBytes2Seconds(handle,BASS_ChannelGetLength(handle,BASS_POS_BYTE));
   const auto maximum=request.value("maxBytes",65536u);if(maximum>262144)throw std::runtime_error("Inspection exceeds limit");
   std::vector<unsigned char> buffer(maximum);DWORD n=0;auto waiting=Clock::now();
   while(n<maximum) {
     const DWORD size=BASS_ChannelGetData(handle,buffer.data()+n,maximum-n);
     if(size==static_cast<DWORD>(-1)){if(BASS_ErrorGetCode()==BASS_ERROR_ENDED)break;throw std::runtime_error("Decode inspection failed");}
     if(!size){if(BASS_ChannelIsActive(handle)==BASS_ACTIVE_STOPPED)break;if(Clock::now()-waiting>std::chrono::seconds(5))throw std::runtime_error("Decode inspection stalled");Sleep(1);continue;}
     n+=size;waiting=Clock::now();
   }
   std::string hex;hex.reserve(n*2);const char* digits="0123456789abcdef";
   for(DWORD i=0;i<n;i++){hex+=digits[buffer[i]>>4];hex+=digits[buffer[i]&15];}
   float dsdRate=0;if(request.value("dsd",false))BASS_ChannelGetAttribute(handle,BASS_ATTRIB_DSD_RATE,&dsdRate);
   freeStream(handle);return {{"dataHex",hex},{"bytes",n},{"sampleRate",info.freq},{"channels",info.chans},{"duration",duration},{"dsdRate",dsdRate}};
 }catch(...){freeStream(handle);throw;}
}
static json command(const json& value) {
 const auto cmd=value.at("cmd").get<std::string>();
 if(cmd=="devices")return devices();
 if(cmd=="capabilities")return capabilities(value);
 if(cmd=="inspect")return inspect(value);
 if(cmd=="open")return open(value);
 if(cmd=="shutdown"){stop();return {{"shutdown",true}};}
 if(!stream||value.value("session",std::string())!=session)throw std::runtime_error("Stale audio session");
 if(cmd=="status")return status();
 if(cmd=="stop"){stop();return status();}
 if(cmd=="play") {if(!error.empty())throw std::runtime_error(error);if(asio){if(!BASS_ASIO_IsStarted())check(BASS_ASIO_Start(0,1),"ASIO playback failed",true);}else check(BASS_ChannelPlay(stream,FALSE),"System playback failed");paused=false;ended=false;endSince={};}
 else if(cmd=="pause") {if(!paused)pausedPosition=BASS_ChannelBytes2Seconds(stream,BASS_ChannelGetPosition(stream,BASS_POS_BYTE));if(asio){if(BASS_ASIO_IsStarted())check(BASS_ASIO_Stop(),"ASIO pause failed",true);}else if(!paused)check(BASS_ChannelPause(stream),"System pause failed");paused=true;}
 else if(cmd=="seek") {
   const double target=value.at("position").get<double>();if(!std::isfinite(target)||target<0)throw std::runtime_error("Invalid seek position");
   const bool resume=!paused;if(asio&&BASS_ASIO_IsStarted()){check(BASS_ASIO_Stop(),"ASIO stop before seek failed",true);paused=true;}
   check(BASS_ChannelSetPosition(stream,BASS_ChannelSeconds2Bytes(stream,target),BASS_POS_BYTE),"Seek failed");pausedPosition=target;ended=false;endSince={};
   if(resume&&asio){check(BASS_ASIO_Start(0,1),"ASIO resume after seek failed",true);paused=false;}
 }
 else if(cmd=="volume") {
   if(mode!="pcm")throw std::runtime_error("DSD/DoP digital volume is locked; use the DAC volume");
   const float gain=value.at("volume").get<float>();if(!std::isfinite(gain)||gain<0||gain>1)throw std::runtime_error("Invalid volume");
   if(asio)check(BASS_ASIO_ChannelSetVolume(FALSE,-1,gain),"ASIO volume failed",true);else check(BASS_ChannelSetAttribute(stream,BASS_ATTRIB_VOL,gain),"System volume failed");
 }else throw std::runtime_error("Unknown command");
 return status();
}
static json decodeFile(const json& request,bool pipe=false) {
 auto accurateRequest=request;accurateRequest["accurate"]=true;
 const HSTREAM input=openFile(accurateRequest,"pcm");HANDLE output=INVALID_HANDLE_VALUE;
 try {
   BASS_CHANNELINFO info{};check(BASS_ChannelGetInfo(input,&info),"Stream information unavailable");
   const auto sourceBytes=BASS_ChannelGetLength(input,BASS_POS_BYTE);
   const double duration=BASS_ChannelBytes2Seconds(input,sourceBytes);
   if(info.chans<1||info.chans>2||!std::isfinite(duration)||duration<=0||duration>3600)throw std::runtime_error("Only mono/stereo tracks of at most one hour are supported");
   const double requestedPosition=request.value("position",0.0);
   if(!std::isfinite(requestedPosition)||requestedPosition<0||requestedPosition>duration+.01)throw std::runtime_error("Invalid decoder start position");
   if(requestedPosition>0)check(BASS_ChannelSetPosition(input,BASS_ChannelSeconds2Bytes(input,std::min(requestedPosition,std::max(0.0,duration-1.0/info.freq))),BASS_POS_BYTE),"Decoder seek failed");
   const auto sourcePosition=BASS_ChannelGetPosition(input,BASS_POS_BYTE);
   if(sourceBytes==static_cast<QWORD>(-1)||sourcePosition==static_cast<QWORD>(-1)||sourcePosition>=sourceBytes||(sourceBytes-sourcePosition)%(info.chans*4))throw std::runtime_error("Source PCM frame count is not available");
   const auto expectedFrames=(sourceBytes-sourcePosition)/(info.chans*4);
   const double positionOffset=BASS_ChannelBytes2Seconds(input,sourcePosition);
   if(pipe) {
     output=GetStdHandle(STD_OUTPUT_HANDLE);
     if(output==INVALID_HANDLE_VALUE||!output)throw std::runtime_error("Decoder pipe is not available");
     std::cout<<json({{"ready",true},{"sampleRate",info.freq},{"channels",2},{"sourceChannels",info.chans},{"frames",expectedFrames},{"duration",static_cast<double>(expectedFrames)/info.freq},{"positionOffset",positionOffset}}).dump()<<std::endl;
   } else {
     const auto destination=wide(request.at("output").get<std::string>());
     output=CreateFileW(destination.c_str(),GENERIC_WRITE,0,nullptr,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);
     if(output==INVALID_HANDLE_VALUE)throw std::runtime_error("Decoder output must not already exist");
   }
   std::vector<float> data(32768),stereo(65536);uint64_t bytes=0;auto waiting=Clock::now();
   while(true) {
     if(bytes/8==expectedFrames)break;
     const DWORD size=BASS_ChannelGetData(input,data.data(),static_cast<DWORD>(data.size()*4));
     if(size==static_cast<DWORD>(-1)){if(BASS_ErrorGetCode()==BASS_ERROR_ENDED)break;throw std::runtime_error("Source decoding failed");}
     if(!size){if(BASS_ChannelIsActive(input)==BASS_ACTIVE_STOPPED)break;if(Clock::now()-waiting>std::chrono::seconds(5))throw std::runtime_error("Source decoding stalled");Sleep(1);continue;}
     waiting=Clock::now();if(size%(info.chans*4))throw std::runtime_error("Incomplete decoded frame");
     // Some Media Foundation AAC decoders return the final codec frame's
     // padding beyond the container duration. Keep the declared PCM timeline,
     // including accurate MPEG prescan, for both pipe and file decoding.
     const DWORD frames=static_cast<DWORD>(std::min<uint64_t>(size/(info.chans*4),expectedFrames-bytes/8));
     const void* content=data.data();DWORD count=frames*info.chans*4;
     if(info.chans==1){for(DWORD i=0;i<frames;i++){stereo[i*2]=data[i];stereo[i*2+1]=data[i];}content=stereo.data();count=frames*8;}
     bytes+=count;if(bytes>2000000000)throw std::runtime_error("Decoded PCM exceeded 2 GB");
     DWORD offset=0;auto outputWaiting=Clock::now();
     while(offset<count){
       DWORD written=0;
       if(!WriteFile(output,static_cast<const char*>(content)+offset,std::min<DWORD>(count-offset,32768),&written,nullptr))throw std::runtime_error("Decoder output write failed (Windows "+std::to_string(GetLastError())+")");
       // Inherited Windows byte pipes can be nonblocking. Successful zero-byte
       // writes mean backpressure, not decode failure; preserve every PCM byte.
       if(!written){if(!pipe||Clock::now()-outputWaiting>std::chrono::seconds(5))throw std::runtime_error("Decoder output did not accept data");Sleep(1);continue;}
       offset+=written;outputWaiting=Clock::now();
     }
   }
   if(bytes/8!=expectedFrames)throw std::runtime_error("Source decoded frame count changed");
   if(!pipe)CloseHandle(output);output=INVALID_HANDLE_VALUE;freeStream(input);
   return {{"ready",true},{"sampleRate",info.freq},{"channels",2},{"frames",bytes/8},{"duration",static_cast<double>(bytes/8)/info.freq},{"positionOffset",positionOffset}};
 }catch(...){if(output!=INVALID_HANDLE_VALUE&&!pipe)CloseHandle(output);freeStream(input);throw;}
}
int main(int argc,char** argv) {
 try {initialize();}catch(const std::exception& e){std::cout<<json({{"fatal",e.what()}}).dump()<<std::endl;return 1;}
 std::string line;
 if(argc==2&&(std::string(argv[1])=="--file-info-json"||std::string(argv[1])=="--decode-json"||std::string(argv[1])=="--decode-stream-json")) {
   try {
     if(!std::getline(std::cin,line)||line.size()>65536)throw std::runtime_error("Invalid decoder request");
     auto request=json::parse(line);json result;
     if(std::string(argv[1])=="--decode-stream-json"){request["accurate"]=true;decodeFile(request,true);BASS_Free();return 0;}
     if(std::string(argv[1])=="--decode-json")result=decodeFile(request);
     else {request["mode"]="pcm";request["maxBytes"]=0;result=inspect(request);}
     std::cout<<result.dump()<<std::endl;BASS_Free();return 0;
   }catch(const std::exception& e){(std::string(argv[1])=="--decode-stream-json"?std::cerr:std::cout)<<json({{"error",e.what()}}).dump()<<std::endl;BASS_Free();return 1;}
 }
 while(std::getline(std::cin,line)) {
   json request;json response;
   try {if(line.size()>65536)throw std::runtime_error("Command exceeds limit");request=json::parse(line);response=command(request);response["ok"]=true;}
   catch(const std::exception& e){response={{"ok",false},{"error",e.what()}};}
   response["id"]=request.is_object()&&request.contains("id")&&request["id"].is_number_integer()?request["id"]:json(0);std::cout<<response.dump()<<std::endl;
   if(response.value("shutdown",false))break;
 }
 stop();BASS_Free();return 0;
}
