export interface SonySettings { dsee: boolean; dc: number; vinyl: number }
export interface SonyExecution { streaming: boolean; parallel: boolean; dsdToPcm?: boolean; startPosition?: number }
export interface SonyProcessing {
  state: "off" | "preparing" | "active" | "error";
  progress: number;
  sampleRate?: number;
  streaming?: boolean;
  workers?: number;
  bufferedSeconds?: number;
  positionOffset?: number;
  message?: string;
  effectiveSettings?: SonySettings;
  bypassed?: string[];
}
export interface SonyStatus { available: boolean; original: boolean; backend?: 'x86-cpp'|'arm-original'; dseeVersion?: string; workers?: number; phaseStereoIsolation?: boolean; error?: string }
export const sonyOff: SonySettings = { dsee: false, dc: 0, vinyl: 0 };
export function normalizeSony(value?: Partial<SonySettings> | null): SonySettings {
  return {
    dsee: value?.dsee === true,
    dc: Number.isInteger(value?.dc) && value!.dc! >= 0 && value!.dc! <= 6 ? value!.dc! : 0,
    vinyl: Number.isInteger(value?.vinyl) && value!.vinyl! >= 0 && value!.vinyl! <= 4 ? value!.vinyl! : 0,
  };
}
export const sonyEnabled = (value: SonySettings) => value.dsee || value.dc !== 0 || value.vinyl !== 0;

interface Job {
  id?: string; state: "queued" | "processing" | "ready" | "error";
  progress: number; sampleRate?: number; audioUrl?: string; error?: string; playable?: boolean; workers?: number; bufferedSeconds?: number; positionOffset?: number;
  effectiveSettings?: SonySettings; bypassed?: string[]; bypassedAll?: boolean; message?: string;
}
async function json(url: string, signal: AbortSignal, body?: unknown): Promise<Job> {
  const response = await fetch(url, { signal, ...(body === undefined ? {} : {
    method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(body),
  }) });
  const value = await response.json();
  if (!response.ok) throw new Error(value.error || "Sony 原版处理请求失败。");
  return value;
}
function delay(signal: AbortSignal, milliseconds=100): Promise<void> {
  return new Promise((resolve, reject) => {
    if (signal.aborted) return reject(new DOMException("Cancelled", "AbortError"));
    const aborted = () => { clearTimeout(timer); reject(new DOMException("Cancelled", "AbortError")); };
    const timer = setTimeout(() => { signal.removeEventListener("abort", aborted); resolve(); }, milliseconds);
    signal.addEventListener("abort", aborted, { once: true });
  });
}
export async function prepareSonyAudio(trackId: string, settings: SonySettings, signal: AbortSignal,
  update: (state: SonyProcessing) => void, execution: SonyExecution = { streaming: true, parallel: true }): Promise<string> {
  update({ state: "preparing", progress: 0 });
  let pendingId: string | undefined;
  const cancelled = () => {
    if (pendingId) void fetch(`/api/sony/jobs/${pendingId}/cancel`,{ method: "POST", headers: { "Content-Type": "application/json" }, body: "{}" }).catch(() => {});
  };
  signal.addEventListener("abort",cancelled,{ once:true });
  try {
  let job = await json("/api/sony/prepare", signal, { trackId, settings, ...execution });
  if (job.id && /^[a-f0-9]{64}$/.test(job.id)) pendingId = job.id;
  if (signal.aborted) { cancelled(); throw new DOMException("Cancelled","AbortError"); }
  if(job.state==='ready'&&job.bypassedAll&&job.audioUrl&&/^\/api\/(?:ftp\/)?audio\/[a-zA-Z0-9-]+$/.test(job.audioUrl)) {
    update({state:'off',progress:1,effectiveSettings:job.effectiveSettings,bypassed:job.bypassed,message:job.message,sampleRate:job.sampleRate,positionOffset:0});
    return job.audioUrl;
  }
  while ((job.state === "queued" || job.state === "processing") && !(execution.streaming && job.playable)) {
    if (!job.id || !/^[a-f0-9]{64}$/.test(job.id)) throw new Error("Sony 处理任务无效。");
    update({ state: "preparing", progress: Math.max(0, Math.min(.99, Number(job.progress) || 0)),bufferedSeconds:job.bufferedSeconds,positionOffset:job.positionOffset });
    await delay(signal);
    job = await json(`/api/sony/jobs/${job.id}`, signal);
  }
  if ((job.state !== "ready" && !(job.state === "processing" && job.playable && execution.streaming)) ||
      !job.audioUrl || !/^\/api\/sony\/audio\/[a-f0-9]{64}$/.test(job.audioUrl))
    throw new Error(job.error || "Sony 原版处理未完成。");
  const active = (value: Job) => update({ state: "active", progress: value.state === "ready" ? 1 : value.progress,
    sampleRate: value.sampleRate, streaming: value.state !== "ready", workers: value.workers,bufferedSeconds:value.bufferedSeconds,positionOffset:value.positionOffset,
    effectiveSettings:value.effectiveSettings,bypassed:value.bypassed,message:value.message });
  active(job);
  if (job.state !== "ready") {
    // Continue checking the actual worker after playback starts. A processing failure
    // must reach the transport instead of silently playing a truncated file.
    const id = job.id;
    if (!id || !/^[a-f0-9]{64}$/.test(id)) throw new Error("Sony 处理任务无效。");
    void (async () => {
      while (job.state === "processing") {
        await delay(signal,250);
        job = await json(`/api/sony/jobs/${id}`, signal);
        if (job.state === "error") throw new Error(job.error || "Sony 原版处理失败。");
        if (job.state !== "processing" && job.state !== "ready") throw new Error("Sony 处理任务状态无效。");
        active(job);
      }
    })().catch((error: Error) => {
      if (!signal.aborted) update({ state: "error", progress: 0, message: error.message });
    });
  }
  pendingId = undefined;
  return job.audioUrl;
  } finally { signal.removeEventListener("abort",cancelled); }
}
