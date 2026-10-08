export interface Position {
    x: number;
    width: number;
}
export type Stagger = "outward" | "start" | "end" | "none";
/**
 * Stagger order for new tokens: 0 for retained tokens, then 1, 2, ... in the given
 * order. "outward" spreads from the nearest retained token so a growing number
 * cascades from the digits already on screen (left to right when nothing is
 * retained); "start" and "end" run across the new tokens from either edge, like a
 * departure board; "none" gives every new token rank 1.
 */
export declare function entryRanks(retained: readonly boolean[], stagger?: Stagger): number[];
/** Missing columns share the next retained edge; trailing columns share the last end. */
export declare function collapsePositions(keys: readonly string[], positions: ReadonlyMap<string, Position>): Map<string, number>;
