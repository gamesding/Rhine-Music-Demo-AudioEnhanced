export type Value = number | bigint;
export type Locales = string | string[];
export interface FormatOptions {
    locales?: Locales | undefined;
    format?: Intl.NumberFormatOptions | undefined;
}
export interface Token {
    key: string;
    identity: string;
    text: string;
    /** Faces this glyph can roll through; undefined for symbols that crossfade instead. */
    wheel?: readonly string[];
    /** Position of `text` on the wheel. */
    index?: number;
}
export declare const DIGITS: readonly string[];
export interface Model {
    text: string;
    tokens: Token[];
    rollable: boolean;
    signature: string;
    magnitude: string;
}
export declare function formatValue(value: Value, options?: FormatOptions): string;
export declare function model(value: Value, options?: FormatOptions): Model;
/** Compare displayed magnitudes without precision loss or parsing localized strings. */
export declare function direction(previous: Model, next: Model): -1 | 0 | 1;
export interface TextOptions {
    /** "direct" rolls each glyph straight to its replacement, without alphabet cycling. Default: "wheel". */
    transition?: "wheel" | "direct" | undefined;
    /**
     * Characters that roll through a wheel, in wheel order; others crossfade in place.
     * An array gives each character position its own wheel, like a board with digit
     * drums for times and letter drums for destinations. Default: FLAP_CHARSET.
     */
    charset?: string | readonly string[] | undefined;
}
/** Split-flap style board default: space, A–Z, digits, then common punctuation. */
export declare const FLAP_CHARSET = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:.-/&+'";
/** One token per grapheme; identity is the character position so words retarget in place. */
export declare function textModel(text: string, options?: TextOptions): Model;
