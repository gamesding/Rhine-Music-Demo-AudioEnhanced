// Deterministic synthetic fixtures, never user music. DSF: Sony v1.01;
// DSDIFF: Philips v1.5. The canonical comparison bytes are interleaved MSB-first.
export function dsdFixture(rate=2822400,bytesPerChannel=8192) {
  const raw=Buffer.alloc(bytesPerChannel*2);
  for(let i=0;i<bytesPerChannel;i++){raw[i*2]=(i*37+13)&255;raw[i*2+1]=(i*71+97)&255}
  const reverse=value=>{let result=0;for(let bit=0;bit<8;bit++)result=(result<<1)|((value>>bit)&1);return result};
  const blocks=Math.ceil(bytesPerChannel/4096),data=Buffer.alloc(blocks*8192);
  for(let i=0;i<bytesPerChannel;i++)for(let ch=0;ch<2;ch++)data[Math.floor(i/4096)*8192+ch*4096+i%4096]=reverse(raw[i*2+ch]);
  const dsf=Buffer.alloc(92);dsf.write('DSD ');dsf.writeBigUInt64LE(28n,4);dsf.writeBigUInt64LE(BigInt(92+data.length),12);
  dsf.write('fmt ',28);dsf.writeBigUInt64LE(52n,32);dsf.writeUInt32LE(1,40);dsf.writeUInt32LE(2,48);dsf.writeUInt32LE(2,52);
  dsf.writeUInt32LE(rate,56);dsf.writeUInt32LE(1,60);dsf.writeBigUInt64LE(BigInt(bytesPerChannel*8),64);dsf.writeUInt32LE(4096,72);
  dsf.write('data',80);dsf.writeBigUInt64LE(BigInt(data.length+12),84);
  const chunk=(id,content)=>{const header=Buffer.alloc(12);header.write(id);header.writeBigUInt64BE(BigInt(content.length),4);return Buffer.concat([header,content,...(content.length%2?[Buffer.alloc(1)]:[])])};
  const frequency=Buffer.alloc(4);frequency.writeUInt32BE(rate);
  const channels=Buffer.alloc(10);channels.writeUInt16BE(2);channels.write('SLFTSRGT',2);
  const compression=Buffer.concat([Buffer.from('DSD '),Buffer.from([14]),Buffer.from('not compressed')]);
  const version=Buffer.from([1,5,0,0]);
  const property=Buffer.concat([Buffer.from('SND '),chunk('FS  ',frequency),chunk('CHNL',channels),chunk('CMPR',compression)]);
  const form=Buffer.concat([Buffer.from('DSD '),chunk('FVER',version),chunk('PROP',property),chunk('DSD ',raw)]);
  return {raw,dsf:Buffer.concat([dsf,data]),dff:chunk('FRM8',form),rate,frames:bytesPerChannel/8,duration:bytesPerChannel*8/rate};
}
export function silentWav(seconds=2,rate=44100,bits=16) {
  if(![16,24,32].includes(bits))throw new Error('Unsupported fixture PCM bit depth');
  const alignment=2*bits/8,data=Buffer.alloc(Math.round(seconds*rate)*alignment),header=Buffer.alloc(44);
  header.write('RIFF');header.writeUInt32LE(36+data.length,4);header.write('WAVEfmt ',8);header.writeUInt32LE(16,16);
  header.writeUInt16LE(1,20);header.writeUInt16LE(2,22);header.writeUInt32LE(rate,24);header.writeUInt32LE(rate*alignment,28);
  header.writeUInt16LE(alignment,32);header.writeUInt16LE(bits,34);header.write('data',36);header.writeUInt32LE(data.length,40);
  return Buffer.concat([header,data]);
}

// A real trailing ID3v2 tag, referenced by the DSF metadata pointer. These
// fixtures exercise both UTF-16 ID3v2.3 and UTF-8 ID3v2.4 without touching DSD.
export function taggedDsf(dsf,{version=4,picture=Buffer.from('iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mP8/x8AAwMCAO+a1ioAAAAASUVORK5CYII=','base64'),title='星河之声',artist='测试歌手',album='原生 DSD 专辑',albumArtist='测试乐团'}={}) {
  if(![3,4].includes(version))throw new Error('Unsupported fixture ID3 version');
  const synchsafe=value=>Buffer.from([(value>>>21)&127,(value>>>14)&127,(value>>>7)&127,value&127]);
  const frame=(id,data)=>{const header=Buffer.alloc(10);header.write(id);if(version===4)synchsafe(data.length).copy(header,4);else header.writeUInt32BE(data.length,4);return Buffer.concat([header,data])};
  const text=value=>version===4?Buffer.concat([Buffer.from([3]),Buffer.from(value,'utf8')]):Buffer.concat([Buffer.from([1,255,254]),Buffer.from(value,'utf16le')]);
  const frames=Buffer.concat([
    ...Object.entries({TIT2:title,TPE1:artist,TALB:album,TPE2:albumArtist,TRCK:'3/8',TPOS:'1/1',TCON:'Jazz'}).map(([id,value])=>frame(id,text(value))),
    frame('APIC',Buffer.concat([Buffer.from([0]),Buffer.from('image/png\0'),Buffer.from([3,0]),picture])),
  ]);
  const tag=Buffer.concat([Buffer.from([73,68,51,version,0,0]),synchsafe(frames.length),frames]);
  const result=Buffer.concat([dsf,tag]);result.writeBigUInt64LE(BigInt(result.length),12);result.writeBigUInt64LE(BigInt(dsf.length),20);
  return result;
}
