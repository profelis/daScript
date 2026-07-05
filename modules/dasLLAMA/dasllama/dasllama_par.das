options gen2
options no_aot = true  // macro module — compile-time only, never AOT-compiled (like jobque_boost)

module dasllama_par shared public

require jobque public
require daslib/jobque_boost public  // emitted code uses parallel_for / invoke
require daslib/ast
require daslib/rtti
require daslib/ast_boost
require daslib/templates_boost
require daslib/macro_boost

//! `maybe_parallel_for(parallel, range_begin, range_end, num_jobs) $(rb, re) { ... }` —
//! parallel_for with a leading runtime `parallel` flag. When `parallel` is true it threads the
//! work across `num_jobs` chunks exactly like parallel_for; when false it runs the SAME block once,
//! inline on the calling thread (no job dispatch, no wait group). Lets a kernel gate on a runtime
//! size threshold without duplicating its loop body across an if/else. The block takes just the
//! chunk bounds `(rb, re)` — no `wg`/`notify_and_release` ceremony; the parallel arm adds it.
[tag_function(tag_maybe_parallel_for), unused_argument(parallel, range_begin, range_end, num_jobs, blk)]
def maybe_parallel_for(parallel : bool; range_begin, range_end : int; num_jobs : int;
                       blk : block<(rb : int; re : int) : void>) {
    //! stub — rewritten by MaybeParallelForMacro into a runtime if/else
}

//! `maybe_parallel_for(range_begin, range_end, num_jobs) $(rb, re) { ... }` — the
//! work-proportional form: `num_jobs` is evaluated ONCE; > 1 dispatches exactly like the bool
//! form's parallel arm, and <= 1 runs the block inline. Pair with the work-aware
//! matmul_chunks / matmul_chunks_gemv shapers, which return 1 when lanes_for_work says the
//! matmul isn't worth a dispatch.
[tag_function(tag_maybe_parallel_for_nj), unused_argument(range_begin, range_end, num_jobs, blk)]
def maybe_parallel_for(range_begin, range_end : int; num_jobs : int;
                       blk : block<(rb : int; re : int) : void>) {
    //! stub — rewritten by MaybeParallelForNjMacro into a runtime if/else
}

// Shared arm bodies — ONE source of truth for both lowerings so the arms can't drift.
// parallel: team mode on → team_parallel_for (workers self-serve chunks off one atomic, one
//   lambda clone per worker); off → parallel_for (its macro wraps the body in new_job, one
//   fifo job per chunk + wait-group notify). inline: invoke the block on the calling thread.
//   The user block body is instantiated in each arm; only one arm runs.
// Synthesize the wrapper param names so they can't shadow the user block's own params.
def private mpf_par_arm(beginE, endE, njE, blkE : ExpressionPtr; at : LineInfo) : array<ExpressionPtr> {
    let rbN = make_unique_private_name("mpf_rb", at)
    let reN = make_unique_private_name("mpf_re", at)
    let wgN = make_unique_private_name("mpf_wg", at)
    let rbT = make_unique_private_name("mpf_trb", at)
    let reT = make_unique_private_name("mpf_tre", at)
    return <- qmacro_block_to_array() {
        count_parallel_dispatch($e(njE))   // dispatch observability (dasllama_math)
        if (get_jobque_team_mode()) {
            team_parallel_for($e(beginE), $e(endE), $e(njE)) <| @($i(rbT) : int; $i(reT) : int) {
                invoke($e(blkE), $i(rbT), $i(reT))
            }
        } else {
            parallel_for($e(beginE), $e(endE), $e(njE)) <| $($i(rbN), $i(reN), $i(wgN)) {
                invoke($e(blkE), $i(rbN), $i(reN))
                $i(wgN) |> notify_and_release
            }
        }
    }
}

[unused_argument(at)]  // symmetry with mpf_par_arm — callers pass call.at uniformly
def private mpf_inline_arm(beginE, endE, blkE : ExpressionPtr; at : LineInfo) : array<ExpressionPtr> {
    return <- qmacro_block_to_array() {
        count_inline_run()
        invoke($e(blkE), $e(beginE), $e(endE))
    }
}

[tag_function_macro(tag="tag_maybe_parallel_for")]
class private MaybeParallelForMacro : AstFunctionAnnotation {
    def override transform(var call : ExprCallFunc?; var errors : das_string) : ExpressionPtr {
        let li = call.arguments.length() - 1
        macro_verify(li == 4 && call.arguments[li] is ExprMakeBlock, compiling_program(), call.at,
            "maybe_parallel_for expects (parallel, range_begin, range_end, num_jobs) and a $(rb, re) block")
        // args: 0=parallel, 1=range_begin, 2=range_end, 3=num_jobs, 4=block.
        // num_jobs stays lazily evaluated in the parallel arm only (the bool already decided).
        var parArm <- mpf_par_arm(call.arguments[1], call.arguments[2], call.arguments[3],
            call.arguments[4], call.at)
        var inlArm <- mpf_inline_arm(call.arguments[1], call.arguments[2], call.arguments[4], call.at)
        var qb = qmacro_block() {
            if ($e(call.arguments[0])) {
                $b(parArm)
            } else {
                $b(inlArm)
            }
        }
        qb |> force_at(call.at)
        return <- qb
    }
}

[tag_function_macro(tag="tag_maybe_parallel_for_nj")]
class private MaybeParallelForNjMacro : AstFunctionAnnotation {
    def override transform(var call : ExprCallFunc?; var errors : das_string) : ExpressionPtr {
        let li = call.arguments.length() - 1
        macro_verify(li == 3 && call.arguments[li] is ExprMakeBlock, compiling_program(), call.at,
            "maybe_parallel_for expects (range_begin, range_end, num_jobs) and a $(rb, re) block")
        // args: 0=range_begin, 1=range_end, 2=num_jobs, 3=block.
        // num_jobs binds ONCE — it both decides the arm and feeds the dispatch.
        let njN = make_unique_private_name("mpf_nj", call.at)
        var njRead = qmacro($i(njN))
        var parArm <- mpf_par_arm(call.arguments[0], call.arguments[1], njRead,
            call.arguments[3], call.at)
        var inlArm <- mpf_inline_arm(call.arguments[0], call.arguments[1], call.arguments[3], call.at)
        var qb = qmacro_block() {
            let $i(njN) = $e(call.arguments[2])
            if ($i(njN) > 1) {
                $b(parArm)
            } else {
                $b(inlArm)
            }
        }
        qb |> force_at(call.at)
        return <- qb
    }
}
