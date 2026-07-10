import json, sys, statistics as st

ev = json.load(open(sys.argv[1]))["traceEvents"]
ev = [e for e in ev if e.get("ph") == "X"]
nstages = {}
for e in ev:
    if e["name"] == "publish":
        nstages[e["args"]["chain"]] = e["args"]["stage"]

pubs = sorted((e for e in ev if e["name"] == "publish"), key=lambda e: e["ts"])
fat = [e for e in pubs if e["dur"] > 5.0]
print(f"publishes={len(pubs)}  dur>5us={len(fat)}  dur p50={st.median(e['dur'] for e in pubs):.2f}  max={max(e['dur'] for e in pubs):.1f}us")
for e in fat[:12]:
    a = e["args"]
    print(f"  fat publish: t={e['ts']/1000:.2f}ms dur={e['dur']:.1f}us stages={a['stage']} chunks={a['arg']} chain={a['chain']}")

# post-classifier gap: last chunk end of each 1-stage chain -> next publish t0
cls_end = {}
for e in ev:
    if e["name"] == "chunk" and nstages.get(e["args"]["chain"], 0) == 1:
        c = e["args"]["chain"]
        cls_end[c] = max(cls_end.get(c, 0), e["ts"] + e["dur"])
gaps = []
for c, end in cls_end.items():
    nxt = next((p for p in pubs if p["ts"] > end), None)
    if nxt:
        gaps.append((nxt["ts"] - end, nxt["dur"], end))
if gaps:
    print(f"\npost-cls gaps: n={len(gaps)} p50={st.median(g[0] for g in gaps):.1f}us max={max(g[0] for g in gaps):.1f}us")
    print(f"  next-publish dur after gap: p50={st.median(g[1] for g in gaps):.1f}us max={max(g[1] for g in gaps):.1f}us")
