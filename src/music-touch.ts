/** Ruler drag supplements the small visual ticks without changing their spacing. */
export function setupTouchRuler(host: HTMLElement, navigate: (steps: number) => void) {
  let pointer: number | null = null, startX = 0, startY = 0, suppressUntil = 0;
  host.addEventListener("pointerdown", (event) => {
    if (event.pointerType === "mouse") return;
    if (pointer !== null) { pointer = null; return; }
    pointer = event.pointerId; startX = event.clientX; startY = event.clientY;
    host.setPointerCapture(event.pointerId);
  });
  host.addEventListener("pointerup", (event) => {
    if (pointer !== event.pointerId) return;
    pointer = null;
    const dx = event.clientX-startX, dy = event.clientY-startY;
    if (Math.hypot(dx,dy) < 14) {
      const nearest = [...host.querySelectorAll<HTMLButtonElement>("button:not(:disabled)")].sort((a,b) => {
        const distance = (button: HTMLButtonElement) => { const r = button.getBoundingClientRect(); return Math.abs(event.clientX-(r.left+r.width/2)); };
        return distance(a)-distance(b);
      })[0];
      nearest?.click();
      suppressUntil = performance.now()+500;
      return;
    }
    if (Math.abs(dx) < 22 || Math.abs(dx) < Math.abs(dy)*1.3) return;
    suppressUntil = performance.now()+500;
    navigate(Math.max(-4,Math.min(4,Math.round(-dx/44)) || -Math.sign(dx)));
  });
  for (const type of ["pointercancel","lostpointercapture"] as const) host.addEventListener(type, () => { pointer = null; });
  host.addEventListener("click", (event) => {
    if (event.detail !== 0 && performance.now() < suppressUntil) { event.preventDefault(); event.stopPropagation(); }
  }, { capture: true });
}
