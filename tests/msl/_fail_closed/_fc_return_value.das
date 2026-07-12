// Fail-closed fixture: kernels are void — `return <value>` must be rejected, not dropped.

expect 50501

options gen2

require metal/msl_shader

class FcReturnValue {
    @ssbo @binding = 0 dat : array<int>

    [metal_kernel(name="fc_return_value_msl")]
    def kern : int {
        let i = gl_GlobalInvocationID.x
        dat[i] = 1
        return 7
    }
}
