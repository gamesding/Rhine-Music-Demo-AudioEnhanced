import { type FormatOptions, type TextOptions, type Value } from "./format.js";
import { type Stagger } from "./layout.js";
export { formatValue, FLAP_CHARSET } from "./format.js";
export type { Value, Locales } from "./format.js";
export type { Stagger } from "./layout.js";
export interface MotionOptions {
    /** Duration in milliseconds. Zero disables animation. Default: 500. */
    duration?: number | undefined;
    /** Milliseconds per hinged card (1–10000). Default: cadence derived from duration. Flap mode only. */
    flipDuration?: number | undefined;
    animated?: boolean | undefined;
    /** Opt-in vertical motion blur for reels and turning split-flap halves. Default: false. */
    motionBlur?: boolean | undefined;
    /** Auto follows displayed magnitude, including for negative values. */
    direction?: "auto" | "up" | "down" | undefined;
    /** Offscreen numbers retain their latest value without animation. Default: true. */
    pauseOffscreen?: boolean | undefined;
    /** Order in which new glyphs cascade in. Default: "outward" from retained glyphs. */
    stagger?: Stagger | undefined;
    /**
     * "roll" (default) glides a wheel of faces through the slot. "flap" hinges one
     * card per face at the midline like a split-flap board; new glyphs flap in from
     * the wheel's blank face. Opt-in motion blur subtly softens the turning halves.
     */
    mode?: "roll" | "flap" | undefined;
}
export interface RollingNumberOptions extends FormatOptions, MotionOptions {
    value: Value;
}
export interface RollingTextOptions extends TextOptions, MotionOptions {
    text: string;
}
export interface RollingController<Options> {
    update(options: Partial<Options>): void;
    /** Explicit invalidation for theme/variable-font changes. */
    refresh(): void;
    /** Immediately show the latest target without motion. */
    finish(): void;
    /** Releases all resources and leaves the final formatted text. Idempotent. */
    destroy(): void;
}
export type RollingNumberController = RollingController<RollingNumberOptions>;
export type RollingTextController = RollingController<RollingTextOptions>;
/** The host's children belong exclusively to this controller until destroy(). */
export declare function createRollingNumber(host: HTMLElement, options: RollingNumberOptions): RollingNumberController;
/** Split-flap style text: characters in the charset roll through a wheel, others crossfade. */
export declare function createRollingText(host: HTMLElement, options: RollingTextOptions): RollingTextController;
