import { type ComponentPropsWithoutRef } from "react";
import { type RollingNumberOptions, type RollingTextOptions } from "./index.js";
type SpanProps = Omit<ComponentPropsWithoutRef<"span">, "children" | "dangerouslySetInnerHTML">;
export type RollingNumberProps = RollingNumberOptions & SpanProps;
export type RollingTextProps = RollingTextOptions & SpanProps;
export declare const RollingNumber: import("react").ForwardRefExoticComponent<RollingNumberOptions & SpanProps & import("react").RefAttributes<HTMLSpanElement>>;
/** Split-flap style text. Characters in `charset` roll; others crossfade in place. */
export declare const RollingText: import("react").ForwardRefExoticComponent<RollingTextOptions & SpanProps & import("react").RefAttributes<HTMLSpanElement>>;
export {};
