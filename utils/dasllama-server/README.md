# dasllama-server — an OpenAI-compatible HTTP server

A drop-in OpenAI-compatible server for [dasLLAMA](../../modules/dasLLAMA) CPU inference, written
entirely in daslang over the public dasLLAMA facade + the `dasHV` HTTP layer. Point any OpenAI
client (opencode, Open WebUI, the `llm` CLI, the `openai` Python SDK, …) at `http://127.0.0.1:<port>/v1`.

It reaches **only** public facade verbs (`load_model` / `create_chat_renderer` / `add_user` /
`render_assistant` / `render_turn` / `eval_batch` via `llm_scheduler` / `transcribe` / `embed`) —
that is the point: the server is the acceptance test for the API rework. If it builds with no
reach into engine internals, the facade is complete.

## Run

```sh
bin/daslang -jit utils/dasllama-server/main.das -- --model <model.gguf> [--port 8080] [--quant q8] \
                                                    [--asr <asr.bin>] [--mmproj <mmproj.gguf>] [--ctx 4096] \
                                                    [--streams 4] [--chunk 64] [--page-rows 64] [--prefix N]
```

Run under `-jit` — interpreted inference is far too slow. Flags:

| Flag | Short | Default | Meaning |
|---|---|---|---|
| `--config` | `-c` | — | TOML config file; keys mirror the long flag names, explicit CLI flags override |
| `--model` | `-m` | *(required)* | GGUF model to serve (here or in `--config`) |
| `--port` | `-p` | `8080` | Listen port |
| `--quant` | `-q` | `q8` | Weight quantization: `fp32` \| `q8` \| `q4` |
| `--kv-dtype` | — | `f16` | KV-cache codec: `f32` \| `f16` \| `q8_0` \| `tq4` (rotated 4-bit; needs pow2 head_size) |
| `--asr` | `-a` | — | ASR model (whisper/parakeet/qwen3-asr) — enables the `/v1/audio/*` routes |
| `--mmproj` | — | — | mmproj GGUF for the Qwen3-ASR route (paired with `--asr`) |
| `--ctx` | — | `4096` | Context-length cap in tokens |
| `--streams` | `-s` | `4` | Max concurrent generation streams |
| `--chunk` | — | `64` | Prefill quantum in tokens — decode stalls at most this per tick |
| `--page-rows` | — | `64` | KV page size in positions for paged serving |
| `--prefix` | — | *auto* | Prefix-cache retention cap in pages (auto: one full context per stream; `-1` = unbounded) |
| `--flat` | — | — | Flat preallocated KV sessions — disables paged serving and the prefix cache |
| `--help` | `-?` | — | Show help and exit |

A config file replaces long command lines (`--config server.toml`); keys are the long flag
names with underscores:

```toml
model = "D:/models/SmolLM2-135M-Instruct-Q8_0.gguf"
port = 8080
quant = "q8"
kv_dtype = "tq4"   # rotated 4-bit KV — half the q8_0 cache bytes
ctx = 4096
streams = 4
```

Chat and completion requests **batch continuously** (`llm_scheduler.das`): up to `--streams`
generations run concurrently through one `eval_batch` decode step per tick, with long prompts
prefilled in `--chunk`-token slices so a new arrival never stalls running streams for more than
one chunk. Requests beyond `--streams` queue (up to 32; then 503). KV is **paged** by default —
cache memory tracks each stream's actual context, and finished streams donate their pages to a
**prefix cache**, so a repeated prompt prefix (a shared system prompt, the next turn of the same
conversation) attaches instead of re-prefilling — time-to-first-token collapses on warm prompts.
Clients whose connection drops mid-generation are evicted within a tick. The buffered endpoints
(`/v1/models`, `/v1/embeddings`, `/v1/audio/*`) still run to completion in-handler and pause
generation for their duration. OpenAI is stateless — the client resends the full transcript each
turn.

## Endpoints

| Method | Path | Notes |
|---|---|---|
| `GET`  | `/v1/models` | Lists the served model (and `--asr` if loaded) |
| `POST` | `/v1/chat/completions` | Chat; `stream: true` → SSE, else buffered |
| `POST` | `/v1/completions` | Raw completion; `stream: true` → SSE, else buffered |
| `POST` | `/v1/embeddings` | Mean-pooled, L2-normalized sentence embeddings |
| `POST` | `/v1/audio/transcriptions` | Speech→text (multipart upload; needs `--asr`) |
| `POST` | `/v1/audio/translations` | Speech→English text (needs `--asr`) |
| `GET`  | `/v1/stats` | Scheduler counters: active/queued/peak_active, decode_steps, avg_batch, evicted, cached_tokens, prefix_pages, … |
| `POST` | `/shutdown` | Graceful stop |

### Chat

```sh
curl http://127.0.0.1:8080/v1/chat/completions -H 'Content-Type: application/json' -d '{
  "messages": [{"role": "user", "content": "Say hello in one word."}],
  "max_tokens": 16, "stream": false
}'
```

### Embeddings

`input` is a string or an array of strings. Each vector is `model.config.dim` floats,
mean-pooled over the decoder's last-layer hidden state (post-final-norm) and L2-normalized.

```sh
curl http://127.0.0.1:8080/v1/embeddings -H 'Content-Type: application/json' -d '{
  "input": ["the quick brown fox", "a lazy dog"]
}'
# -> {"object":"list","data":[{"object":"embedding","embedding":[...],"index":0}, ...],
#     "model":"...","usage":{"prompt_tokens":N,"total_tokens":N}}
```

A decoder-only LLM used as an embedder gives **RAG-grade** vectors (good for retrieval /
similarity), not a substitute for a dedicated embedding model.

### Transcription (with `--asr`)

```sh
curl http://127.0.0.1:8080/v1/audio/transcriptions \
  -F file=@audio.wav -F response_format=verbose_json
```

## Testing

All tests in this directory are model-gated and JIT-only (they skip cleanly when the GGUF is
absent; set `DASLLAMA_MODELS_DIR`):

- `test_openai_server.das` — endpoint conformance (`/v1/models`, `/v1/embeddings`, buffered chat)
  over the real dashv HTTP client; needs `tinyllama-1.1b-chat-v1.0.Q8_0.gguf`.
- `test_llm_scheduler.das` — the continuous-batching scheduler against `generate()` references
  (bit-exact single stream, chunk invariance, staggered admits, eviction); needs
  `SmolLM2-135M-Instruct-Q8_0.gguf`.
- `test_openai_server_stream.das` — SSE chunk framing, the over-long-prompt 400, two concurrent
  clients batching on one server (`peak_active >= 2` via `/v1/stats`), mid-generation disconnect
  eviction, and the prefix cache returning an identical completion for a repeated request; needs
  `SmolLM2-135M-Instruct-Q8_0.gguf`.

```sh
bin/daslang -jit dastest/dastest.das -- --test utils/dasllama-server/test_openai_server.das
```

`server_bench.das` (same directory) measures the serving latencies directly through the scheduler
seam: tok/s + TTFT + inter-token percentiles vs batch size, decode stall per prefill chunk size,
and warm-vs-cold TTFT for the prefix cache.

## Not yet implemented

Tool / function calling (`tools`, `tool_choice`) — parked as a follow-up.
