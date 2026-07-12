// Fail-closed fixture: simdgroup_store targets @ssbo buffers only — no fixture exercises a
// threadgroup store, so per the census discipline the emitter rejects it rather than shipping
// an untested lowering.

expect 50501

options gen2

require metal/msl_shader

class FcSgmatStoreTg {
    @ssbo @binding = 0 fa : array<float16>
    @ssbo @binding = 1 fc : array<float16>
    @workgroup tile : float16[64]

    [metal_kernel(name="fc_sgmat_store_tg_msl")]
    def kern {
        var m : simdgroup_half8x8
        simdgroup_load(m, fa, 0u, 8u)
        simdgroup_store(m, tile, 0u, 8u)
        let lid = gl_LocalInvocationID.x
        fc[lid] = tile[lid]
    }
}
