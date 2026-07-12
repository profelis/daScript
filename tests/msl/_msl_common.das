options gen2
options indenting = 4

// Shared fixture for the dasMetal MSL test suite (mirrors tests/spirv/_spirv_common.das): the
// [metal_kernel] fixture classes whose emitted text the shape, golden, and census tests read,
// plus the declared census — the gate-B contract the fixture union must equal in both directions.
// [marker(no_coverage)] keeps daslib/coverage from instrumenting the kernel bodies: they are
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

// Phase-2 arithmetic: one class per scalar class so every opcode flavor is asserted per type
class UArith {
    @ssbo @binding = 0 a : array<uint>
    @ssbo @binding = 1 b : array<uint>
    @ssbo @binding = 2 c : array<uint>
    @ssbo @binding = 3 d : array<uint>

    [metal_kernel(name="uarith_msl"), marker(no_coverage)]
    def uarith {
        let i = gl_GlobalInvocationID.x
        let x = a[i]
        let y = b[i] | 1u
        c[i] = ((x + y) - (x * y)) + ((x / y) + (x % y))
        d[i] = ((x & y) | (x ^ y)) + ((~x) + ((x << 2u) >> 1u))
    }
}

class IArith {
    @ssbo @binding = 0 a : array<int>
    @ssbo @binding = 1 b : array<int>
    @ssbo @binding = 2 c : array<int>
    @ssbo @binding = 3 d : array<int>

    [metal_kernel(name="iarith_msl"), marker(no_coverage)]
    def iarith {
        let i = gl_GlobalInvocationID.x
        let x = a[i]
        let y = b[i] | 1
        c[i] = (((x + y) - (x * y)) + ((x / y) + (x % y))) + (-x)
        d[i] = ((x & y) | (x ^ y)) + ((~x) + ((x << 2) >> 1))
    }
}

class FArith {
    @ssbo @binding = 0 a : array<float>
    @ssbo @binding = 1 b : array<float>
    @ssbo @binding = 2 c : array<float>

    [metal_kernel(name="farith_msl"), marker(no_coverage)]
    def farith {
        let i = gl_GlobalInvocationID.x
        let x = a[i]
        let y = b[i] + 1.5
        c[i] = ((((x + y) - (x * y)) + (x / y)) + (x % y)) + (-x)
    }
}

// Phase-2 vector arithmetic: componentwise float4/int2 infix, vector<op>scalar broadcast, vector
// negate, and das's scalar-bool vector ==/!= (lowered via all()/any())
class VecArith {
    @ssbo @binding = 0 fa : array<float4>
    @ssbo @binding = 1 fb : array<float4>
    @ssbo @binding = 2 fc : array<float4>
    @ssbo @binding = 3 ia : array<int2>
    @ssbo @binding = 4 ib : array<int2>
    @ssbo @binding = 5 flags : array<int>

    [metal_kernel(name="vecarith_msl"), marker(no_coverage)]
    def vecarith {
        let i = gl_GlobalInvocationID.x
        let u = fa[i]
        let v = fb[i] * 0.5
        fc[i] = (((u + v) - (u * v)) + (u / v)) + ((u * 2.0) + (-u))
        let p = ia[i]
        let q = ib[i]
        flags[i] = (p == q) ? 1 : ((((p + q) - (p * q)) != q) ? 2 : 3)
    }
}

// Phase-2 control flow: mutable + zero-init locals, compound assignment (arithmetic + bitwise),
// ++/--, every comparison flavor per scalar class, logical &&/||/!, if/elif/else, ternary
class Control {
    @ssbo @binding = 0 a : array<uint>
    @ssbo @binding = 1 b : array<uint>
    @ssbo @binding = 2 p : array<int>
    @ssbo @binding = 3 q : array<int>
    @ssbo @binding = 4 f : array<float>
    @ssbo @binding = 5 g : array<float>
    @ssbo @binding = 6 out1 : array<uint>
    @ssbo @binding = 7 out2 : array<int>
    @ssbo @binding = 8 out3 : array<float>

    [metal_kernel(name="control_msl"), marker(no_coverage)]
    def control {
        let i = gl_GlobalInvocationID.x
        let x = a[i]
        let y = b[i]
        var acc = 0u
        var zed : uint
        var hot = false
        if (x > y && x != 0u) {
            acc += x
            hot = true
        } elif (x < y || y >= 8u) {
            acc -= x
        } else {
            acc *= 3u
        }
        if (x <= y) {
            acc /= 2u
            acc %= 101u
        }
        if (x == y) {
            acc |= 1u
            acc &= 255u
            acc ^= 129u
            acc <<= 1u
            acc >>= 1u
        }
        acc++
        ++acc
        acc--
        --acc
        let snap = acc++     // value-level postfix survives as postfix (statement-level arrives prefix)
        let dnap = acc--
        zed += (acc + snap) + dnap
        out1[i] = hot ? zed : (zed + 7u)
        let m = p[i]
        let w = q[i]
        var iacc = 0
        if (m > w) {
            iacc += 9
        }
        if (m < w) {
            iacc += 2
        }
        if (m >= w) {
            iacc += 3
        }
        if (m <= w) {
            iacc += 4
        }
        if (m == w) {
            iacc += 5
        }
        if (m != w) {
            iacc += 6
        }
        out2[i] = (!(m > w)) ? iacc : (-iacc)
        let s = f[i]
        let z = g[i]
        var facc = 1.0
        if (s > z) {
            facc += 2.0
        }
        if (s < z) {
            facc += 4.0
        }
        if (s >= z) {
            facc *= 2.0
        }
        if (s <= z) {
            facc += 8.0
        }
        if (s == z) {
            facc += 16.0
        }
        if (s != z) {
            facc += 32.0
        }
        out3[i] = facc
    }
}

// Phase-2 loops + the non-exact-grid bounds guard: @uniform scalar, early return, while with
// break/continue, constant range-for, dynamic-end range-for (das evaluates range endpoints once —
// the emitter hoists the end into a loop-scoped local, proven here by mutating `s` in the body),
// and a urange loop over the uniform
class Loops {
    @ssbo @binding = 0 src : array<int>
    @ssbo @binding = 1 dst : array<int>
    @uniform @binding = 2 n : uint
    @ssbo @binding = 3 udst : array<uint>

    [metal_kernel(name="loops_msl"), marker(no_coverage)]
    def loops {
        let i = gl_GlobalInvocationID.x
        if (i >= n) {
            return
        }
        var s = 0
        var j = 0
        while (j < 100) {
            j++
            if (j == 3) {
                continue
            }
            if (j >= 7) {
                break
            }
            s += j
        }
        for (k in range(4)) {
            s += k * src[i]
        }
        for (_k in range(0, s)) {
            s++
        }
        dst[i] = s
        var usum = 0u
        for (ku in urange(n)) {
            usum += ku
        }
        udst[i] = usum
    }
}

// Phase-3 threadgroup memory + barriers: @workgroup members (fixed array + scalar) lower to
// threadgroup declarations at the top of the kernel body; barrier() and memoryBarrierShared()
// both lower to threadgroup_barrier(mem_flags::mem_threadgroup) — MSL has no execution-free
// threadgroup fence; and the five workgroup-grid builtins lower to attributed parameters
class Reduce {
    @ssbo @binding = 0 src : array<uint>
    @ssbo @binding = 1 dst : array<uint>
    @workgroup tile : uint[64]
    @workgroup total : uint

    [metal_kernel(name="reduce_msl"), marker(no_coverage)]
    def reduce {
        let gid = gl_GlobalInvocationID.x
        let lid = gl_LocalInvocationID.x
        tile[lid] = src[gid]
        barrier()
        var s = gl_WorkGroupSize.x / 2u
        while (s > 0u) {
            if (lid < s) {
                tile[lid] += tile[lid + s]
            }
            barrier()
            s /= 2u
        }
        if (gl_LocalInvocationIndex == 0u) {
            total = tile[0] + (gl_NumWorkGroups.x * 0u)
            memoryBarrierShared()
            dst[gl_WorkGroupID.x] = total
        }
    }
}

// Phase-3 simdgroup intrinsics: the four simdgroup builtins and all fifteen simd_* overloads
// (sum + the four shuffles, each for float/int/uint)
class Simd {
    @ssbo @binding = 0 fa : array<float>
    @ssbo @binding = 1 ia : array<int>
    @ssbo @binding = 2 ua : array<uint>
    @ssbo @binding = 3 fo : array<float>
    @ssbo @binding = 4 io : array<int>
    @ssbo @binding = 5 uo : array<uint>
    @ssbo @binding = 6 meta : array<uint>

    [metal_kernel(name="simd_msl"), marker(no_coverage)]
    def simd_all {
        let i = gl_GlobalInvocationID.x
        let lane = gl_SubgroupInvocationID
        fo[i] = ((simd_sum(fa[i]) + simd_shuffle(fa[i], lane)) +
            (simd_shuffle_up(fa[i], 1u) + simd_shuffle_down(fa[i], 1u))) + simd_shuffle_xor(fa[i], 1u)
        io[i] = ((simd_sum(ia[i]) + simd_shuffle(ia[i], lane)) +
            (simd_shuffle_up(ia[i], 1u) + simd_shuffle_down(ia[i], 1u))) + simd_shuffle_xor(ia[i], 1u)
        uo[i] = ((simd_sum(ua[i]) + simd_shuffle(ua[i], lane)) +
            (simd_shuffle_up(ua[i], 1u) + simd_shuffle_down(ua[i], 1u))) + simd_shuffle_xor(ua[i], 1u)
        meta[i] = (lane + gl_SubgroupSize) + (gl_NumSubgroups + gl_SubgroupID)
    }
}

//! Gate B: exactly the construct kinds the fixture set must emit — the census meta-test
//! asserts equality with the observed union in both directions.
def public declared_msl_census : table<string> {
    return <- {
        // signature + parameters
        "preamble",
        "kernel_sig",
        "param.buffer",
        "param.buffer_const",
        "param.uniform",
        "param.builtin.thread_position_in_grid",
        "param.builtin.thread_position_in_threadgroup",
        "param.builtin.threadgroup_position_in_grid",
        "param.builtin.threadgroups_per_grid",
        "param.builtin.threads_per_threadgroup",
        "param.builtin.thread_index_in_threadgroup",
        "param.builtin.thread_index_in_simdgroup",
        "param.builtin.threads_per_simdgroup",
        "param.builtin.simdgroups_per_threadgroup",
        "param.builtin.simdgroup_index_in_threadgroup",
        // threadgroup memory + synchronization
        "decl.threadgroup",
        "decl.threadgroup_array",
        "call.barrier",
        "call.memory_barrier_shared",
        // simdgroup intrinsics
        "call.simd_sum.f32",
        "call.simd_sum.i32",
        "call.simd_sum.u32",
        "call.simd_shuffle.f32",
        "call.simd_shuffle.i32",
        "call.simd_shuffle.u32",
        "call.simd_shuffle_up.f32",
        "call.simd_shuffle_up.i32",
        "call.simd_shuffle_up.u32",
        "call.simd_shuffle_down.f32",
        "call.simd_shuffle_down.i32",
        "call.simd_shuffle_down.u32",
        "call.simd_shuffle_xor.f32",
        "call.simd_shuffle_xor.i32",
        "call.simd_shuffle_xor.u32",
        // values
        "expr.builtin.thread_position_in_grid",
        "expr.builtin.thread_position_in_threadgroup",
        "expr.builtin.threadgroup_position_in_grid",
        "expr.builtin.threadgroups_per_grid",
        "expr.builtin.threads_per_threadgroup",
        "expr.builtin.thread_index_in_threadgroup",
        "expr.builtin.thread_index_in_simdgroup",
        "expr.builtin.threads_per_simdgroup",
        "expr.builtin.simdgroups_per_threadgroup",
        "expr.builtin.simdgroup_index_in_threadgroup",
        "expr.var",
        "expr.member",
        "expr.index",
        "expr.swizzle",
        "const.int",
        "const.uint",
        "const.float",
        "const.bool",
        // uint scalar arithmetic + bitwise
        "op.add.u32",
        "op.sub.u32",
        "op.mul.u32",
        "op.div.u32",
        "op.mod.u32",
        "op.band.u32",
        "op.bor.u32",
        "op.bxor.u32",
        "op.bnot.u32",
        "op.shl.u32",
        "op.shr.u32",
        // int scalar arithmetic + bitwise
        "op.add.i32",
        "op.sub.i32",
        "op.mul.i32",
        "op.div.i32",
        "op.mod.i32",
        "op.band.i32",
        "op.bor.i32",
        "op.bxor.i32",
        "op.bnot.i32",
        "op.shl.i32",
        "op.shr.i32",
        "op.neg.i32",
        // float scalar arithmetic
        "op.add.f32",
        "op.sub.f32",
        "op.mul.f32",
        "op.div.f32",
        "op.mod.f32",
        "op.neg.f32",
        // vector arithmetic
        "op.add.f32v",
        "op.sub.f32v",
        "op.mul.f32v",
        "op.div.f32v",
        "op.neg.f32v",
        "op.add.i32v",
        "op.sub.i32v",
        "op.mul.i32v",
        "op.eq.i32v",
        "op.ne.i32v",
        // comparisons
        "op.eq.u32",
        "op.ne.u32",
        "op.lt.u32",
        "op.le.u32",
        "op.gt.u32",
        "op.ge.u32",
        "op.eq.i32",
        "op.ne.i32",
        "op.lt.i32",
        "op.le.i32",
        "op.gt.i32",
        "op.ge.i32",
        "op.eq.f32",
        "op.ne.f32",
        "op.lt.f32",
        "op.le.f32",
        "op.gt.f32",
        "op.ge.f32",
        // logical + ternary + increment/decrement
        "op.land",
        "op.lor",
        "op.lnot",
        "op.select",
        "op.preinc",
        "op.postinc",
        "op.predec",
        "op.postdec",
        // compound assignment
        "op.add_assign.u32",
        "op.sub_assign.u32",
        "op.mul_assign.u32",
        "op.div_assign.u32",
        "op.mod_assign.u32",
        "op.band_assign.u32",
        "op.bor_assign.u32",
        "op.bxor_assign.u32",
        "op.shl_assign.u32",
        "op.shr_assign.u32",
        "op.add_assign.i32",
        "op.add_assign.f32",
        "op.mul_assign.f32",
        // statements
        "stmt.let",
        "stmt.var",
        "stmt.var.zero",
        "stmt.assign",
        "stmt.if",
        "stmt.elif",
        "stmt.else",
        "stmt.while",
        "stmt.for",
        "stmt.break",
        "stmt.continue",
        "stmt.return"
    }
}

//! Every fixture kernel's census companion, for the census meta-test's union.
def public all_msl_censuses : array<string> {
    return <- [mul_ab_msl_census, uarith_msl_census, iarith_msl_census, farith_msl_census,
        vecarith_msl_census, control_msl_census, loops_msl_census, reduce_msl_census, simd_msl_census]
}
