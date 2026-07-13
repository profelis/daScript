# dictation — a local voice-transcription Telegram bot

Transcribes voice notes and audio files into clean, easy-to-read text — entirely on your machines.
For every voice/audio message (in a group or a direct message) the bot:

1. downloads the audio and transcodes it to 16 kHz mono WAV with **ffmpeg**;
2. sends it to a running **dasllama-server** — `/v1/audio/transcriptions` for the speech-to-text
   (auto-detecting the language — Russian, English, …);
3. asks the same server's `/v1/chat/completions` to rewrite the raw transcript into clean,
   paragraph-split text, preserving the speaker's own words and languages (no translation,
   no paraphrasing);
4. replies with the result, threaded to the original message.

The bot itself is **Telegram-only** — no models, no job queue, no JIT requirement. All inference
runs on [dasllama-server](../../../utils/dasllama-server) (one shared LLM instance for the bot and
any other OpenAI-compatible client); Telegram plumbing is
[dasTelegram](https://github.com/borisbat/dasTelegram).

## Requirements

- A running **dasllama-server** with BOTH models in ITS config: `model =` the instruct LLM GGUF
  (e.g. `Qwen3-4B-Instruct-2507`) and `asr =` the ASR ggml `.bin` (whisper or parakeet,
  auto-sniffed — parakeet-tdt v3 is ~15× faster on short notes).
- **ffmpeg** on `PATH` (or an absolute path in the config) — needed to decode Telegram's OGG/Opus voice notes.
- A **bot token** from [@BotFather](https://t.me/BotFather).

## Setup

```
daspkg install                 # installs dasTelegram into modules/ (reads .das_package)
```

Edit `dictation.toml` — point `server` at your dasllama-server, tweak the `prompt`, `min_chars`,
`keep_audio_dir`, etc. Put your bot token in `bot_token`, or leave it empty and set the
`TELEGRAM_BOT_TOKEN` environment variable (which overrides the config).

## Run

From the repo root (the interpreter is fine — the bot does no inference):

```
bin/daslang -project_root examples/telegram/dictation examples/telegram/dictation/main.das
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
| `server` | dasllama-server base URL (default `http://127.0.0.1:8080`); it must have `asr =` loaded |
| `bot_token` | Bot token (or use `TELEGRAM_BOT_TOKEN`, which wins) |
| `prompt` | The dictation system prompt (TOML multi-line string; `{lang}` → detected language; remove the key for the built-in) |
| `language` | ASR hint; `auto` detects per message |
| `max_tokens` | Reply-token budget for the cleanup |
| `temp` | LLM sampling temperature (0 = greedy/faithful) |
| `llm_timeout` | Seconds to wait for the cleanup response (long notes at low tok/s need headroom) |
| `ffmpeg` | ffmpeg executable |
| `poll_timeout` | `getUpdates` long-poll timeout, seconds |
| `log_file` / `log_level` | Log path (default `dictation.log` next to the exe) and level |
| `min_chars` | Skip the LLM when the transcript is ≤ this many bytes (drops silence hallucinations) |
| `keep_audio_dir` | If set, archive every received audio file here (empty = don't keep) |

## Notes

- The LLM step's latency scales with transcript length, so a long voice note can take a couple of
  minutes — raise `llm_timeout` if you dictate essays. The server queues the bot fairly alongside
  other clients (it serves several streams concurrently).
- For a redistributable build, `daspkg release --root examples/telegram/dictation --out <dir>`
  produces `<dir>/dictation-bot/` — a standalone executable (plus the daslang runtime DLLs, shared
  modules, and `dictation.toml`) that runs with no daslang installed. Point the shipped
  `dictation.toml` at the server on the target machine.
