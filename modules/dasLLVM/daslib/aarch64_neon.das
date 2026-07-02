options gen2

module aarch64_neon shared public

// AArch64 NEON intrinsics exposed as plain daslang functions, each with a portable fallback body.
//
// Every function here computes the correct result on ANY target via its daslang body — so the
// interpreter, AOT, and non-ARM JIT builds all just run that body. On an aarch64 JIT target the
// LLVM JIT recognizes the call BY NAME (see g_aarch64_intrin_lookup in llvm_jit_intrin.das, gated
// on g_target_is_aarch64) and emits the hardware NEON instruction in place of the call. There is
// nothing to annotate and nothing to require from the llvm module — the recognition is purely
// name-based at JIT codegen time, so the fallback runs verbatim everywhere the intrinsic isn't
// emitted. Callers therefore get the fast path for free on arm64 and stay correct elsewhere.

//! Signed dot-product (`SDOT` / `@llvm.aarch64.neon.sdot`): load 16 int8 from each of `w` and `x`
//! (16-wide unaligned loads), multiply elementwise, and accumulate consecutive groups of 4 products
//! into the 4 lanes of `acc` — lane j += sum over e in 0..3 of w[4j+e]*x[4j+e], exact int32, with
//! NO horizontal reduce. On an aarch64 JIT target this lowers to a single SDOT instruction; on every
//! other target it is the scalar loop below. Pointers are passed pre-offset by the caller.
def sdot4(acc : int4; w : int8 const?; x : int8 const?) : int4 {
    var s0 = 0
    var s1 = 0
    var s2 = 0
    var s3 = 0
    unsafe {
        for (e in range(4)) {
            s0 += int(w[e]) * int(x[e])
            s1 += int(w[4 + e]) * int(x[4 + e])
            s2 += int(w[8 + e]) * int(x[8 + e])
            s3 += int(w[12 + e]) * int(x[12 + e])
        }
    }
    return acc + int4(s0, s1, s2, s3)
}

//! Signed dot-product with a VALUE weight operand: like `sdot4`, but `w` is 16 int8 packed
//! little-endian into the 4 lanes of an `int4` (byte e of lane g = element 4g+e) instead of a
//! pointer — the form `tbl16_lo`/`tbl16_hi` return, so a LUT-dequantized vector feeds SDOT with no
//! memory round-trip. On an aarch64 JIT target this is one SDOT (the `int4` is bitcast in a NEON
//! register); elsewhere it is the scalar body below.
def sdot4_w(acc : int4; w : int4; x : int8 const?) : int4 {
    var s0 = 0
    var s1 = 0
    var s2 = 0
    var s3 = 0
    unsafe {
        for (e in range(4)) {
            s0 += sxb(w.x, e) * int(x[e])
            s1 += sxb(w.y, e) * int(x[4 + e])
            s2 += sxb(w.z, e) * int(x[8 + e])
            s3 += sxb(w.w, e) * int(x[12 + e])
        }
    }
    return acc + int4(s0, s1, s2, s3)
}

// sign-extend byte e (0..3, little-endian) of a packed int lane
def private sxb(lane : int; e : int) : int => (((lane >> (e * 8)) & 0xff) ^ 0x80) - 0x80

//! Byte table lookup of LOW nibbles (`TBL` / `vqtbl1q_s8(table, nib & 0x0f)`): load 16 bytes from
//! `table` and 16 bytes from `nib`, look up each byte's low nibble in the table, and return the 16
//! resulting int8 packed little-endian into an `int4` (byte e of lane g = result byte 4g+e) — feed
//! it to `sdot4_w`. The nibble is masked to 0..15, so the lookup never leaves the table. On an
//! aarch64 JIT target this lowers to AND + one TBL; elsewhere it is the scalar body below.
def tbl16_lo(lut : int8 const?; nib : uint8 const?) : int4 {
    var l0 = 0
    var l1 = 0
    var l2 = 0
    var l3 = 0
    unsafe {
        for (e in range(4)) {
            l0 |= (int(lut[int(nib[e]) & 0x0f]) & 0xff) << (e * 8)
            l1 |= (int(lut[int(nib[4 + e]) & 0x0f]) & 0xff) << (e * 8)
            l2 |= (int(lut[int(nib[8 + e]) & 0x0f]) & 0xff) << (e * 8)
            l3 |= (int(lut[int(nib[12 + e]) & 0x0f]) & 0xff) << (e * 8)
        }
    }
    return int4(l0, l1, l2, l3)
}

//! Byte table lookup of HIGH nibbles (`TBL` / `vqtbl1q_s8(table, nib >> 4)`): same as `tbl16_lo`
//! but each byte's high nibble (logical shift right by 4) indexes the table. On an aarch64 JIT
//! target this lowers to USHR + one TBL; elsewhere it is the scalar body below.
def tbl16_hi(lut : int8 const?; nib : uint8 const?) : int4 {
    var l0 = 0
    var l1 = 0
    var l2 = 0
    var l3 = 0
    unsafe {
        for (e in range(4)) {
            l0 |= (int(lut[int(nib[e]) >> 4]) & 0xff) << (e * 8)
            l1 |= (int(lut[int(nib[4 + e]) >> 4]) & 0xff) << (e * 8)
            l2 |= (int(lut[int(nib[8 + e]) >> 4]) & 0xff) << (e * 8)
            l3 |= (int(lut[int(nib[12 + e]) >> 4]) & 0xff) << (e * 8)
        }
    }
    return int4(l0, l1, l2, l3)
}

//! Lane-indexed signed dot-product (`SDOT (by element)` / `vdotq_laneq_s32`): like `sdot4`, but the
//! 4-byte group selected by `lane` (0..3) of the 16 int8 at `x` is broadcast against ALL 4 groups of
//! `w` — so lane L += sum over e in 0..3 of w[4L+e]*x[4*lane+e]. With `w` holding 4 DIFFERENT weight
//! rows (interleaved repack) and `x` one token's 16 int8 loaded once, four calls with lane 0..3 finish
//! 16 k-values across 4 rows into 4 SEPARATE accumulator lanes — each lane is a distinct output row, so
//! there is never a horizontal reduce. On aarch64 JIT this lowers to one indexed SDOT (one `x` load
//! feeds all four); elsewhere it is the scalar body below. `lane` must be a compile-time constant.
def sdot4_laneq(acc : int4; w : int8 const?; x : int8 const?; lane : int) : int4 {
    let b = lane * 4
    var r = acc
    unsafe {
        let x0 = int(x[b])
        let x1 = int(x[b + 1])
        let x2 = int(x[b + 2])
        let x3 = int(x[b + 3])
        r.x += int(w[0]) * x0 + int(w[1]) * x1 + int(w[2]) * x2 + int(w[3]) * x3
        r.y += int(w[4]) * x0 + int(w[5]) * x1 + int(w[6]) * x2 + int(w[7]) * x3
        r.z += int(w[8]) * x0 + int(w[9]) * x1 + int(w[10]) * x2 + int(w[11]) * x3
        r.w += int(w[12]) * x0 + int(w[13]) * x1 + int(w[14]) * x2 + int(w[15]) * x3
    }
    return r
}
