import { type Motion } from "./motion.js";
/**
 * Four temporary half-card strips model one hinge: the current top falls, then
 * the next bottom lands. Native stepped timing advances their glyphs together.
 * Travel is bounded by the wheel size; all strips disappear on settlement.
 */
/** Milliseconds per card. Derived from the requested duration, kept in a mechanical range. */
export declare function flapCadence(duration: number): number;
/** Logical wheel position advancing one face per card, for interruption sampling. */
export declare function flapMotion(from: number, to: number, cadence: number): Motion;
/** Pure timeline for a positive number of steps. Every boundary uses identical offsets. */
export declare function flapFrames(steps: number): {
    index: {
        "--rn-flap-step": string;
        offset: number;
        easing: string;
    }[];
    falls: Keyframe[];
    lands: Keyframe[];
};
/** Disable softness without interrupting a half-card's transform or timing. */
export declare function clearFlapBlur(root: HTMLElement): void;
export declare function buildFlaps(reel: HTMLElement, wheel: readonly string[], from: number, to: number, height: number, cadence: number, delay: number, blur?: string): void;
