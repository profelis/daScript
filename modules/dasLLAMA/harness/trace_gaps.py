import json, sys, statistics as st
from collections import defaultdict

path = sys.argv[1]
ev = json.load(open(path))["traceEvents"]
ev = [e for e in ev if e.get("ph") == "X"]
caller_tid = max(e["tid"] for e in ev)

chains = defaultdict(lambda: {"pub": None, "chunks": defaultdict(list), "cwaits": {}, "nstages": 0, "total": 0})
wakes = []
for e in ev:
    a = e.get("args", {})
    t0, dur, tid = e["ts"], e["dur"], e["tid"]
    if e["name"] == "publish":
        c = chains[a["chain"]]
        c["pub"] = (t0, dur)
        c["nstages"] = a["stage"]
        c["total"] = a["arg"]
    elif e["name"] == "chunk":
        chains[a["chain"]]["chunks"][a["stage"]].append((t0, dur, tid))
    elif e["name"] == "stage_wait" and tid == caller_tid:
        chains[a["chain"]]["cwaits"][a["stage"]] = (t0, dur)
    elif e["name"] == "wake":
        wakes.append((t0, dur, tid))

# classify by stage count: 4=attn(sliced) 3=attn 2=ffn 1=final
classes = defaultdict(list)
for cid, c in chains.items():
    if c["pub"] is None:
        continue
    classes[c["nstages"]].append((cid, c))

def p(v, q):
    return st.quantiles(v, n=100)[q - 1] if len(v) > 3 else (st.median(v) if v else 0.0)

name = {4: "attn(4st)", 3: "attn(3st)", 2: "ffn", 1: "final"}
print(f"chains={len(chains)} wakes={len(wakes)} (wake dur p50={st.median([w[1] for w in wakes]) if wakes else 0:.1f}us)")
for ns in sorted(classes, reverse=True):
    rows = classes[ns]
    walls, pubs, reacts = [], [], []
    stage_span = defaultdict(list); stage_busy = defaultdict(list); stage_par = defaultdict(list)
    stage_lanes = defaultdict(list); stage_tail = defaultdict(list)
    interstage = defaultdict(list)
    for cid, c in rows:
        pub_t0, pub_dur = c["pub"]
        pub_end = pub_t0 + pub_dur
        last_wait = max((w[0] + w[1]) for w in c["cwaits"].values()) if c["cwaits"] else pub_end
        walls.append(last_wait - pub_t0)
        pubs.append(pub_dur)
        wchunks = [t0 for s in c["chunks"] for (t0, d, tid) in c["chunks"][s] if tid != caller_tid]
        if wchunks:
            reacts.append(min(wchunks) - pub_end)
        prev_end = None
        for s in sorted(c["chunks"]):
            ch = c["chunks"][s]
            s0 = min(t0 for t0, d, t in ch); s1 = max(t0 + d for t0, d, t in ch)
            busy = sum(d for t0, d, t in ch)
            span = s1 - s0
            stage_span[s].append(span); stage_busy[s].append(busy)
            stage_par[s].append(busy / span if span > 0 else 1.0)
            stage_lanes[s].append(len(set(t for t0, d, t in ch)))
            # tail: span minus the point where all-but-last lane finished ~ last chunk dur
            lastdur = max(d for t0, d, t in ch if t0 + d == s1)
            stage_tail[s].append(lastdur)
            if prev_end is not None:
                interstage[s].append(s0 - prev_end)
            prev_end = s1
    print(f"\n== {name.get(ns, ns)}  n={len(rows)}  chunks/chain={rows[0][1]['total']}")
    print(f"  wall/chain us: p50={st.median(walls):.1f} p95={p(walls, 95):.1f}   publish: p50={st.median(pubs):.1f}   first-worker-claim after pub: p50={st.median(reacts):.1f} p95={p(reacts, 95):.1f}")
    for s in sorted(stage_span):
        print(f"  stage {s}: span p50={st.median(stage_span[s]):7.1f}  busy-sum p50={st.median(stage_busy[s]):7.1f}  eff-par p50={st.median(stage_par[s]):5.2f}  lanes p50={st.median(stage_lanes[s]):4.1f}  last-chunk p50={st.median(stage_tail[s]):5.1f}"
              + (f"  gap-from-prev p50={st.median(interstage[s]):5.1f}" if s in interstage else ""))
