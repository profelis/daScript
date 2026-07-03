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

[tag_function_macro(tag="tag_maybe_parallel_for")]
class private MaybeParallelForMacro : AstFunctionAnnotation {
    def override transform(var call : ExprCallFunc?; var errors : das_string) : ExpressionPtr {
        let li = call.arguments.length() - 1
        macro_verify(li == 4 && call.arguments[li] is ExprMakeBlock, compiling_program(), call.at,
            "maybe_parallel_for expects (parallel, range_begin, range_end, num_jobs) and a $(rb, re) block")
        // args: 0=parallel, 1=range_begin, 2=range_end, 3=num_jobs, 4=block.
        // parallel: team mode on → team_parallel_for (workers self-serve chunks off one atomic, one
        //   lambda clone per worker); off → parallel_for (its macro wraps the body in new_job, one
        //   fifo job per chunk + wait-group notify). single: invoke the block inline. The user block
        //   body is instantiated in each arm; only one arm runs.
        // Synthesize the wrapper param names so they can't shadow the user block's own params.
        let rbN = make_unique_private_name("mpf_rb", call.at)
        let reN = make_unique_private_name("mpf_re", call.at)
        let wgN = make_unique_private_name("mpf_wg", call.at)
        let rbT = make_unique_private_name("mpf_trb", call.at)
        let reT = make_unique_private_name("mpf_tre", call.at)
        var qb = qmacro_block() {
            if ($e(call.arguments[0])) {
                count_parallel_dispatch($e(call.arguments[3]))   // dispatch observability (dasllama_math)
                if (get_jobque_team_mode()) {
                    team_parallel_for($e(call.arguments[1]), $e(call.arguments[2]), $e(call.arguments[3])) <| @($i(rbT) : int; $i(reT) : int) {
                        invoke($e(call.arguments[4]), $i(rbT), $i(reT))
                    }
                } else {
                    parallel_for($e(call.arguments[1]), $e(call.arguments[2]), $e(call.arguments[3])) <| $($i(rbN), $i(reN), $i(wgN)) {
                        invoke($e(call.arguments[4]), $i(rbN), $i(reN))
                        $i(wgN) |> notify_and_release
                    }
                }
            } else {
                count_inline_run()
                invoke($e(call.arguments[4]), $e(call.arguments[1]), $e(call.arguments[2]))
            }
        }
        qb |> force_at(call.at)
        return <- qb
    }
}
