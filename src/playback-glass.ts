import { Vector2, Vector4 } from "three";
import { OutputPass } from "three/addons/postprocessing/OutputPass.js";

// Original optical implementation. Extends Three.js' MIT OutputPass, retaining
// its tone mapping/color conversion. No Shadertoy or Apple shader code is copied.
const optics = /* glsl */ `
uniform vec4 playbackRect;
uniform vec2 playbackViewport;
uniform vec2 playbackPointer;
uniform float playbackRadius;
uniform float playbackReveal;
uniform float playbackNight;
uniform float playbackTime;
uniform float playbackTouch;

vec3 playbackSample(vec2 uv) {
  return texture2D(tDiffuse, clamp(uv, vec2(0.001), vec2(0.999))).rgb;
}

vec4 playbackLens(vec2 uv) {
  vec4 original = texture2D(tDiffuse, uv);
  if (playbackReveal <= 0.0) return original;
  vec2 local = uv * playbackViewport - playbackRect.xy;
  // Heavy sampling is restricted to the small capsule; the remaining frame
  // retains the original single sample in the existing final output pass.
  if (any(lessThan(local, vec2(-2.0))) || any(greaterThan(local, playbackRect.zw + 2.0))) return original;
  vec2 halfSize = playbackRect.zw * 0.5;
  float radius = min(playbackRadius, min(halfSize.x, halfSize.y));
  vec2 p = local - halfSize;
  vec2 q = abs(p) - halfSize + radius;
  float sdf = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - radius;
  float mask = 1.0 - smoothstep(-0.6, 0.8, sdf);
  if (mask <= 0.0) return original;

  vec2 corner = max(q, vec2(0.0));
  vec2 normal = length(corner) > 0.001 ? normalize(corner) * sign(p)
    : (q.x > q.y ? vec2(sign(p.x), 0.0) : vec2(0.0, sign(p.y)));
  float edge = 1.0 - smoothstep(0.0, 18.0, -sdf);
  vec2 refractOffset = normal * (7.5 * edge + 1.2 * edge * edge) * playbackReveal;
  vec2 lensUv = uv - (refractOffset + p * 0.014) / playbackViewport;
  vec2 blur = vec2(1.8 + 1.2 * (1.0 - edge)) / playbackViewport;
  vec3 transmitted = playbackSample(lensUv) * 0.4;
  transmitted += (playbackSample(lensUv + vec2(blur.x, 0.0)) + playbackSample(lensUv - vec2(blur.x, 0.0))
    + playbackSample(lensUv + vec2(0.0, blur.y)) + playbackSample(lensUv - vec2(0.0, blur.y))) * 0.15;
  // Subpixel dispersion at the bevel rather than colorful fringes over text.
  vec2 dispersion = normal * edge * 0.55 / playbackViewport;
  transmitted.r = mix(transmitted.r, playbackSample(lensUv + dispersion).r, edge * 0.3);
  transmitted.b = mix(transmitted.b, playbackSample(lensUv - dispersion).b, edge * 0.3);

  vec3 tint = mix(vec3(0.71, 0.69, 0.62), vec3(0.026, 0.038, 0.058), playbackNight);
  vec3 glass = mix(transmitted, tint, mix(0.56, 0.69, playbackNight));
  float bevel = exp(-abs(sdf + 1.4) * 0.42);
  // Constant angular velocity: a quiet highlight travels around the rim.
  float angle = playbackTime * 0.4488;
  vec2 light = vec2(cos(angle), sin(angle));
  float movingHighlight = pow(max(dot(normal, light), 0.0), 12.0);
  float pointerLight = exp(-length(local - playbackPointer) / 78.0) * playbackTouch;
  glass += vec3(0.27, 0.29, 0.31) * bevel * (0.24 + movingHighlight * 0.72 + pointerLight * 0.7);
  glass += vec3(0.025, 0.028, 0.031) * pointerLight;
  return vec4(mix(original.rgb, glass, mask * playbackReveal), original.a);
}
`;

// Readability veils remain unchanged around the bar. Their capsule-sized hole
// exposes the same scene pixels sampled by the lens, including in Pad portrait.
function veilCutout(
  width: number,
  height: number,
  x: number,
  y: number,
  w: number,
  h: number,
  r: number,
) {
  const right = x + w,
    bottom = y + h;
  const hole = `M${x + r} ${y}H${right - r}A${r} ${r} 0 0 1 ${right} ${y + r}V${bottom - r}A${r} ${r} 0 0 1 ${right - r} ${bottom}H${x + r}A${r} ${r} 0 0 1 ${x} ${bottom - r}V${y + r}A${r} ${r} 0 0 1 ${x + r} ${y}Z`;
  return `path(evenodd, "M0 0H${width}V${height}H0Z${hole}")`;
}

/** Refracts the live 3D scene in the existing final pass, without another draw,
 * render target, WebGL context, scene render or CPU/GPU pixel transfer. */
export class PlaybackGlassPass extends OutputPass {
  private host?: HTMLElement;
  private canvas?: HTMLCanvasElement;
  private resize?: ResizeObserver;
  private mutation?: MutationObserver;
  private dirty = true;
  private last = 0;
  private reveal = 0;
  private touch = 0;
  private touchTarget = 0;
  private bounds?: DOMRect;
  private readonly motion = matchMedia("(prefers-reduced-motion: reduce)");

  constructor() {
    super();
    Object.assign(this.uniforms, {
      playbackRect: { value: new Vector4() },
      playbackViewport: { value: new Vector2(1, 1) },
      playbackPointer: { value: new Vector2(-1000, -1000) },
      playbackRadius: { value: 40 },
      playbackReveal: { value: 0 },
      playbackNight: { value: 0 },
      playbackTime: { value: 0 },
      playbackTouch: { value: 0 },
    });
    this.material.name = "RhinePlaybackGlassOutput";
    this.material.fragmentShader = this.material.fragmentShader
      .replace("void main()", `${optics}\nvoid main()`)
      .replace("texture2D( tDiffuse, vUv )", "playbackLens(vUv)");
  }

  attach(host: HTMLElement, canvas: HTMLCanvasElement) {
    this.detach();
    this.host = host;
    this.canvas = canvas;
    host.dataset.glassRenderer = "gpu";
    this.dirty = true;
    this.resize = new ResizeObserver(this.invalidate);
    this.resize.observe(host);
    this.resize.observe(canvas);
    this.mutation = new MutationObserver(this.invalidate);
    this.mutation.observe(host, {
      attributes: true,
      attributeFilter: ["hidden"],
    });
    if (host.parentElement)
      this.mutation.observe(host.parentElement, {
        attributes: true,
        attributeFilter: ["data-layout"],
      });
    window.addEventListener("resize", this.invalidate);
    host.addEventListener("pointermove", this.move);
    host.addEventListener("pointerdown", this.press);
    host.addEventListener("pointerleave", this.leave);
    window.addEventListener("pointerup", this.release);
    window.addEventListener("pointercancel", this.leave);
    canvas.addEventListener("webglcontextlost", this.contextLost);
    canvas.addEventListener("webglcontextrestored", this.contextRestored);
  }

  private invalidate = () => {
    this.dirty = true;
  };
  private move = (event: PointerEvent) => {
    if (!this.bounds || this.host?.inert) return;
    this.uniforms.playbackPointer.value.set(
      event.clientX - this.bounds.left,
      this.bounds.bottom - event.clientY,
    );
    if (event.pointerType !== "touch") this.touchTarget = 0.35;
  };
  private press = (event: PointerEvent) => {
    this.move(event);
    this.touchTarget = 1;
  };
  private release = () => {
    this.touchTarget = 0;
  };
  private leave = () => {
    this.touchTarget = 0;
  };
  private contextLost = () => {
    if (this.host) this.host.dataset.glassRenderer = "fallback";
  };
  private contextRestored = () => {
    if (this.host) this.host.dataset.glassRenderer = "gpu";
    this.dirty = true;
  };

  update(time: number, reduced: boolean, night: number) {
    reduced ||= this.motion.matches;
    const host = this.host,
      canvas = this.canvas;
    if (!host || !canvas) return;
    const dt = Math.max(0, Math.min(0.05, time - this.last));
    this.last = time;
    if (this.dirty && !host.hidden) {
      this.bounds = host.getBoundingClientRect();
      const viewport = canvas.getBoundingClientRect();
      this.uniforms.playbackRect.value.set(
        this.bounds.left - viewport.left,
        viewport.bottom - this.bounds.bottom,
        this.bounds.width,
        this.bounds.height,
      );
      this.uniforms.playbackViewport.value.set(viewport.width, viewport.height);
      this.uniforms.playbackRadius.value = Math.min(
        parseFloat(getComputedStyle(host).borderRadius) || 40,
        this.bounds.height / 2,
      );
      const rect = this.bounds,
        radius = this.uniforms.playbackRadius.value;
      const stage = host.parentElement;
      const x = rect.left - viewport.left,
        y = rect.top - viewport.top;
      stage?.style.setProperty(
        "--playback-glass-cutout",
        veilCutout(
          viewport.width,
          viewport.height,
          x,
          y,
          rect.width,
          rect.height,
          radius,
        ),
      );
      stage?.style.setProperty(
        "--playback-glass-cutout-portrait",
        veilCutout(
          viewport.width,
          viewport.height * 0.54,
          x,
          y - viewport.height * 0.46,
          rect.width,
          rect.height,
          radius,
        ),
      );
      this.dirty = false;
    }
    const visible = !host.hidden && host.dataset.glassRenderer === "gpu";
    this.reveal = visible ? Math.min(1, this.reveal + dt / 0.32) : 0;
    const target = visible && !host.inert ? this.touchTarget : 0;
    this.touch +=
      Math.sign(target - this.touch) *
      Math.min(Math.abs(target - this.touch), dt * 5);
    this.uniforms.playbackReveal.value = reduced
      ? Number(visible)
      : this.reveal;
    this.uniforms.playbackNight.value = night;
    this.uniforms.playbackTime.value = reduced ? 0 : time;
    this.uniforms.playbackTouch.value = reduced ? 0 : this.touch;
  }

  private detach() {
    this.resize?.disconnect();
    this.mutation?.disconnect();
    window.removeEventListener("resize", this.invalidate);
    this.host?.removeEventListener("pointermove", this.move);
    this.host?.removeEventListener("pointerdown", this.press);
    this.host?.removeEventListener("pointerleave", this.leave);
    window.removeEventListener("pointerup", this.release);
    window.removeEventListener("pointercancel", this.leave);
    this.canvas?.removeEventListener("webglcontextlost", this.contextLost);
    this.canvas?.removeEventListener(
      "webglcontextrestored",
      this.contextRestored,
    );
    if (this.host) {
      delete this.host.dataset.glassRenderer;
      this.host.parentElement?.style.removeProperty("--playback-glass-cutout");
      this.host.parentElement?.style.removeProperty(
        "--playback-glass-cutout-portrait",
      );
    }
    this.host = undefined;
    this.canvas = undefined;
    this.bounds = undefined;
  }

  override dispose() {
    this.detach();
    super.dispose();
  }
}
