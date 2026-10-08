import { type Motion, type Sample } from "./motion.js";
/** Start every effect in a transition on the same document frame, without a pending play task. */
export declare function animateNow(element: HTMLElement, keyframes: Keyframe[], timing: KeyframeAnimationOptions): Animation;
/** One animation owner per property. No accumulated effects or finished promises. */
export declare class Track {
    private element;
    private property;
    private animation;
    private motion;
    private value;
    constructor(element: HTMLElement, property: "transform" | "opacity");
    read(): Sample;
    set(value: number, format: (value: number) => string): void;
    play(motion: Motion, format: (value: number) => string, done?: () => void): void;
    cancel(): void;
}
