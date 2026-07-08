# dictation — a local voice-transcription Telegram bot

Transcribes voice notes and audio files into clean, easy-to-read text — entirely on your machine.
For every voice/audio message (in a group or a direct message) the bot:

1. downloads the audio and transcodes it to 16 kHz mono WAV with **ffmpeg**;
2. transcribes it with a local **whisper** model (auto-detecting the language — Russian, English, …);
3. rewrites the raw transcript into clean, paragraph-split text with a local **instruct LLM** (dasLLAMA),
   preserving the speaker's own words and languages (no translation, no paraphrasing);
4. replies with the result, threaded to the original message.

Everything runs offline through [dasLLAMA](../../../modules/dasLLAMA) (whisper + the LLM) and
[dasTelegram](https://github.com/borisbat/dasTelegram) (the Bot API).

## Requirements

- A **JIT-enabled** `daslang` build (dasLLAMA inference on the interpreter is unusably slow).
- **ffmpeg** on `PATH` (or an absolute path in the config) — needed to decode Telegram's OGG/Opus voice notes.
- A **whisper** ASR model (whisper.cpp `ggml-*.bin`) — multilingual `large-v3-turbo` is a good RU+EN default.
- An **instruct LLM** GGUF (e.g. `Qwen3-4B-Instruct-2507`, `gemma-3-4b-it`).
- A **bot token** from [@BotFather](https://t.me/BotFather).

## Setup

```
daspkg install                 # installs dasTelegram into modules/ (reads .das_package)
```

Edit `dictation.toml` — point `whisper_model` / `llm_model` at your model files, adjust `threads`,
`min_chars`, `keep_audio_dir`, etc. Put your bot token in `bot_token`, or leave it empty and set the
`TELEGRAM_BOT_TOKEN` environment variable (which overrides the config).

## Run

From the repo root, under the JIT:

```
bin/daslang -jit -project_root examples/telegram/dictation examples/telegram/dictation/main.das
```

The bot logs to `dictation.log` (a proper leveled/structured log via `daslib/logger`) — including each
message's sender, transcript, reply, and a link to the archived audio. Watch it with `tail -f dictation.log`.

## Receiving messages in a group

Telegram bots have **privacy mode on** by default, so in a group a bot only sees messages that address it.
To transcribe every voice note posted in a group, either:

- disable privacy mode in @BotFather (`/setprivacy` → *Disable*), then remove and re-add the bot to the group; **or**
- add the bot to the group and make it an **admin**.

## Configuration (`dictation.toml`)

| Key | Meaning |
|---|---|
| `whisper_model` | Path to the whisper ggml `.bin` |
| `llm_model` | Path to the instruct LLM GGUF |
| `bot_token` | Bot token (or use `TELEGRAM_BOT_TOKEN`, which wins) |
| `threads` | dasLLAMA worker cap; workers + main = compute lanes (7 → 8) |
| `language` | Whisper hint; `auto` detects per message |
| `max_tokens` | Reply-token budget for the cleanup |
| `temp` | LLM sampling temperature (0 = greedy/faithful) |
| `ffmpeg` | ffmpeg executable |
| `poll_timeout` | `getUpdates` long-poll timeout, seconds |
| `log_file` / `log_level` | Log path (default `dictation.log` next to the exe) and level |
| `min_chars` | Skip the LLM when the transcript is ≤ this many bytes (drops silence hallucinations) |
| `keep_audio_dir` | If set, archive every received audio file here (empty = don't keep) |

## Notes

- The LLM step's latency scales with transcript length (decode is memory-bandwidth-bound), so a long
  voice note can take a few minutes. Model size — not core count — is the main lever.
- A standalone `daspkg release` executable is a work in progress: the dasLLAMA `-exe` codegen path does
  not yet resolve the address of the tune kernels' `@@`-function-pointer struct-field defaults. Until
  that lands, run the bot under `-jit` as above.
