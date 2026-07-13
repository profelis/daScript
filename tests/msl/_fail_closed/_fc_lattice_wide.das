// Fail-closed fixture: an @ssbo buffer of an 8/16-lane lattice element (half8, byte16, ...)
// must be rejected with the dedicated CPU-only diagnostic — shader vectors cap at 4 lanes.

expect 50501

options gen2

require metal/msl_shader

class FcLatticeWide {
    @ssbo @binding = 0 src : array<half8>
    @ssbo @binding = 1 dst : array<half8>

    [metal_kernel(name="fc_lattice_wide_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        dst[i] = src[i]
    }
}
