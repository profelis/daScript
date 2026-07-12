options gen2

module dasllama_metal_prefill shared public

require math
require metal/msl_shader

// Phase-6 dasMetal: the full-GPU-resident prefill kernel set — everything between the Q8 GEMMs
// that Phase 5c left on the CPU: activation requant, rmsnorm, table-driven NORM RoPE, fused
// causal-softmax attention scores, the P·V gather, fused SwiGLU, and the residual add. Each
// kernel mirrors its dasLLAMA CPU twin's math exactly (same formula, same rounding ops):
//   metal_q8_quant      ~ quantize_q8_0_into_ptr   (amax/127 scale, round-half-away quants)
//   metal_rmsnorm       ~ rmsnorm                  (w[i] * x[i] * rsqrt(mean(x^2) + eps))
//   metal_rope          ~ rope_scaled_tab          (NORM adjacent pairs; cos/sin table rows)
//   metal_attn_scores   ~ the classic per-head causal scores + softmax (start_pos = 0 prefill)
//   metal_attn_av       ~ the per-head P·V accumulation into xb
//   metal_swiglu        ~ swiglu                   (g = g/(1+exp(-g)) * u)
//   metal_add           ~ add_inplace
// Reductions ride simd_sum / a max butterfly over simd_shuffle_xor with hardcoded masks 16..1 —
// Apple-GPU simdgroups are width 32 (asserted at driver init). Kernels with barriers/simd ops are
// NOT sequentially CPU-replayable; their oracles are the dasLLAMA CPU functions themselves
// (tests/dasLLAMA/test_metal_prefill_kernels.das).

// One thread per 32-element block of one activation row: amax -> d = amax/127 -> q = round(x*id).
// Grid covers ntok*(n/32) blocks (uniform nblk guards the ceil-padded dispatch); pad rows of the
// resident xq/xs image are never written here — the GEMM's C-block row independence keeps stale
// pad rows out of every live output row.
class MetalQ8Quant {
    @ssbo @binding = 0 x : array<float>     // [ntok x n] activations
    @ssbo @binding = 1 xq : array<int8>     // [mp x n] quants (live rows only)
    @ssbo @binding = 2 xs : array<float>    // [mp x n/32] scales (live rows only)
    @uniform @binding = 3 n : uint          // row width, % 32
    @uniform @binding = 4 nblk : uint       // ntok * n/32 — grid guard

    [metal_kernel(name="metal_q8_quant_msl")]
    def metal_q8_quant {
        let gid = gl_GlobalInvocationID.x
        if (gid >= nblk) {
            return
        }
        let nb = n / 32u
        let row = gid / nb
        let cb = gid % nb
        let base = row * n + cb * 32u
        var amax = 0.0
        var k = 0u
        while (k < 32u) {
            amax = max(amax, abs(x[base + k]))
            k++
        }
        let d = amax / 127.0
        let id = d != 0.0 ? 1.0 / d : 0.0
        xs[row * nb + cb] = d
        k = 0u
        while (k < 32u) {
            xq[base + k] = int8(round(x[base + k] * id))
            k++
        }
    }
}

// One threadgroup per row: cooperative sum of squares (simd_sum + per-simdgroup partials),
// lane 0 folds partials into rsqrt(mean + eps), every thread scales its strided slice.
class MetalRmsNorm {
    @ssbo @binding = 0 x : array<float>     // [nrows x dim] source
    @ssbo @binding = 1 w : array<float>     // [dim] weight
    @ssbo @binding = 2 y : array<float>     // [nrows x dim] out (x aliasing is safe: x is fully
                                            // read before the barrier that precedes any write)
    @uniform @binding = 3 dim : uint
    @uniform @binding = 4 eps : float
    @workgroup partial : float[8]           // one per simdgroup (256 threads / width 32)
    @workgroup inv_sh : float

    [metal_kernel(name="metal_rmsnorm_msl")]
    def metal_rmsnorm {
        let row = gl_WorkGroupID.x
        let lid = gl_LocalInvocationID.x
        var ss = 0.0
        var k = lid
        while (k < dim) {
            let vv = x[row * dim + k]
            ss += vv * vv
            k += gl_WorkGroupSize.x
        }
        ss = simd_sum(ss)
        if (gl_SubgroupInvocationID == 0u) {
            partial[gl_SubgroupID] = ss
        }
        barrier()
        if (lid == 0u) {
            var tot = 0.0
            var sgi = 0u
            while (sgi < gl_NumSubgroups) {
                tot += partial[sgi]
                sgi++
            }
            inv_sh = rsqrt(tot / float(dim) + eps)
        }
        barrier()
        let inv = inv_sh
        k = lid
        while (k < dim) {
            y[row * dim + k] = w[k] * (x[row * dim + k] * inv)
            k += gl_WorkGroupSize.x
        }
    }
}

// One thread per rotation pair, NORM layout (adjacent elements 2j, 2j+1 within each head):
// v0*c - v1*s / v0*s + v1*c with this position's precomputed table row — rope_scaled_tab exactly.
// One kernel serves q (n = qd) and k (n = kv_dim) as two dispatches.
class MetalRope {
    @ssbo @binding = 0 v : array<float>     // [ntok x n], roped in place
    @ssbo @binding = 1 tcos : array<float>  // [ntok x head_size/2]
    @ssbo @binding = 2 tsin : array<float>
    @uniform @binding = 3 n : uint          // row width (qd or kv_dim), % head_size
    @uniform @binding = 4 head_size : uint
    @uniform @binding = 5 npairs : uint     // ntok * n/2 — grid guard

    [metal_kernel(name="metal_rope_msl")]
    def metal_rope {
        let gid = gl_GlobalInvocationID.x
        if (gid >= npairs) {
            return
        }
        let pairs_per_row = n / 2u
        let p = gid / pairs_per_row
        let rem = gid % pairs_per_row
        let half = head_size / 2u
        let h = rem / half
        let j = rem % half
        let i = p * n + h * head_size + 2u * j
        let fcr = tcos[p * half + j]
        let fci = tsin[p * half + j]
        let v0 = v[i]
        let v1 = v[i + 1u]
        v[i] = v0 * fcr - v1 * fci
        v[i + 1u] = v0 * fci + v1 * fcr
    }
}

// One threadgroup (128 threads = 4 simdgroups) per (query row, head): causal scores
// s_j = scale * q_i . k_j for j in [0, qi], then an in-row softmax — max via a simd butterfly
// (width-32 masks) + threadgroup partials, exp and sum likewise, normalize in place. GQA: head h
// reads kv head h / kv_mul. start_pos = 0 by driver contract (fresh prefill), so cnt = qi + 1.
class MetalAttnScores {
    @ssbo @binding = 0 q : array<float>     // [ntok x qd], roped
    @ssbo @binding = 1 k : array<float>     // [ntok x kv_dim], roped
    @ssbo @binding = 2 att : array<float>   // [n_heads x ntok x ntok] P, normalized rows
    @uniform @binding = 3 qd : uint
    @uniform @binding = 4 kv_dim : uint
    @uniform @binding = 5 head_size : uint
    @uniform @binding = 6 kv_mul : uint
    @uniform @binding = 7 npos : uint
    @uniform @binding = 8 scale : float
    @workgroup red : float[4]               // one per simdgroup
    @workgroup bcast : float

    [metal_kernel(name="metal_attn_scores_msl")]
    def metal_attn_scores {
        let qi = gl_WorkGroupID.x
        let h = gl_WorkGroupID.y
        let lid = gl_LocalInvocationID.x
        let nthreads = gl_WorkGroupSize.x
        let cnt = qi + 1u
        let qoff = qi * qd + h * head_size
        let kvhoff = (h / kv_mul) * head_size
        let rowbase = (h * npos + qi) * npos
        // scores + per-lane running max
        var m = -1.0e30
        var j = lid
        while (j < cnt) {
            var dot = 0.0
            var d = 0u
            while (d < head_size) {
                dot += q[qoff + d] * k[j * kv_dim + kvhoff + d]
                d++
            }
            let sc = dot * scale
            att[rowbase + j] = sc
            m = max(m, sc)
            j += nthreads
        }
        // row max: butterfly within each simdgroup, threadgroup fold across the 4
        m = max(m, simd_shuffle_xor(m, 16u))
        m = max(m, simd_shuffle_xor(m, 8u))
        m = max(m, simd_shuffle_xor(m, 4u))
        m = max(m, simd_shuffle_xor(m, 2u))
        m = max(m, simd_shuffle_xor(m, 1u))
        if (gl_SubgroupInvocationID == 0u) {
            red[gl_SubgroupID] = m
        }
        barrier()
        if (lid == 0u) {
            var mm = red[0]
            var sgi = 1u
            while (sgi < gl_NumSubgroups) {
                mm = max(mm, red[sgi])
                sgi++
            }
            bcast = mm
        }
        barrier()
        let rowmax = bcast
        // exp pass + per-lane sum
        var sum = 0.0
        j = lid
        while (j < cnt) {
            let e = exp(att[rowbase + j] - rowmax)
            att[rowbase + j] = e
            sum += e
            j += nthreads
        }
        sum = simd_sum(sum)
        if (gl_SubgroupInvocationID == 0u) {
            red[gl_SubgroupID] = sum
        }
        barrier()
        if (lid == 0u) {
            var tot = 0.0
            var sgi = 0u
            while (sgi < gl_NumSubgroups) {
                tot += red[sgi]
                sgi++
            }
            bcast = 1.0 / tot
        }
        barrier()
        let inv = bcast
        j = lid
        while (j < cnt) {
            att[rowbase + j] *= inv
            j += nthreads
        }
    }
}

// One threadgroup per (query row, head), one thread per head dimension: xb element = the
// P-weighted sum of cached V rows (raw, never roped). Same GQA mapping as the scores kernel.
class MetalAttnAV {
    @ssbo @binding = 0 att : array<float>   // [n_heads x ntok x ntok] normalized P
    @ssbo @binding = 1 v : array<float>     // [ntok x kv_dim] raw V
    @ssbo @binding = 2 xb : array<float>    // [ntok x qd] attention output
    @uniform @binding = 3 qd : uint
    @uniform @binding = 4 kv_dim : uint
    @uniform @binding = 5 head_size : uint
    @uniform @binding = 6 kv_mul : uint
    @uniform @binding = 7 npos : uint

    [metal_kernel(name="metal_attn_av_msl")]
    def metal_attn_av {
        let qi = gl_WorkGroupID.x
        let h = gl_WorkGroupID.y
        let d = gl_LocalInvocationID.x
        if (d >= head_size) {
            return
        }
        let cnt = qi + 1u
        let rowbase = (h * npos + qi) * npos
        let kvhoff = (h / kv_mul) * head_size
        var acc = 0.0
        var j = 0u
        while (j < cnt) {
            acc += att[rowbase + j] * v[j * kv_dim + kvhoff + d]
            j++
        }
        xb[qi * qd + h * head_size + d] = acc
    }
}

// Fused SwiGLU gate, one thread per element: g = silu(g) * u — swiglu exactly (the CPU side's
// exp4 polynomial vs the GPU exp differ inside the shared tolerance envelope).
class MetalSwiglu {
    @ssbo @binding = 0 g : array<float>     // [ntok x hidden] W1 gate, in place
    @ssbo @binding = 1 u : array<float>     // [ntok x hidden] W3 up
    @uniform @binding = 2 total : uint      // ntok * hidden — grid guard

    [metal_kernel(name="metal_swiglu_msl")]
    def metal_swiglu {
        let gid = gl_GlobalInvocationID.x
        if (gid >= total) {
            return
        }
        let vv = g[gid]
        g[gid] = (vv / (1.0 + exp(-vv))) * u[gid]
    }
}

// Residual add, one thread per element: x += y (add_inplace).
class MetalAdd {
    @ssbo @binding = 0 x : array<float>
    @ssbo @binding = 1 y : array<float>
    @uniform @binding = 2 total : uint      // grid guard

    [metal_kernel(name="metal_add_msl")]
    def metal_add {
        let gid = gl_GlobalInvocationID.x
        if (gid >= total) {
            return
        }
        x[gid] += y[gid]
    }
}
