options gen2

require dastest/testing_boost public
require daslib/fio
require sqlite/sqlite_migrate
require cadmus_history

def private test_db_path() : string {
    var error : string
    return path_join(temp_directory(error), "cadmus_history_test.db")
}

def private test_message(chat_id, message_id, sender_id, date : int64; text : string) : CadmusMessage {
    return CadmusMessage(
        Id = 0,
        ChatId = chat_id,
        TelegramMessageId = message_id,
        SenderId = sender_id,
        SenderName = "Tester",
        SenderUsername = "tester",
        Role = CADMUS_ROLE_USER,
        SourceKind = "text",
        Content = text,
        Caption = "",
        RawTranscript = "",
        MessageDate = date,
        EditedAt = 0l,
        ReplyToMessageId = 0l,
        Deleted = false)
}

[test]
def test_history_migrations_linq_and_fts(t : T?) {
    let path = test_db_path()
    remove(path)
    ensure_cadmus_database(path)

    t |> run("starts at migration two") @(t : T?) {
        with_sqlite(path) $(db) {
            t |> equal(db |> current_schema_version(), 2)
        }
    }

    t |> run("upsert is idempotent and edits replace FTS text") @(t : T?) {
        upsert_cadmus_message(path, test_message(10l, 1l, 7l, 1000l, "alpha original"))
        upsert_cadmus_message(path, test_message(10l, 1l, 7l, 1000l, "beta edited"))
        let recent <- load_recent_cadmus_messages(path, 10l, 10)
        t |> equal(length(recent), 1)
        t |> equal(recent[0].Content, "beta edited")
        t |> equal(length(search_cadmus_messages(path, 10l, "alpha", 10)), 0)
        t |> equal(length(search_cadmus_messages(path, 10l, "beta", 10)), 1)
    }

    t |> run("audio caption edits preserve transcripts and refresh FTS") @(tt : T?) {
        var audio = test_message(10l, 3l, 7l, 1200l, "cleaned transcript")
        audio.SourceKind = "voice"
        audio.Caption = "original caption"
        upsert_cadmus_message(path, audio)
        update_cadmus_audio_edit(path, 10l, 3l, "replacement caption", 1300l)
        let recent <- load_recent_cadmus_messages(path, 10l, 10)
        var edited = -1
        for (i in range(length(recent))) {
            if (recent[i].TelegramMessageId == 3l) {
                edited = i
                break
            }
        }
        if (edited < 0) {
            tt |> failure("edited audio message was not loaded")
            return
        }
        tt |> equal(recent[edited].Content, "cleaned transcript")
        tt |> equal(recent[edited].Caption, "replacement caption")
        tt |> equal(recent[edited].EditedAt, 1300l)
        tt |> equal(length(search_cadmus_messages(path, 10l, "original", 10)), 0)
        tt |> equal(length(search_cadmus_messages(path, 10l, "replacement", 10)), 1)
    }

    t |> run("chat and sender filters stay local") @(t : T?) {
        upsert_cadmus_message(path, test_message(10l, 2l, 8l, 1100l, "first chat"))
        upsert_cadmus_message(path, test_message(20l, 1l, 7l, 1100l, "second chat"))
        let chat_rows <- load_cadmus_messages(path, 10l, 0l, 2000l, 100)
        let user_rows <- load_cadmus_messages_for_sender(path, 10l, 7l, 0l, 2000l, 100)
        t |> equal(length(chat_rows), 3)
        t |> equal(length(user_rows), 2)
        t |> equal(user_rows[0].ChatId, 10l)
    }

    t |> run("empty username never resolves to an anonymous sender") @(t : T?) {
        var anonymous = test_message(10l, 4l, 99l, 1400l, "anonymous message")
        anonymous.SenderUsername = ""
        upsert_cadmus_message(path, anonymous)
        t |> equal(find_cadmus_sender(path, 10l, "@"), 0l)
        t |> equal(find_cadmus_sender(path, 10l, " @ "), 0l)
    }

    t |> run("Telegram offset persists") @(t : T?) {
        save_cadmus_offset(path, 42l)
        t |> equal(load_cadmus_offset(path), 42l)
    }

    remove(path)
}
