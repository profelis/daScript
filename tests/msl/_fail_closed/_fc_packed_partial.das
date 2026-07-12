// Fail-closed fixture: a component write into a packed 3-lane buffer element must be rejected —
// the packed_T3 lvalue has no sound component-store lowering; assign the whole element.

expect 50501

options gen2

require metal/msl_shader

class FcPackedPartial {
    @ssbo @binding = 0 pos : array<float3>

    [metal_kernel(name="fc_packed_partial_msl")]
    def kern {
        let i = gl_GlobalInvocationID.x
        pos[i].x = 1.0
    }
}
