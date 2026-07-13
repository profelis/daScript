// Fail-closed fixture: a LOCAL of an 8/16-lane lattice type must be rejected with the dedicated
// CPU-only diagnostic (same gate as buffer elements — shader vectors cap at 4 lanes).

expect 50501

options gen2

require metal/msl_shader

class FcLatticeWideLocal {
    @ssbo @binding = 0 src : array<uint>
    @ssbo @binding = 1 dst : array<uint>

    [metal_kernel(name="fc_lattice_wide_local_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        var t : short8
        dst[i] = src[i]
    }
}
