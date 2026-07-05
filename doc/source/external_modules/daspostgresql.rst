dasPostgreSQL
=============

dasPostgreSQL binds PostgreSQL's client library (libpq) as a daslang SQL
provider — the same typed surface as the in-tree SQLite provider, against a
networked server. The ``_sql(...)`` chain, ``[sql_table]`` DDL/CRUD,
``@sql_json`` / ``@sql_blob`` columns, and savepoint-nested transactions work
unchanged; the provider renders PostgreSQL's dialect (``$n`` placeholders,
``DISTINCT ON``, identity primary keys, ``INSERT .. RETURNING``). Client-side
UDFs don't exist on a networked server, so ``[sql_function]`` against a
PostgreSQL runner is a compile-time capability error rather than a runtime
surprise.

Where to go
-----------

* **Documentation**: https://borisbat.github.io/dasPostgreSQL/
* **Repository**: https://github.com/borisbat/dasPostgreSQL

What's there
------------

* ``postgres`` — the auto-generated libpq binding (dasClangBind) plus a
  hand-written text-format ``exec_params`` trampoline with explicit parameter
  OIDs, so ``$n`` type inference never fails.
* ``postgres/postgres_boost`` — ``SqlRunner`` over a connection string
  (``with_postgres(conninfo)``), the exec/query runtime, and the provider
  shim.
* A copy of the daslang repository's shared SQL provider conformance suite;
  CI runs it against a real server on both lanes (a dockerized ``postgres``
  service on Linux, Homebrew PostgreSQL on macOS).

Install with ``daspkg install dasPostgreSQL``.
