// Fail-closed fixture: reaching into a simdgroup matrix's `.data` inside a kernel must be
// rejected — on GPU the tile is an opaque hardware type with no elementwise access; the
// reference field exists only for the CPU replay.

expect 50501

options gen2

require metal/msl_shader

class FcSgmatField {
    @ssbo @binding = 0 fa : array<float>
    @ssbo @binding = 1 fc : array<float>

    [metal_kernel(name="fc_sgmat_field_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        var m : simdgroup_float8x8
        simdgroup_load(m, fa, 0u, 8u)
        fc[i] = m.data[0]
    }
}
