// Fail-closed fixture: @workgroup must be a scalar, vector, or single-dimension fixed array of
// those — a dynamic array<T> has no threadgroup form.

expect 50501

options gen2

require metal/msl_shader

class FcWgType {
    @ssbo @binding = 0 dat : array<uint>
    @workgroup tile : array<uint>

    [metal_kernel(name="fc_wg_type_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        dat[i] = tile[i]
    }
}
