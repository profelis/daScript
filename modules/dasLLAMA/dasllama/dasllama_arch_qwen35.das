options gen2

module dasllama_arch_qwen35 shared public

require dasllama/dasllama_common

// Qwen 3.5/3.6 — hybrid: 3 of every 4 layers are Gated-DeltaNet (recurrent linear attention, no
// KV), the rest gated full attention (2x-wide Q with per-head sigmoid out-gate, partial NEOX rope
// 64/256, QK-norm). ChatML template like qwen2/qwen3; the pre-FFN norm ships as
// post_attention_norm (gpt-oss naming).
def private configure_qwen35(var c : Config) {
    c.rope_neox = true
    c.qk_norm = true
    c.q_gated = true
    c.partial_rope = true
    c.hybrid_deltanet = true
    c.post_attn_is_ffn_norm = true
}

[init]
def register_arch_qwen35() {
    var d = ArchDesc(name = "qwen35", configure = @@configure_qwen35)
    d.blocks = qwen35_blocks()
    d.chat.system.parts <- [chat_special("<|im_start|>"), chat_text("system\n"), chat_content(), chat_special("<|im_end|>"), chat_text("\n")]
    d.chat.user.parts <- [chat_special("<|im_start|>"), chat_text("user\n"), chat_content(), chat_special("<|im_end|>"), chat_text("\n")]
    d.chat.assistant_open.parts <- [chat_special("<|im_start|>"), chat_text("assistant\n")]
    d.chat.stop <- ["<|im_end|>", "<|endoftext|>"]
    register_arch("qwen35", d)
}
