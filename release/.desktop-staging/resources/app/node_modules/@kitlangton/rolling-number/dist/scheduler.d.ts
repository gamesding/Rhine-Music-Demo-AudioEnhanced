export interface Participant {
    stage(): (() => void) | undefined;
    measure(): (() => void) | undefined;
    refresh(): void;
    visibility(visible: boolean): void;
    sizeChanged(element: Element, width: number, height: number): boolean;
}
type Browser = Window & typeof globalThis;
/** Shared across counters: one frame, resize observer, intersection observer and listener set. */
export declare class Scheduler {
    private view;
    readonly media: MediaQueryList;
    private members;
    private pending;
    private sizes;
    private intersections;
    private resize;
    private intersection;
    private frame;
    static for(view: Browser): Scheduler;
    private constructor();
    private refresh;
    add(owner: Participant, host: Element): void;
    watch(element: Element, owner: Participant): void;
    unwatch(element: Element): void;
    enqueue(owner: Participant): void;
    remove(owner: Participant, host: Element): void;
}
export {};
