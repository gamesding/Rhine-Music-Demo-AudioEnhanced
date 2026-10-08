/* The build replaces both tokens; this file is never registered in development. */
const VERSION = "be441d54ea61c215";
const FILES = ["archives/RHINE-LAB-X-001.txt","archives/RHINE-LAB-X-002.txt","archives/RHINE-LAB-X-003.txt","archives/RHINE-LAB-X-004.txt","archives/RHINE-LAB-X-005.txt","archives/RHINE-LAB-X-006.txt","archives/RHINE-LAB-X-007.txt","archives/RHINE-LAB-X-008.txt","archives/RHINE-LAB-X-009.txt","archives/RHINE-LAB-X-010.txt","archives/RHINE-LAB-X-011.txt","archives/RHINE-LAB-X-012.txt","archives/RHINE-LAB-X-013.txt","archives/RHINE-LAB-X-014.txt","archives/RHINE-LAB-X-015.txt","archives/RHINE-LAB-X-016.txt","archives/RHINE-LAB-X-017.txt","archives/RHINE-LAB-X-018.txt","archives/RHINE-LAB-X-019.txt","archives/RHINE-LAB-X-020.txt","archives/RHINE-LAB-X-021.txt","archives/RHINE-LAB-X-022.txt","archives/RHINE-LAB-X-023.txt","archives/RHINE-LAB-X-024.txt","archives/RHINE-LAB-X-025.txt","archives/RHINE-LAB-X-026.txt","archives/RHINE-LAB-X-027.txt","archives/RHINE-LAB-X-028.txt","archives/RHINE-LAB-X-029.txt","archives/RHINE-LAB-X-030.txt","archives/RHINE-LAB-X-031.txt","archives/RHINE-LAB-X-032.txt","archives/RHINE-LAB-X-033.txt","archives/RHINE-LAB-X-034.txt","archives/RHINE-LAB-X-035.txt","archives/RHINE-LAB-X-036.txt","archives/RHINE-LAB-X-037.txt","archives/RHINE-LAB-X-038.txt","archives/RHINE-LAB-X-039.txt","archives/RHINE-LAB-X-040.txt","assets/archive-assembly.glb","assets/archive-cassette.glb","assets/archive-main-BnXVggHh.js","assets/archive-main-DO9dVcMl.css","assets/audio-BesObhbc.css","assets/audio-YSx6dQDm.js","assets/index-ygRcXDpM.js","assets/music-app-Bb1riC4M.js","assets/music-app-CmOuXORO.css","assets/music-cd.glb","audio/atmosphere.ogg","audio/motif.ogg","audio/pulse.ogg","favicon.svg","fonts/MiSans-Bold.woff2","fonts/MiSans-Demibold.woff2","fonts/MiSans-Light.woff2","fonts/MiSans-Regular.woff2","fonts/MiSans-license.pdf","fonts/NOTICE.txt","icons/app-icon.svg","icons/apple-touch-icon.png","icons/icon-192.png","icons/icon-512.png","icons/icon-maskable-512.png","index.html","licenses/apache-2.0.txt","licenses/basic-ftp.txt","licenses/music-metadata.txt","licenses/opencc-js-third-party.md","licenses/opencc-js.txt","licenses/project-mit.txt","licenses/rolling-number.txt","licenses/three.txt","manifest.webmanifest"];
const PREFIX = `rhine-lab:${new URL(self.registration.scope).pathname}:`;
const CACHE = PREFIX + VERSION;
const urls = FILES.map(path => new URL(path, self.registration.scope).href);
const allowed = new Set(urls);
const index = new URL("index.html", self.registration.scope).href;

self.addEventListener("install", event => {
  event.waitUntil((async () => {
    try {
      const cache = await caches.open(CACHE);
      // Conditional validation also catches model/font changes at stable URLs.
      await cache.addAll(urls.map(url => new Request(url, { cache: "no-cache" })));
    } catch (error) {
      await caches.delete(CACHE);
      throw error;
    }
  })());
});
self.addEventListener("activate", event => {
  event.waitUntil((async () => {
    for (const key of await caches.keys())
      if (key.startsWith(PREFIX) && key !== CACHE) await caches.delete(key);
    await self.clients.claim();
  })());
});
self.addEventListener("message", event => {
  if (event.data?.type === "RHINE_APPLY_UPDATE") event.waitUntil(self.skipWaiting());
});
self.addEventListener("fetch", event => {
  if (event.request.method !== "GET") return;
  const url = new URL(event.request.url);
  if (url.origin !== self.location.origin) return;
  url.search = "";
  url.hash = "";
  const navigation = event.request.mode === "navigate" &&
    (url.href === self.registration.scope || url.href === index);
  const key = navigation ? index : url.href;
  if (!allowed.has(key)) return;
  event.respondWith((async () => {
    const cache = await caches.open(CACHE);
    // HTML, hashed bundles and stable model URLs come from the same release.
    // A new release stays waiting until the user chooses to restart or exits.
    const cached = await cache.match(key);
    return cached ?? fetch(event.request);
  })());
});
