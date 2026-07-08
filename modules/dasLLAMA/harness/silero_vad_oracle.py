#!/usr/bin/env python3
# Silero-VAD parity oracle: onnxruntime on the official silero_vad_16k_op15.onnx, driven with
# the exact streaming framing (context64 ++ chunk512, reflect the state, carry LSTM state).
# Emits one `PROB<TAB>frame<TAB>prob` line per 512-sample chunk — diff against
# silero_parity_probe.das. Proven bit-exact to silero's OnnxWrapper (scratch validate2.py).
#
#   python silero_vad_oracle.py <audio.wav> [op15.onnx]
#
# Framing matches get_speech_timestamps: iterate 0..len step 512, zero-pad the ragged tail.
import sys, os
import numpy as np
import soundfile as sf
import onnxruntime as ort

N, CTX = 512, 64


def default_model():
    try:
        import silero_vad
        return os.path.join(os.path.dirname(silero_vad.__file__), "data", "silero_vad_16k_op15.onnx")
    except Exception:
        return "silero_vad_16k_op15.onnx"


def main():
    wav_path = sys.argv[1]
    model = sys.argv[2] if len(sys.argv) > 2 else default_model()
    wav, sr = sf.read(wav_path, dtype="float32")
    if wav.ndim > 1:
        wav = wav.mean(axis=1)
    assert sr == 16000, f"expected 16 kHz, got {sr}"

    s = ort.InferenceSession(model, providers=["CPUExecutionProvider"])
    state = np.zeros((2, 1, 128), np.float32)
    ctx = np.zeros(CTX, np.float32)
    srn = np.array(16000, np.int64)

    frame = 0
    for start in range(0, len(wav), N):
        chunk = wav[start:start + N]
        if len(chunk) < N:
            chunk = np.pad(chunk, (0, N - len(chunk)))
        x = np.concatenate([ctx, chunk]).astype(np.float32)[None, :]
        out, state = s.run(None, {"input": x, "state": state, "sr": srn})
        print(f"PROB\t{frame}\t{float(np.ravel(out)[0]):.6f}")
        ctx = chunk[-CTX:].astype(np.float32)
        frame += 1


if __name__ == "__main__":
    main()
