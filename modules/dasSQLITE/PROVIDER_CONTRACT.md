# SQL provider contract

What a database provider implements to plug into the `_sql` LINQ-to-SQL machinery
(`sqlite_linq.das`, migrating to `daslib/sql_linq` in a follow-up). SQLite
(`sqlite_boost.das`) is the reference implementation; DuckDB and PostgreSQL are the
planned consumers. This document is the contract; the registry in
`modules/dasSQLITE/daslib/sql_provider.das` (required as `sqlite/sql_provider`;
moves to root `daslib/` with the sql_linq promotion) is its executable form.

## Architecture in one paragraph

`_sql(...)` and its siblings analyze a LINQ-shaped chain at **compile time** and emit
(a) a SQL string with positional placeholders, (b) a bind block, (c) a row-reader
block/lambda, all passed to a **runtime runner helper** (`run_select`,
`run_each_select`, ...). Nothing provider-specific survives to runtime except the
helper call — dispatch is by ordinary overload resolution on the provider's runner
type. The macro learns which provider it is emitting for from the **provider
registry**: a compile-time (macro-context) table keyed by the runner's type name,
carrying the provider's statement type, dialect hooks, and capability flags.

## What a provider ships

### 1. Runtime types

| Piece | SQLite reference | Notes |
|---|---|---|
| Runner struct | `SqlRunner { sqlite_handle, schema_name }` | The value user code threads through every call. Must be a struct (registry keys on its type name) |
| Statement handle | `sqlite3_stmt?` | Spliced by the macro into emitted bind/reader blocks; opaque to the analyzer |
| `finalize(var db)` | closes the connection | enables `var inscope db` RAII |
| `with_<provider>(path) <\| $(db)` | `with_sqlite` | scoped open/close |
| open family | `open_sqlite` / `try_open_sqlite` | strict + `try_` forms |

### 2. Runtime runner helpers (overloads on the runner type)

The macro emits calls to these **unqualified** names; overload resolution on the
first argument picks the provider. Signatures are generic over the row type
(`auto(TT)`) and take the provider's concrete stmt type in block/lambda positions:

| Helper | Shape | Used by |
|---|---|---|
| `run_select` | `(db, sql, bind_blk, row_blk) : array<TT>` | `_sql` (default terminal) |
| `run_select_one` | `... : TT` (panics on empty) | `_sql(... \|> _first())` |
| `run_select_one_opt` | `... : Option<TT>` | `_first_opt()` |
| `try_run_select` / `_one` / `_one_opt` | `... : Result<..., string>` | `_try_sql` |
| `run_each_select` | `(db, sql, bind_blk, row_lam) : iterator<TT>` | `_each_sql`; finalize in generator `finally` |
| `run_exec_binds` | `(db, sql, bind_blk) : int` (rows affected) | `_sql_update` / `_sql_delete` |
| `run_returning` variants | rows-after-write | `_sql_*_returning` |
| `sql_bind_to_stmt` | `(var stmt, idx, v)` per storage class + adapter fallthrough | emitted bind blocks; generated `_sql_bind_row` |
| `sql_read_witness` / `read_via_adapter` | `(stmt, col, ...)` per storage class | row readers; generated `_sql_read_row` |
| `exec` / `query*` raw-SQL family | see skills/sql.md | not macro-emitted; provider-specific surface |

The generated per-table helpers (`_sql_bind_row`, `_sql_read_row`, from
`[sql_table]`) are **generic over the stmt parameter** — they monomorphize per
provider, and their interior `sql_bind_to_stmt` / `read_via_adapter` calls
overload-resolve against whichever provider's stmt type instantiated them.

### 3. Registry entry (compile-time)

Registered via `sqlite/sql_provider`'s `register_sql_provider` (the provider's
registration code must be in the `require` closure of the macro module —
consumer-requires-contributor; see skills/das_macros.md "Macro modules each
compile into their own context"):

| Field | SQLite value | Consulted by |
|---|---|---|
| `name` | `"sqlite"` | diagnostics |
| `runnerModule` + `runnerStruct` | `"sqlite_boost"` + `"SqlRunner"` | registry lookup key, matched against `q.dbExpr._type`'s struct + owning module |
| `makeStmtType` | `qmacro_type(type<sqlite3_stmt?>)` | bind-block parameter splices (mutable flavor) |
| `makeStmtTypeConst` | `qmacro_type(type<sqlite3_stmt? const>)` | row-reader block/lambda parameter splices — qualifiers are spelled in the type expression; `$t` substitution replaces the placeholder type wholesale, so the parser's const-append on non-`var` params does not apply to spliced types |
| `renderPlaceholder(ordinal)` | `"?"` | `fold_to_builder` — the single render point for bind frags (`?` inside `build_sql_string` output is internal IR that `sql_to_frags` re-splits). Ordinal is 1-based among macro-enumerated binds; upsert row-binds are emitted as literal `?` text (bound by the generated `_sql_bind_row`, not enumerated), so a numbered-placeholder provider must also handle row-binder placeholders at port time |
| `noLimitSpelling` | `"LIMIT -1"` | OFFSET-without-LIMIT rendering in `build_sql_string` |
| `renderJsonExtract(target, path)` | `json_extract({target}, '$....')` | `@sql_json` column descent (`render_json_extract`) |
| `quoteId(name)` | `"name"` (double quotes) | registered, NOT yet routed — double-quote identifier quoting is portable across SQLite/DuckDB/PostgreSQL; the renderers keep inline quoting until a diverging provider (e.g. MySQL backticks) forces the sweep |
| `sqlTypeFor(SqlType)` | `sqlite_sql_type` | registered, NOT yet routed — `[sql_table]` DDL emission is provider-agnostic at struct declaration time; routing lands with the neutral `[sql_table]` (per-provider DDL selected by the runner at the `create_table` call site) |
| `identityDdl` | `PRIMARY KEY` (INTEGER PK aliases rowid) | registered, NOT yet routed — same story as `sqlTypeFor` |
| capability flags | see below | macro_error gates |

### 4. Capability flags — `SqlProviderCaps` bitfield + `pkReport`

| Field | SQLite | Gate |
|---|---|---|
| `caps.fts5` | set | `[sql_fts5]` / `text_match` → compile error when absent |
| `caps.client_udfs` | set | `[sql_function]` → compile error when absent (PG has no client-side UDFs) |
| `caps.returning` | set | `_sql_*_returning` |
| `pkReport : SqlPkReport` | `LastInsertRowid` | `insert(...) : id` — `ReturningPk` for providers without rowid |

The gates wire up as the second provider lands; in this PR the flags are
registered data only.

A missing capability is a **compile-time** `macro_error` naming the provider and the
feature — never a runtime failure.

## Dialect notes (what is already portable)

`ON CONFLICT` upsert, `RETURNING`, double-quote identifier quoting, and
`LIKE ... ESCAPE '\'` are portable across SQLite / DuckDB / PostgreSQL. DuckDB even
shares the `json_extract` spelling. The known divergence points are exactly the
registry hooks above plus placeholder style (`?` vs `$n`).

## Conformance

A provider passes the shared conformance suite (`tests/sql_conformance/`, follow-up
PR) by shipping a `conformance_provider.das` shim exposing its runner + capability
flags for self-skip of unsupported groups.
