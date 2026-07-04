options gen2

module dasllama_gemm_schema shared public

// The one place the Q8 interleaved-weight layout is defined (gemm_generator_plan.md part 3):
// the [llvm_code] tile generator derives its strides from q8q8_repack_type at emit time, and
// the load-time repack implements the same descriptor — one source, two callers, no desync.
// Pure das, no dependencies: required by both the llvm-jit-context generator module
// (dasllama_gemm_gen) and the runtime kernel module (dasllama_math_gen).

//! Layout descriptor for an mr-row register-tile repack.
struct Q8RepackType {
    //! rows interleaved per dword group (= the tile's mr)
    interleave : int
    //! scales pre-converted to f32 at repack time and interleaved per group
    f32_scales : bool
}

//! The repack layout an mr-row tile perm requires: mr-row block interleave with f32 group
//! scales. `needs_repack` and every kernel stride derive from this.
def q8q8_repack_type(mr : int) : Q8RepackType {
    return Q8RepackType(interleave = mr, f32_scales = true)
}

//! The mr of the REFERENCE tier's layout (repack_q8q8_neon = the q8q8_repack_type(4)
//! layout the reference stub bodies read). Non-reference mr runs on the generated pair:
//! the tile generator emits the grp<mr> kernel and the layout companion reports mr to the
//! runtime repack — stamped from one manifest entry, declining in lockstep (M4).
let GEMM_REFERENCE_MR = 4
