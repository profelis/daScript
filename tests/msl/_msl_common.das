options gen2
options indenting = 4

// Shared fixture for the dasMetal MSL test suite (mirrors tests/spirv/_spirv_common.das): the
// Phase-1 [metal_kernel] a*b class whose emitted text the shape, golden, and census tests read,
// plus the declared census — the gate-B contract the fixture union must equal in both directions.
// [marker(no_coverage)] keeps daslib/coverage from instrumenting the kernel body: it is
// compile-time MSL source, not runtime code, and injected coverage nodes are not lowerable.

module _msl_common shared public

require metal/msl_shader public

class MulAB {
    @ssbo @binding = 0 a : array<float>
    @ssbo @binding = 1 b : array<float>
    @ssbo @binding = 2 c : array<float>

    [metal_kernel(name="mul_ab_msl"), marker(no_coverage)]
    def mul_ab {
        let i = gl_GlobalInvocationID.x
        c[i] = a[i] * b[i]
    }
}

//! Gate B: exactly the construct kinds the Phase-1 fixture set must emit — the census meta-test
//! asserts equality with the observed union in both directions.
def public declared_msl_census : table<string> {
    return <- {
        "preamble",
        "kernel_sig",
        "param.buffer",
        "param.buffer_const",
        "param.builtin.thread_position_in_grid",
        "expr.builtin.thread_position_in_grid",
        "expr.var",
        "expr.member",
        "expr.index",
        "expr.swizzle",
        "op.mul.f32",
        "stmt.let",
        "stmt.assign"
    }
}
