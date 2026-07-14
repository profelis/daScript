# dictation / Cadmus - local Telegram dictation and conversation bot

Cadmus transcribes Telegram voice notes through a local `dasllama-server`, cleans the transcript,
and answers questions using the current chat's locally stored history. The Telegram bot contains no
models; the server owns ASR and LLM inference.

For each voice message the bot downloads the audio, converts it to 16 kHz mono WAV with ffmpeg,
calls `/v1/audio/transcriptions`, then applies the editable `dictation_prompt` through
`/v1/chat/completions`. The cleaned transcript is recorded as the user's message. The bot's
transcript-delivery reply is deliberately not recorded as an assistant turn.

Every inbound text, caption, voice, and audio message visible to the bot is retained in local SQLite.
Real Cadmus answers are retained in the same history. In private chats Cadmus answers every message;
in groups it answers mentions, replies to the bot, commands, and configured wake-name prefixes.
Retrieval and summaries never cross the current Telegram chat.

## Requirements

- A running `dasllama-server` with both an instruct model and an ASR model.
- ffmpeg on `PATH`, or an absolute `ffmpeg` path in `dictation.toml`.
- A Telegram token from `@BotFather`.

## Setup and run from source

```text
bin/daslang utils/daspkg/main.das -- install --root examples/telegram/dictation
bin/daslang -project_root examples/telegram/dictation examples/telegram/dictation/main.das
```

The bot itself does not require JIT. Edit `dictation.toml` first. `TELEGRAM_BOT_TOKEN` overrides
`bot_token`. Relative database and log paths resolve beside the executable in a release and beside
`main.das` during development.

The database is created automatically. Migration 1 creates message/state storage; migration 2 adds
the FTS5 retrieval index. Telegram update offsets are persisted, and `(chat_id, message_id)` makes
replayed updates and edits idempotent. History is retained indefinitely.

## Conversation and summary commands

```text
/help
/summary
/summary me
/summary yesterday
/summary 2026-07-13
/summary @username 2026-07-13
```

Bare `/summary` (and `today`) means the rolling previous 24 hours. `yesterday` and an explicit
`YYYY-MM-DD` use local calendar days. `me` and `@username` filter by Telegram user ID after resolving
the participant inside this chat. Forum topics currently share their parent chat's history.

Anyone who can address the bot in a chat can request a chat-wide or per-user summary. Long histories
are summarized in chunks and reduced into one answer.

## Telegram group setup

Commands work without registering them, but the Telegram command menu is configured manually:

1. Open `@BotFather`, run `/setcommands`, and select this bot.
2. Paste:

   ```text
   summary - Summarize recent conversation
   help - Show Cadmus commands and usage
   ```

3. Run `/setprivacy`, select the bot, and choose `Disable` so it can retain ordinary group messages.
4. Remove and re-add the bot to each group, or make it an administrator, for the privacy change to
   take effect.

## Important configuration

| Key | Meaning |
|---|---|
| `server` | dasllama-server base URL |
| `bot_token` | BotFather token; the environment variable wins |
| `dictation_prompt` | Transcript-repair prompt; `{language}` is replaced per message |
| `assistant_name`, `assistant_aliases` | Display identity and comma-separated group wake names |
| `assistant_prompt` | Editable conversational personality, separate from trusted runtime rules |
| `database` | Local SQLite history path |
| `recent_messages`, `history_search_results` | Recent and FTS context sizes |
| `summary_chunk_messages`, `summary_max_messages` | Summary reduction limits |
| `max_tokens`, `temp` | Dictation cleanup generation settings |
| `assistant_max_tokens`, `assistant_temp` | Conversational generation settings |
| `language`, `min_chars`, `llm_timeout` | ASR and request controls |
| `ffmpeg`, `poll_timeout`, `log_file`, `log_level` | Process and logging controls |
| `keep_audio_dir` | Optional archive for original audio; empty keeps none |

The legacy `prompt` key is still accepted for deployed configs, but new configs should use
`dictation_prompt`. Keeping it separate from `assistant_prompt` prevents conversational personality
from changing dictation.

## Release

```text
bin/daslang utils/daspkg/main.das -- release --root examples/telegram/dictation --out <staging>
```

The release contains a standalone executable, runtime DLLs, required shared modules, and the config
template. Preserve deployed `dictation.toml` and `cadmus.db` when re-releasing.
