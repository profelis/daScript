#!/usr/bin/env python3
# Canary-Qwen-2.5B greedy-transcribe oracle (Wave A1 ASR reference).
#
# NO CLI oracle exists for Canary-Qwen (SALM: FastConformer encoder + Qwen3-1.7B
# decoder + LoRA). NeMo python greedy transcribe IS the reference. This engine-level
# driver (no HTTP) mirrors the onnx_bench.py rail: pinned venv, deterministic greedy,
# emits the token-for-token fixture the dasLLAMA parity gate freezes against.
#
# Venv (NeMo trunk, PyTorch 2.6+):
#   python3.11 -m venv ~/Work/canary-nemo-oracle/.venv     # a Python whose _decimal loads
#   ~/Work/canary-nemo-oracle/.venv/bin/pip install \
#       "nemo_toolkit[asr] @ git+https://github.com/NVIDIA/NeMo.git" peft
#   # brew-python _decimal fix (mpdecimal 3->4 drift):
#   ln -sf $(brew --prefix mpdecimal)/lib/libmpdec.4.dylib \
#          $(brew --prefix mpdecimal)/lib/libmpdec.3.dylib
#
# Usage (deterministic greedy, token-for-token):
#   ~/Work/canary-nemo-oracle/.venv/bin/python canary_qwen_oracle.py \
#       --wav corpus/jfk.wav --max-new-tokens 128
import argparse
import sys


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model", default="nvidia/canary-qwen-2.5b")
    ap.add_argument("--wav", action="append", required=True)
    ap.add_argument("--max-new-tokens", type=int, default=128)
    ap.add_argument("--prompt", default="Transcribe the following: ")
    args = ap.parse_args()

    import torch
    from transformers import GenerationConfig
    from nemo.collections.speechlm2.models import SALM

    torch.manual_seed(0)
    torch.use_deterministic_algorithms(True, warn_only=True)

    model = SALM.from_pretrained(args.model)
    model.eval()

    # Force pure greedy: do_sample off, single beam. bos/eos/pad from the model.
    gen_cfg = GenerationConfig(
        do_sample=False,
        num_beams=1,
        bos_token_id=model.text_bos_id,
        eos_token_id=model.text_eos_id,
        pad_token_id=model.text_pad_id,
    )

    tag = model.audio_locator_tag
    for wav in args.wav:
        with torch.inference_mode():
            answer_ids = model.generate(
                prompts=[[{"role": "user",
                           "content": f"{args.prompt}{tag}",
                           "audio": [wav]}]],
                generation_config=gen_cfg,
                max_new_tokens=args.max_new_tokens,
            )
        ids = answer_ids[0].cpu().tolist()
        text = model.tokenizer.ids_to_text(answer_ids[0].cpu())
        base = wav.rsplit("/", 1)[-1]
        # Fixture format: one IDS line (space-joined generated token ids) + one TEXT line.
        print(f"IDS\t{base}\t{' '.join(str(i) for i in ids)}")
        print(f"TEXT\t{base}\t{text}")
        sys.stdout.flush()


if __name__ == "__main__":
    main()
