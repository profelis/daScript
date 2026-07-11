// Fail-closed fixture: writing an @uniform member must be rejected (uniforms live in the
// constant address space — outputs are @ssbo buffers).

expect 50501

options gen2

require metal/msl_shader

class FcUniformWritten {
    @ssbo @binding = 0 dat : array<uint>
    @uniform @binding = 1 n : uint

    [metal_kernel(name="fc_uniform_written_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        n += dat[i]
    }
}
