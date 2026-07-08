options gen2

module dasllama_arch_qwen3moe shared public

require dasllama/dasllama_common

// Qwen3-MoE (30B-A3B / 235B-A22B) — Qwen3 attention (per-head QK-norm, NEOX rope, no QKV bias)
// with the routed-experts FFN: softmax router -> RENORMALIZED top-k, and NO shared expert. vs
// qwen2moe: qwen2moe leaves the top-k weights un-renormalized and adds a sigmoid-gated shared
// expert; qwen3moe renormalizes and drops the shared expert. The expert geometry (48/128/8/768 on
// the 30B-A3B) comes from GGUF metadata at load. llama.cpp hardcodes norm_w=true in build_qwen3moe,
// so norm_topk_prob defaults true here (the loader still honors an explicit expert_weights_norm key).
def private configure_qwen3moe(var c : Config) {
    c.rope_neox = true
    c.qk_norm = true
    c.moe = true
    c.norm_topk_prob = true
}

[init]
def register_arch_qwen3moe() {
    var d = ArchDesc(name = "qwen3moe", configure = @@configure_qwen3moe)
    d.blocks = moe_blocks()
    d.chat.system.parts <- [chat_special("<|im_start|>"), chat_text("system\n"), chat_content(), chat_special("<|im_end|>"), chat_text("\n")]
    d.chat.user.parts <- [chat_special("<|im_start|>"), chat_text("user\n"), chat_content(), chat_special("<|im_end|>"), chat_text("\n")]
    d.chat.assistant_open.parts <- [chat_special("<|im_start|>"), chat_text("assistant\n")]
    d.chat.stop <- ["<|im_end|>", "<|endoftext|>"]
    register_arch("qwen3moe", d)
}
