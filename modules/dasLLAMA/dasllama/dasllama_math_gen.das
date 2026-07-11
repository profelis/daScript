options gen2

module dasllama_math_gen shared public

require dasllama/dasllama_math
require dasllama/dasllama_math_aarch64_neon
require dasllama/dasllama_math_default  // dot_q8q8_f16s — the row-major tails of the s16 twins
require llvm/daslib/llvm_tune  // [tune]/[tune_perm]/[tune_companion] + the [llvm_code] annotation it re-exports
require dasllama/dasllama_gemm_schema
require daslib/jobque_boost public
require dasllama/dasllama_par
require math

// The GEMM family as a [tune] client (gemm_generator_plan.md part 3; promoted from the M2
// GO/NO-GO experiment): the perm grid below stamps dasllama_gemm_gen::q8q8_tile perms through
// [llvm_code], and the [tune_companion] rows stamp q8q8_layout_gen + q8q8_wbias_gen +
// q8q8_kgroup_gen + q8q8_tokstep_gen + q8q8_gemv_gen + mx4q8_gemv_gen + q8q8_family_live from
// the same entry — the eight-function stamp: the runtime repacks (Q8 AND mx4 planes) ask the
// layout companion which interleave the stamped cores read, the wbias companion how the plane
// bytes are baked (bias128), the kgroup companion how the plane groups its k-bytes (kg8 on
// smmla stamps), the tokstep companion how many tokens one tile call covers (16·nrsplit on
// amx stamps — the batch wrapper walks its space off it), the witness answers "did the family
// actually emit", the q8q8_tile_s16_gen/q8q8_gemv_s16_gen twins serve the wscale_f16 rail
// (same perm, only the scale-fold load widens binary16), and ALL the generators share one
// decline predicate, so kernels, repacks, walk shape and availability cannot desync on any
// tier. Normal runs stamp exactly one winner (manifest > the per-ISA fallback chain:
// biased busd512 on AVX512-VNNI boxes / biased busd256 on VEX-VNNI / maddubs on plain AVX2 /
// kstep2 elsewhere — each ISA's measured tune winner as the manifest-less default);
// DAS_TUNE_MODE=tune/test stamps the grid + the *_variants() registries for the harness
// (gen_parity_probe / gen_tune_probe). This module registers TWO backends over the SAME
// ISA-agnostic slot traversals: "arm64-gen" (priority 25, the arm64 load-select tier since
// slice C) and "x64-gen" (priority 25, witness-gated — only selectable when the stamped
// family emitted). dasllama_common pulls it in behind a path guard
// (`require ?llvm/daslib/llvm_tune`), so any Q8/mx4 model load on a gen-capable box runs the
// generated family. The generators live in dasllama/dasllama_gemm_gen.das (llvm-jit context,
// wired via llvm/daslib/llvm_user_modules.das).

// The library-owned tune scope: every app that pulls dasLLAMA in shares the per-box winners
// at <das_root>/dasllama.tune.json, and [tune_policy]/--tune run gen_tune_probe to produce
// them (point DASLLAMA_CONFIRM_MODEL at a q8 gguf to arm its e2e confirm gate).
[tune_scope(name = "dasllama", tuner = "../harness/gen_tune_probe.das")]
struct private DasllamaTuneScope {}

//! The layout companion (the six-function stamp): the repack interleave (mr) the stamped tile
//! reads. Reference body = the reference tile's grp4; the generator emits the perm's mr and
//! declines in lockstep with the tile generator (shared perm_declines), so a perm the tile
//! can't emit keeps the grp4 reference pair on both sides — on every tier, JIT-time declines
//! included.
def q8q8_layout_gen() : int {
    return q8q8_repack_type(GEMM_REFERENCE_MR).interleave
}

//! The wbias companion (slice H): the additive bias baked into the grp<mr> plane's GROUP-row
//! bytes — 128 for the bias128 vpdpbusd perms (w^0x80, plain-u8 dots, −128·Σx acc-init
//! correction), 0 otherwise. Reference body = the unbiased grp4 pair; declines in lockstep
//! via the shared predicate, so plane bytes and kernels can never disagree about the bias.
def q8q8_wbias_gen() : int {
    return q8q8_repack_type(GEMM_REFERENCE_MR).wbias
}

//! The kgroup companion (slice J): k-bytes per row per interleave group of the stamped plane —
//! 8 for the smmla perms (row-pair × 8-k MMA operands load straight off the plane), 4 for
//! every vector-dot perm. Reference body = the kg4 grp4 pair; declines in lockstep via the
//! shared predicate, so plane byte order and kernels can never disagree about the grouping.
def q8q8_kgroup_gen() : int {
    return q8q8_repack_type(GEMM_REFERENCE_MR).kgroup
}

//! The tokstep companion (slice I): tokens one stamped tile call covers — 16·nrsplit for the
//! amx perms (whose TMUL macro also spans tokstep/16 row-groups: amx macros are square in
//! tile units), 4 for every vector perm. The batch wrapper walks its (token, row-group) space
//! off it. Reference body = the 4-token contract; declines in lockstep via the shared
//! predicate, so walk shape and tile can never disagree.
def q8q8_tokstep_gen() : int {
    return 4
}

//! The tile-config companion (slice K I1): a latch=1 raw-tile stamp carries no per-call
//! ldtilecfg and no tilerelease, so the batch wrapper calls this once per dispatch chunk to
//! load the family's static TMUL palette on the worker thread. Reference body — and the
//! generated body of every non-latch stamp — is a no-op.
def q8q8_amx_cfg_gen() : void {}

//! The witness companion: did the stamped family actually EMIT on this target? Reference body
//! = false; the generator emits `return true`, declining in lockstep with the whole family
//! (the one shared predicate) — so true ⟺ every slot below is generated code. Read at backend
//! SELECTION time only (never [init] — the slice C rule): on x64 a declined stamp keeps the
//! gen backend unavailable, because the reference bodies there are the NEON functions' scalar
//! fallbacks — correct, but far slower than the portable backend. On arm64 a declined stamp
//! still leaves the fast grp4 reference pair, so arm64-gen stays available regardless.
def q8q8_family_live() : bool {
    return false
}

//! The GEMV companion (the nr=1 perm sub-family, slice D): a rows-range core with the mm_rows
//! slot signature — rows [rb, re) of one region, no internal dispatch, rb/re multiples of the
//! stamped mr (the mm/group3/groupn wrappers chunk by groups; the mm_rows slot contract is
//! multiples of 32). The generator emits the grp<mr> single-token k-loop with the group walk
//! inside (gkstep blocks per iteration — independent sdot chains); the reference body is the
//! hand laneq rows walk over the grp4 reference layout, declining in lockstep with the tile
//! and layout via the shared predicate. Not `private`: it IS the mm_rows slot and is called
//! from inside lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = wp, noalias = sp, noalias = xqp, noalias = xsp)]
def q8q8_gemv_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) : void {
    let nb = n / 32l
    unsafe {
        for (g in range64(rb / 4l, re / 4l)) {
            let f = dot_q8q8_laneq4(wp + g * 4l * n, sp + g * 4l * nb, xqp, xsp, n)
            yp[g * 4l + 0l] = f.x
            yp[g * 4l + 1l] = f.y
            yp[g * 4l + 2l] = f.z
            yp[g * 4l + 3l] = f.w
        }
    }
}

//! The mx4 GEMV companion (slice E — the second quant family): the MXFP4·Q8 twin of
//! q8q8_gemv_gen, rows [rb, re) of one region off the grp<mr>-interleaved nibble/exponent
//! planes (repack_mx4_grp — the SAME mr as the Q8 layout, one companion for both). The
//! generator emits the tbl-dequant laneq shape (per block: 4 nibble loads per row quad feed
//! tbl lo/hi + indexed sdot, e8m0 scale fold in-register); reference body = the hand laneq
//! mx4 rows walk over the grp4 reference planes, declining in lockstep via the shared
//! predicate. Not `private`: called from inside lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = wn, noalias = we, noalias = xqp, noalias = xsp)]
def mx4q8_gemv_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) : void {
    let nrow = n / 2l
    let nbb = n / 32l
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])
        for (g in range64(rb / 4l, re / 4l)) {
            let f = dot_mx4q8_laneq4(lutp, wn + g * 4l * nrow, we + g * 4l * nbb, xqp, xsp, n)
            yp[g * 4l + 0l] = f.x
            yp[g * 4l + 1l] = f.y
            yp[g * 4l + 2l] = f.z
            yp[g * 4l + 3l] = f.w
        }
    }
}

//! The f16-scale GEMV companion (the wscale_f16 rail): q8q8_gemv_gen's twin over the raw
//! binary16 group-scale plane (Model.qscales16 — the repacked f32 plane, converted in place,
//! element order preserved). Same rows-range contract; the generated body differs only in the
//! scale fold's widen (fcvtl/vcvtph2ps). Reference body = the hand laneq f16s rows walk over
//! the grp4 reference layout, declining in lockstep via the shared predicate. Not `private`:
//! it IS the mm_rows_s16 slot and is called from inside lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = wp, noalias = sp, noalias = xqp, noalias = xsp)]
def q8q8_gemv_s16_gen(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) : void {
    let nb = n / 32l
    unsafe {
        for (g in range64(rb / 4l, re / 4l)) {
            let f = dot_q8q8_laneq4_f16s(wp + g * 4l * n, sp + g * 4l * nb, xqp, xsp, n)
            yp[g * 4l + 0l] = f.x
            yp[g * 4l + 1l] = f.y
            yp[g * 4l + 2l] = f.z
            yp[g * 4l + 3l] = f.w
        }
    }
}

//! The f16-scale tile companion: q8q8_tile_gen's twin over the binary16 group-scale plane —
//! same 4-token contract, stamped with the SAME perm (bias128/amx/smmla included; only the
//! scale-fold load differs). Reference body = 4 single-token laneq f16s dots with the tile's
//! per-block fold order. Not `private`: called from inside the lifted parallel_for worker
//! lambdas.
[unused_argument(xbsp), hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xqp, noalias = xsp, noalias = xbsp)]
def q8q8_tile_s16_gen(var yp : float?; wg : int8 const?; sg : uint16 const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, g, t0 : int64) : void {
    let nb = n / 32l
    unsafe {
        for (t in range64(4l)) {
            let f = dot_q8q8_laneq4_f16s(wg, sg, xqp + (t0 + t) * n, xsp + (t0 + t) * nb, n)
            let r = g * 4l
            yp[(t0 + t) * d + r + 0l] = f.x
            yp[(t0 + t) * d + r + 1l] = f.y
            yp[(t0 + t) * d + r + 2l] = f.z
            yp[(t0 + t) * d + r + 3l] = f.w
        }
    }
}

//! The generated tile: mr interleaved rows x 4 tokens (the q8q8_repack_type(mr) layout — see
//! dasllama_gemm_schema; the stamped mr is what q8q8_layout_gen reports). The reference body —
//! 4 single-token laneq4 dots with the same per-block fold order as the tile — runs on interp,
//! AOT, non-arm64 JIT, and whenever the generator declines; it ignores xbsp (the bias128 bsums
//! plane — only biased stamps read it, and their wrapper always passes one). The dot=/width=
//! rows are the x64 legs (slice F): they decline on arm64 and light per cpuid tier on x86-64
//! (avx2 / vnni256 / avx512bw / avx512vnni / avxvnniint8), so ONE grid serves every ISA; the
//! bias=128 rows (slice H) additionally bake w^0x80 into the plane and drop the sign trick;
//! the amx pipe=1 row (slice K) defers the TMUL macro's scale fold one k-block behind a
//! double-buffered C spill so vector ports fold while TMUL crunches.
//! The trailing suffix rows and the bias-on-maddubs row decline by design everywhere (q-reg
//! budget, lane structure, a dot with no 128-bit leg, word-saturating biased pair-sums) and
//! pin the decline rail in test mode. Not `private`: called from inside the lifted
//! parallel_for worker lambda below.
[tune_perm(kstep = 1), tune_perm(kstep = 2), tune_perm(kstep = 4), tune_perm(kstep = 2, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2), tune_perm(kstep = 4, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2, mr = 8), tune_perm(kstep = 2, nrsplit = 2, mr = 8), tune_perm(kstep = 4, nrsplit = 2, mr = 8),
 tune_perm(kstep = 2, gkstep = 2), tune_perm(kstep = 2, gkstep = 4),
 tune_perm(kstep = 4, nrsplit = 2, mr = 8, gkstep = 2), tune_perm(kstep = 4, nrsplit = 2, mr = 8, gkstep = 4),
 tune_perm(dot = "maddubs", width = 256, mr = 8, kstep = 2, requires = "avx2"), tune_perm(dot = "maddubs", width = 256, mr = 8, kstep = 4, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2), tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 4, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 16, kstep = 2, nrsplit = 2), tune_perm(dot = "vpdpbssd", width = 256, mr = 8, kstep = 2),
 tune_perm(dot = "maddubs", width = 512, mr = 16, kstep = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2),
 tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 4, nrsplit = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 32, kstep = 2, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2, gkstep = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2, gkstep = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2, bias = 128), tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2, gkstep = 2, bias = 128, requires = "avxvnni|avx512vnni"),
 tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2, bias = 128), tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2, gkstep = 2, bias = 128, requires = "avx512vnni,avx512bw"),
 tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 4, nrsplit = 2, bias = 128),
 tune_perm(dot = "maddubs", width = 256, mr = 8, kstep = 2, bias = 128),
 tune_perm(dot = "smmla", mr = 4, kstep = 2, requires = "i8mm"), tune_perm(dot = "smmla", mr = 4, kstep = 2, nrsplit = 2, requires = "i8mm"),
 tune_perm(dot = "smmla", mr = 8, kstep = 2, nrsplit = 2, requires = "i8mm"), tune_perm(dot = "smmla", mr = 8, kstep = 4, nrsplit = 2, requires = "i8mm"),
 tune_perm(dot = "smmla", mr = 8, kstep = 2, nrsplit = 2, gkstep = 2, requires = "i8mm"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 1, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, gkstep = 2, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, pipe = 1, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, latch = 1, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, bias = 128, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, pipe = 1, latch = 1, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, pipe = 1, bias = 128, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, latch = 1, bias = 128, requires = "amx-int8"),
 tune_perm(dot = "amx_int8", width = 512, mr = 16, kstep = 1, nrsplit = 2, pipe = 1, latch = 1, bias = 128, requires = "amx-int8"),
 tune_perm(suffix = "mr8_budget", mr = 8), tune_perm(suffix = "mr2_lanes", mr = 2), tune_perm(dot = "vpdpbusd"),
 tune_companion(fn = "q8q8_layout_gen", gen = "dasllama_gemm_gen::q8q8_layout"),
 tune_companion(fn = "q8q8_wbias_gen", gen = "dasllama_gemm_gen::q8q8_wbias"),
 tune_companion(fn = "q8q8_kgroup_gen", gen = "dasllama_gemm_gen::q8q8_kgroup"),
 tune_companion(fn = "q8q8_tokstep_gen", gen = "dasllama_gemm_gen::q8q8_tokstep"),
 tune_companion(fn = "q8q8_amx_cfg_gen", gen = "dasllama_gemm_gen::q8q8_amx_cfg"),
 tune_companion(fn = "q8q8_gemv_gen", gen = "dasllama_gemm_gen::q8q8_gemv"),
 tune_companion(fn = "q8q8_tile_s16_gen", gen = "dasllama_gemm_gen::q8q8_tile_s16"),
 tune_companion(fn = "q8q8_gemv_s16_gen", gen = "dasllama_gemm_gen::q8q8_gemv_s16"),
 tune_companion(fn = "mx4q8_gemv_gen", gen = "dasllama_gemm_gen::mx4_gemv"),
 tune_companion(fn = "q8q8_family_live", gen = "dasllama_gemm_gen::q8q8_witness"),
 tune(gen = "dasllama_gemm_gen::q8q8_tile",
      fallback = "dot_vpdpbusd_width512_mr16_kstep2_gkstep2_bias128;dot_vpdpbusd_width256_mr8_kstep2_gkstep2_bias128;dot_maddubs_width256_mr8_kstep2;kstep2"), unused_argument(xbsp),
 hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xqp, noalias = xsp, noalias = xbsp)]
def q8q8_tile_gen(var yp : float?; wg : int8 const?; sg : float const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, g, t0 : int64) : void {
    let nb = n / 32l
    unsafe {
        for (t in range64(4l)) {
            let f = dot_q8q8_laneq4(wg, sg, xqp + (t0 + t) * n, xsp + (t0 + t) * nb, n)
            let r = g * 4l
            yp[(t0 + t) * d + r + 0l] = f.x
            yp[(t0 + t) * d + r + 1l] = f.y
            yp[(t0 + t) * d + r + 2l] = f.z
            yp[(t0 + t) * d + r + 3l] = f.w
        }
    }
}

//! mr-generalized Q8 interleave repack — the q8q8_repack_type(mr) layout for any mr
//! (mr=4 reproduces the old hand arm64-laneq interleave byte-for-byte). mr-row
//! groups, kgroup k-bytes per row per group (4 = the dword-group layout every vector-dot
//! perm reads; 8 = the smmla row-pair layout, slice J), f32 scales interleaved per
//! block; group bytes biased by wbias (the bias128 vpdpbusd stamps bake w^0x80; tail rows
//! stay row-major AND unbiased — the sdot4x4 tail path reads them as plain s8). Runs once
//! per weight tensor at load, on the main context. Public: the probes repack per-variant
//! copies with an explicit mr/wbias/kgroup.
def repack_q8q8_grp(var wp : int8?; var sp : float?; n, d, mr : int64; wbias : int64 = 0l; kgroup : int64 = 4l) {
    let nb = n / 32l
    let ng = d / mr
    let ncg = n / kgroup
    var tw : array<int8>
    var ts : array<float>
    tw |> resize(int(d * n))
    ts |> resize(int(d * nb))
    unsafe {
        var twp = addr(tw[0])
        var tsp = addr(ts[0])
        for (i in range64(d * n)) {
            twp[i] = wp[i]
        }
        for (i in range64(d * nb)) {
            tsp[i] = sp[i]
        }
        for (g in range64(ng)) {
            let gbase = g * mr * n
            for (kg in range64(ncg)) {
                let dst = gbase + kg * kgroup * mr
                for (r in range64(mr)) {
                    let src = (g * mr + r) * n + kg * kgroup
                    for (j in range64(kgroup)) {
                        wp[dst + r * kgroup + j] = twp[src + j]
                    }
                }
            }
            let sgbase = g * mr * nb
            for (bi in range64(nb)) {
                for (r in range64(mr)) {
                    sp[sgbase + bi * mr + r] = tsp[(g * mr + r) * nb + bi]
                }
            }
        }
        if (wbias != 0l) {
            // bias128: one pass over the GROUP region only (tails stay plain s8);
            // int8 truncation makes +128 the byte xor 0x80
            for (i in range64(ng * mr * n)) {
                wp[i] = int8(int(wp[i]) + int(wbias))
            }
        }
    }
    delete tw
    delete ts
}

// the backend repack slot: the layout companion decides the interleave, the wbias companion
// the plane bias, the kgroup companion the k-byte grouping — so a stamped bias128-mr16 tile
// gets biased grp16 weights and an smmla stamp gets the kg8 row-pair plane from the same
// load path that gave the grp4 pair its plain grp4 weights
def private repack_q8q8_gen(var wp : int8?; var sp : float?; n, d : int64) {
    repack_q8q8_grp(wp, sp, n, d, int64(q8q8_layout_gen()), int64(q8q8_wbias_gen()), int64(q8q8_kgroup_gen()))
}

//! mr-generalized MXFP4 plane repack (mr=4 reproduces the old hand arm64-laneq mx
//! interleave byte-for-byte). Nibble bytes interleave [dword-group j][row r][4 bytes]
//! per block (16*mr bytes per block-group — the layout whose nibble order maps byte-for-byte
//! onto the grp<mr> Q8 order, see expand_mx4_region_q8), E8M0 scale bytes mr-per-block; tail
//! rows (d % mr) stay row-major. Public: the probes repack per-variant copies with an
//! explicit mr.
def repack_mx4_grp(var np : uint8?; var ep : uint8?; n, d, mr : int64) {
    let nrow = n / 2l    // nibble bytes per row
    let nbb = n / 32l    // blocks per row
    let ng = d / mr
    var tn : array<uint8>
    var te : array<uint8>
    tn |> resize(int(d * nrow))
    te |> resize(int(d * nbb))
    unsafe {
        var tnp = addr(tn[0])
        var tep = addr(te[0])
        for (i in range64(d * nrow)) {
            tnp[i] = np[i]
        }
        for (i in range64(d * nbb)) {
            tep[i] = ep[i]
        }
        for (g in range64(ng)) {
            let gnb = g * mr * nrow
            for (bi in range64(nbb)) {
                let dst = gnb + bi * 16l * mr
                for (j in range64(4l)) {
                    for (r in range64(mr)) {
                        let src = (g * mr + r) * nrow + bi * 16l + j * 4l
                        let dj = dst + j * 4l * mr + r * 4l
                        np[dj + 0l] = tnp[src + 0l]
                        np[dj + 1l] = tnp[src + 1l]
                        np[dj + 2l] = tnp[src + 2l]
                        np[dj + 3l] = tnp[src + 3l]
                    }
                }
            }
            let geb = g * mr * nbb
            for (bi in range64(nbb)) {
                for (r in range64(mr)) {
                    ep[geb + bi * mr + r] = tep[(g * mr + r) * nbb + bi]
                }
            }
        }
    }
    delete tn
    delete te
}

// the backend mx4 repack slot: same layout companion as the Q8 repack — planes and weights
// interleave at the ONE stamped mr
def private repack_mx4_gen(var np : uint8?; var ep : uint8?; n, d : int64) {
    repack_mx4_grp(np, ep, n, d, int64(q8q8_layout_gen()))
}

//! Generic grp<mr> single-token dot for the mr != 4 slots and tails: scalar, correct
//! anywhere, same per-block fold order as the tile (acc int-exact, then f += float(acc) * s *
//! q per block in bi order). Writes the group's mr outputs for token trow at column col.
//! wbias un-biases bias128 planes byte-wise (int8(b + 128) — the +128-mod-256 involution,
//! int-exact, same acc as the plain plane; identity at wbias=0); kgroup selects the plane's
//! k-byte grouping (4 = dword groups, 8 = the smmla row-pair plane). Public: the parity probe
//! uses it as the grp<mr> reference when the stamped mr isn't 4.
def q8q8_token_grp_generic(var yp : float?; wg : int8 const?; sg : float const?; xq : int8 const?; xs : float const?; n, d, col, trow, mr : int64; wbias : int64 = 0l; kgroup : int64 = 4l) {
    let nb = n / 32l
    let wb0 = int(wbias)
    var f : float[32]   // scratch cap = the grid's max stampable mr (busd512 mr32 row)
    for (r in range(int(mr))) {
        f[r] = 0.0
    }
    unsafe {
        for (bi in range64(nb)) {
            let wb = bi * mr * 32l
            let xb = bi * 32l
            let xsb = xs[bi]
            for (r in range64(mr)) {
                var acc = 0
                for (kg in range64(8l)) {
                    let wo = (kgroup == 8l
                        ? wb + (kg / 2l) * 8l * mr + r * 8l + (kg % 2l) * 4l
                        : wb + kg * 4l * mr + r * 4l)
                    let xo = xb + kg * 4l
                    acc += int(int8(int(wg[wo + 0l]) + wb0)) * int(xq[xo + 0l])
                    acc += int(int8(int(wg[wo + 1l]) + wb0)) * int(xq[xo + 1l])
                    acc += int(int8(int(wg[wo + 2l]) + wb0)) * int(xq[xo + 2l])
                    acc += int(int8(int(wg[wo + 3l]) + wb0)) * int(xq[xo + 3l])
                }
                f[int(r)] += float(acc) * sg[bi * mr + r] * xsb
            }
        }
        for (r in range64(mr)) {
            yp[trow * d + col + r] = f[int(r)]
        }
    }
}

// One (unit range × token range) cell of the interleaved batch walk — the worker body of the
// classic 1-D dispatch verbatim (TB blocks outer, groups inner): the 1-D arm calls it once with
// the full token range, the 2-D grid arm once per cell, so the two arms share one walk and the
// off-path stays byte-identical.
def private q8q8_batch_cell_gen(var myp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, nb, mr, TB, kg, wbias : int64; ub, ue : int; tb0, te : int64) {
    unsafe {
        var tb = tb0
        while (tb < te) {
            let tbe = min(tb + TB, te)
            let tb4 = tb + ((tbe - tb) / 4l) * 4l
            for (gi in range(ub, ue)) {
                let g = int64(gi)
                let wgp = wp + g * mr * n
                let sgp = sp + g * mr * nb
                var tk = tb
                while (tk < tb4) {
                    q8q8_tile_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, g, tk)
                    tk += 4l
                }
                if (mr == 4l && kg == 4l) {   // an smmla mr4 stamp's plane is kg8 — generic tail below
                    while (tk < tbe) {
                        let f = dot_q8q8_laneq4(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
                        myp[tk * d + g * 4l + 0l] = f.x
                        myp[tk * d + g * 4l + 1l] = f.y
                        myp[tk * d + g * 4l + 2l] = f.z
                        myp[tk * d + g * 4l + 3l] = f.w
                        tk++
                    }
                } else {
                    while (tk < tbe) {
                        q8q8_token_grp_generic(myp, wgp, sgp, xqp + tk * n, xsp + tk * nb, n, d, g * mr, tk, mr, wbias, kg)
                        tk++
                    }
                }
            }
            tb += TB
        }
    }
}

// One (unit range × token range) cell of the amx-shaped walk (slice K I2 — the ts≠4 twin of
// q8q8_batch_cell_gen): (ts-token × gs-group) macro units over units [ub, ue), tokens
// [tb0, te). The 1-D arm calls it with the full token range, the 2-D grid once per cell.
// Interior token cells are whole-macro by construction (whole-ts even division); a ragged
// block tail rides ONE overlapped macro when the overlap stays inside this cell's token range
// (the tile zero-inits its own y region — same-thread recompute is idempotent, and the tb0
// guard keeps the overlap from ever crossing into a concurrent cell's rows), else the vector
// rows-core per token.
def private q8q8_batch_amx_cell_gen(var myp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, nb, mr, TBa, ts, gs : int64; ub, ue : int; tb0, te : int64) {
    unsafe {
        var tb = tb0
        while (tb < te) {
            let tbe = min(tb + TBa, te)
            let tbS = tb + ((tbe - tb) / ts) * ts
            for (ui in range(ub, ue)) {
                let gg = int64(ui) * gs
                let wgp = wp + gg * mr * n
                let sgp = sp + gg * mr * nb
                var tk = tb
                while (tk < tbS) {
                    q8q8_tile_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, gg, tk)
                    tk += ts
                }
                if (tk < tbe) {
                    if (tbe - ts >= tb0) {
                        q8q8_tile_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, gg, tbe - ts)
                    } else {
                        while (tk < tbe) {
                            q8q8_gemv_gen(myp + tk * d, wp, sp, xqp + tk * n, xsp + tk * nb, n, gg * mr, (gg + gs) * mr)
                            tk++
                        }
                    }
                }
            }
            tb += TBa
        }
    }
}

// The interleaved batch GEMM (grew out of the hand laneq batch kernel, tile swapped for the
// generated one). Token-blocked: TB tokens outer, groups inner, so the TB×n activation slice
// stays L2-resident and is reused across this thread's groups instead of re-streaming the whole
// activation once per group (effective_token_block clamps TB to the per-box L2 budget — above
// ~L2/n the slice spills and prefill cliffs). Strides come off the layout companion: any
// stamped mr walks grp<mr> groups and runs its token tail through the generic dot; the tokstep
// companion picks the walk shape (4-token vector tiles, or the amx macro's ts×gs units). For a
// bias128 stamp the bsums plane (−128·Σx i32 per (token, block) — the tile's acc-init
// correction) is built once per call before dispatch: O(ntok·n), noise against the dots'
// O(ntok·n·d), amortized over every group.
def private q8q8_batch_kernel_neon_laneq_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let wbias = int64(q8q8_wbias_gen())
    let kg = int64(q8q8_kgroup_gen())
    let ng = d / mr
    var myp = yp
    let TB = effective_token_block(g_q8_token_block, n)
    var bs : array<int>
    if (wbias != 0l) {
        bs |> resize(int(ntok * nb))
        unsafe {
            var bsp = addr(bs[0])
            for (t in range64(ntok)) {
                let xrow = xqp + t * n
                for (bi in range64(nb)) {
                    var s = 0
                    let xb = bi * 32l
                    for (j in range64(32l)) {
                        s += int(xrow[xb + j])
                    }
                    bsp[t * nb + bi] = -128 * s
                }
            }
        }
    }
    let xbsp : int const? = wbias != 0l ? unsafe(addr(bs[0])) : null
    let ts = int64(q8q8_tokstep_gen())   // tokens per tile call (4; 16/32 on amx stamps)
    if (ts != 4l) {
        // the amx-shaped walk (slice I): one tile call covers ts tokens × gs row-groups, so
        // the chunk space is gs-group units. Full-macro calls only; the token tail rides ONE
        // overlapped macro call (the tile zero-inits its own y region, so recomputing covered
        // tokens is idempotent); a batch shorter than one macro rides the vector rows-core
        // per token. TB clamps up to one macro (a sub-macro block would overlap every call).
        let gs = ts / 16l                // row-groups per call — amx macros are square in tile units
        let ngu = ng / gs
        let TBa = max(TB, ts)
        let grid = matmul_grid(int(ngu), gs * mr, get_q8_batch_chunks_per_job(), n * d * ntok, ntok, int(ts))
        if (grid.y <= 1) {
            maybe_parallel_for(0, int(ngu), grid.x) $(ub, ue) {
                q8q8_amx_cfg_gen()      // latch stamps: load the TMUL palette on this worker
                q8q8_batch_amx_cell_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TBa, ts, gs, ub, ue, 0l, ntok)
            }
        } else {
            // the 2-D grid on the amx walk (slice K I2 — 135M qkv = 18 macro units for 48
            // lanes was twice as starved as the vector walk): one claim per (unit range ×
            // token range) cell, ROWS-FASTEST decode, token axis in whole ts-token macros
            let ntile = ntok / ts
            let cells = grid.x * grid.y
            maybe_parallel_for(0, cells, cells) $(cb, ce) {
                q8q8_amx_cfg_gen()      // latch stamps: load the TMUL palette on this worker
                for (ci in range(cb, ce)) {
                    let ri = ci % grid.x
                    let ti = ci / grid.x
                    let ub = int(int64(ri) * ngu / int64(grid.x))
                    let ue = int(int64(ri + 1) * ngu / int64(grid.x))
                    let ctb = int64(ti) * ntile / int64(grid.y) * ts
                    let cte = ti == grid.y - 1 ? ntok : int64(ti + 1) * ntile / int64(grid.y) * ts
                    q8q8_batch_amx_cell_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TBa, ts, gs, ub, ue, ctb, cte)
                }
            }
        }
        if (ngu * gs < ng) {
            // leftover row-groups (ng % gs — dims that are 16- but not 32-multiples): the
            // vector rows-core per token
            unsafe {
                for (tk in range64(ntok)) {
                    q8q8_gemv_gen(myp + tk * d, wp, sp, xqp + tk * n, xsp + tk * nb, n, ngu * gs * mr, ng * mr)
                }
            }
        }
    } else {
        let grid = matmul_grid(int(ng), mr, get_q8_batch_chunks_per_job(), n * d * ntok, ntok, 4)
        if (grid.y <= 1) {
            maybe_parallel_for(0, int(ng), grid.x) $(rb, re) {
                q8q8_batch_cell_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TB, kg, wbias, rb, re, 0l, ntok)
            }
        } else {
            // the 2-D grid (matmul_grid engaged): one claim per (unit range × token range) cell,
            // decoded ROWS-FASTEST so concurrent workers share a token block's activation slice
            // in LLC while streaming disjoint weight rows. Even-division bounds, token axis in
            // whole ts=4 tiles with the range tail folded into the last cell.
            let ntile = ntok / 4l
            let cells = grid.x * grid.y
            maybe_parallel_for(0, cells, cells) $(cb, ce) {
                for (ci in range(cb, ce)) {
                    let ri = ci % grid.x
                    let ti = ci / grid.x
                    let ub = int(int64(ri) * ng / int64(grid.x))
                    let ue = int(int64(ri + 1) * ng / int64(grid.x))
                    let ctb = int64(ti) * ntile / int64(grid.y) * 4l
                    let cte = ti == grid.y - 1 ? ntok : int64(ti + 1) * ntile / int64(grid.y) * 4l
                    q8q8_batch_cell_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TB, kg, wbias, ub, ue, ctb, cte)
                }
            }
        }
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_sdot4x4(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
    delete bs
}

// mm slot: the hand laneq dispatch shape with the group walk handed to the generated rows
// core — ONE core call per chunk (the group loop lives inside the generated code). Strides
// come off the layout companion, so the same wrapper serves both stamped layouts; the row
// tail (d % mr) stays row-major in the repack and rides sdot4x4.
def private q8q8_kernel_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(0, int(ng), matmul_chunks_gemv(int(ng * mr), get_q8_batch_chunks_per_job(), n * d)) $(rb, re) {
        q8q8_gemv_gen(myp, wp, sp, xqp, xsp, n, int64(rb) * mr, int64(re) * mr)
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_q8q8_sdot4x4(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

// group3: the hand laneq fused walk (one dispatch over the three regions' combined group
// space), each worker chunk split at region boundaries into at most three rows-core calls
def private q8q8_group3_gen(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                            woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng0 = d0 / mr
    let ng1 = d1 / mr
    let ng2 = d2 / mr
    let ngtot = ng0 + ng1 + ng2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    // oversplit only under team dispatch — same trade as the hand laneq group3
    maybe_parallel_for(0, int(ngtot), matmul_chunks_gemv(int(ngtot * mr), get_jobque_team_mode() ? get_q8_batch_chunks_per_job() : 1, n * (d0 + d1 + d2))) $(rb, re) {
        unsafe {
            let b0 = int64(rb)
            let e0 = min(int64(re), ng0)
            if (b0 < e0) {
                q8q8_gemv_gen(w0, wp + woff0, sp + woff0 / 32l, xqp, xsp, n, b0 * mr, e0 * mr)
            }
            let b1 = max(int64(rb) - ng0, 0l)
            let e1 = min(int64(re) - ng0, ng1)
            if (b1 < e1) {
                q8q8_gemv_gen(w1, wp + woff1, sp + woff1 / 32l, xqp, xsp, n, b1 * mr, e1 * mr)
            }
            let b2 = max(int64(rb) - ng0 - ng1, 0l)
            let e2 = min(int64(re) - ng0 - ng1, ng2)
            if (b2 < e2) {
                q8q8_gemv_gen(w2, wp + woff2, sp + woff2 / 32l, xqp, xsp, n, b2 * mr, e2 * mr)
            }
        }
    }
    unsafe {
        for (i in range64(ng0 * mr, d0)) {
            w0[i] = dot_q8q8_sdot4x4(wp + woff0 + i * n, sp + woff0 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng1 * mr, d1)) {
            w1[i] = dot_q8q8_sdot4x4(wp + woff1 + i * n, sp + woff1 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng2 * mr, d2)) {
            w2[i] = dot_q8q8_sdot4x4(wp + woff2 + i * n, sp + woff2 / 32l + i * nb, xqp, xsp, n)
        }
    }
}

// groupn: the hand laneq fused walk over the (region x group) space; each worker chunk runs
// region-contiguous rows-core spans + the bias post-add over the same span (an extra y pass,
// trivial next to the dots)
def private q8q8_groupn_gen(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(0, int(nregions * ng), matmul_chunks_gemv(int(nregions * ng * mr), get_q8_batch_chunks_per_job(), n * d * nregions)) $(gb, ge) {
        unsafe {
            var gg = int64(gb)
            while (gg < int64(ge)) {
                let r = gg / ng
                let gLocal = gg % ng
                let gEnd = min(int64(ge) - r * ng, ng)
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                q8q8_gemv_gen(myp + r * d, wp + woff, sp + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, gLocal * mr, gEnd * mr)
                if (bp != null) {
                    for (i in range64(gLocal * mr, gEnd * mr)) {
                        myp[r * d + i] += bp[boffs[r] + i]
                    }
                }
                gg = r * ng + gEnd
            }
        }
    }
    unsafe {
        for (r in range64(nregions)) {   // row tails (d % mr): row-major sdot4x4 per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * mr, d)) {
                var v = dot_q8q8_sdot4x4(wp + woff + i * n, sp + woff / 32l + i * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

// mm_mx4 slot: the mx4 twin of q8q8_kernel_gen — group chunks handed to the generated mx4
// rows core, row tail (d % mr) row-major via dot_mx4q8 (tail planes stay row-major in the
// repack)
def private mx4q8_kernel_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nrow = n / 2l
    let nbb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(ng), matmul_chunks_gemv(int(ng * mr), get_q8_batch_chunks_per_job(), n * d)) $(rb, re) {
            mx4q8_gemv_gen(myp, wn, we, xqp, xsp, n, int64(rb) * mr, int64(re) * mr)
        }
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_mx4q8(lutp, wn + i * nrow, we + i * nbb, xqp, xsp, n)
        }
    }
}

// groupn_mx4: the mx4 twin of q8q8_groupn_gen — region-contiguous rows-core spans + bias
// post-add, row tails row-major per region
def private mx4q8_groupn_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nrow = n / 2l
    let nbb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(nregions * ng), matmul_chunks_gemv(int(nregions * ng * mr), get_q8_batch_chunks_per_job(), n * d * nregions)) $(gb, ge) {
            unsafe {
                var gg = int64(gb)
                while (gg < int64(ge)) {
                    let r = gg / ng
                    let gLocal = gg % ng
                    let gEnd = min(int64(ge) - r * ng, ng)
                    let woff = offs[r * 2l]
                    let xoff = offs[r * 2l + 1l]
                    mx4q8_gemv_gen(myp + r * d, wn + woff / 2l, we + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, gLocal * mr, gEnd * mr)
                    if (bp != null) {
                        for (i in range64(gLocal * mr, gEnd * mr)) {
                            myp[r * d + i] += bp[boffs[r] + i]
                        }
                    }
                    gg = r * ng + gEnd
                }
            }
        }
        for (r in range64(nregions)) {   // row tails (d % mr): row-major dot per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * mr, d)) {
                var v = dot_mx4q8(lutp, wn + woff / 2l + i * nrow, we + woff / 32l + i * nbb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

// ===== f16-scale twins (the wscale_f16 rail): the same slot traversals over the binary16
// group-scale plane — generated cores via the s16 companions, row-major tails via
// dot_q8q8_f16s, token tails via the s16 rows core (no laneq fork needed: the generated
// core covers every stamped layout) =====

def private q8q8_batch_cell_s16_gen(var myp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, nb, mr, TB : int64; ub, ue : int; tb0, te : int64) {
    unsafe {
        var tb = tb0
        while (tb < te) {
            let tbe = min(tb + TB, te)
            let tb4 = tb + ((tbe - tb) / 4l) * 4l
            for (gi in range(ub, ue)) {
                let g = int64(gi)
                let wgp = wp + g * mr * n
                let sgp = sp + g * mr * nb
                var tk = tb
                while (tk < tb4) {
                    q8q8_tile_s16_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, g, tk)
                    tk += 4l
                }
                while (tk < tbe) {
                    q8q8_gemv_s16_gen(myp + tk * d, wp, sp, xqp + tk * n, xsp + tk * nb, n, g * mr, (g + 1l) * mr)
                    tk++
                }
            }
            tb += TB
        }
    }
}

def private q8q8_batch_amx_cell_s16_gen(var myp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; xbsp : int const?; n, d, nb, mr, TBa, ts, gs : int64; ub, ue : int; tb0, te : int64) {
    unsafe {
        var tb = tb0
        while (tb < te) {
            let tbe = min(tb + TBa, te)
            let tbS = tb + ((tbe - tb) / ts) * ts
            for (ui in range(ub, ue)) {
                let gg = int64(ui) * gs
                let wgp = wp + gg * mr * n
                let sgp = sp + gg * mr * nb
                var tk = tb
                while (tk < tbS) {
                    q8q8_tile_s16_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, gg, tk)
                    tk += ts
                }
                if (tk < tbe) {
                    if (tbe - ts >= tb0) {
                        q8q8_tile_s16_gen(myp, wgp, sgp, xqp, xsp, xbsp, n, d, gg, tbe - ts)
                    } else {
                        while (tk < tbe) {
                            q8q8_gemv_s16_gen(myp + tk * d, wp, sp, xqp + tk * n, xsp + tk * nb, n, gg * mr, (gg + gs) * mr)
                            tk++
                        }
                    }
                }
            }
            tb += TBa
        }
    }
}

def private q8q8_batch_kernel_s16_gen(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let wbias = int64(q8q8_wbias_gen())
    let ng = d / mr
    var myp = yp
    let TB = effective_token_block(g_q8_token_block, n)
    var bs : array<int>
    if (wbias != 0l) {
        bs |> resize(int(ntok * nb))
        unsafe {
            var bsp = addr(bs[0])
            for (t in range64(ntok)) {
                let xrow = xqp + t * n
                for (bi in range64(nb)) {
                    var s = 0
                    let xb = bi * 32l
                    for (j in range64(32l)) {
                        s += int(xrow[xb + j])
                    }
                    bsp[t * nb + bi] = -128 * s
                }
            }
        }
    }
    let xbsp : int const? = wbias != 0l ? unsafe(addr(bs[0])) : null
    let ts = int64(q8q8_tokstep_gen())   // tokens per tile call (4; 16/32 on amx stamps)
    if (ts != 4l) {
        let gs = ts / 16l                // row-groups per call — amx macros are square in tile units
        let ngu = ng / gs
        let TBa = max(TB, ts)
        let grid = matmul_grid(int(ngu), gs * mr, get_q8_batch_chunks_per_job(), n * d * ntok, ntok, int(ts))
        if (grid.y <= 1) {
            maybe_parallel_for(0, int(ngu), grid.x) $(ub, ue) {
                q8q8_amx_cfg_gen()      // latch stamps: load the TMUL palette on this worker
                q8q8_batch_amx_cell_s16_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TBa, ts, gs, ub, ue, 0l, ntok)
            }
        } else {
            let ntile = ntok / ts
            let cells = grid.x * grid.y
            maybe_parallel_for(0, cells, cells) $(cb, ce) {
                q8q8_amx_cfg_gen()      // latch stamps: load the TMUL palette on this worker
                for (ci in range(cb, ce)) {
                    let ri = ci % grid.x
                    let ti = ci / grid.x
                    let ub = int(int64(ri) * ngu / int64(grid.x))
                    let ue = int(int64(ri + 1) * ngu / int64(grid.x))
                    let ctb = int64(ti) * ntile / int64(grid.y) * ts
                    let cte = ti == grid.y - 1 ? ntok : int64(ti + 1) * ntile / int64(grid.y) * ts
                    q8q8_batch_amx_cell_s16_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TBa, ts, gs, ub, ue, ctb, cte)
                }
            }
        }
        if (ngu * gs < ng) {
            unsafe {
                for (tk in range64(ntok)) {
                    q8q8_gemv_s16_gen(myp + tk * d, wp, sp, xqp + tk * n, xsp + tk * nb, n, ngu * gs * mr, ng * mr)
                }
            }
        }
    } else {
        let grid = matmul_grid(int(ng), mr, get_q8_batch_chunks_per_job(), n * d * ntok, ntok, 4)
        if (grid.y <= 1) {
            maybe_parallel_for(0, int(ng), grid.x) $(rb, re) {
                q8q8_batch_cell_s16_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TB, rb, re, 0l, ntok)
            }
        } else {
            let ntile = ntok / 4l
            let cells = grid.x * grid.y
            maybe_parallel_for(0, cells, cells) $(cb, ce) {
                for (ci in range(cb, ce)) {
                    let ri = ci % grid.x
                    let ti = ci / grid.x
                    let ub = int(int64(ri) * ng / int64(grid.x))
                    let ue = int(int64(ri + 1) * ng / int64(grid.x))
                    let ctb = int64(ti) * ntile / int64(grid.y) * 4l
                    let cte = ti == grid.y - 1 ? ntok : int64(ti + 1) * ntile / int64(grid.y) * 4l
                    q8q8_batch_cell_s16_gen(myp, wp, sp, xqp, xsp, xbsp, n, d, nb, mr, TB, ub, ue, ctb, cte)
                }
            }
        }
    }
    unsafe {
        for (i in range64(ng * mr, d)) {   // row tails (d % mr) stay row-major in the repack
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_f16s(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
    delete bs
}

def private q8q8_kernel_s16_gen(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(0, int(ng), matmul_chunks_gemv(int(ng * mr), get_q8_batch_chunks_per_job(), n * d)) $(rb, re) {
        q8q8_gemv_s16_gen(myp, wp, sp, xqp, xsp, n, int64(rb) * mr, int64(re) * mr)
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_q8q8_f16s(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_group3_s16_gen(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : uint16 const?;
                                woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng0 = d0 / mr
    let ng1 = d1 / mr
    let ng2 = d2 / mr
    let ngtot = ng0 + ng1 + ng2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    maybe_parallel_for(0, int(ngtot), matmul_chunks_gemv(int(ngtot * mr), get_jobque_team_mode() ? get_q8_batch_chunks_per_job() : 1, n * (d0 + d1 + d2))) $(rb, re) {
        unsafe {
            let b0 = int64(rb)
            let e0 = min(int64(re), ng0)
            if (b0 < e0) {
                q8q8_gemv_s16_gen(w0, wp + woff0, sp + woff0 / 32l, xqp, xsp, n, b0 * mr, e0 * mr)
            }
            let b1 = max(int64(rb) - ng0, 0l)
            let e1 = min(int64(re) - ng0, ng1)
            if (b1 < e1) {
                q8q8_gemv_s16_gen(w1, wp + woff1, sp + woff1 / 32l, xqp, xsp, n, b1 * mr, e1 * mr)
            }
            let b2 = max(int64(rb) - ng0 - ng1, 0l)
            let e2 = min(int64(re) - ng0 - ng1, ng2)
            if (b2 < e2) {
                q8q8_gemv_s16_gen(w2, wp + woff2, sp + woff2 / 32l, xqp, xsp, n, b2 * mr, e2 * mr)
            }
        }
    }
    unsafe {
        for (i in range64(ng0 * mr, d0)) {
            w0[i] = dot_q8q8_f16s(wp + woff0 + i * n, sp + woff0 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng1 * mr, d1)) {
            w1[i] = dot_q8q8_f16s(wp + woff1 + i * n, sp + woff1 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng2 * mr, d2)) {
            w2[i] = dot_q8q8_f16s(wp + woff2 + i * n, sp + woff2 / 32l + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_groupn_s16_gen(var yp : float?; wp : int8 const?; sp : uint16 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(0, int(nregions * ng), matmul_chunks_gemv(int(nregions * ng * mr), get_q8_batch_chunks_per_job(), n * d * nregions)) $(gb, ge) {
        unsafe {
            var gg = int64(gb)
            while (gg < int64(ge)) {
                let r = gg / ng
                let gLocal = gg % ng
                let gEnd = min(int64(ge) - r * ng, ng)
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                q8q8_gemv_s16_gen(myp + r * d, wp + woff, sp + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, gLocal * mr, gEnd * mr)
                if (bp != null) {
                    for (i in range64(gLocal * mr, gEnd * mr)) {
                        myp[r * d + i] += bp[boffs[r] + i]
                    }
                }
                gg = r * ng + gEnd
            }
        }
    }
    unsafe {
        for (r in range64(nregions)) {   // row tails (d % mr): row-major per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * mr, d)) {
                var v = dot_q8q8_f16s(wp + woff + i * n, sp + woff / 32l + i * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

[init]
def dasllama_math_gen_register() {
    // Same gate as the laneq backend it superseded; needs_repack keeps it out of auto-select
    // (direct callers stay on arm64-sdot). Every slot — Q8 and mx4 — reads the STAMPED
    // layout at runtime (repacks and traversal strides off the layout companion, cores
    // generated for that mr). The q8_layout field feeds the activation-time cache the mx4
    // expand's positional map reads; it is evaluated at selection time, never at [init]
    // ([init]s run before the JIT installs generated code — the slice C mr8 bug). arm64
    // needs no availability predicate: a declined stamp still leaves the fast grp4
    // reference pair there (the s16 slots' references are scalar until the neon laneq
    // f16s twins land — wscale_f16 stays a per-box opt-in meanwhile).
    if (get_architecture_name() == "arm64" && jit_enabled()) {
        register_kernel_backend(KernelBackend(name = "arm64-gen", mm = @@q8q8_kernel_gen,
            batch = @@q8q8_batch_kernel_neon_laneq_gen, group3 = @@q8q8_group3_gen,
            repack = @@repack_q8q8_gen,
            mm_mx4 = @@mx4q8_kernel_gen, repack_mx4 = @@repack_mx4_gen,
            groupn = @@q8q8_groupn_gen, groupn_mx4 = @@mx4q8_groupn_gen,
            mm_rows = @@q8q8_gemv_gen,
            mm_s16 = @@q8q8_kernel_s16_gen, batch_s16 = @@q8q8_batch_kernel_s16_gen,
            group3_s16 = @@q8q8_group3_s16_gen, groupn_s16 = @@q8q8_groupn_s16_gen,
            mm_rows_s16 = @@q8q8_gemv_s16_gen,
            needs_repack = true, mx4_expand_interleaved = true, priority = 25,
            q8_layout = @@q8q8_layout_gen, q8_wbias = @@q8q8_wbias_gen,
            q8_kgroup = @@q8q8_kgroup_gen))
    }
    // The x64 twin (slice F emitters + the witness): the das traversals above are
    // ISA-agnostic, so the ONLY x64-specific wiring is the availability predicate — the
    // witness companion is true iff the stamped family actually emitted (a declined stamp's
    // reference bodies are the NEON functions' scalar fallbacks here, far slower than the
    // portable backend, so an un-emitted family must never load-select). avx2 is the
    // family's minimum tier (the maddubs leg).
    if (get_architecture_name() == "x86_64" && jit_enabled() && cpu_supports("avx2")) {
        register_kernel_backend(KernelBackend(name = "x64-gen", mm = @@q8q8_kernel_gen,
            batch = @@q8q8_batch_kernel_neon_laneq_gen, group3 = @@q8q8_group3_gen,
            repack = @@repack_q8q8_gen,
            mm_mx4 = @@mx4q8_kernel_gen, repack_mx4 = @@repack_mx4_gen,
            groupn = @@q8q8_groupn_gen, groupn_mx4 = @@mx4q8_groupn_gen,
            mm_rows = @@q8q8_gemv_gen,
            mm_s16 = @@q8q8_kernel_s16_gen, batch_s16 = @@q8q8_batch_kernel_s16_gen,
            group3_s16 = @@q8q8_group3_s16_gen, groupn_s16 = @@q8q8_groupn_s16_gen,
            mm_rows_s16 = @@q8q8_gemv_s16_gen,
            needs_repack = true, mx4_expand_interleaved = true, priority = 25,
            q8_layout = @@q8q8_layout_gen, q8_wbias = @@q8q8_wbias_gen,
            q8_kgroup = @@q8q8_kgroup_gen,
            available = @@q8q8_family_live))
    }
}
