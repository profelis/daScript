// Fail-closed fixture: a function call in the kernel body is outside the supported subset and
// must be rejected with a clean error (never silently walked over).

expect 50501

options gen2

require metal/msl_shader

def helper(x : int) : int {
    return x + 1
}

class FcCall {
    @ssbo @binding = 0 dat : array<int>

    [metal_kernel(name="fc_call_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        dat[i] = helper(dat[i])
    }
}
