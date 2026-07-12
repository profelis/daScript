// Fail-closed fixture: @workgroup with @binding must be rejected — threadgroup memory is a
// kernel-body declaration, not a bindable buffer.

expect 50501

options gen2

require metal/msl_shader

class FcWgBinding {
    @ssbo @binding = 0 dat : array<uint>
    @workgroup @binding = 1 tile : uint[64]

    [metal_kernel(name="fc_wg_binding_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        dat[i] = tile[i & 63u]
    }
}
