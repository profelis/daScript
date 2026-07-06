import numpy as np
from scipy.special import erf as sperf  # if scipy missing, use vectorized math.erf
from gguf import GGUFReader

OUT = '/private/tmp/claude-501/-Users-borisbatkin-Work-daScript/2cf0cd37-1dc2-4ff3-8b49-8f4e44e398e8/scratchpad/'
r = GGUFReader('/Users/borisbatkin/Work/llama.cpp/models/qwen2audio-mmproj-f32.gguf')
T = {t.name: np.array(t.data).astype(np.float32) for t in r.tensors}

def gelu_erf(x):
    return 0.5 * x * (1.0 + sperf(x / np.sqrt(2.0).astype(np.float32)))

def conv1d(x, w, b, stride):
    # x [C_in, L], w [C_out, C_in, 3], pad 1
    C_in, L = x.shape
    C_out = w.shape[0]
    xp = np.zeros((C_in, L + 2), dtype=np.float32)
    xp[:, 1:L+1] = x
    OL = L // stride if stride > 1 else L
    out = np.zeros((C_out, OL), dtype=np.float32)
    # im2col: [OL, C_in*3]
    cols = np.zeros((OL, C_in * 3), dtype=np.float32)
    for o in range(OL):
        s = o * stride
        cols[o] = xp[:, s:s+3].reshape(-1)  # [C_in,3] -> c-major k-minor
    wf = w.reshape(C_out, C_in * 3)         # [o][c][k] -> same c-major k-minor
    out = cols @ wf.T + b                    # [OL, C_out]
    return out.T  # [C_out, OL]

mel = np.ones((128, 3000), dtype=np.float32)
y1 = gelu_erf(conv1d(mel, T['a.conv1d.1.weight'], T['a.conv1d.1.bias'].reshape(-1), 1))
y2 = gelu_erf(conv1d(y1, T['a.conv1d.2.weight'], T['a.conv1d.2.bias'].reshape(-1), 2))
x = y2.T  # [1500, 1280]
x = x + T['a.position_embd.weight'][:1500]
x.astype(np.float32).tofile(OUT + 'np_after_conv_pos.f32')

def ln(x, w, b, eps=1e-5):
    m = x.mean(axis=-1, keepdims=True)
    v = x.var(axis=-1, keepdims=True)
    return (x - m) / np.sqrt(v + eps) * w + b

n_head, hs = 20, 64
scale = 1.0 / np.sqrt(64.0)
for l in range(32):
    p = f'a.blk.{l}.'
    xb = ln(x, T[p+'ln1.weight'], T[p+'ln1.bias'])
    q = xb @ T[p+'attn_q.weight'].T + T[p+'attn_q.bias']
    k = xb @ T[p+'attn_k.weight'].T
    v = xb @ T[p+'attn_v.weight'].T + T[p+'attn_v.bias']
    q = q.reshape(1500, n_head, hs).transpose(1, 0, 2)
    k = k.reshape(1500, n_head, hs).transpose(1, 0, 2)
    v = v.reshape(1500, n_head, hs).transpose(1, 0, 2)
    att = (q @ k.transpose(0, 2, 1)) * scale
    att = att - att.max(axis=-1, keepdims=True)
    e = np.exp(att)
    att = e / e.sum(axis=-1, keepdims=True)
    o = (att @ v).transpose(1, 0, 2).reshape(1500, 1280)
    x = x + (o @ T[p+'attn_out.weight'].T + T[p+'attn_out.bias'])
    xb = ln(x, T[p+'ln2.weight'], T[p+'ln2.bias'])
    h = gelu_erf(xb @ T[p+'ffn_up.weight'].T + T[p+'ffn_up.bias'])
    x = x + (h @ T[p+'ffn_down.weight'].T + T[p+'ffn_down.bias'])
    if l == 0:
        x.astype(np.float32).tofile(OUT + 'np_after_block0.f32')

x.astype(np.float32).tofile(OUT + 'np_after_blocks.f32')
xp = 0.5 * (x[0::2] + x[1::2])  # [750, 1280]
xp = ln(xp, T['a.post_ln.weight'], T['a.post_ln.bias'])
out = xp @ T['mm.a.fc.weight'].T + T['mm.a.fc.bias']
out.astype(np.float32).tofile(OUT + 'np_out.f32')

print('tok0 first16:', ' '.join(f'{v:.6f}' for v in out[0, :16]))
print(f'stats: mean={out.mean():.6f} std={out.std():.6f} min={out.min():.6f} max={out.max():.6f} sum={out.sum():.3f}')
