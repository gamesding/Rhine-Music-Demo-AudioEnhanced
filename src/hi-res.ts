import type { MusicAlbum, MusicTrack } from "./music-types";

/** Original file metadata, never the sample rate produced by a DSP or output device.
 * JAS / JEITA: https://www.jas-audio.or.jp/hi-res/definition
 * Sony's source definition also includes DSD. Unknown / lossy files stay unmarked.
 */
type SourceFormat = Pick<MusicTrack, "format" | "codec" | "sampleRate" | "bitsPerSample" | "lossless">;

/** Require parsed DSD metadata; a filename or a selected output mode is not evidence. */
export function isDsdTrack(track: SourceFormat): boolean {
  return track.lossless === true && Number.isFinite(track.sampleRate) &&
    (track.sampleRate ?? 0) >= 2_822_400 &&
    (/^(DSF|DFF|DSD)$/i.test(track.format) || /^DSD(?:\b|\d)/i.test(track.codec ?? ""));
}

export function isDsdAlbum(album?: Pick<MusicAlbum, "tracks">): boolean {
  return !!album?.tracks.length && album.tracks.every(isDsdTrack);
}

export function isHiResTrack(track: SourceFormat): boolean {
  const rate = track.sampleRate, bits = track.bitsPerSample;
  if (track.lossless !== true || !Number.isFinite(rate) || !rate || rate <= 0) return false;
  if (/^(DSF|DFF|DSD)$/i.test(track.format) || /^DSD(?:\b|\d)/i.test(track.codec ?? ""))
    return isDsdTrack(track);
  return Number.isFinite(bits) && !!bits && rate >= 44_100 && bits >= 16 &&
    (rate > 48_000 || bits > 16);
}

export function isHiResAlbum(album?: Pick<MusicAlbum, "tracks">): boolean {
  return !!album?.tracks.length && album.tracks.every(isHiResTrack);
}

export function hiResBadgeMarkup(size: "album" | "track", id = "", hidden = false): string {
  return `<span class="hi-res-badge hi-res-${size}"${id ? ` id="${id}"` : ""}${hidden ? " hidden" : ""} role="img" aria-label="${size === "album" ? "全专辑 Hi-Res Audio" : "Hi-Res Audio 音源"}" title="${size === "album" ? "整张专辑均为 Hi-Res 音源" : "Hi-Res 音源"}"><img src="${import.meta.env.BASE_URL}audio-tech/hi-res.svg" alt="" draggable="false" decoding="async"><i class="hi-res-luster" aria-hidden="true"></i><i class="hi-res-halo" aria-hidden="true"></i></span>`;
}

export function dsdBadgeMarkup(size: "album" | "track", id = "", hidden = false): string {
  const label = size === "album" ? "整张专辑均为 DSD 音源" : "DSD 音源";
  return `<span class="dsd-badge dsd-${size}"${id ? ` id="${id}"` : ""}${hidden ? " hidden" : ""} role="img" aria-label="${label}" title="${label}"><i class="dsd-symbol" aria-hidden="true"></i></span>`;
}
