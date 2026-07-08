// simple_ids_margin — simple_ids + per-step logit-margin diagnostics (to stderr).
//
// Same greedy CPU generation as simple_ids (GEN_IDS to stdout), but at each step also emits, to
// stderr, the reference's own top-1/top-2 logits and margin. Use it to tell a dasLLAMA *bug* from a
// genuine near-tie: where dasLLAMA diverges from GEN_IDS, a SMALL oracle margin means the reference
// itself is near-tied (a coin-flip no float engine can pin — not a forward bug), a LARGE margin
// means dasLLAMA computed the wrong answer. Minted the gemma-4-26B MoE near-tie analysis (Wave G2).
// The l[...] probes are hard-coded ids — retarget them per investigation.
//
// Build (from the llama.cpp checkout, against its already-built libs):
//   clang++ -std=c++17 -O2 -I include -I ggml/include harness/oracle/simple_ids_margin.cpp \
//     -L build/bin -lllama -lggml -Wl,-rpath,"$PWD/build/bin" -o build/bin/simple_ids_margin
// Run:
//   build/bin/simple_ids_margin -m <model.gguf> -n 40 -p "<prompt>" 2>margins.log

#include "llama.h"
#include <clocale>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

static void print_usage(const char * argv0) {
    fprintf(stderr, "\nusage: %s -m model.gguf [-n n_predict] [-ngl n_gpu_layers] [-p prompt]\n\n", argv0);
}

int main(int argc, char ** argv) {
    std::setlocale(LC_NUMERIC, "C");

    std::string model_path;
    std::string prompt = "Once upon a time";
    int ngl = 0;          // CPU only — match dasLLAMA's CPU forward so argmax ties agree
    int n_predict = 40;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            model_path = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            n_predict = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "-ngl") == 0 && i + 1 < argc) {
            ngl = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            prompt = argv[++i];
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }
    if (model_path.empty()) {
        print_usage(argv[0]);
        return 1;
    }

    ggml_backend_load_all();

    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = ngl;
    llama_model * model = llama_model_load_from_file(model_path.c_str(), model_params);
    if (model == NULL) {
        fprintf(stderr, "simple_ids: unable to load model\n");
        return 1;
    }

    const llama_vocab * vocab = llama_model_get_vocab(model);

    // tokenize the prompt exactly as llama.cpp would (add BOS + specials)
    const int n_prompt = -llama_tokenize(vocab, prompt.c_str(), prompt.size(), NULL, 0, true, true);
    std::vector<llama_token> prompt_tokens(n_prompt);
    if (llama_tokenize(vocab, prompt.c_str(), prompt.size(), prompt_tokens.data(), prompt_tokens.size(), true, true) < 0) {
        fprintf(stderr, "simple_ids: tokenize failed\n");
        return 1;
    }

    printf("PROMPT_IDS:");
    for (auto id : prompt_tokens) {
        printf(" %d", id);
    }
    printf("\n");

    llama_context_params ctx_params = llama_context_default_params();
    ctx_params.n_ctx   = n_prompt + n_predict;
    ctx_params.n_batch = n_prompt;
    ctx_params.no_perf = true;
    llama_context * ctx = llama_init_from_model(model, ctx_params);
    if (ctx == NULL) {
        fprintf(stderr, "simple_ids: failed to create context\n");
        return 1;
    }

    auto sparams = llama_sampler_chain_default_params();
    sparams.no_perf = true;
    llama_sampler * smpl = llama_sampler_chain_init(sparams);
    llama_sampler_chain_add(smpl, llama_sampler_init_greedy());

    llama_batch batch = llama_batch_get_one(prompt_tokens.data(), prompt_tokens.size());
    llama_token new_token_id;
    std::vector<llama_token> gen;
    gen.reserve(n_predict);
    for (int n = 0; n < n_predict; n++) {
        if (llama_decode(ctx, batch)) {
            fprintf(stderr, "simple_ids: decode failed at step %d\n", n);
            return 1;
        }
        const float * lg = llama_get_logits_ith(ctx, -1);
        int nv = llama_vocab_n_tokens(vocab);
        int t1 = 0; for (int v = 1; v < nv; v++) if (lg[v] > lg[t1]) t1 = v;
        int t2 = -1; for (int v = 0; v < nv; v++) { if (v == t1) continue; if (t2 < 0 || lg[v] > lg[t2]) t2 = v; }
        fprintf(stderr, "OSTEP %d: top1=%d(%.4f) top2=%d(%.4f) margin=%.4f  l[236778]=%.4f l[236800]=%.4f\n",
                n, t1, lg[t1], t2, lg[t2], lg[t1]-lg[t2], lg[236778], lg[236800]);
        new_token_id = llama_sampler_sample(smpl, ctx, -1);   // greedy argmax over the last position
        gen.push_back(new_token_id);
        batch = llama_batch_get_one(&new_token_id, 1);        // &new_token_id stays valid until the next decode
    }

    printf("GEN_IDS:");
    for (auto id : gen) {
        printf(" %d", id);
    }
    printf("\n");

    llama_sampler_free(smpl);
    llama_free(ctx);
    llama_model_free(model);
    return 0;
}
