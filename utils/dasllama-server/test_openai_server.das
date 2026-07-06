options gen2
options persistent_heap   // the server thread loads/frees a multi-GB model once; explicit deletes below
options stack = 262144    // the forward chain runs under the HTTP tick + C++->das bridge (matches main.das)
options fast_math = true  // ggml-parity FP laxity — this is an inference tool test, not the bit-exact suite

require dastest/testing_boost public
require openai_server                                   // the server: OpenAiServer + set_model + run_server (sibling)
require dasllama/dasllama                               // load_model / QuantMode / embed
require daslib/jobque_boost                             // with_job_status (server-thread lifecycle)
require daslib/json_boost                               // read_json / from_JV
require daslib/fio                                      // get_env_variable / stat / path_join / sleep / base_name
require math                                            // sqrt

// End-to-end conformance for the OpenAI-compatible server: spin it up on its own thread (a separate
// context — so the model loads INSIDE that thread, since g_model is a per-context module global),
// then drive /v1/models, /v1/embeddings and /v1/chat/completions over the real dashv HTTP client.
// Model-gated + JIT-only, so it's a real regression locally and a clean skip in CI (no GGUF).
// Lives here (not tests/dasLLAMA/) because a require path can't contain the '-' in "dasllama-server":
// a require_module_name is NAME tokens joined by / . % .. — so hyphenated-dir tools keep tests in-dir
// and require the sibling module by BARE name (same convention as detect-dupe / find-dupe / mcp).

let TEST_PORT = 18099

def private models_dir() : string {
    return get_env_variable("DASLLAMA_MODELS_DIR")   // empty -> MODEL_PATH is relative -> the test skips
}
let MODEL_PATH = path_join(models_dir(), "tinyllama-1.1b-chat-v1.0.Q8_0.gguf")

// Response shapes we assert on (from_JV ignores the object/model/usage fields we don't check).
struct private EmbItem {
    embedding : array<float>
    index : int
}
struct private EmbResp {
    data : array<EmbItem>
}

def private l2(v : array<float>) : float {
    var s = 0.0
    for (x in v) {
        s += x * x
    }
    return sqrt(s)
}

def private vecs_equal(a, b : array<float>) : bool {
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

// Start the server on a dedicated thread (model loaded in-thread), wait until it answers /v1/models,
// run the block, then POST /shutdown (flips the server context's stop flag) and join.
def private with_llama_server(model_path : string; port : int; blk : block<(base_url : string) : void>) {
    with_job_status(1) $(finished) {
        new_thread() @() {
            var m <- load_model(model_path, QuantMode.q8)
            set_model(m, "test-llm")
            run_server(port)   // blocks (with_job_que + tick loop) until POST /shutdown
            finished |> notify_and_release
        }
        let base_url = "http://127.0.0.1:{port}"
        var ready = false
        for (_attempt in range(300)) {   // up to ~30s for load + JIT
            GET("{base_url}/v1/models") $(resp) {
                if (resp != null && resp.status_code == http_status.OK) {
                    ready = true
                }
            }
            if (ready) {
                break
            }
            sleep(100u)
        }
        if (ready) {
            invoke(blk, base_url)
        }
        POST("{base_url}/shutdown", "") $(_resp) {}
        finished |> join
        assert(ready, "dasllama server became ready")
    }
}

[test]
def test_openai_server(t : T?) {
    t |> run("OpenAI server: models + embeddings + chat (needs tinyllama q8)") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA server test is JIT-only)")
            return
        }
        if (!stat(MODEL_PATH).is_valid) {
            t |> success(true, "skipped: {base_name(MODEL_PATH)} not present (set DASLLAMA_MODELS_DIR)")
            return
        }
        with_llama_server(MODEL_PATH, TEST_PORT) $(base_url) {
            // /v1/models
            GET("{base_url}/v1/models") $(resp) {
                t |> equal(int(resp.status_code), int(http_status.OK))
                var err : string
                var js = read_json(string(resp.body), err)
                t |> success(js != null, "models JSON parses")
                if (js != null) {
                    t |> equal(string(js?["object"] ?? ""), "list")
                    unsafe {
                        delete js
                    }
                }
            }
            // /v1/embeddings — single input: unit-normalized vector of the model's hidden dim
            POST("{base_url}/v1/embeddings", "\{\"input\":\"the quick brown fox\"}") $(resp) {
                t |> equal(int(resp.status_code), int(http_status.OK))
                var err : string
                var js = read_json(string(resp.body), err)
                t |> success(js != null, "embeddings JSON parses")
                if (js != null) {
                    t |> equal(string(js?["object"] ?? ""), "list")
                    let r = from_JV(js, type<EmbResp>)
                    t |> success(length(r.data) == 1, "one embedding returned")
                    if (length(r.data) == 1) {
                        t |> success(length(r.data[0].embedding) > 0, "embedding is non-empty")
                        t |> success(abs(l2(r.data[0].embedding) - 1.0) < 1.0e-4, "embedding is L2-normalized")
                    }
                    unsafe {
                        delete js
                    }
                }
            }
            // /v1/embeddings — batch: identical inputs give identical vectors (deterministic), distinct differ
            POST("{base_url}/v1/embeddings",
                 "\{\"input\":[\"hello world\",\"a different sentence\",\"hello world\"]}") $(resp) {
                t |> equal(int(resp.status_code), int(http_status.OK))
                var err : string
                var js = read_json(string(resp.body), err)
                if (js != null) {
                    let r = from_JV(js, type<EmbResp>)
                    t |> success(length(r.data) == 3, "three embeddings returned")
                    if (length(r.data) == 3) {
                        t |> success(vecs_equal(r.data[0].embedding, r.data[2].embedding),
                                     "identical inputs -> identical vectors")
                        t |> success(!vecs_equal(r.data[0].embedding, r.data[1].embedding),
                                     "distinct inputs -> distinct vectors")
                    }
                    unsafe {
                        delete js
                    }
                }
            }
            // /v1/chat/completions (non-streaming) — end-to-end generation smoke
            POST("{base_url}/v1/chat/completions",
                 "\{\"messages\":[\{\"role\":\"user\",\"content\":\"Say hi.\"}],\"max_tokens\":8}") $(resp) {
                t |> equal(int(resp.status_code), int(http_status.OK))
                var err : string
                var js = read_json(string(resp.body), err)
                t |> success(js != null, "chat JSON parses")
                if (js != null) {
                    t |> equal(string(js?["object"] ?? ""), "chat.completion")
                    unsafe {
                        delete js
                    }
                }
            }
        }
    }
}
