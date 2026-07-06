# dasllama-server — an OpenAI-compatible HTTP server

A drop-in OpenAI-compatible server for [dasLLAMA](../../modules/dasLLAMA) CPU inference, written
entirely in daslang over the public dasLLAMA facade + the `dasHV` HTTP layer. Point any OpenAI
client (opencode, Open WebUI, the `llm` CLI, the `openai` Python SDK, …) at `http://127.0.0.1:<port>/v1`.

It reaches **only** public facade verbs (`load_model` / `create_chat` / `add_user` / `add_assistant` /
`respond` / `transcribe` / `embed`) — that is the point: the server is the acceptance test for the
API rework. If it builds with no reach into engine internals, the facade is complete.

## Run

```sh
bin/daslang -jit utils/dasllama-server/main.das -- --model <model.gguf> [--port 8080] [--quant q8] \
                                                    [--asr <asr.bin>] [--mmproj <mmproj.gguf>] [--ctx 4096]
```

Run under `-jit` — interpreted inference is far too slow. Flags:

| Flag | Short | Default | Meaning |
|---|---|---|---|
| `--model` | `-m` | *(required)* | GGUF model to serve |
| `--port` | `-p` | `8080` | Listen port |
| `--quant` | `-q` | `q8` | Weight quantization: `fp32` \| `q8` \| `q4` |
| `--asr` | `-a` | — | ASR model (whisper/parakeet/qwen3-asr) — enables the `/v1/audio/*` routes |
| `--mmproj` | — | — | mmproj GGUF for the Qwen3-ASR route (paired with `--asr`) |
| `--ctx` | — | `4096` | Context-length cap in tokens |
| `--help` | `-?` | — | Show help and exit |

The server is single-context and serializes requests on the tick thread (one in-flight request),
matching dasLLAMA's one-generation-loop. OpenAI is stateless — the client resends the full
transcript each turn.

## Endpoints

| Method | Path | Notes |
|---|---|---|
| `GET`  | `/v1/models` | Lists the served model (and `-asr` if loaded) |
| `POST` | `/v1/chat/completions` | Chat; `stream: true` → SSE, else buffered |
| `POST` | `/v1/completions` | Raw completion; `stream: true` → SSE, else buffered |
| `POST` | `/v1/embeddings` | Mean-pooled, L2-normalized sentence embeddings |
| `POST` | `/v1/audio/transcriptions` | Speech→text (multipart upload; needs `--asr`) |
| `POST` | `/v1/audio/translations` | Speech→English text (needs `--asr`) |
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

`test_openai_server.das` (in this directory) is a model-gated, JIT-only conformance test: it starts
the server on its own thread, then drives `/v1/models`, `/v1/embeddings`, and `/v1/chat/completions`
over the real dashv HTTP client. It skips cleanly when the model GGUF is absent; set
`DASLLAMA_MODELS_DIR` to point at a directory containing `tinyllama-1.1b-chat-v1.0.Q8_0.gguf`, then:

```sh
bin/daslang -jit dastest/dastest.das -- --test utils/dasllama-server/test_openai_server.das
```

## Not yet implemented

Tool / function calling (`tools`, `tool_choice`) — parked as a follow-up.
