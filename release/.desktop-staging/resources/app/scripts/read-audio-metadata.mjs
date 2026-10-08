import {promises as fs} from 'node:fs';
import path from 'node:path';
import {parseFile,parseBuffer} from 'music-metadata';

export const AUDIO_METADATA_VERSION = 4;

/** ALACSpecificConfig is authoritative: the legacy MP4 audio sample entry has
 * only a 16.16 sample-rate field and may report 16 bits / 1 Hz for 24/192 ALAC.
 * Read the bounded atom tree, never scan or allocate the mdat sound payload.
 * https://github.com/macosforge/alac/blob/master/ALACMagicCookieDescription.txt
 */
export async function readAlacFormat(filename) {
  const file=await fs.open(filename,'r');
  try {
    const {size}=await file.stat();let atoms=0;
    const read=async(position,length)=>{
      if(!Number.isSafeInteger(position)||position<0||length<0||position+length>size)throw new Error('Invalid MP4 atom bounds');
      const bytes=Buffer.alloc(length);let offset=0;
      while(offset<length){const {bytesRead}=await file.read(bytes,offset,length-offset,position+offset);if(!bytesRead)throw new Error('Truncated MP4 atom');offset+=bytesRead}
      return bytes;
    };
    const atom=async(position,end)=>{
      if(++atoms>20000||position+8>end)throw new Error('Invalid MP4 atom list');
      const header=await read(position,8),type=header.toString('ascii',4,8);let length=header.readUInt32BE(),headerSize=8;
      if(length===1){if(position+16>end)throw new Error('Truncated MP4 extended atom');const wide=(await read(position+8,8)).readBigUInt64BE();if(wide>BigInt(Number.MAX_SAFE_INTEGER))throw new Error('MP4 atom too large');length=Number(wide);headerSize=16}
      if(length===0)length=end-position;
      if(length<headerSize||!Number.isSafeInteger(position+length)||position+length>end)throw new Error('MP4 atom exceeds its parent');
      return {type,data:position+headerSize,end:position+length};
    };
    const walk=async(start,end,depth=0)=>{
      if(depth>6)throw new Error('MP4 nesting limit exceeded');
      for(let position=start;position<end;){
        const box=await atom(position,end);position=box.end;
        if(['moov','trak','mdia','minf','stbl'].includes(box.type)){
          const result=await walk(box.data,box.end,depth+1);if(result)return result;
        }else if(box.type==='stsd'){
          if(box.data+8>box.end)throw new Error('Truncated MP4 sample descriptions');
          const count=(await read(box.data,8)).readUInt32BE(4);if(count>256)throw new Error('Too many MP4 sample descriptions');
          let offset=box.data+8;
          for(let i=0;i<count;i++){
            const entry=await atom(offset,box.end);offset=entry.end;if(entry.type!=='alac')continue;
            if(entry.data+28>entry.end)throw new Error('Truncated ALAC audio sample entry');
            const version=(await read(entry.data+8,2)).readUInt16BE(),extra=version===0?0:version===1?16:version===2?36:undefined;
            if(extra===undefined)throw new Error('Unsupported ALAC audio sample entry version');
            for(let child=entry.data+28+extra;child<entry.end;){
              const config=await atom(child,entry.end);child=config.end;if(config.type!=='alac')continue;
              if(config.end-config.data!==28)throw new Error('Invalid ALACSpecificConfig length');
              const bytes=await read(config.data,28),bitsPerSample=bytes[9],numberOfChannels=bytes[13],sampleRate=bytes.readUInt32BE(24);
              if(bytes.readUInt32BE(0)!==0||bytes[8]!==0||![16,20,24,32].includes(bitsPerSample)||numberOfChannels<1||numberOfChannels>8||sampleRate<8000||sampleRate>768000)throw new Error('Invalid ALACSpecificConfig values');
              return {sampleRate,bitsPerSample,numberOfChannels,lossless:true};
            }
          }
        }
      }
    };
    return await walk(0,size);
  }finally{await file.close()}
}

/** DSDIFF 1.5 chunk sizes exclude the even-alignment pad byte.
 * https://www.sonicstudio.com/pdf/dsd/DSDIFF_1.5_Spec.pdf
 * Only headers / tags are read; sound data is skipped by offset.
 */
export async function readDffMetadata(filename,options={}) {
  const file=await fs.open(filename,'r');
  try {
    const stat=await file.stat(),format={container:'DSDIFF/DSD'},common={};
    const read=async(position,size)=>{
      if(!Number.isSafeInteger(position)||position<0||position+size>stat.size)throw new Error('Invalid DFF chunk bounds');
      const bytes=Buffer.alloc(size);let offset=0;
      while(offset<size){const {bytesRead}=await file.read(bytes,offset,size-offset,position+offset);if(!bytesRead)throw new Error('Truncated DFF header');offset+=bytesRead}
      return bytes;
    };
    const header=await read(0,16),size=header.readBigUInt64BE(4),end=12+Number(size);
    if(header.toString('ascii',0,4)!=='FRM8'||header.toString('ascii',12,16)!=='DSD '||size>BigInt(Number.MAX_SAFE_INTEGER)||end>stat.size||end<16)throw new Error('Invalid DFF form');
    let chunks=0,soundBytes,compression;
    const walk=async(start,limit,property=false)=>{
      for(let offset=start;offset<limit;){
        if(++chunks>10000||offset+12>limit)throw new Error('Invalid DFF chunk list');
        const chunk=await read(offset,12),id=chunk.toString('ascii',0,4),wide=chunk.readBigUInt64BE(4);
        if(!/^[\x20-\x7e]{4}$/.test(id)||wide>BigInt(Number.MAX_SAFE_INTEGER))throw new Error('Invalid DFF chunk header');
        const length=Number(wide),data=offset+12,next=data+length+length%2;
        if(!Number.isSafeInteger(next)||next>limit)throw new Error('DFF chunk exceeds its parent');
        if(!property&&id==='PROP'){
          if(length<4||(await read(data,4)).toString('ascii')!=='SND ')throw new Error('Invalid DFF sound properties');
          await walk(data+4,data+length,true);
        }else if(property&&id==='FS  '){
          if(length!==4)throw new Error('Invalid DFF sample rate');format.sampleRate=(await read(data,4)).readUInt32BE();
        }else if(property&&id==='CHNL'){
          if(length<2)throw new Error('Invalid DFF channels');const channels=(await read(data,2)).readUInt16BE();
          if(!channels||channels>32||length!==2+channels*4)throw new Error('Invalid DFF channel list');format.numberOfChannels=channels;
        }else if(property&&id==='CMPR'){
          if(length<5||length>260)throw new Error('Invalid DFF compression');const value=await read(data,length);
          if(value[4]>length-5)throw new Error('Invalid DFF compression name');compression=value.toString('ascii',0,4).trim();
          format.codec=`${compression} (${value.toString('ascii',5,5+value[4])})`;
        }else if(!property&&id==='DSD ')soundBytes=length;
        else if(!property&&id==='ID3 '&&length<=30*1024*1024){
          try {Object.assign(common,(await parseBuffer(await read(data,length),{mimeType:'audio/mpeg'},options)).common)}catch{}
        }
        offset=next;
      }
    };
    await walk(16,end);
    if(!format.sampleRate||!format.numberOfChannels||compression!=='DSD'||!Number.isSafeInteger(soundBytes)||soundBytes<=0||soundBytes%format.numberOfChannels)throw new Error('Incomplete or unsupported DFF sound properties');
    Object.assign(format,{lossless:true,bitsPerSample:1,numberOfSamples:soundBytes*8/format.numberOfChannels,
      duration:soundBytes*8/format.numberOfChannels/format.sampleRate,bitrate:format.sampleRate*format.numberOfChannels});
    return {common,format,native:{},quality:{warnings:[]}};
  }finally{await file.close()}
}

export async function readAudioMetadata(filename,options={}) {
  let metadata;
  try {metadata=await parseFile(filename,options)}
  catch(error){if(path.extname(filename).toLowerCase()!=='.dff')throw error;return readDffMetadata(filename,options)}
  if(metadata.format.codec==='ALAC'&&['.m4a','.mp4','.m4b'].includes(path.extname(filename).toLowerCase())) {
    const format=await readAlacFormat(filename);
    if(format){Object.assign(metadata.format,format);const track=metadata.format.trackInfo?.find(item=>item.codecName==='ALAC');if(track?.audio)Object.assign(track.audio,{samplingFrequency:format.sampleRate,bitDepth:format.bitsPerSample,channels:format.numberOfChannels})}
  }
  return metadata;
}
