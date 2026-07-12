options gen2

module dasllama_math_metal shared public

require dasllama/dasllama_math
require metal/msl_shader
require metal/das_metal_boost

// The Metal GPU prefill-GEMM backend (Phase-5 dasMetal offload experiment): a BATCH-ONLY donor —
// decode GEMV is bandwidth-bound on the same unified memory and stays CPU. Registered at [init]
// with priority -1 so it never wins auto/load-select; it activates only through
// select_batch_backend("metal") (env rail: DASLLAMA_PIN_BATCH_BACKEND). The donor rules of
// apply_batch_override make the full recipe:
//   DASLLAMA_PIN_BACKEND=arm64-sdot   (row-major weights — a repack backend's layout is unreadable here)
//   DASLLAMA_WSCALE_F16=0             (keep the f32 scale plane — the override swaps only the f32 batch slot)
//   DASLLAMA_PIN_BATCH_BACKEND=metal
//
// The kernel is the ggml mul_mm shape: each threadgroup (128 threads = 4 simdgroups) owns a
// 32x32 C block; per 32-k step it dequantizes the Q8 activation and weight blocks into f16
// threadgroup tiles (scale folded in), barriers, and each simdgroup runs its 16x16 quadrant as
// 2x2 8x8 tiles via the MIXED simdgroup mac (f32 accumulators, f16 operands). Dequant-to-half
// carries ggml's tolerance envelope: int8 quants are exact in half, the folded scale product
// rounds — pinned runs compare against CPU within relative tolerance, not bit-exact.
//
// The host driver is self-contained: weight regions upload lazily ON FIRST USE, keyed by the
// region's base address (weights are stable owned arrays after load; the GPU copy doubles their
// unified-memory footprint — an experiment cost, recorded in the masterplan). Activations and
// outputs ride pooled shared-memory buffers, padded to 32-row multiples (the kernel has no edge
// masking — pad activations are zeroed, pad output rows are never read back).

class MetalQ8Gemm {
    @ssbo @binding = 0 wq : array<int8>     // W [d x n] row-major Q8 quants
    @ssbo @binding = 1 ws : array<float>    // W scales [d x n/32]
    @ssbo @binding = 2 xq : array<int8>     // X [M' x n] Q8 quants (M' = 32-padded ntok)
    @ssbo @binding = 3 xs : array<float>    // X scales [M' x n/32]
    @ssbo @binding = 4 y : array<float>     // Y [M' x d]
    @uniform @binding = 5 kdim : uint       // n (K)
    @uniform @binding = 6 ndim : uint       // d (N)
    @workgroup ta : float16[1024]           // A block: 32 tokens x 32 k, dequantized
    @workgroup tb : float16[1024]           // B block: 32 k x 32 outputs, dequantized + transposed

    [metal_kernel(name="metal_q8_gemm_msl")]
    def metal_q8_gemm {
        let lid = gl_LocalInvocationID.x
        let sg = gl_SubgroupID
        let ntileN = ndim / 32u
        let mBase = (gl_WorkGroupID.x / ntileN) * 32u
        let nBase = (gl_WorkGroupID.x % ntileN) * 32u
        let qm = (sg / 2u) * 16u            // this simdgroup's 16x16 quadrant of the C block
        let qn = (sg % 2u) * 16u
        var c00 : simdgroup_float8x8
        var c01 : simdgroup_float8x8
        var c10 : simdgroup_float8x8
        var c11 : simdgroup_float8x8
        var kb = 0u
        while (kb * 32u < kdim) {
            var e = lid                     // stage 2x1024 tile elements, 8 per thread
            while (e < 1024u) {
                let r = e / 32u
                let c = e % 32u
                let k = kb * 32u + c
                ta[e] = float16(float(xq[(mBase + r) * kdim + k]) * xs[(mBase + r) * (kdim / 32u) + kb])
                tb[c * 32u + r] = float16(float(wq[(nBase + r) * kdim + k]) * ws[(nBase + r) * (kdim / 32u) + kb])
                e += 128u
            }
            barrier()
            var k8 = 0u
            while (k8 < 32u) {
                var a0 : simdgroup_half8x8
                var a1 : simdgroup_half8x8
                var b0 : simdgroup_half8x8
                var b1 : simdgroup_half8x8
                simdgroup_load(a0, ta, qm * 32u + k8, 32u)
                simdgroup_load(a1, ta, (qm + 8u) * 32u + k8, 32u)
                simdgroup_load(b0, tb, k8 * 32u + qn, 32u)
                simdgroup_load(b1, tb, k8 * 32u + (qn + 8u), 32u)
                simdgroup_multiply_accumulate(c00, a0, b0, c00)
                simdgroup_multiply_accumulate(c01, a0, b1, c01)
                simdgroup_multiply_accumulate(c10, a1, b0, c10)
                simdgroup_multiply_accumulate(c11, a1, b1, c11)
                k8 += 8u
            }
            barrier()
            kb++
        }
        let row0 = mBase + qm
        let col0 = nBase + qn
        simdgroup_store(c00, y, row0 * ndim + col0, ndim)
        simdgroup_store(c01, y, row0 * ndim + (col0 + 8u), ndim)
        simdgroup_store(c10, y, (row0 + 8u) * ndim + col0, ndim)
        simdgroup_store(c11, y, (row0 + 8u) * ndim + (col0 + 8u), ndim)
    }
}

// ===== host driver =====

var private g_dev : MetalDevice?
var private g_queue : MetalCommandQueue?
var private g_pso : MetalComputePipeline?
var private g_failed = false
var private g_wbufs : table<uint64; MetalBuffer?>   // intptr(region base) -> lazily uploaded weights
var private g_sbufs : table<uint64; MetalBuffer?>   // intptr(region base) -> lazily uploaded scales
var private g_pool : MetalBufferPool
var private g_min_ntok = 32l
var private g_dispatches = 0l
var private g_fallbacks = 0l

//! Batches below this token count delegate to the CPU portable batch kernel (GPU submit
//! overhead outweighs the work). Set 1 to force every pinned batch onto the GPU (tests).
def public set_metal_gemm_min_ntok(v : int64) {
    g_min_ntok = v
}

//! (gpu dispatches, cpu fallbacks) since load — diagnostics / tests.
def public metal_gemm_stats() : tuple<dispatches : int64; fallbacks : int64> {
    return (dispatches = g_dispatches, fallbacks = g_fallbacks)
}

//! Release every GPU object the driver holds (weight caches, pools, pipeline, queue, device) —
//! the tests' leak-gate rail. The next pinned dispatch re-initializes lazily.
def public metal_gemm_shutdown {
    for (buf in values(g_wbufs)) {
        if (buf != null) {
            metal_release(buf)
        }
        buf = null
    }
    unsafe {
        delete g_wbufs
    }
    for (buf in values(g_sbufs)) {
        if (buf != null) {
            metal_release(buf)
        }
        buf = null
    }
    unsafe {
        delete g_sbufs
    }
    pool_drain(g_pool)
    if (g_pso != null) {
        metal_release(g_pso)
        g_pso = null
    }
    if (g_queue != null) {
        metal_release(g_queue)
        g_queue = null
    }
    if (g_dev != null) {
        metal_release(g_dev)
        g_dev = null
    }
    g_failed = false
}

def private metal_gemm_init : bool {
    if (g_pso != null) {
        return true
    }
    if (g_failed) {
        return false
    }
    g_dev = metal_create_system_default_device()
    if (g_dev == null) {
        to_log(LOG_WARNING, "dasLLAMA metal: no Metal device — batch pin falls back to the portable CPU kernel\n")
        g_failed = true
        return false
    }
    g_queue = metal_new_command_queue(g_dev)
    var err : string
    g_pso = pipeline_from_source(g_dev, metal_q8_gemm_msl, metal_q8_gemm_msl_entry, metal_q8_gemm_msl_fastmath, err)
    if (g_pso == null) {
        to_log(LOG_ERROR, "dasLLAMA metal: kernel compile failed — {err}\n")
        metal_release(g_queue)
        g_queue = null
        metal_release(g_dev)
        g_dev = null
        g_failed = true
        return false
    }
    to_log(LOG_INFO, "dasLLAMA metal: GEMM offload live on {metal_device_name(g_dev)}\n")
    return true
}

// lazily upload one stable weight/scale region, keyed by its base address (post-load weight
// arrays never move; the reinterpret is address math only — nothing writes through it)
def private upload_region(var tab : table<uint64; MetalBuffer?>; src : void?; bytes : uint64) : MetalBuffer? {
    let key = intptr(src)
    if (key_exists(tab, key)) {
        return tab[key]
    }
    var buf = metal_new_buffer(g_dev, bytes)
    unsafe {
        memcpy(metal_buffer_contents(buf), src, int(bytes))
    }
    tab[key] = buf
    return buf
}

// one pooled 4-byte uniform buffer holding a uint
def private uniform_u32(v : uint) : MetalBuffer? {
    var buf = pool_acquire(g_pool, g_dev, 4ul)
    var p = unsafe(reinterpret<uint?>(metal_buffer_contents(buf)))
    unsafe(p[0]) = v
    return buf
}

//! The batch slot (MatmulQ8Q8BatchFn): y[ntok x d] = X[ntok x n] . W[d x n]^T on the GPU.
//! Small/odd shapes delegate to the portable CPU batch kernel; any GPU-side init failure
//! degrades to the same fallback (logged once).
def metal_q8q8_batch(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    if (ntok < g_min_ntok || (n % 32l) != 0l || (d % 32l) != 0l || !metal_gemm_init()) {
        g_fallbacks++
        let cpu = kernel_backend_batch_fn("portable")
        invoke(cpu, yp, wp, sp, xqp, xsp, n, d, ntok)
        return
    }
    let nb = n / 32l
    let mp = ((ntok + 31l) / 32l) * 32l     // kernel has no edge masking — pad M to 32 rows
    var wbuf = upload_region(g_wbufs, unsafe(reinterpret<void?>(wp)), uint64(d * n))
    var sbuf = upload_region(g_sbufs, unsafe(reinterpret<void?>(sp)), uint64(d * nb * 4l))
    var xqbuf = pool_acquire(g_pool, g_dev, uint64(mp * n))
    var xsbuf = pool_acquire(g_pool, g_dev, uint64(mp * nb * 4l))
    var ybuf = pool_acquire(g_pool, g_dev, uint64(mp * d * 4l))
    unsafe {
        var pq = reinterpret<uint8?>(metal_buffer_contents(xqbuf))
        memcpy(reinterpret<void?>(pq), reinterpret<void?>(xqp), int(ntok * n))
        memset8(reinterpret<void?>(pq + ntok * n), uint8(0), int((mp - ntok) * n))
        var ps = reinterpret<uint8?>(metal_buffer_contents(xsbuf))
        memcpy(reinterpret<void?>(ps), reinterpret<void?>(xsp), int(ntok * nb * 4l))
        memset8(reinterpret<void?>(ps + ntok * nb * 4l), uint8(0), int((mp - ntok) * nb * 4l))
    }
    var kdimbuf = uniform_u32(uint(n))
    var ndimbuf = uniform_u32(uint(d))
    var err : string
    let groups = uint((mp / 32l) * (d / 32l))
    let ran = with_compute_encoder(g_queue, err) $(enc : MetalComputeEncoder?) {
        metal_set_pipeline(enc, g_pso)
        metal_set_buffer(enc, wbuf, 0ul, 0)
        metal_set_buffer(enc, sbuf, 0ul, 1)
        metal_set_buffer(enc, xqbuf, 0ul, 2)
        metal_set_buffer(enc, xsbuf, 0ul, 3)
        metal_set_buffer(enc, ybuf, 0ul, 4)
        metal_set_buffer(enc, kdimbuf, 0ul, 5)
        metal_set_buffer(enc, ndimbuf, 0ul, 6)
        metal_dispatch_threadgroups(enc, uint3(groups, 1u, 1u), uint3(128u, 1u, 1u))
    }
    if (ran) {
        unsafe {
            memcpy(reinterpret<void?>(yp), metal_buffer_contents(ybuf), int(ntok * d * 4l))
        }
        g_dispatches++
    } else {
        to_log(LOG_ERROR, "dasLLAMA metal: dispatch failed ({err}) — falling back to the portable CPU kernel\n")
        g_fallbacks++
        let cpu = kernel_backend_batch_fn("portable")
        invoke(cpu, yp, wp, sp, xqp, xsp, n, d, ntok)
    }
    pool_release(g_pool, xqbuf, uint64(mp * n))
    pool_release(g_pool, xsbuf, uint64(mp * nb * 4l))
    pool_release(g_pool, ybuf, uint64(mp * d * 4l))
    pool_release(g_pool, kdimbuf, 4ul)
    pool_release(g_pool, ndimbuf, 4ul)
}

// ===== registration =====

def private metal_backend_available : bool {
    if (g_pso != null) {
        return true
    }
    if (g_failed) {
        return false
    }
    let dev = metal_create_system_default_device()
    if (dev == null) {
        return false
    }
    metal_release(dev)
    return true
}

[unused_argument(yp, wp, sp, xqp, xsp, n, d)]
def private metal_no_gemv(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    panic("dasLLAMA metal backend is batch-only — pin it via DASLLAMA_PIN_BATCH_BACKEND=metal, never as the whole backend")
}

[unused_argument(y0p, y1p, y2p, wp, sp, woff0, woff1, woff2, xqp, xsp, n, d0, d1, d2)]
def private metal_no_group3(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?; woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    panic("dasLLAMA metal backend is batch-only — pin it via DASLLAMA_PIN_BATCH_BACKEND=metal, never as the whole backend")
}

[unused_argument(wp, sp, n, d)]
def private metal_repack_noop(var wp : int8?; var sp : float?; n, d : int64) {}

[init]
def dasllama_math_metal_register() {
    // priority -1: never wins auto- or load-select (even registering first); reachable only by
    // name — select_batch_backend("metal") — with the device probe as the availability witness
    register_kernel_backend(KernelBackend(name = "metal", mm = @@metal_no_gemv, batch = @@metal_q8q8_batch,
        group3 = @@metal_no_group3, repack = @@metal_repack_noop,
        needs_repack = false, priority = -1, available = @@metal_backend_available))
}
