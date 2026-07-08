#!/usr/bin/env python3
# Segment oracle: silero get_speech_timestamps (default 16 kHz opts) -> `SEG<TAB>start<TAB>end`
# (sample indices). Diff against silero_segment_probe.das.
#   python silero_segment_oracle.py <audio.wav>
import sys
import numpy as np
import soundfile as sf
from silero_vad import load_silero_vad, get_speech_timestamps

wav, sr = sf.read(sys.argv[1], dtype="float32")
if wav.ndim > 1:
    wav = wav.mean(axis=1)
assert sr == 16000
model = load_silero_vad(onnx=True)
segs = get_speech_timestamps(wav, model)  # defaults: thr .5, min_speech 250, min_sil 100, pad 30
for s in segs:
    print(f"SEG\t{s['start']}\t{s['end']}")
