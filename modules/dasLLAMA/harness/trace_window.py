import json, sys
from collections import defaultdict

src, dst, t_lo, t_hi = sys.argv[1], sys.argv[2], float(sys.argv[3]), float(sys.argv[4])
ev = json.load(open(src))["traceEvents"]
ev = [e for e in ev if e.get("ph") == "X"]

# chain -> stage count + op tag (packed in the publish's stage field: nstages | tag<<8)
nstages = {}
tags = {}
for e in ev:
    if e["name"] == "publish":
        packed = e["args"]["stage"]
        nstages[e["args"]["chain"]] = packed & 0xFF
        tags[e["args"]["chain"]] = packed >> 8

lo, hi = t_lo * 1000.0, t_hi * 1000.0   # args in ms, trace ts in us
out = []
kinds = {"publish": 0, "chunk": 1, "stage_wait": 2, "wake": 3, "fifo_job": 4}
for e in ev:
    ts, dur = e["ts"], e["dur"]
    if ts + dur < lo or ts > hi:
        continue
    a = e.get("args", {})
    ch = a.get("chain", 0)
    st = a.get("stage", 0)
    if e["name"] == "publish":
        st = st & 0xFF
    out.append([e["tid"], round(ts - lo, 1), round(dur, 1), kinds[e["name"]],
                st, nstages.get(ch, 0), ch, a.get("arg", 0), tags.get(ch, 0)])

out.sort(key=lambda r: (r[0], r[1]))
lanes = max(r[0] for r in out) + 1
span = hi - lo
compact = json.dumps(out, separators=(",", ":"))
open(dst, "w").write(f'{{"lanes":{lanes},"span":{span:.1f},"events":{compact}}}')
print(f"events={len(out)} lanes={lanes} span_us={span:.0f} bytes={len(compact)}")
