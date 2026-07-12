// Fail-closed fixture: a simdgroup matrix is thread-storage only — an @ssbo buffer of tiles has
// no MSL element form and must be rejected.

expect 50501

options gen2

require metal/msl_shader

class FcSgmatMember {
    @ssbo @binding = 0 tiles : array<simdgroup_float8x8>
    @ssbo @binding = 1 fc : array<float>

    [metal_kernel(name="fc_sgmat_member_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        fc[i] = tiles[i].data[0]
    }
}
