# numpy stage oracle for the whisper-proper encoder (dasllama_whisper) — reads a whisper.cpp
# ggml bin directly, mirrors whisper.cpp's mel rules + the fp16-LUT tanh gelu, dumps np_*.f32
# stage files the das-side probe (or set_audio_encode_ref_dir rail) diffs against.
#
#   python3 whisper_np_oracle.py <ggml-model.bin> <audio.wav> <out_dir>
import struct
import sys
import wave

import numpy as np

MODEL, WAV, OUT = sys.argv[1], sys.argv[2], sys.argv[3].rstrip('/') + '/'

# ---- ggml bin reader ----
f = open(MODEL, 'rb')
assert struct.unpack('<I', f.read(4))[0] == 0x67676d6c
hp = struct.unpack('<11i', f.read(44))
(n_vocab, n_audio_ctx, n_audio_state, n_audio_head, n_audio_layer,
 n_text_ctx, n_text_state, n_text_head, n_text_layer, n_mels, ftype) = hp
fm, fn = struct.unpack('<2i', f.read(8))
filters = np.frombuffer(f.read(fm * fn * 4), dtype='<f4').reshape(fm, fn)
nv = struct.unpack('<i', f.read(4))[0]
for _ in range(nv):
    ln = struct.unpack('<I', f.read(4))[0]
    f.seek(ln, 1)
T = {}
while True:
    hdr = f.read(12)
    if len(hdr) < 12:
        break
    nd, nl, tt = struct.unpack('<3i', hdr)
    ne = struct.unpack(f'<{nd}i', f.read(4 * nd))
    name = f.read(nl).decode()
    n = int(np.prod(ne))
    raw = f.read(n * (4 if tt == 0 else 2))
    a = np.frombuffer(raw, dtype='<f4' if tt == 0 else '<f2').astype(np.float32)
    T[name] = a.reshape(ne[::-1])  # ne[0] is innermost

# ---- mel: whisper.cpp log_mel_spectrogram rules ----
wf = wave.open(WAV, 'rb')
assert wf.getframerate() == 16000 and wf.getnchannels() == 1 and wf.getsampwidth() == 2
pcm = np.frombuffer(wf.readframes(wf.getnframes()), dtype='<i2')
samples = (pcm / 32768.0).astype(np.float32)
samples.tofile(OUT + 'np_samples.f32')

n_in = len(samples)
head = 200
padded = np.zeros(n_in + 16000 * 30 + 2 * head, dtype=np.float32)
padded[head:head + n_in] = samples
padded[:head] = samples[1:head + 1][::-1]
n_len = (len(padded) - 400) // 160
n_compute = min((n_in + head) // 160 + 1, n_len)
hann = (0.5 * (1.0 - np.cos(2.0 * np.pi * np.arange(400) / 400.0))).astype(np.float32)
idx = np.arange(n_compute)[:, None] * 160 + np.arange(400)[None, :]
frames = (padded[idx] * hann).astype(np.float32)
spec = np.fft.rfft(frames.astype(np.float64), n=400, axis=1)
power = (spec.real.astype(np.float32) ** 2 + spec.imag.astype(np.float32) ** 2)
melv = power.astype(np.float64) @ filters.T.astype(np.float64)  # close enough to the 4-group float sums
logm = np.log10(np.maximum(melv, 1e-10)).astype(np.float32)
mel = np.full((n_mels, n_len), np.float32(np.log10(1e-10)), dtype=np.float32)
mel[:, :n_compute] = logm.T
mmax = mel.max() - 8.0
mel = ((np.maximum(mel, np.float32(mmax)).astype(np.float64) + 4.0) / 4.0).astype(np.float32)
mel.tofile(OUT + 'np_mel.f32')

window = np.zeros((n_mels, 3000), dtype=np.float32)
n_take = min(3000, n_len)
window[:, :n_take] = mel[:, :n_take]

# ---- encoder: conv frontend + pre-LN blocks + ln_post, fp16-LUT tanh gelu ----
def gelu_lut(x):
    xr = x.astype(np.float16).astype(np.float32)
    g = 0.5 * xr * (1.0 + np.tanh(np.float32(0.79788456080286535587989211986876) * xr * (1.0 + np.float32(0.044715) * xr * xr)))
    g = g.astype(np.float16).astype(np.float32)
    return np.where(x <= -10.0, np.float32(0.0), np.where(x >= 10.0, x, g)).astype(np.float32)

def conv1d(x, w, b, stride):
    C_in, L = x.shape
    C_out = w.shape[0]
    xp = np.zeros((C_in, L + 2), dtype=np.float32)
    xp[:, 1:L + 1] = x
    OL = L // stride if stride > 1 else L
    cols = np.zeros((OL, C_in * 3), dtype=np.float32)
    for o in range(OL):
        s = o * stride
        cols[o] = xp[:, s:s + 3].reshape(-1)
    wf2 = w.reshape(C_out, C_in * 3)
    return (cols @ wf2.T + b).T.astype(np.float32)

d = n_audio_state
nh = n_audio_head
hs = d // nh
tt_ctx = n_audio_ctx
y1 = gelu_lut(conv1d(window, T['encoder.conv1.weight'], T['encoder.conv1.bias'].reshape(-1), 1))
y2 = gelu_lut(conv1d(y1, T['encoder.conv2.weight'], T['encoder.conv2.bias'].reshape(-1), 2))
x = y2.T + T['encoder.positional_embedding'][:tt_ctx]
x = x.astype(np.float32)
x.tofile(OUT + 'np_after_conv_pos.f32')

def ln(x, w, b, eps=1e-5):
    m = x.mean(axis=-1, keepdims=True)
    v = x.var(axis=-1, keepdims=True)
    return ((x - m) / np.sqrt(v + eps) * w + b).astype(np.float32)

scale = np.float32(1.0 / np.sqrt(hs))
for l in range(n_audio_layer):
    p = f'encoder.blocks.{l}.'
    xb = ln(x, T[p + 'attn_ln.weight'], T[p + 'attn_ln.bias'])
    q = xb @ T[p + 'attn.query.weight'].T + T[p + 'attn.query.bias']
    k = xb @ T[p + 'attn.key.weight'].T
    v = xb @ T[p + 'attn.value.weight'].T + T[p + 'attn.value.bias']
    if l == 0:
        xb.tofile(OUT + 'np_b0_ln1.f32')
        q.astype(np.float32).tofile(OUT + 'np_b0_q.f32')
        k.astype(np.float32).tofile(OUT + 'np_b0_k.f32')
        v.astype(np.float32).tofile(OUT + 'np_b0_v.f32')
    q = q.reshape(tt_ctx, nh, hs).transpose(1, 0, 2)
    k = k.reshape(tt_ctx, nh, hs).transpose(1, 0, 2)
    v = v.reshape(tt_ctx, nh, hs).transpose(1, 0, 2)
    att = (q @ k.transpose(0, 2, 1)) * scale
    att = att - att.max(axis=-1, keepdims=True)
    e = np.exp(att)
    att = e / e.sum(axis=-1, keepdims=True)
    o = (att @ v).transpose(1, 0, 2).reshape(tt_ctx, d).astype(np.float32)
    if l == 0:
        o.tofile(OUT + 'np_b0_attnout.f32')
    x = x + (o @ T[p + 'attn.out.weight'].T + T[p + 'attn.out.bias'])
    xb = ln(x, T[p + 'mlp_ln.weight'], T[p + 'mlp_ln.bias'])
    h = gelu_lut((xb @ T[p + 'mlp.0.weight'].T + T[p + 'mlp.0.bias']).astype(np.float32))
    x = (x + (h @ T[p + 'mlp.2.weight'].T + T[p + 'mlp.2.bias'])).astype(np.float32)
    if l == 0:
        x.tofile(OUT + 'np_after_block0.f32')

x.tofile(OUT + 'np_after_blocks.f32')
enc_out = ln(x, T['encoder.ln_post.weight'], T['encoder.ln_post.bias'])
enc_out.tofile(OUT + 'np_out.f32')
print(f'mel n_len={n_len} n_compute={n_compute} window[0,:4]', window[0, :4])
print('enc_out[0,:8]', ' '.join(f'{v:.6f}' for v in enc_out[0, :8]))
print(f'enc_out stats: mean={enc_out.mean():.6f} std={enc_out.std():.6f} min={enc_out.min():.6f} max={enc_out.max():.6f}')
