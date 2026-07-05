options gen2

// Intentional compile error — lint sweep skips via the expect directive.
expect 31403

module sql_provider shared public

// Deprecation stub — the provider registry moved to the daslang standard library.

def private _moved_error {
    static_assert(false, "sqlite/sql_provider moved to daslib/sql_provider — update the require (see skills/sql.md)")
}
