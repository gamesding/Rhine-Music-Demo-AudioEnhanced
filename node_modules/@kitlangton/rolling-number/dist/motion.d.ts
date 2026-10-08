export interface Motion {
    readonly points: readonly number[];
    readonly duration: number;
    readonly target: number;
}
export interface Sample {
    position: number;
    velocity: number;
}
/** Let horizontal space open before a new glyph rises through its fixed viewport. */
export declare function entrance(height: number, duration: number, hold?: number): Motion;
/** Hold the first point for `delay`, then play the motion unchanged; sampling stays exact. */
export declare function delayed(motion: Motion, delay: number): Motion;
/** Critically damped spring, sampled once for native WAAPI playback. */
export declare function spring(from: number, target: number, velocity: number, duration: number): Motion;
/** Blend into a vertical smear as reel speed rises from 4 to 24 rows/second. */
export declare function blurEnvelope(motion: Motion, from?: number, fullSpeed?: number): Motion;
/** Matches linear interpolation between the exact keyframes sent to the browser. */
export declare function sample(motion: Motion, time: number): Sample;
/** Nearest wheel position showing `index`, honoring the trend; `size` faces per revolution. */
export declare function rollTarget(position: number, index: number, trend: -1 | 0 | 1, size?: number): number;
/** The face shown at an integer wheel position, wrapping in both directions. */
export declare const face: (wheel: readonly string[], position: number) => string;
export declare const numeral: (position: number) => string;
/** Keep only the visible pair plus the newest glyph; interrupted words never build a queue. */
export declare function directRoll(previous: readonly string[], position: number, glyph: string): {
    wheel: string[];
    from: number;
    target: number;
};
