options gen2
options indenting = 4

// Host sugar over the das_metal binding (Apple-only — this file requires the C++ module, so
// consumers guard with `require ?das_metal metal/das_metal_boost` + static_if
// builtin_module_exists(das_metal)). v1 covers what the behavioral gate needs: scoped device
// access, the source->pipeline chain with intermediate handles released, a one-line 1D dispatch,
// and the leak assert.

module das_metal_boost shared public

require das_metal public

//! Scoped system-default device: creates, invokes, releases. `dev` is null when the box has no
//! Metal device — the block decides whether that is a skip or a failure.
def public with_metal_device(blk : block<(dev : MetalDevice?) : void>) {
    let dev = metal_create_system_default_device()
    invoke(blk, dev)
    if (dev != null) {
        metal_release(dev)
    }
}

//! MSL source -> compute pipeline (library and function handles released on the way; the pipeline
//! keeps what it needs). Returns null with `error` filled on any failure — including an entry
//! point missing from a successfully compiled library.
def public pipeline_from_source(dev : MetalDevice?; source, entry : string; fastmath : bool; var error : string&) : MetalComputePipeline? {
    let lib = metal_new_library_from_source(dev, source, fastmath, error)
    if (lib == null) {
        return null
    }
    let fn = metal_new_function(lib, entry)
    if (fn == null) {
        metal_release(lib)
        error = "kernel entry point `{entry}` not found in compiled library"
        return null
    }
    var pso = metal_new_compute_pipeline(dev, fn, error)
    metal_release(fn)
    metal_release(lib)
    return pso
}

//! One 1D dispatch: encode pipeline + buffers (bound to [[buffer(0..N-1)]] in array order),
//! dispatch ceil(threads/threads_per_group) threadgroups, commit, wait. Returns false with
//! `error` filled when the command buffer reports a GPU-side failure.
def public run_compute_1d(queue : MetalCommandQueue?; pso : MetalComputePipeline?; buffers : array<MetalBuffer?>; threads, threads_per_group : uint; var error : string&) : bool {
    let cb = metal_new_command_buffer(queue)
    let enc = metal_new_compute_encoder(cb)
    metal_set_pipeline(enc, pso)
    for (buf, index in buffers, range(length(buffers))) {
        metal_set_buffer(enc, buf, 0ul, index)
    }
    let groups = (threads + threads_per_group - 1u) / threads_per_group
    metal_dispatch_threadgroups(enc, uint3(groups, 1u, 1u), uint3(threads_per_group, 1u, 1u))
    metal_end_encoding(enc)
    metal_commit(cb)
    metal_wait_until_completed(cb)
    error = metal_command_buffer_error(cb)
    metal_release(enc)
    metal_release(cb)
    return empty(error)
}

//! The leak gate: call at the end of every tests/metal file — Metal objects are invisible to all
//! six das leak detectors, so the shim-side counter is the only witness.
def public assert_no_metal_leaks {
    let live = metal_live_object_count()
    if (live != 0l) {
        panic("metal_live_object_count() == {live} — every handle must be metal_release()d")
    }
}
