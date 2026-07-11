import json, sys, statistics as st
from collections import defaultdict

ev = json.load(open(sys.argv[1]))["traceEvents"]
ev = [e for e in ev if e.get("ph") == "X"]
nstages = {}
for e in ev:
    if e["name"] == "publish":
        nstages[e["args"]["chain"]] = e["args"]["stage"] & 0xFF   # publish packs nstages | tag<<8

# per chain+stage: per-lane last chunk end
by = defaultdict(lambda: defaultdict(list))
for e in ev:
    if e["name"] != "chunk":
        continue
    a = e["args"]
    by[(a["chain"], a["stage"])][e["tid"]].append((e["ts"], e["ts"] + e["dur"]))

def tail_stats(cl_name, want_ns, stage):
    spans, idle_frac, tail_frac, laneN = [], [], [], []
    for (ch, s), lanes in by.items():
        if nstages.get(ch, 0) != want_ns or s != stage:
            continue
        ends = sorted(max(e for _, e in v) for v in lanes.values())
        starts = min(t for v in lanes.values() for t, _ in v)
        span = ends[-1] - starts
        if span <= 0 or len(ends) < 4:
            continue
        med_end = ends[len(ends) // 2]
        busy = sum(e - t for v in lanes.values() for t, e in v)
        spans.append(span)
        idle_frac.append(1 - busy / (span * len(lanes)))
        tail_frac.append((ends[-1] - med_end) / span)   # window between median lane done and last done
        laneN.append(len(lanes))
    if not spans:
        return
    print(f"{cl_name} stage{stage}: n={len(spans)} span p50={st.median(spans):7.1f}us  lanes p50={st.median(laneN):4.0f}  "
          f"idle p50={100*st.median(idle_frac):4.1f}%  tail(median-lane-done -> last-done) p50={100*st.median(tail_frac):4.1f}% of span")

tail_stats("classifier", 1, 0)
tail_stats("ffn", 2, 0)
tail_stats("ffn", 2, 1)
tail_stats("attn", 4, 3)
