options gen2

module cadmus_history public

require sqlite/sqlite_migrate
require daslib/sql_linq
require daslib/linq_das
require daslib/strings_boost
require daslib/strings_convert

let CADMUS_ROLE_USER = "user"
let CADMUS_ROLE_ASSISTANT = "assistant"

[sql_table(name = "cadmus_messages"),
 sql_index(fields = ("ChatId", "TelegramMessageId"), unique = true),
 sql_index(fields = ("ChatId", "MessageDate")),
 sql_index(fields = ("ChatId", "SenderId", "MessageDate"))]
struct CadmusMessage {
    @sql_primary_key Id : int
    ChatId : int64
    TelegramMessageId : int64
    SenderId : int64
    SenderName : string
    SenderUsername : string
    Role : string
    SourceKind : string
    Content : string
    Caption : string
    RawTranscript : string
    MessageDate : int64
    EditedAt : int64
    ReplyToMessageId : int64
    Deleted : bool
}

[sql_table(name = "cadmus_state")]
struct CadmusState {
    @sql_primary_key Id : int
    UpdateOffset : int64
}

[sql_fts5(name = "cadmus_message_fts")]
struct CadmusSearchRow {
    ChatId : string
    TelegramMessageId : string
    Body : string
    @sql_fts_rank Rank : float
}

// Frozen v1 snapshot: durable messages + Telegram poll state.
[sql_migration(version = 1, description = "create Cadmus conversation history")]
def cadmus_migration_001(db : SqlRunner) {
    db |> exec(
        "CREATE TABLE cadmus_messages (" +
        "Id INTEGER PRIMARY KEY AUTOINCREMENT," +
        "ChatId INTEGER NOT NULL," +
        "TelegramMessageId INTEGER NOT NULL," +
        "SenderId INTEGER NOT NULL," +
        "SenderName TEXT NOT NULL," +
        "SenderUsername TEXT NOT NULL," +
        "Role TEXT NOT NULL," +
        "SourceKind TEXT NOT NULL," +
        "Content TEXT NOT NULL," +
        "Caption TEXT NOT NULL," +
        "RawTranscript TEXT NOT NULL," +
        "MessageDate INTEGER NOT NULL," +
        "EditedAt INTEGER NOT NULL," +
        "ReplyToMessageId INTEGER NOT NULL," +
        "Deleted INTEGER NOT NULL," +
        "UNIQUE(ChatId, TelegramMessageId))")
    db |> exec("CREATE INDEX idx_cadmus_messages_chat_date ON cadmus_messages(ChatId, MessageDate)")
    db |> exec("CREATE INDEX idx_cadmus_messages_chat_sender_date ON cadmus_messages(ChatId, SenderId, MessageDate)")
    db |> exec("CREATE TABLE cadmus_state (Id INTEGER PRIMARY KEY, UpdateOffset INTEGER NOT NULL)")
    db |> exec("INSERT INTO cadmus_state (Id, UpdateOffset) VALUES (1, 0)")
}

// Frozen v2 snapshot: self-contained FTS5 index. FTS rows mirror live message text.
[sql_migration(version = 2, description = "add Cadmus full-text history index")]
def cadmus_migration_002(db : SqlRunner) {
    db |> exec(
        "CREATE VIRTUAL TABLE cadmus_message_fts USING fts5(" +
        "ChatId, TelegramMessageId, Body, tokenize='unicode61')")
}

def ensure_cadmus_database(path : string) {
    with_latest_sqlite(path) $(db) {
        db |> check_schema(type<CadmusMessage>)
        db |> check_schema(type<CadmusState>)
    }
}

// FTS5 v1 has typed INSERT + SELECT but no typed UPDATE/DELETE. Keep that narrow
// provider gap here; every ordinary application read/write uses LINQ/_sql below.
def private sync_cadmus_search(db : SqlRunner; msg : CadmusMessage) {
    db |> exec(
        "DELETE FROM cadmus_message_fts WHERE ChatId = ? AND TelegramMessageId = ?",
        "{msg.ChatId}", "{msg.TelegramMessageId}")
    if (!msg.Deleted && !empty(strip(msg.Content))) {
        let body = empty(strip(msg.Caption)) ? msg.Content : "{msg.Content}\n{msg.Caption}"
        db |> insert(CadmusSearchRow(
            ChatId = "{msg.ChatId}",
            TelegramMessageId = "{msg.TelegramMessageId}",
            Body = body,
            Rank = 0.0))
    }
}

def upsert_cadmus_message(path : string; msg : CadmusMessage) {
    with_latest_sqlite(path) $(db) {
        db |> with_transaction(SqliteTxnMode.Immediate) {
            let existing <- %linq! from m : CadmusMessage in db
                                   where m.ChatId == msg.ChatId && m.TelegramMessageId == msg.TelegramMessageId
                                   select m.Id %%
            if (empty(existing)) {
                db |> insert(msg)
            } else {
                db |> _sql_update(
                    type<CadmusMessage>,
                    _.Id == existing[0],
                    (SenderId = msg.SenderId,
                     SenderName = msg.SenderName,
                     SenderUsername = msg.SenderUsername,
                     Role = msg.Role,
                     SourceKind = msg.SourceKind,
                     Content = msg.Content,
                     Caption = msg.Caption,
                     RawTranscript = msg.RawTranscript,
                     MessageDate = msg.MessageDate,
                     EditedAt = msg.EditedAt,
                     ReplyToMessageId = msg.ReplyToMessageId,
                     Deleted = msg.Deleted))
            }
            sync_cadmus_search(db, msg)
        }
    }
}

def update_cadmus_audio_edit(
                             path : string;
                             chat_id, message_id : int64;
                             caption : string;
                             edited_at : int64
                             ) {
    with_latest_sqlite(path) $(db) {
        db |> with_transaction(SqliteTxnMode.Immediate) {
            let rows <- %linq! from m : CadmusMessage in db
                               where m.ChatId == chat_id && m.TelegramMessageId == message_id
                               select m %%
            if (!empty(rows)) {
                db |> _sql_update(
                    type<CadmusMessage>,
                    _.Id == rows[0].Id,
                    (Caption = caption, EditedAt = edited_at))
                var updated = rows[0]
                updated.Caption = caption
                updated.EditedAt = edited_at
                sync_cadmus_search(db, updated)
            }
        }
    }
}

def mark_cadmus_message_deleted(path : string; chat_id, message_id, edited_at : int64) {
    with_latest_sqlite(path) $(db) {
        db |> with_transaction(SqliteTxnMode.Immediate) {
            db |> _sql_update(
                type<CadmusMessage>,
                _.ChatId == chat_id && _.TelegramMessageId == message_id,
                (Deleted = true, EditedAt = edited_at))
            db |> exec(
                "DELETE FROM cadmus_message_fts WHERE ChatId = ? AND TelegramMessageId = ?",
                "{chat_id}", "{message_id}")
        }
    }
}

def load_cadmus_offset(path : string) : int64 {
    var offset = 0l
    with_latest_sqlite(path) $(db) {
        let rows <- %linq! from s : CadmusState in db where s.Id == 1 select s.UpdateOffset %%
        if (!empty(rows)) {
            offset = rows[0]
        }
    }
    return offset
}

def save_cadmus_offset(path : string; offset : int64) {
    with_latest_sqlite(path) $(db) {
        db |> _sql_update(type<CadmusState>, _.Id == 1, (UpdateOffset = offset))
    }
}

def load_recent_cadmus_messages(path : string; chat_id : int64; count : int) : array<CadmusMessage> {
    var result : array<CadmusMessage>
    with_latest_sqlite(path) $(db) {
        let newest <- _sql(
            db |> select_from(type<CadmusMessage>)
               |> _where(_.ChatId == chat_id && !_.Deleted)
               |> _order_by_descending((_.MessageDate, _.TelegramMessageId))
               |> take(count))
        result |> reserve(length(newest))
        for (i in range(length(newest))) {
            result |> push(newest[length(newest) - i - 1])
        }
    }
    return <- result
}

def private cadmus_fts_query(text : string) : string {
    let words <- split_by_chars(to_lower(text), " \t\r\n.,!?;:()[]<>/\\|@#$%^&*+=~")
    var terms : array<string>
    for (word in words) {
        let clean = strip(word)
        if (length(clean) >= 3 && length(terms) < 12) {
            terms |> push("\"{replace(clean, "\"", "\"\"")}\"")
        }
    }
    return terms |> join(" OR ")
}

def private parse_stored_int64(value : string; var result : int64&) : bool {
    let parsed = try_to_int64(value)
    if (parsed |> is_err) {
        return false
    }
    result = parsed |> unwrap
    return true
}

def search_cadmus_messages(path : string; chat_id : int64; question : string; count : int) : array<CadmusMessage> {
    var result : array<CadmusMessage>
    let query_text = cadmus_fts_query(question)
    if (empty(query_text)) {
        return <- result
    }
    with_latest_sqlite(path) $(db) {
        let chat_key = "{chat_id}"
        let hits <- _sql(
            db |> select_from(type<CadmusSearchRow>)
               |> _where(_.ChatId == chat_key && _.Body |> text_match(query_text))
               |> _order_by(_.Rank)
               |> take(count))
        for (hit in hits) {
            var message_id = 0l
            if (!parse_stored_int64(hit.TelegramMessageId, message_id)) {
                continue
            }
            let rows <- %linq! from m : CadmusMessage in db
                               where m.ChatId == chat_id && m.TelegramMessageId == message_id && !m.Deleted
                               select m %%
            if (!empty(rows)) {
                result |> push(rows[0])
            }
        }
    }
    return <- result
}

def load_cadmus_messages(
                         path : string;
                         chat_id, from_time, until_time : int64;
                         count : int
                         ) : array<CadmusMessage> {
    var result : array<CadmusMessage>
    with_latest_sqlite(path) $(db) {
        result <- _sql(
            db |> select_from(type<CadmusMessage>)
               |> _where(
                    _.ChatId == chat_id && !_.Deleted &&
                    _.MessageDate >= from_time && _.MessageDate < until_time)
               |> _order_by((_.MessageDate, _.TelegramMessageId))
               |> take(count))
    }
    return <- result
}

def load_cadmus_messages_for_sender(
                                    path : string;
                                    chat_id, sender_id, from_time, until_time : int64;
                                    count : int
                                    ) : array<CadmusMessage> {
    var result : array<CadmusMessage>
    with_latest_sqlite(path) $(db) {
        result <- _sql(
            db |> select_from(type<CadmusMessage>)
               |> _where(
                    _.ChatId == chat_id && _.SenderId == sender_id && !_.Deleted &&
                    _.MessageDate >= from_time && _.MessageDate < until_time)
               |> _order_by((_.MessageDate, _.TelegramMessageId))
               |> take(count))
    }
    return <- result
}

def find_cadmus_sender(path : string; chat_id : int64; username : string) : int64 {
    var sender_id = 0l
    let bare_username = to_lower(strip(trim_prefix(strip(username), "@")))
    if (empty(bare_username)) {
        return 0l
    }
    with_latest_sqlite(path) $(db) {
        let rows <- %linq! from m : CadmusMessage in db
                           where m.ChatId == chat_id && m.SenderUsername |> to_lower == bare_username
                           orderby m.MessageDate descending
                           select m.SenderId %%
        if (!empty(rows)) {
            sender_id = rows[0]
        }
    }
    return sender_id
}

def format_cadmus_message(msg : CadmusMessage) : string {
    let stamp = format_time(unsafe(reinterpret<clock>(msg.MessageDate)), "%Y-%m-%d %H:%M")
    let who = empty(msg.SenderName) ? msg.Role : msg.SenderName
    let body = empty(strip(msg.Caption)) ? msg.Content : "{msg.Content}\n[caption: {msg.Caption}]"
    return "[{stamp}] {who}: {body}"
}
