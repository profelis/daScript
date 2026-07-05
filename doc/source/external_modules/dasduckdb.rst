dasDuckDB
=========

dasDuckDB binds `DuckDB <https://duckdb.org/>`_ — an embedded, columnar,
analytics-first SQL engine — as a daslang SQL provider. It implements the
provider contract behind ``daslib/sql_linq``, so the whole typed SQL surface
works unchanged against a DuckDB database: the ``_sql(...)`` LINQ-to-SQL chain,
``[sql_table]`` DDL/CRUD, ``[sql_function]`` client UDFs, ``@sql_json`` /
``@sql_blob`` columns, nested transactions, and the ``DISTINCT ON`` lowering of
``_distinct_by``. Swap ``with_sqlite(path)`` for ``with_duckdb(path)`` and the
rest of the code stays the same; aggregate-heavy queries land dramatically
faster on the columnar engine (see ``examples/benchmarks/sql`` in the main
repository for four-engine numbers).

Where to go
-----------

* **Documentation**: https://borisbat.github.io/dasDuckDB/
* **Repository**: https://github.com/borisbat/dasDuckDB

What's there
------------

* ``duckdb`` — the auto-generated C-API binding (dasClangBind over
  ``duckdb.h``), linked against the prebuilt platform library so the core
  function set and the JSON extension come bundled.
* ``duckdb/duckdb_boost`` — ``SqlRunner``, the exec/query runtime,
  ``[sql_function]`` scalar UDFs, and the provider shim registering DuckDB's
  dialect: ``DISTINCT ON``, ``RETURNING``-reported primary keys,
  sequence-backed identity columns, ``json_extract_string`` descent.
* A copy of the daslang repository's shared SQL provider conformance suite,
  run in CI on Linux and macOS.

Install with ``daspkg install dasDuckDB``.
