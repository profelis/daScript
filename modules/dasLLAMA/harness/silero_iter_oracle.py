#!/usr/bin/env python3
# Streaming oracle: silero VADIterator -> `EVT<TAB>start|end<TAB>sample`. Diff against
# silero_iter_probe.das. Processes full 512-sample windows (ragged tail dropped, matching the
# probe's pending buffer).
#   python silero_iter_oracle.py <audio.wav>
import sys
import numpy as np
import soundfile as sf
import torch
from silero_vad import load_silero_vad, VADIterator

wav, sr = sf.read(sys.argv[1], dtype="float32")
if wav.ndim > 1:
    wav = wav.mean(axis=1)
assert sr == 16000
model = load_silero_vad(onnx=True)
it = VADIterator(model, sampling_rate=16000)  # defaults: thr .5, min_sil 100ms, pad 30ms

N = 512
for start in range(0, len(wav) // N * N, N):
    chunk = torch.from_numpy(wav[start:start + N].copy())
    out = it(chunk)
    if out is not None:
        if "start" in out:
            print(f"EVT\tstart\t{out['start']}")
        if "end" in out:
            print(f"EVT\tend\t{out['end']}")
