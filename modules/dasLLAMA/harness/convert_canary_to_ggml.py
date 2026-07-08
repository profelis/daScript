#!/usr/bin/env python3
# Convert nvidia/canary-qwen-2.5b (SALM: FastConformer encoder + Qwen3-1.7B decoder + LoRA)
# from its HF-native single safetensors into the dasLLAMA two-file ASR pair:
#
#   1. decoder GGUF   — the LoRA-MERGED Qwen3-1.7B (W += (alpha/r)*B*A = W + 2.0*B*A on
#                       q_proj/v_proj), a plain qwen3-arch GGUF via llama.cpp convert_hf_to_gguf.py
#   2. encoder bin    — the FastConformer-32 encoder + perception.proj, a self-describing
#                       named-tensor f32 container (bf16 -> f32 is lossless), read by
#                       dasllama_canary.das
#
# The checkpoint ships HF-native config.json + model.safetensors (bf16, 1718 tensors) — NOT a
# .nemo — so we convert from safetensors directly (no NeMo import needed).
#
# Usage:
#   python convert_canary_to_ggml.py \
#     --src ~/.cache/huggingface/hub/models--nvidia--canary-qwen-2.5b/snapshots/<hash> \
#     --qwen3-tokenizer ~/.cache/huggingface/hub/models--Qwen--Qwen3-1.7B/snapshots/<hash> \
#     --llama-cpp ~/Work/llama.cpp \
#     --out-dir ~/Work/llama.cpp/models \
#     --decoder-outtype f16
#
# Any of --src / --qwen3-tokenizer resolve the newest snapshot automatically if given the
# models--.../ hub root or left unset.

import argparse
import glob
import json
import os
import shutil
import struct
import subprocess
import sys
import tempfile

import numpy as np
from safetensors import safe_open

CANARY_MAGIC = 0x59524E43  # bytes "CNRY" little-endian
CANARY_BIN_VERSION = 1
LORA_SCALE = 2.0  # alpha/r = 256/128


def _newest_snapshot(path, repo_substr):
    """Resolve a HF hub dir (models--...) to its newest snapshot, or pass through a real dir."""
    if path and os.path.isdir(path) and glob.glob(os.path.join(path, "*.safetensors")) + \
            glob.glob(os.path.join(path, "*.json")):
        # already a snapshot dir (has weights or config)
        if os.path.exists(os.path.join(path, "config.json")) or \
                glob.glob(os.path.join(path, "*.safetensors")) or \
                os.path.exists(os.path.join(path, "tokenizer.json")):
            return path
    roots = []
    if path:
        roots.append(path)
    roots.append(os.path.expanduser(f"~/.cache/huggingface/hub/{repo_substr}"))
    for root in roots:
        snaps = sorted(glob.glob(os.path.join(root, "snapshots", "*")))
        if snaps:
            return snaps[-1]
    raise FileNotFoundError(f"could not resolve a snapshot dir for {repo_substr} (tried {roots})")


def bf16_to_f32(t):
    return t.astype(np.float32)


# ---------------------------------------------------------------------------
# Encoder bin writer
# ---------------------------------------------------------------------------

def _wi(f, v):
    f.write(struct.pack("<i", int(v)))


def _wf(f, v):
    f.write(struct.pack("<f", float(v)))


def _wtensor(f, name, arr):
    arr = np.ascontiguousarray(arr.astype(np.float32))
    nb = name.encode("utf-8")
    f.write(struct.pack("<i", len(nb)))
    f.write(nb)
    f.write(struct.pack("<q", int(arr.size)))
    arr.tofile(f)


def write_encoder_bin(st, out_path):
    """Write the FastConformer encoder + projector as a named-tensor f32 container."""
    def g(name):
        return st.get_tensor(name).float().numpy()

    d_model = 1024
    n_head = 8
    n_ff = 4096
    n_mel = 128
    n_fft = 512
    subsampling = 8
    n_sub_ch = 256
    conv_kernel = 9
    # count encoder layers
    n_layer = 0
    while f"perception.encoder.layers.{n_layer}.norm_out.weight" in st.keys():
        n_layer += 1
    proj_w = g("perception.proj.weight")   # [2048, 1024]
    proj_dim = proj_w.shape[0]
    fb = g("perception.preprocessor.featurizer.fb")     # [1, 128, 257]
    fb = np.squeeze(fb)                                  # [128, 257]
    n_fb = fb.shape[1]
    window = g("perception.preprocessor.featurizer.window")  # [400]
    assert fb.shape == (n_mel, n_fb), fb.shape
    assert n_fb == n_fft // 2 + 1

    print(f"encoder: d_model={d_model} n_layer={n_layer} n_head={n_head} n_ff={n_ff} "
          f"n_mel={n_mel} proj_dim={proj_dim} n_fb={n_fb} n_window={window.shape[0]}")

    with open(out_path, "wb") as f:
        f.write(struct.pack("<I", CANARY_MAGIC))
        _wi(f, CANARY_BIN_VERSION)
        for v in (d_model, n_layer, n_head, n_ff, n_mel, n_fft, subsampling,
                  n_sub_ch, conv_kernel, proj_dim):
            _wi(f, v)
        _wf(f, 1e-5)      # layernorm eps
        _wi(f, n_fb)
        # mel filterbank [n_mel * n_fb], then window
        np.ascontiguousarray(fb.astype(np.float32)).tofile(f)
        _wi(f, window.shape[0])
        np.ascontiguousarray(window.astype(np.float32)).tofile(f)

        # tensor records (name / n_elem / f32 data)
        pe = "perception.encoder"
        # pre-encode subsampling stack + out
        _wtensor(f, "pre_encode.conv.0.weight", np.squeeze(g(f"{pe}.pre_encode.conv.0.weight")).reshape(n_sub_ch, 9))
        _wtensor(f, "pre_encode.conv.0.bias", g(f"{pe}.pre_encode.conv.0.bias"))
        _wtensor(f, "pre_encode.conv.2.weight", np.squeeze(g(f"{pe}.pre_encode.conv.2.weight")).reshape(n_sub_ch, 9))
        _wtensor(f, "pre_encode.conv.2.bias", g(f"{pe}.pre_encode.conv.2.bias"))
        _wtensor(f, "pre_encode.conv.3.weight", np.squeeze(g(f"{pe}.pre_encode.conv.3.weight")).reshape(n_sub_ch, n_sub_ch))
        _wtensor(f, "pre_encode.conv.3.bias", g(f"{pe}.pre_encode.conv.3.bias"))
        _wtensor(f, "pre_encode.conv.5.weight", np.squeeze(g(f"{pe}.pre_encode.conv.5.weight")).reshape(n_sub_ch, 9))
        _wtensor(f, "pre_encode.conv.5.bias", g(f"{pe}.pre_encode.conv.5.bias"))
        _wtensor(f, "pre_encode.conv.6.weight", np.squeeze(g(f"{pe}.pre_encode.conv.6.weight")).reshape(n_sub_ch, n_sub_ch))
        _wtensor(f, "pre_encode.conv.6.bias", g(f"{pe}.pre_encode.conv.6.bias"))
        _wtensor(f, "pre_encode.out.weight", g(f"{pe}.pre_encode.out.weight"))   # [1024, 4096]
        _wtensor(f, "pre_encode.out.bias", g(f"{pe}.pre_encode.out.bias"))

        for l in range(n_layer):
            p = f"{pe}.layers.{l}"
            def gl(sub):
                return g(f"{p}.{sub}")
            _wtensor(f, f"L{l}.norm_ff1.weight", gl("norm_feed_forward1.weight"))
            _wtensor(f, f"L{l}.norm_ff1.bias", gl("norm_feed_forward1.bias"))
            _wtensor(f, f"L{l}.ff1.linear1.weight", gl("feed_forward1.linear1.weight"))
            _wtensor(f, f"L{l}.ff1.linear1.bias", gl("feed_forward1.linear1.bias"))
            _wtensor(f, f"L{l}.ff1.linear2.weight", gl("feed_forward1.linear2.weight"))
            _wtensor(f, f"L{l}.ff1.linear2.bias", gl("feed_forward1.linear2.bias"))
            _wtensor(f, f"L{l}.norm_att.weight", gl("norm_self_att.weight"))
            _wtensor(f, f"L{l}.norm_att.bias", gl("norm_self_att.bias"))
            _wtensor(f, f"L{l}.attn.q.weight", gl("self_attn.linear_q.weight"))
            _wtensor(f, f"L{l}.attn.q.bias", gl("self_attn.linear_q.bias"))
            _wtensor(f, f"L{l}.attn.k.weight", gl("self_attn.linear_k.weight"))
            _wtensor(f, f"L{l}.attn.k.bias", gl("self_attn.linear_k.bias"))
            _wtensor(f, f"L{l}.attn.v.weight", gl("self_attn.linear_v.weight"))
            _wtensor(f, f"L{l}.attn.v.bias", gl("self_attn.linear_v.bias"))
            _wtensor(f, f"L{l}.attn.out.weight", gl("self_attn.linear_out.weight"))
            _wtensor(f, f"L{l}.attn.out.bias", gl("self_attn.linear_out.bias"))
            _wtensor(f, f"L{l}.attn.pos.weight", gl("self_attn.linear_pos.weight"))
            _wtensor(f, f"L{l}.attn.pos_bias_u", gl("self_attn.pos_bias_u"))
            _wtensor(f, f"L{l}.attn.pos_bias_v", gl("self_attn.pos_bias_v"))
            _wtensor(f, f"L{l}.norm_conv.weight", gl("norm_conv.weight"))
            _wtensor(f, f"L{l}.norm_conv.bias", gl("norm_conv.bias"))
            _wtensor(f, f"L{l}.conv.pw1.weight", np.squeeze(gl("conv.pointwise_conv1.weight")))  # [2048, 1024]
            _wtensor(f, f"L{l}.conv.pw1.bias", gl("conv.pointwise_conv1.bias"))
            _wtensor(f, f"L{l}.conv.dw.weight", np.squeeze(gl("conv.depthwise_conv.weight")))    # [1024, 9]
            _wtensor(f, f"L{l}.conv.dw.bias", gl("conv.depthwise_conv.bias"))
            _wtensor(f, f"L{l}.conv.bn.weight", gl("conv.batch_norm.weight"))
            _wtensor(f, f"L{l}.conv.bn.bias", gl("conv.batch_norm.bias"))
            _wtensor(f, f"L{l}.conv.bn.running_mean", gl("conv.batch_norm.running_mean"))
            _wtensor(f, f"L{l}.conv.bn.running_var", gl("conv.batch_norm.running_var"))
            _wtensor(f, f"L{l}.conv.pw2.weight", np.squeeze(gl("conv.pointwise_conv2.weight")))  # [1024, 1024]
            _wtensor(f, f"L{l}.conv.pw2.bias", gl("conv.pointwise_conv2.bias"))
            _wtensor(f, f"L{l}.norm_ff2.weight", gl("norm_feed_forward2.weight"))
            _wtensor(f, f"L{l}.norm_ff2.bias", gl("norm_feed_forward2.bias"))
            _wtensor(f, f"L{l}.ff2.linear1.weight", gl("feed_forward2.linear1.weight"))
            _wtensor(f, f"L{l}.ff2.linear1.bias", gl("feed_forward2.linear1.bias"))
            _wtensor(f, f"L{l}.ff2.linear2.weight", gl("feed_forward2.linear2.weight"))
            _wtensor(f, f"L{l}.ff2.linear2.bias", gl("feed_forward2.linear2.bias"))
            _wtensor(f, f"L{l}.norm_out.weight", gl("norm_out.weight"))
            _wtensor(f, f"L{l}.norm_out.bias", gl("norm_out.bias"))
        _wtensor(f, "proj.weight", proj_w)              # [2048, 1024]
        _wtensor(f, "proj.bias", g("perception.proj.bias"))
    sz = os.path.getsize(out_path) / (1024 ** 2)
    print(f"wrote encoder bin: {out_path} ({sz:.1f} MB)")


# ---------------------------------------------------------------------------
# Decoder GGUF (LoRA-merged Qwen3-1.7B)
# ---------------------------------------------------------------------------

def write_decoder_gguf(st, qwen3_tok_dir, llama_cpp_dir, out_gguf, outtype):
    from safetensors.torch import save_file
    import torch

    n_layer = 0
    while f"llm.base_model.model.model.layers.{n_layer}.input_layernorm.weight" in st.keys():
        n_layer += 1
    print(f"decoder: qwen3 {n_layer} layers, LoRA-merging q_proj/v_proj (scale {LORA_SCALE})")

    def T(name):
        return st.get_tensor(name)  # torch tensor (bf16)

    sd = {}
    sd["model.embed_tokens.weight"] = T("embed_tokens.weight").clone()
    base = "llm.base_model.model.model"
    for l in range(n_layer):
        lp = f"{base}.layers.{l}"
        # LoRA merge (q_proj, v_proj): W += scale * (B @ A), in f32 then back to bf16
        for proj in ("q_proj", "v_proj"):
            W = T(f"{lp}.self_attn.{proj}.base_layer.weight").to(torch.float32)
            A = T(f"{lp}.self_attn.{proj}.lora_A.default.weight").to(torch.float32)  # [r, in]
            B = T(f"{lp}.self_attn.{proj}.lora_B.default.weight").to(torch.float32)  # [out, r]
            Wm = W + LORA_SCALE * (B @ A)
            sd[f"model.layers.{l}.self_attn.{proj}.weight"] = Wm.to(torch.bfloat16)
        sd[f"model.layers.{l}.self_attn.k_proj.weight"] = T(f"{lp}.self_attn.k_proj.weight").clone()
        sd[f"model.layers.{l}.self_attn.o_proj.weight"] = T(f"{lp}.self_attn.o_proj.weight").clone()
        sd[f"model.layers.{l}.self_attn.q_norm.weight"] = T(f"{lp}.self_attn.q_norm.weight").clone()
        sd[f"model.layers.{l}.self_attn.k_norm.weight"] = T(f"{lp}.self_attn.k_norm.weight").clone()
        sd[f"model.layers.{l}.input_layernorm.weight"] = T(f"{lp}.input_layernorm.weight").clone()
        sd[f"model.layers.{l}.post_attention_layernorm.weight"] = T(f"{lp}.post_attention_layernorm.weight").clone()
        sd[f"model.layers.{l}.mlp.gate_proj.weight"] = T(f"{lp}.mlp.gate_proj.weight").clone()
        sd[f"model.layers.{l}.mlp.up_proj.weight"] = T(f"{lp}.mlp.up_proj.weight").clone()
        sd[f"model.layers.{l}.mlp.down_proj.weight"] = T(f"{lp}.mlp.down_proj.weight").clone()
    sd["model.norm.weight"] = T(f"{base}.norm.weight").clone()

    with tempfile.TemporaryDirectory() as hf_dir:
        save_file(sd, os.path.join(hf_dir, "model.safetensors"),
                  metadata={"format": "pt"})
        # config.json for Qwen3-1.7B (tie_word_embeddings -> no separate lm_head)
        cfg = {
            "architectures": ["Qwen3ForCausalLM"],
            "attention_bias": False, "attention_dropout": 0.0,
            "bos_token_id": 151643, "eos_token_id": 151645,
            "head_dim": 128, "hidden_act": "silu", "hidden_size": 2048,
            "initializer_range": 0.02, "intermediate_size": 6144,
            "max_position_embeddings": 40960, "max_window_layers": n_layer,
            "model_type": "qwen3", "num_attention_heads": 16,
            "num_hidden_layers": n_layer, "num_key_value_heads": 8,
            "rms_norm_eps": 1e-06, "rope_scaling": None, "rope_theta": 1000000,
            "sliding_window": None, "tie_word_embeddings": True,
            "torch_dtype": "bfloat16", "use_cache": True,
            "use_sliding_window": False, "vocab_size": 151936,
        }
        with open(os.path.join(hf_dir, "config.json"), "w") as f:
            json.dump(cfg, f, indent=2)
        # tokenizer files from the Qwen3-1.7B snapshot
        for fn in ("tokenizer.json", "tokenizer_config.json", "vocab.json",
                   "merges.txt", "generation_config.json", "special_tokens_map.json"):
            src = os.path.join(qwen3_tok_dir, fn)
            if os.path.exists(src):
                shutil.copy(src, os.path.join(hf_dir, fn))
        conv = os.path.join(llama_cpp_dir, "convert_hf_to_gguf.py")
        env = dict(os.environ)
        env["PYTHONPATH"] = os.path.join(llama_cpp_dir, "gguf-py") + \
            (os.pathsep + env["PYTHONPATH"] if "PYTHONPATH" in env else "")
        cmd = [sys.executable, conv, hf_dir, "--outfile", out_gguf, "--outtype", outtype]
        print("running:", " ".join(cmd))
        subprocess.run(cmd, check=True, env=env)
    print(f"wrote decoder gguf: {out_gguf} ({os.path.getsize(out_gguf) / (1024**3):.2f} GB)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default=None, help="canary snapshot dir or hub root")
    ap.add_argument("--qwen3-tokenizer", default=None, help="Qwen3-1.7B snapshot dir or hub root")
    ap.add_argument("--llama-cpp", default=os.path.expanduser("~/Work/llama.cpp"))
    ap.add_argument("--out-dir", default=os.path.expanduser("~/Work/llama.cpp/models"))
    ap.add_argument("--decoder-outtype", default="f16", choices=["f32", "f16", "bf16", "q8_0"])
    ap.add_argument("--encoder-only", action="store_true")
    ap.add_argument("--decoder-only", action="store_true")
    args = ap.parse_args()

    src = _newest_snapshot(args.src, "models--nvidia--canary-qwen-2.5b")
    os.makedirs(args.out_dir, exist_ok=True)
    st_path = os.path.join(src, "model.safetensors")
    print(f"source: {st_path}")

    st = safe_open(st_path, framework="pt")

    if not args.decoder_only:
        enc_out = os.path.join(args.out_dir, "canary-qwen-2.5b-encoder-f32.bin")
        write_encoder_bin(st, enc_out)
    if not args.encoder_only:
        tok = _newest_snapshot(args.qwen3_tokenizer, "models--Qwen--Qwen3-1.7B")
        suffix = {"f16": "f16", "f32": "f32", "bf16": "bf16", "q8_0": "Q8_0"}[args.decoder_outtype]
        dec_out = os.path.join(args.out_dir, f"canary-qwen-2.5b-decoder-{suffix}.gguf")
        write_decoder_gguf(st, tok, args.llama_cpp, dec_out, args.decoder_outtype)


if __name__ == "__main__":
    main()
