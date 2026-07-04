options gen2

// Intentional compile error — lint sweep skips via the expect directive.
expect 31403

module sqlite_linq shared public

// Deprecation stub — the `_sql` chain analyzer moved to the daslang standard library.

def private _moved_error {
    static_assert(false, "sqlite/sqlite_linq moved to daslib/sql_linq — require daslib/sql_linq plus sqlite/sqlite_boost for the provider (see skills/sql.md)")
}
