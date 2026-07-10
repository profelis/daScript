options gen2
options stack = 131072    // model frames: a Scheduler (workspace Session inline) + reference Sessions
options persistent_heap   // each test frees its model/scheduler before the next loads

require dastest/testing_boost public
require llm_scheduler                                   // the scheduler under test (sibling — bare require, hyphenated dir)
require dasllama/dasllama                               // facade: load/encode/generate references + engine knobs
require daslib/jobque_boost
require daslib/fio
require math

// Unit gates for the continuous-batching scheduler — all through the SchedEvent seam, zero HTTP:
// scheduler ≡ generate bit-exact (1 stream), chunk-size invariance under classic prefill, staggered
// admit + queue overflow, stop/budget/context-length finishes, evict mid-run. Model-gated + JIT-only
// (SmolLM2-135M GGUF via DASLLAMA_MODELS_DIR), same skip contract as test_openai_server.

def private models_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}
let MODEL_PATH = path_join(models_dir(), "SmolLM2-135M-Instruct-Q8_0.gguf")

def private model_missing(t : T?) : bool {
    if (!jit_enabled()) {
        t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
        return true
    }
    if (!stat(MODEL_PATH).is_valid) {
        t |> success(true, "skipped: {MODEL_PATH} not present")
        return true
    }
    return false
}

def private load_capped(cap : int64) : Model {
    var m <- load_model(MODEL_PATH, QuantMode.q8)
    m.config.seq_len = min(m.config.seq_len, cap)
    return <- m
}

def private same(a, b : array<int64>) : bool {
    if (length(a) != length(b)) {
        return false
    }
    for (i in range(length(a))) {
        if (a[i] != b[i]) {
            return false
        }
    }
    return true
}

// One stream's reference: generate() with the wiring's stop protocol (stop token ends the stream
// unemitted; otherwise the budget runs out) — what the scheduler must reproduce.
struct private RefStream {
    toks : array<int64>
    pieces : array<string>
    finish : string
}

def private ref_generate(m : Model; prompt : array<int64>; params : SamplingParams;
                         max_new : int64; stop_ids : array<int64>; seed : int = 0) : RefStream {
    var s <- create_session(m)
    if (seed != 0) {
        set_seed(s, seed)
    }
    var r : RefStream
    var stops := stop_ids
    var hit_stop = false
    generate(m, s, prompt, params, max_new) $(id, pc) {
        for (sid in stops) {
            if (id == sid) {
                hit_stop = true
                return false
            }
        }
        r.toks |> push(id)
        r.pieces |> push(pc)
        return true
    }
    r.finish = hit_stop ? "stop" : "length"
    delete s
    return <- r
}

def private make_req(id : int64; prompt : array<int64>; params : SamplingParams; max_new : int64;
                     stop_ids : array<int64>; seed : int = 0) : PendingReq {
    var r <- PendingReq(id = id, params = params, max_new = max_new, seed = seed)
    r.prompt := prompt
    r.stop_ids := stop_ids
    return <- r
}

// step until idle (bounded — a runaway scheduler must not hang the suite)
def private drain(m : Model; var sch : Scheduler; var events : array<SchedEvent>) {
    var steps = 0
    while (scheduler_step(m, sch, events)) {
        steps ++
        if (steps > 4096) {
            panic("test_llm_scheduler: scheduler did not go idle in 4096 steps")
        }
    }
}

def private toks_of(events : array<SchedEvent>; id : int64) : array<int64> {
    return <- [for (e in events); e.token; where e.stream == id && e.kind == SchedEventKind.piece]
}

def private pieces_of(events : array<SchedEvent>; id : int64) : array<string> {
    return <- [for (e in events); e.text; where e.stream == id && e.kind == SchedEventKind.piece]
}

def private finished_of(events : array<SchedEvent>; id : int64) : SchedEvent {
    for (e in events) {
        if (e.stream == id && e.kind == SchedEventKind.finished) {
            return e
        }
    }
    return SchedEvent(stream = -1l)
}

// ===== scheduler ≡ generate (1 stream): greedy bit-exact, seeded sampling, stop finish =====

[test]
def test_scheduler_matches_generate(t : T?) {
    t |> run("scheduler ≡ generate: bit-exact stream, seeded sampling, stop/budget (needs SmolLM2-135M)") @(t : T?) {
        if (model_missing(t)) {
            return
        }
        with_job_que() {
            setup_dasllama_jobque()
            var m <- load_capped(128l)
            var prompt <- encode(m, "Once upon a time", true, false)
            var none : array<int64>
            // greedy, single-chunk prefill: the eval sequence is identical to generate()'s, so the
            // emitted stream must be BIT-exact (B==1 eval_batch delegates to the same forward())
            let greedy = SamplingParams()
            var ref <- ref_generate(m, prompt, greedy, 10l, none)
            var sch <- create_scheduler(m, 1l, 4l, 512l)
            var events : array<SchedEvent>
            t |> success(submit(m, sch, make_req(1l, prompt, greedy, 10l, none)), "greedy stream queued")
            drain(m, sch, events)
            var got <- toks_of(events, 1l)
            var gotp <- pieces_of(events, 1l)
            t |> success(same(got, ref.toks), "greedy tokens ≡ generate() bit-exact")
            t |> equal(length(gotp), length(ref.pieces))
            for (i in range(length(gotp))) {
                t |> equal(gotp[i], ref.pieces[i])
            }
            let fin = finished_of(events, 1l)
            t |> equal(fin.finish, "length")
            t |> equal(fin.n_gen, 10l)
            t |> equal(fin.n_prompt, int64(length(prompt)))
            t |> success(fin.ttft_us > 0l, "TTFT recorded")
            t |> equal(sch.gen_tokens, 10l)
            t |> success(sch.decode_steps > 0l, "decode steps counted")
            // seeded sampling (temp + top-k): the scheduler makes the same sample() calls in the
            // same order, so a seeded run reproduces generate() exactly
            let sp = SamplingParams(temp = 0.8, top_k = 40l)
            var ref2 <- ref_generate(m, prompt, sp, 10l, none, 4242)
            events |> clear()
            t |> success(submit(m, sch, make_req(2l, prompt, sp, 10l, none, 4242)), "seeded stream queued")
            drain(m, sch, events)
            var got2 <- toks_of(events, 2l)
            t |> success(same(got2, ref2.toks), "seeded sampled tokens ≡ generate()")
            // stop finish: pick the first greedy token that did not occur earlier in the stream,
            // declare it a stop id — the scheduler must end there, stop token unemitted
            var kstop = -1
            for (k in range(1, length(ref.toks))) {
                var seen = false
                for (j in range(k)) {
                    seen ||= ref.toks[j] == ref.toks[k]
                }
                if (!seen) {
                    kstop = k
                    break
                }
            }
            if (kstop > 0) {
                var stops <- [ref.toks[kstop]]
                var ref3 <- ref_generate(m, prompt, greedy, 10l, stops)
                events |> clear()
                t |> success(submit(m, sch, make_req(3l, prompt, greedy, 10l, stops)), "stop stream queued")
                drain(m, sch, events)
                var got3 <- toks_of(events, 3l)
                t |> equal(length(got3), kstop)
                t |> success(same(got3, ref3.toks), "stop-bounded tokens ≡ generate()")
                let fin3 = finished_of(events, 3l)
                t |> equal(fin3.finish, "stop")
                t |> equal(fin3.n_gen, int64(kstop))
                delete got3
                delete ref3
                delete stops
            } else {
                t |> success(true, "no unique stop candidate in 10 greedy tokens — stop arm skipped")
            }
            delete got
            delete gotp
            delete got2
            delete ref
            delete ref2
            delete events
            unsafe {
                delete sch
            }
            delete prompt
            delete m
        }
    }
}

// ===== chunked prefill: {1,3,17,64} produce the identical stream under classic prefill =====

[test]
def test_scheduler_chunk_sizes(t : T?) {
    t |> run("prefill chunk sizes 1/3/17/64 give the same stream — classic mode (needs SmolLM2-135M)") @(t : T?) {
        if (model_missing(t)) {
            return
        }
        with_job_que() {
            setup_dasllama_jobque()
            var m <- load_capped(128l)
            // classic prefill is bit-exact under ANY chunking (test_prefill's contract) — the same
            // pin as test_chat's render-seam case, so every chunk size must yield ONE stream
            let saved_mode = get_prefill_attn_mode()
            set_prefill_attn_mode(AttnPrefillMode.classic)
            var prompt <- encode(m, "The quick brown fox jumps over the lazy dog while the little robot watches from a small hill near the old village bakery and counts every bird that crosses the evening sky", true, false)
            t |> success(int64(length(prompt)) > 17l, "prompt spans multiple chunks ({length(prompt)} tokens)")
            var none : array<int64>
            let greedy = SamplingParams()
            var first <- [-1l, -1l, -1l, -1l]
            var streams : array<array<int64>>
            for (ci, K in range(4), [1l, 3l, 17l, 64l]) {
                var sch <- create_scheduler(m, 1l, 4l, K)
                var events : array<SchedEvent>
                t |> success(submit(m, sch, make_req(int64(ci), prompt, greedy, 6l, none)), "stream queued (K={K})")
                drain(m, sch, events)
                var got <- toks_of(events, int64(ci))
                first[ci] = length(got) > 0 ? got[0] : -1l
                streams |> emplace(got)
                delete events
                unsafe {
                    delete sch
                }
            }
            t |> success(first[0] >= 0l, "chunked runs produced tokens")
            for (ci in range(1, 4)) {
                t |> equal(first[ci], first[0])
                t |> success(same(streams[ci], streams[0]), "K arm {ci}: full stream identical to K=1")
            }
            set_prefill_attn_mode(saved_mode)
            delete first
            delete streams
            delete prompt
            delete m
        }
    }
}

// ===== staggered admit, queue overflow, queued eviction, multi-stream token match =====

[test]
def test_scheduler_batching(t : T?) {
    t |> run("staggered admit + queue overflow: every stream matches its solo reference (needs SmolLM2-135M)") @(t : T?) {
        if (model_missing(t)) {
            return
        }
        with_job_que() {
            setup_dasllama_jobque()
            var m <- load_capped(128l)
            // the batch worker mirrors the std decode path — pin the fused chain off so the solo
            // generate() references share its numerics (test_batch_decode's contract)
            let prev_fused = get_fused_decode()
            set_fused_decode(false)
            let greedy = SamplingParams()
            var none : array<int64>
            var pa <- encode(m, "Once upon a time", true, false)
            var pb <- encode(m, "The little robot", true, false)
            var pc <- encode(m, "In a small village", true, false)
            var refs <- [ <- ref_generate(m, pa, greedy, 6l, none), <- ref_generate(m, pb, greedy, 6l, none),
                         <- ref_generate(m, pc, greedy, 6l, none)]
            var sch <- create_scheduler(m, 2l, 2l, 64l)
            var events : array<SchedEvent>
            t |> success(submit(m, sch, make_req(10l, pa, greedy, 6l, none)), "stream A queued")
            t |> success(submit(m, sch, make_req(11l, pb, greedy, 6l, none)), "stream B queued")
            // 3 ticks: A and B admit (cap 2) and start decoding; C arrives mid-run — staggered
            for (_i in range(3)) {
                scheduler_step(m, sch, events)
            }
            t |> equal(n_active(sch), 2l)
            t |> success(submit(m, sch, make_req(12l, pc, greedy, 6l, none)), "stream C queued mid-run")
            t |> success(submit(m, sch, make_req(13l, pa, greedy, 6l, none)), "stream D queued (fills the queue)")
            t |> success(!submit(m, sch, make_req(14l, pb, greedy, 6l, none)), "queue full: submit rejected")
            t |> success(evict(sch, 13l, events), "queued stream D evicted")
            t |> equal(finished_of(events, 13l).finish, "evicted")
            t |> equal(n_queued(sch), 1l)
            drain(m, sch, events)
            var ga <- toks_of(events, 10l)
            var gb <- toks_of(events, 11l)
            var gc <- toks_of(events, 12l)
            t |> success(same(ga, refs[0].toks), "stream A (batched) matches its solo reference")
            t |> success(same(gb, refs[1].toks), "stream B (batched) matches its solo reference")
            t |> success(same(gc, refs[2].toks), "stream C (admitted after a slot freed) matches its solo reference")
            t |> equal(finished_of(events, 12l).finish, "length")
            t |> equal(length(toks_of(events, 13l)), 0)
            t |> equal(sch.peak_active, 2l)
            t |> equal(sch.n_evicted, 1l)
            t |> equal(sch.n_finished, 3l)
            t |> success(sch.sum_batch >= 2l * 2l, "decode steps actually batched (Σ batch {sch.sum_batch})")
            set_fused_decode(prev_fused)
            delete ga
            delete gb
            delete gc
            delete events
            unsafe {
                delete sch
            }
            delete refs
            delete pa
            delete pb
            delete pc
            delete m
        }
    }
}

// ===== active eviction mid-run + the context-exhaustion length pre-check =====

[test]
def test_scheduler_evict_and_context_length(t : T?) {
    t |> run("evict mid-run leaves the survivor exact; context exhaustion finishes 'length' (needs SmolLM2-135M)") @(t : T?) {
        if (model_missing(t)) {
            return
        }
        with_job_que() {
            setup_dasllama_jobque()
            var m <- load_capped(64l)
            let prev_fused = get_fused_decode()
            set_fused_decode(false)
            let greedy = SamplingParams()
            var none : array<int64>
            var pa <- encode(m, "Once upon a time", true, false)
            var pb <- encode(m, "The little robot", true, false)
            var ref_a <- ref_generate(m, pa, greedy, 8l, none)
            var sch <- create_scheduler(m, 2l, 4l, 64l)
            var events : array<SchedEvent>
            t |> success(submit(m, sch, make_req(20l, pa, greedy, 8l, none)), "survivor queued")
            t |> success(submit(m, sch, make_req(21l, pb, greedy, 8l, none)), "victim queued")
            for (_i in range(4)) {   // both prefilled + a few decode steps at B=2
                scheduler_step(m, sch, events)
            }
            let b_before = length(toks_of(events, 21l))
            t |> success(b_before > 0, "victim generated before eviction")
            t |> success(evict(sch, 21l, events), "victim evicted mid-run")
            t |> equal(finished_of(events, 21l).finish, "evicted")
            drain(m, sch, events)
            t |> equal(length(toks_of(events, 21l)), b_before)
            var ga <- toks_of(events, 20l)
            t |> success(same(ga, ref_a.toks), "survivor stream unaffected by the eviction")
            t |> equal(finished_of(events, 20l).finish, "length")
            // context exhaustion: budget far beyond the capped seq_len — the decode pre-check must
            // finish "length" (n_gen = seq_len - n_prompt + 1) instead of reaching the engine panic
            events |> clear()
            t |> success(submit(m, sch, make_req(22l, pa, greedy, 512l, none)), "exhaustion stream queued")
            drain(m, sch, events)
            let fin = finished_of(events, 22l)
            t |> equal(fin.finish, "length")
            t |> equal(fin.n_gen, m.config.seq_len - int64(length(pa)) + 1l)
            set_fused_decode(prev_fused)
            delete ga
            delete events
            unsafe {
                delete sch
            }
            delete ref_a
            delete pa
            delete pb
            delete m
        }
    }
}
