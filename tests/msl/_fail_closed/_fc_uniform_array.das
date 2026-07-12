// Fail-closed fixture: @uniform on an array member must be rejected — array members are @ssbo
// buffers; @uniform is for scalar/vector values.

expect 50501

options gen2

require metal/msl_shader

class FcUniformArray {
    @uniform @binding = 0 xs : array<float>
    @ssbo @binding = 1 dat : array<float>

    [metal_kernel(name="fc_uniform_array_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        dat[i] = xs[i]
    }
}
