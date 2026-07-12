#!/usr/bin/env python3
# Bit-exact oracle for the K-quant dequant (Q4_K / Q6_K) in dasllama_gguf.das.
# Pairs with q4k_dequant_probe.das:
#   bin/daslang modules/dasLLAMA/harness/q4k_dequant_probe.das -- <model.gguf> > dump.txt
#   python modules/dasLLAMA/harness/q4k_dequant_compare.py <model.gguf> dump.txt
# Compares the das dump against gguf-py's dequantize (an independent implementation of the
# ggml superblock spec) as raw uint32 bit patterns — exit 0 only on bit-exact agreement.
# gguf-py location defaults to D:/Work/llama.cpp/gguf-py; override with LLAMA_CPP_DIR.

import os
import sys

import numpy as np

llama_cpp = os.environ.get("LLAMA_CPP_DIR", r"D:\Work\llama.cpp")
sys.path.insert(0, os.path.join(llama_cpp, "gguf-py"))
from gguf import GGUFReader
from gguf.quants import dequantize

gguf_path = sys.argv[1]
dump_path = sys.argv[2]

# parse the das dump: "TENSOR <name> <n> type <t>" followed by n hex bit patterns, one per line
sections = {}
with open(dump_path) as f:
    vals = None
    for line in f:
        line = line.strip()
        if line.startswith("TENSOR"):
            vals = []
            sections[line.split()[1]] = vals
        elif line:
            vals.append(int(line, 16))
ours = {k: np.array(v, dtype=np.uint32).view(np.float32) for k, v in sections.items()}

r = GGUFReader(gguf_path)
by_name = {t.name: t for t in r.tensors}
fail = 0
for name, mine in ours.items():
    t = by_name[name]
    ref = dequantize(t.data, t.tensor_type).reshape(-1)[: len(mine)].astype(np.float32)
    if np.array_equal(mine.view(np.uint32), ref.view(np.uint32)):
        print(f"{name}: BIT-EXACT over {len(mine)} values ({t.tensor_type.name})")
    else:
        bad = mine.view(np.uint32) != ref.view(np.uint32)
        idx = int(np.argmax(bad))
        print(f"{name}: MISMATCH {int(bad.sum())}/{len(mine)} values, "
              f"first at {idx}: ours {mine[idx]} ref {ref[idx]}")
        fail = 1
sys.exit(fail)
