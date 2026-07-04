options gen2

require daslib/sql
require sqlite/sqlite_boost

// Tutorial 22 — Transactions: atomic groups of statements.
//
//   db |> with_transaction() { ... }                   // BEGIN/COMMIT
//   db |> with_transaction(SqliteTxnMode.Immediate) {} // BEGIN IMMEDIATE
//   db |> try_transaction() { ... }                   // non-panic
//   db |> in_transaction()                             // status query
//
// `with_transaction` emits ``BEGIN`` on entry, ``COMMIT`` on normal exit, and
// ``ROLLBACK`` on early return (a block ``return`` unwinds through ``finally``).
// A panic does NOT roll back — daslang skips ``finally`` on panic by design; the
// open transaction's writes are discarded when the connection closes. When
// nested inside an existing transaction it falls back to ``SAVEPOINT`` /
// ``RELEASE`` / ``ROLLBACK TO`` so user code can compose freely without
// SQLite's "no nested transactions" rule biting.
//
// Two overloads — not one optional-parameter function — because the
// trailing-block convention puts the block last; an optional middle
// ``mode`` parameter wouldn't resolve from a no-mode call site. Same shape
// for ``try_transaction``.
//
// ``try_transaction`` only converts SQL failures (BEGIN / COMMIT errors) into
// ``some(errmsg)`` and returns ``none`` on success. A panic from inside the
// block propagates without rolling back (``finally`` is skipped on panic) —
// fallible steps inside a transaction should use the ``try_`` API forms.

[sql_table(name = "Friends")]
struct Friend {
    @sql_primary_key Id : int
    Name : string
}

[export]
def main {
    with_sqlite(":memory:") $(db) {
        db |> create_table(type<Friend>)

        // Canonical form: 2-arg `with_transaction`. The INSERTs commit as
        // one unit; the inner array-insert nests via SAVEPOINT.
        db |> with_transaction() {
            db |> insert([
                Friend(Id = 1, Name = "tom"),
                Friend(Id = 2, Name = "jerry"),
                Friend(Id = 3, Name = "spike")
            ])
        }
        to_log(LOG_INFO, "after commit: {length(db |> select_from(type<Friend>))} row(s)\n")

        // 3-arg overload: SQLite-specific BEGIN modifier. ``Immediate``
        // takes the RESERVED lock at BEGIN, so concurrent writers block at
        // BEGIN time rather than on first write — avoids the "another
        // writer raced us between read and write" trap.
        db |> with_transaction(SqliteTxnMode.Immediate) {
            db |> insert(Friend(Id = 4, Name = "jasmine"))
        }

        // Status check — `in_transaction()` wraps SQLite's autocommit flag.
        // Mostly useful for library code that wants "join an ambient
        // transaction if one is active, else start one".
        to_log(LOG_INFO, "in transaction now? {db |> in_transaction()}\n")

        // Nested calls fall back to SAVEPOINT — proper LIFO composition,
        // no need for the runner to track depth itself.
        db |> with_transaction() {
            db |> insert(Friend(Id = 5, Name = "max"))
            db |> with_transaction() {
                db |> insert(Friend(Id = 6, Name = "rover"))
                to_log(LOG_INFO, "deep in nested txn? {db |> in_transaction()}\n")
            }
        }

        // Non-panic variant. Returns ``some(errmsg)`` on SQL failure;
        // ``none`` on success. Useful for retry-on-SQLITE_BUSY loops.
        let r = db |> try_transaction() {
            db |> insert(Friend(Id = 7, Name = "lola"))
        }
        if (r |> is_some) {
            to_log(LOG_ERROR, "txn failed: {r |> unwrap}\n")
        } else {
            to_log(LOG_INFO, "txn ok\n")
        }

        let final_rows <- db |> select_from(type<Friend>)
        to_log(LOG_INFO, "final row count: {length(final_rows)}\n")
    }
}
