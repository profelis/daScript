options gen2

//! dasLLAMA — CPU LLM inference over GGUF models, in pure daslang. This module is the public API:
//! ``load_model`` -> ``create_session`` -> ``encode`` / ``eval`` / ``sample`` (or the one-call
//! streaming ``generate``), plus the chat layer (``create_chat`` / ``add_user`` / ``respond``).
//! Requiring it also registers every supported architecture (Llama-2/3, Mistral, Qwen, Phi-3,
//! Gemma-2/3/4, Qwen-MoE, gpt-oss) — ``load_model`` dispatches on GGUF metadata, so the same
//! program runs any of them.
//!
//! Run model programs with ``-jit`` (interpreted inference is far too slow), and wrap the
//! generation in ``with_job_que()`` from ``daslib/jobque_boost`` so the kernels can thread —
//! see ``examples/dasLLAMA/run.das`` and ``chat.das`` for the canonical shape.

module dasllama shared public

require dasllama/dasllama_transformer public   // the engine + arch registry; every arch [init] fires
require dasllama/dasllama_chat public          // layer 2: chat sessions over the same engine
require dasllama/dasllama_audio public         // audio tower (mel frontend + whisper encoder + projectors)
require dasllama/dasllama_asr public           // uniform ASR surface (whisper today; parakeet/qwen3-asr land behind the same sniff)
require dasllama/dasllama_math                 // setup_dasllama_jobque_ (engine-level, wrapped below, not re-exported)

// This facade owns the good names; the engine spells each wrapped function with a trailing
// underscore (load_model_, eval_, ...) so the public re-export above and the documented stub
// below never collide at a call site.

// ===== Model, session, tokenizer =====

def setup_dasllama_jobque() {
    //! Configure the job queue for dasLLAMA's pure fork/join matmul dispatch: pooled fork contexts,
    //! batched dispatch, and the worker spin-before-park window (``box_profile.json``'s runtime
    //! ``jobque_spin_us`` tunes the window per box; 0 disables the spin). Call it INSIDE
    //! ``with_job_que()``, before the first ``generate``/``eval`` — see ``examples/dasLLAMA/run.das``.
    setup_dasllama_jobque_()
}

def load_model(path : string; mode : QuantMode = QuantMode.fp32) : Model {
    //! Load a model AND its tokenizer from a GGUF file — the one entry point. The architecture and
    //! tokenizer backend are auto-selected from GGUF metadata; ``mode`` picks the weight quantization
    //! (``QuantMode.fp32`` = the token-exact reference, ``QuantMode.q8`` = the fast int8 path).
    return <- load_model_(path, mode)
}

def create_session(model : Model) : Session {
    //! Create a fresh session (KV cache + scratch) sized to ``model.config.seq_len``. A model serves
    //! many sessions, each with its own position and cache — one model, many independent conversations.
    //! On large-context models cap ``model.config.seq_len`` BEFORE creating sessions to bound KV memory.
    return <- create_session_(model)
}

def encode(model : Model; text : string; add_special = true; parse_special = false) : array<int64> {
    //! Encode ``text`` to token ids with the model's tokenizer. ``add_special`` prepends BOS where the
    //! model expects one. ``parse_special`` is reserved and not yet honored — special tokens reach the
    //! model as atomic ids from the chat layer's template renderer, never by spelling them in text.
    return <- encode_(model, text, add_special, parse_special)
}

def decode(model : Model; ids : array<int64>) : string {
    //! Decode a token-id sequence back to text with the model's tokenizer.
    return decode_(model, ids)
}

def piece(model : Model; id : int64) : string {
    //! Decode a single token to its text piece — the streaming counterpart of ``decode``.
    return piece_(model, id)
}

// ===== Evaluation and sampling =====

def eval(model : Model; var session : Session; tokens : array<int64>) {
    //! THE eval primitive: run ``tokens`` at the session's current position and advance it. Prefill =
    //! ``eval(prompt)``; each generation step = ``eval([token])`` — the same call at different batch
    //! sizes. Logits land in ``session.logits``.
    eval_(model, session, tokens)
}

def eval_embd(model : Model; var session : Session; embd : array<float>; npos : int64) {
    //! ``eval``'s embedding-input twin: prefill ``npos`` pre-built embedding rows (``npos × dim``,
    //! token-major) at the session's current position and advance it. This is the multimodal splice
    //! entry — fill text spans with ``embed_text_rows`` and media spans with an encoder tower's
    //! soft tokens (see ``examples/dasLLAMA/audio.das``). Logits land in ``session.logits``.
    eval_embd_(model, session, embd, npos)
}

def sample(var session : Session; params : SamplingParams) : int64 {
    //! Sample the next token from ``session.logits`` per ``params``: repetition penalty over the recent
    //! window, then temperature + top-k + softmax + CDF — or greedy argmax when ``params.temp <= 0``.
    //! ``SamplingParams()`` defaults are greedy.
    return sample_(session, params)
}

def set_seed(var session : Session; seed : int) {
    //! Seed the session's sampling RNG for reproducible generation.
    set_seed_(session, seed)
}

def stats(session : Session) : Stats {
    //! Timing of the most recent ``generate``/``respond`` call on ``session``: prompt/generated token
    //! counts, time to first token, prefill and generation tok/s.
    return stats_(session)
}

// ===== Generation =====

def generate(model : Model; var session : Session; prompt : array<int64>; params : SamplingParams;
             max_tokens : int64; blk : block<(id : int64; piece : string) : bool>) : int64 {
    //! Stream-generate up to ``max_tokens`` from ``prompt``, invoking the trailing block per token with
    //! ``(id, piece)``; return ``false`` from the block to stop early (e.g. on a stop token). Prefills
    //! the prompt in one ``eval``, then samples one token at a time, advancing the session. Returns the
    //! number of tokens emitted; timing is available afterwards via ``stats``.
    return generate_(model, session, prompt, params, max_tokens, blk)
}

def generate_embd(model : Model; var session : Session; embd : array<float>; npos : int64;
                  params : SamplingParams; max_tokens : int64;
                  blk : block<(id : int64; piece : string) : bool>) : int64 {
    //! ``generate``'s embedding-prefill twin: prefill ``npos`` pre-built embedding rows (the
    //! multimodal splice — see ``eval_embd``), then stream-sample exactly like ``generate``. The
    //! chat layer's audio turns run on this; use it directly for custom multimodal prompts.
    return generate_embd_(model, session, embd, npos, params, max_tokens, blk)
}

// ===== Chat =====

def create_chat(model : Model; system : string = ""; max_new : int64 = 256l) : ChatSession {
    //! Start a conversation over ``model``: resolves the model's chat template (sniffed from the GGUF's
    //! embedded template, falling back to the arch registry) and creates the session. ``system`` is the
    //! system prompt (empty = none); ``max_new`` caps each reply. One model can drive many chats.
    return <- create_chat_(model, system, max_new)
}

def create_chat(model : Model; var tower : AudioTower; system : string = ""; max_new : int64 = 256l) : ChatSession {
    //! Start an AUDIO-CAPABLE conversation: the chat takes ownership of ``tower`` (moved in — load
    //! one with ``load_audio_tower``) so ``add_user_audio`` can splice audio into its turns. The
    //! prompt shape around the audio span comes from the model's chat template (qwen2-family audio
    //! markers, llama-3 bare embeddings, voxtral ``[BEGIN_AUDIO]``). Panics on a mismatched
    //! decoder/mmproj pair.
    return <- create_chat_(model, tower, system, max_new)
}

def add_user(var chat : ChatSession; text : string) {
    //! Queue a user message for the next ``respond``.
    add_user_(chat, text)
}

def add_user_audio(var chat : ChatSession; samples : array<float> | #) {
    //! Queue audio (16 kHz mono f32 PCM) for the next ``respond`` — encoded to soft tokens
    //! immediately, spliced at the head of the turn before any ``add_user`` text. Multiple clips
    //! concatenate. Needs a chat created with ``create_chat(model, tower)``; call inside
    //! ``with_job_que()`` (the encoder threads its kernels).
    add_user_audio_(chat, samples)
}

def caps(model : Model) : LlmCaps {
    //! What ``model`` honestly supports at the chat layer (see LlmCaps) — e.g. gemma has no system
    //! role, so the chat layer folds the system prompt into the first user turn; ``system_prompt``
    //! is false there so callers can surface it instead of being silently absorbed.
    return caps_(model)
}

def render_turn(model : Model; chat : ChatSession) : array<int64> {
    //! Render the next turn's prefill token ids — BOS + system on the first turn, then the user turn
    //! and the generation prompt — WITHOUT running the model. For inspection, token budgeting, tests.
    return <- render_turn_(model, chat)
}

def respond(model : Model; var chat : ChatSession; params : SamplingParams;
            blk : block<(piece : string) : bool>) : string {
    //! Generate the assistant's reply to the queued user message: render the turn, prefill it, then
    //! stream pieces through the trailing block (return ``false`` to stop early) until a stop token or
    //! the ``max_new`` budget. Terminates the turn in the KV cache and appends both turns to
    //! ``chat.history``. Returns the full reply text; timing via ``stats(chat.session)``.
    return respond_(model, chat, params, blk)
}
