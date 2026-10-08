import { type JSX } from "solid-js";
import { type RollingNumberOptions, type RollingTextOptions } from "./index.js";
type SpanProps = Omit<JSX.HTMLAttributes<HTMLSpanElement>, "children" | "innerHTML" | "textContent" | "innerText">;
export type RollingNumberProps = RollingNumberOptions & SpanProps;
export type RollingTextProps = RollingTextOptions & SpanProps;
export declare const RollingNumber: (props: RollingNumberOptions & SpanProps) => JSX.Element;
/** Split-flap style text. Characters in `charset` roll; others crossfade in place. */
export declare const RollingText: (props: RollingTextOptions & SpanProps) => JSX.Element;
export {};
