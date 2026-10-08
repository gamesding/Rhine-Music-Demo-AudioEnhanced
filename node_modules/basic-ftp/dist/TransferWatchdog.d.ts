import { Socket } from "net";
/** A transfer either sends data to or receives data from the data connection. */
export type TransferDirection = "upload" | "download";
/**
 * Watches a data connection during a transfer and reports it as stalled if the server stopped
 * making progress.
 *
 * This replaces a plain inactivity timeout on the data socket. Such a timeout can't tell apart
 * "the server stopped sending" from "our own source or destination isn't ready yet". A slow local
 * stream is not an error: A download piped into a decompressor, or an upload fed by a stream that
 * computes its data, can legitimately leave the connection idle for minutes. Timing out on that
 * kills a healthy transfer and truncates the data the destination already received.
 *
 * Only time spent waiting for the server counts towards the timeout, see `isWaitingForServer`.
 */
export declare class TransferWatchdog {
    protected timer: NodeJS.Timeout | undefined;
    /**
     * Start watching a transfer. Calls `onStall` if the server hasn't made progress for
     * `timeout` milliseconds, or for twice that if we made it wait ourselves before that.
     * A timeout of 0 disables the watchdog.
     */
    start(socket: Socket, direction: TransferDirection, timeout: number, onStall: () => void): void;
    /**
     * Stop watching. Safe to call at any time, also if no transfer is being watched.
     */
    stop(): void;
}
