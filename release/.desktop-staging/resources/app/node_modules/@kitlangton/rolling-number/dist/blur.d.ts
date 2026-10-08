import { type Motion } from "./motion.js";
/** Optional, bounded decoration. The reel's one transform moves both copies. */
export declare class ReelBlur {
    private host;
    private layers;
    private filter;
    /** Multiplier on the vertical deviation; set before `apply`, read at definition time. */
    intensity: number;
    constructor(host: HTMLElement);
    /** Shared vertical-only kernel for reel copies and hinged half-card copies. */
    filterUrl(height: number): string;
    apply(reel: HTMLElement, motion: Motion, height: number, from: number, kind?: "roll" | "entry"): boolean;
    remove(reel: HTMLElement): number;
    destroy(): void;
}
