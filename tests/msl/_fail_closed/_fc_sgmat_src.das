// Fail-closed fixture: simdgroup_load's buffer argument must be an @ssbo or @workgroup member —
// another matrix's reference `.data` is a das-legal fixed-array source for the CPU body, but has
// no device/threadgroup pointer on the GPU side.

expect 50501

options gen2

require metal/msl_shader

class FcSgmatSrc {
    @ssbo @binding = 0 fa : array<float>
    @ssbo @binding = 1 fc : array<float>

    [metal_kernel(name="fc_sgmat_src_msl")]
    def kern {
        var m : simdgroup_float8x8
        var m2 : simdgroup_float8x8
        simdgroup_load(m2, fa, 0u, 8u)
        simdgroup_load(m, m2.data, 0u, 8u)
        simdgroup_store(m, fc, 0u, 8u)
    }
}
