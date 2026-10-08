"""Trace the supplied monochrome marks as transparent SVG paths (Pillow required)."""
from pathlib import Path
import math
from PIL import Image

ROOT = Path(__file__).resolve().parent
OUTPUT = ROOT.parent / 'public' / 'audio-tech'

def simplify(points, tolerance=.6):
    if len(points) < 3: return points
    ax, ay = points[0]; bx, by = points[-1]
    dx, dy = bx-ax, by-ay
    length = math.hypot(dx,dy)
    distances = [abs(dx*(ay-y)-(ax-x)*dy)/length if length else math.hypot(x-ax,y-ay) for x,y in points]
    index = max(range(len(points)),key=distances.__getitem__)
    if distances[index] <= tolerance: return [points[0],points[-1]]
    return simplify(points[:index+1],tolerance)[:-1]+simplify(points[index:],tolerance)

def trace(filename, output, title, crop=None):
    image = Image.open(ROOT / filename).convert('RGBA')
    if crop: image = image.crop(crop)
    width, height = image.size
    pixels = image.load()
    ink = {(x,y) for y in range(height) for x in range(width) if pixels[x,y][3]>127 and sum(pixels[x,y][:3])<384}
    x0=min(x for x,y in ink)-3; y0=min(y for x,y in ink)-3
    x1=max(x for x,y in ink)+4; y1=max(y for x,y in ink)+4
    edges={}
    def edge(a,b): edges.setdefault(a,[]).append(b)
    for x,y in sorted(ink):
        if (x,y-1) not in ink: edge((x,y),(x+1,y))
        if (x+1,y) not in ink: edge((x+1,y),(x+1,y+1))
        if (x,y+1) not in ink: edge((x+1,y+1),(x,y+1))
        if (x-1,y) not in ink: edge((x,y+1),(x,y))
    paths=[]
    while edges:
        start=next(iter(edges)); cursor=start; points=[start]
        while True:
            options=edges[cursor]; following=options.pop()
            if not options: del edges[cursor]
            points.append(following); cursor=following
            if cursor==start: break
        # Codec specks smaller than two square pixels are not part of the mark.
        area=abs(sum(a[0]*b[1]-b[0]*a[1] for a,b in zip(points,points[1:])))/2
        if area<2: continue
        points=simplify(points)
        paths.append('M'+' L'.join(f'{x-x0},{y-y0}' for x,y in points[:-1])+' Z')
    OUTPUT.mkdir(parents=True,exist_ok=True)
    svg=f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {x1-x0} {y1-y0}" role="img"><title>{title}</title><path fill="currentColor" fill-rule="evenodd" d="{" ".join(paths)}"/></svg>\n'
    (OUTPUT/output).write_text(svg,encoding='utf-8')
    print(output, x1-x0, y1-y0, len(svg), 'bytes')

if __name__=='__main__':
    trace('DSEE_LOGO.avif','dsee.svg','DSEE')
    # Use the supplied main S-Master wordmark; omit the amplifier hardware subtitle.
    trace('S-MASTER.webp','s-master.svg','S-Master HX',(0,0,1520,355))
    trace('vinyl.png','vinyl.svg','Vinyl')
