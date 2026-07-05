options gen2
options indenting = 4
options no_unused_block_arguments = false
options no_unused_function_arguments = false
options strict_smart_pointers

module sqlite_migrate shared public

// Intentionally opt in for user-facing docs: keep comments concise and actionable.
options _comment_hygiene = true

require sqlite_boost public
require daslib/sql_migrate public

require strings public
require daslib/option public

//! SQLite glue for the provider-neutral migrations engine (``daslib/sql_migrate``,
//! re-exported here — ``[sql_migration]``, ``migrate_to_latest``, ``baseline``,
//! ``[struct_convert]``, ``convert`` / ``convert_and_rename`` all keep working via this
//! module). The glue supplies the engine's per-provider hooks: stream identity, the
//! ``BEGIN IMMEDIATE`` write lock, sqlite_master catalog probes, the audit-history read
//! rail, and typed migration-body invocation. Contract:
//! modules/dasSQLITE/PROVIDER_CONTRACT.md §Migrations.

// ===== Migration glue hooks (see PROVIDER_CONTRACT.md §Migrations) =====

[unused_argument(db)]
def _migration_stream_key(db : SqlRunner) : string {
    //! Stream identity for SQLite migrations — must spell ``<runnerModule>::<RunnerStruct>``
    //! exactly as the provider registry keys the runner (the ``[sql_migration]`` annotation
    //! derives the same string from the body's runner parameter type).
    return "sqlite_boost::SqlRunner"
}

[unused_argument(blocking)]
def _migration_begin(db : SqlRunner; blocking : bool) : SqlError {
    //! SQLite's migration lock IS the transaction: ``BEGIN IMMEDIATE`` takes the write
    //! lock up front. The ``blocking`` flag has no separate meaning here — lock waits
    //! follow the connection's ``busy_timeout``; contention surfaces as ``SQLITE_BUSY``.
    return db |> try_exec("BEGIN IMMEDIATE")
}

[unused_argument(db)]
def _migration_end(db : SqlRunner) : void {
    //! No-op: the write lock is released with COMMIT/ROLLBACK.
}

def _migration_query_int(db : SqlRunner; sql : string) : Result<int, string> {
    //! One-int-result query rail for the engine's COUNT/MAX probes (the raw ``query*``
    //! family is provider-specific, so the engine can't call it unqualified).
    return <- db |> try_query_scalar(sql, type<int>)
}

def _migration_audit_exists(db : SqlRunner) : Result<bool, string> {
    //! Catalog probe for ``__schema_version``. sqlite_master itself never reports
    //! "no such table"; transient errors here propagate.
    let r <- db |> try_query_scalar(
        "SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='__schema_version'", type<int>)
    if (r |> is_err) return err(r |> unwrap_err, type<bool>)
    return ok((r |> unwrap) > 0, type<string>)
}

def _migration_has_user_objects(db : SqlRunner) : bool {
    //! True when the DB already has user tables/views/indexes — drives the engine's
    //! adoption hint. sqlite_* names are reserved for internals (sqlite_sequence,
    //! sqlite_autoindex_*); query failure counts as "no objects".
    let r = db |> try_query_scalar(
        "SELECT COUNT(*) FROM sqlite_master WHERE name NOT LIKE 'sqlite_%' AND name != '__schema_version'", type<int>)
    return (r |> is_ok) && (r |> unwrap) > 0
}

def _migration_history_rows(db : SqlRunner) : Result<array<MigrationRecord>, string> {
    //! Reads every ``__schema_version`` row via the native statement rail.
    return <- try_run_select(db,
        "SELECT version, description, applied_at FROM __schema_version ORDER BY version",
        $(var _stmt : sqlite3_stmt?) {},
        $(stmt : sqlite3_stmt?) {
            return MigrationRecord(
                version = sqlite3_column_int(stmt, 0),
                description = sqlite3_column_text_(stmt, 1),
                applied_at = sqlite3_column_int64(stmt, 2))
        })
}

def _migration_invoke_body(db : SqlRunner; body : MigrationBodyCarrier) : void {
    //! Re-types the erased registry entry back to this provider's body signature and runs it.
    let typed = unsafe(reinterpret<function<(db : SqlRunner) : void>>(body))
    invoke(typed, db)
}

// ===== with_latest_sqlite — convenience wrapper =====

def with_latest_sqlite(path : string; blk : block<(db : SqlRunner) : void>) : void {
    //! Combines ``with_sqlite(path)`` + ``apply_recommended_pragmas`` + ``migrate_to_latest``.
    //! Preferred form for app code; the explicit two-step ``with_sqlite + migrate_to_latest``
    //! sequence stays available for tools/CI that may want to inspect before migrating.
    with_sqlite(path) $(db) {
        db |> apply_recommended_pragmas()
        db |> migrate_to_latest()
        invoke(blk, db)
    }
}
