import type { MusicPlayerState } from "./music-player";

export const sonyTechMarkup = `<div class="sony-tech-indicators" id="sony-tech-indicators" aria-label="当前 Sony 音效" data-count="0">
  <span class="sony-tech-badge" data-tech="dsee" hidden><i class="sony-tech-symbol sony-tech-dsee" aria-hidden="true"></i><span class="sony-tech-caption">DSEE AI</span></span>
  <span class="sony-tech-badge" data-tech="dc" hidden><i class="sony-tech-symbol sony-tech-phase" aria-hidden="true"></i><span class="sony-tech-caption">DC PHASE</span></span>
  <span class="sony-tech-badge" data-tech="vinyl" hidden><i class="sony-tech-symbol sony-tech-vinyl" aria-hidden="true"></i><span class="sony-tech-caption">VINYL</span></span>
</div>`;

export function updateSonyTechIndicators(host: HTMLElement | null, state: MusicPlayerState, albumId?: string): void {
  if (!host) return;
  const active = state.sonyProcessing.state === "active" && state.currentTrack?.albumId === albumId &&
    (state.playing || state.transport === "paused");
  const effects=state.sonyProcessing.effectiveSettings??state.sonySettings;
  const enabled = { dsee: active && effects.dsee, dc: active && effects.dc !== 0,
    vinyl: active && effects.vinyl !== 0 };
  let count = 0;
  for (const [name, show] of Object.entries(enabled)) {
    const badge = host.querySelector<HTMLElement>(`[data-tech="${name}"]`);
    if (badge) badge.hidden = !show;
    if (show) count++;
  }
  host.dataset.count = String(count);
  host.dataset.playing = String(state.playing && !state.loading);
}
