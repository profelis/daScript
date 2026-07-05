# Four-engine SQL benchmarks — SQLite / DuckDB / PostgreSQL / Array

The same `_fold` query families (mirroring `benchmarks/sql`) run over one `Car`
schema (n = 100 000 cars, 100 dealers, 5 brands) against four engines; cells are
ns/op, `—` = absent lane. The tables between the `BENCH:TABLES` markers are
machine-generated (see "How to re-run"); all other text is hand-edited.

Engine lanes (each in its own file, fixtures built once in `[init]`; the sweep
runs one process per file so lanes never contaminate each other):

- **SQLite** — in-memory DB via the in-tree `sqlite/sqlite_boost` provider.
- **DuckDB** — in-memory DB via [dasDuckDB](https://github.com/borisbat/dasDuckDB);
  columnar/analytical engine, so aggregate-heavy families land very differently
  than row stores.
- **PostgreSQL** — a live server via
  [dasPostgreSQL](https://github.com/borisbat/dasPostgreSQL) (`DAS_PG_CONNINFO`,
  default `host=localhost port=5499 user=postgres dbname=postgres`). Numbers
  include same-box TCP round-trip cost — that IS the honest client-side view of
  a networked engine; don't read them as engine-core speed.
- **Array** — no database at all: the same chains as fused linq folds over an
  in-memory `array<Car>`. The baseline the engines are paying their overhead
  against.

## Missing cells

The six `—` rows on DuckDB/PostgreSQL (`distinct_by_*`, `distinct_count_pred`,
`groupby_first`, `groupby_select_order`, `reverse_distinct_by`) are a known
dialect gap this suite exposed: `_distinct_by` lowers to `GROUP BY <key>` with
bare selected columns — SQLite's documented arbitrary-row-per-group semantics,
which strict engines reject (`column must appear in the GROUP BY clause`). The
portable lowering (`DISTINCT ON`, which both DuckDB and PostgreSQL support) is
a pending `daslib/sql_linq` dialect hook. A PostgreSQL `—` in *every* row just
means no server was reachable (the lane self-skips).

<!-- BENCH:TABLES BEGIN -->
*Generated 2026-07-05 by `examples/benchmarks/sql/_update_results.das` — ns/op; `—` = absent lane (e.g. no PostgreSQL server was reachable). Edit the prose around the markers, not the tables.*

## INTERP

| Benchmark | SQLite | DuckDB | PostgreSQL | Array |
|---|---:|---:|---:|---:|
| `aggregate_match` | 52.4 | 6.8 | 147.1 | 9.7 |
| `all_match` | 38.2 | 3.9 | 72.1 | 5.9 |
| `any_match` | 0.1 | 5.7 | 1.5 | 0.0 |
| `average_aggregate` | 43.9 | 4.8 | 143.7 | 8.8 |
| `bare_order_where` | 429.0 | 481.6 | 883.4 | 199.7 |
| `chained_where` | 51.1 | 7.8 | 90.2 | 9.3 |
| `contains_match` | 0.1 | 5.5 | 1.5 | 2.9 |
| `count_aggregate` | 42.1 | 6.0 | 81.9 | 6.4 |
| `cross_join` | 19616.3 | 18298.2 | 47220.1 | 5393.6 |
| `distinct_by_count` | 66.7 | 24.4 | 137.8 | 23.4 |
| `distinct_by_order_take` | 398.8 | — | — | 29.8 |
| `distinct_by_order_to_array` | 398.1 | — | — | 30.0 |
| `distinct_count` | 66.8 | 26.0 | 147.9 | 23.9 |
| `distinct_count_pred` | 407.0 | — | — | 23.3 |
| `distinct_take` | 0.1 | 27.3 | 147.5 | 0.0 |
| `element_at_match` | 0.1 | 6.0 | 1.5 | 0.0 |
| `first_match` | 0.1 | 5.9 | 1.5 | 0.0 |
| `first_or_default_match` | 0.1 | 5.9 | 1.5 | 0.0 |
| `groupby_average` | 294.4 | 9.9 | 227.4 | 55.9 |
| `groupby_count` | 253.3 | 8.6 | 161.1 | 50.3 |
| `groupby_first` | 403.1 | — | — | 31.6 |
| `groupby_having_count` | 252.0 | 9.7 | 160.9 | 32.1 |
| `groupby_having_hidden_sum` | 304.9 | 12.3 | 235.8 | 52.5 |
| `groupby_having_post_where` | 293.8 | 11.7 | 227.4 | 47.2 |
| `groupby_max` | 306.0 | 10.0 | 162.1 | 52.5 |
| `groupby_min` | 307.2 | 9.4 | 160.9 | 40.1 |
| `groupby_multi_reducer` | 339.3 | 11.8 | 241.2 | 59.2 |
| `groupby_select_order` | 293.1 | — | — | 49.0 |
| `groupby_select_sum` | 313.5 | 36.6 | 246.7 | 73.0 |
| `groupby_sum` | 301.2 | 9.5 | 219.9 | 48.8 |
| `groupby_where_count` | 133.2 | 10.1 | 122.9 | 21.4 |
| `groupby_where_sum` | 149.7 | 10.9 | 159.6 | 22.4 |
| `join_count` | 58.4 | 9.5 | 175.1 | 67.5 |
| `join_groupby_count` | 279.2 | 15.3 | 258.1 | 112.5 |
| `join_groupby_to_array` | 317.9 | 16.7 | 347.1 | 137.6 |
| `join_select` | 238.9 | 387.4 | 439.0 | 107.8 |
| `join_where_count` | 59.8 | 13.2 | 139.6 | 85.0 |
| `last_match` | 0.1 | 38.8 | 1.6 | 10.1 |
| `long_count_aggregate` | 44.5 | 6.1 | 75.1 | 6.3 |
| `max_aggregate` | 56.0 | 4.8 | 75.4 | 9.1 |
| `min_aggregate` | 54.9 | 4.8 | 75.7 | 9.1 |
| `order_by_multi_key` | 525.5 | 488.7 | 1001.3 | 463.4 |
| `order_distinct_take` | 240.2 | 28.7 | 128.6 | 23.1 |
| `order_reverse_normalized` | 65.9 | 19.9 | 97.3 | 21.6 |
| `order_take_desc` | 68.6 | 19.8 | 97.1 | 21.4 |
| `reverse_distinct_by` | 475.9 | — | — | 33.7 |
| `reverse_take` | 0.1 | 115.8 | 1.6 | 0.0 |
| `reverse_take_select` | 0.1 | 114.9 | 1.6 | 0.0 |
| `select_count` | 0.2 | 3.4 | 45.0 | 0.0 |
| `select_where` | 309.8 | 402.7 | 607.8 | 18.8 |
| `select_where_count` | 54.6 | 6.8 | 83.0 | 7.6 |
| `select_where_order_take` | 61.7 | 22.5 | 105.1 | 17.4 |
| `select_where_sum` | 66.0 | 8.4 | 125.7 | 10.8 |
| `single_match` | 0.1 | 5.5 | 1.5 | 4.9 |
| `skip_take` | 0.8 | 13.7 | 2.8 | 0.2 |
| `skip_while_match` | 6.5 | 8.9 | 44.7 | 7.5 |
| `sort_first` | 67.6 | 16.0 | 96.3 | 13.0 |
| `sort_take` | 69.0 | 20.0 | 97.1 | 21.2 |
| `sort_take_select` | 68.0 | 18.3 | 193.6 | 21.6 |
| `sum_aggregate` | 43.3 | 4.4 | 135.5 | 3.8 |
| `sum_where` | 46.7 | 6.8 | 113.4 | 6.6 |
| `take_count` | 5.8 | 22.6 | 13.3 | 0.4 |
| `take_count_filtered` | 1.8 | 6.4 | 3.8 | 0.2 |
| `take_sum_aggregate` | 1.4 | 12.9 | 3.5 | 0.1 |
| `take_where_count` | 1.4 | 13.4 | 3.1 | 0.1 |
| `take_while_match` | 16.6 | 9.6 | 46.1 | 3.5 |
| `to_array_filter` | 106.8 | 60.2 | 206.3 | 20.4 |
| `where_join_count` | 59.1 | 12.4 | 139.0 | 40.9 |
| `zip_count_pred` | 62.7 | 8.3 | 88.8 | 26.8 |
| `zip_dot_product` | 74.9 | 7.3 | 94.7 | 21.2 |
| `zip_dot_product_3arg` | 76.7 | 7.1 | 95.6 | 19.8 |

## JIT

| Benchmark | SQLite | DuckDB | PostgreSQL | Array |
|---|---:|---:|---:|---:|
| `aggregate_match` | 52.1 | 7.0 | 147.9 | 0.7 |
| `all_match` | 39.0 | 3.9 | 71.7 | 0.8 |
| `any_match` | 0.1 | 5.7 | 1.3 | 0.0 |
| `average_aggregate` | 43.0 | 4.8 | 144.3 | 0.9 |
| `bare_order_where` | 272.1 | 266.7 | 695.1 | 61.8 |
| `chained_where` | 50.6 | 7.7 | 89.8 | 0.9 |
| `contains_match` | 0.0 | 5.4 | 1.4 | 0.2 |
| `count_aggregate` | 43.6 | 6.0 | 81.5 | 0.6 |
| `cross_join` | 9743.5 | 6468.0 | 33712.7 | 1351.3 |
| `distinct_by_count` | 66.6 | 25.6 | 137.6 | 1.6 |
| `distinct_by_order_take` | 402.5 | — | — | 2.4 |
| `distinct_by_order_to_array` | 398.9 | — | — | 2.7 |
| `distinct_count` | 65.9 | 26.7 | 146.7 | 1.6 |
| `distinct_count_pred` | 403.2 | — | — | 1.6 |
| `distinct_take` | 0.1 | 26.6 | 147.4 | 0.0 |
| `element_at_match` | 0.1 | 5.8 | 1.3 | 0.0 |
| `first_match` | 0.1 | 5.8 | 1.3 | 0.0 |
| `first_or_default_match` | 0.1 | 5.8 | 1.4 | 0.0 |
| `groupby_average` | 297.8 | 9.6 | 226.3 | 2.1 |
| `groupby_count` | 249.3 | 8.6 | 153.9 | 1.8 |
| `groupby_first` | 413.9 | — | — | 1.8 |
| `groupby_having_count` | 255.9 | 9.9 | 155.5 | 1.8 |
| `groupby_having_hidden_sum` | 303.0 | 11.5 | 231.1 | 2.1 |
| `groupby_having_post_where` | 297.6 | 11.0 | 224.4 | 2.4 |
| `groupby_max` | 303.2 | 9.3 | 160.8 | 2.0 |
| `groupby_min` | 302.4 | 9.3 | 159.8 | 2.2 |
| `groupby_multi_reducer` | 328.4 | 11.9 | 237.9 | 2.2 |
| `groupby_select_order` | 294.1 | — | — | 2.1 |
| `groupby_select_sum` | 305.1 | 36.2 | 247.8 | 4.0 |
| `groupby_sum` | 293.7 | 9.6 | 217.8 | 1.9 |
| `groupby_where_count` | 135.9 | 10.2 | 122.2 | 1.5 |
| `groupby_where_sum` | 145.0 | 10.8 | 161.0 | 1.5 |
| `join_count` | 58.7 | 9.3 | 175.1 | 19.6 |
| `join_groupby_count` | 279.7 | 15.5 | 255.3 | 28.5 |
| `join_groupby_to_array` | 315.7 | 17.1 | 341.3 | 36.7 |
| `join_select` | 155.4 | 235.4 | 366.3 | 32.5 |
| `join_where_count` | 58.8 | 13.1 | 139.6 | 24.7 |
| `last_match` | 0.1 | 38.7 | 1.5 | 1.0 |
| `long_count_aggregate` | 42.5 | 6.2 | 74.7 | 0.7 |
| `max_aggregate` | 54.2 | 4.9 | 75.2 | 0.6 |
| `min_aggregate` | 54.5 | 4.8 | 75.2 | 0.6 |
| `order_by_multi_key` | 354.6 | 269.8 | 832.4 | 100.7 |
| `order_distinct_take` | 241.8 | 29.4 | 127.9 | 1.4 |
| `order_reverse_normalized` | 67.6 | 20.1 | 96.7 | 1.1 |
| `order_take_desc` | 69.3 | 20.2 | 98.8 | 1.2 |
| `reverse_distinct_by` | 473.8 | — | — | 2.3 |
| `reverse_take` | 0.1 | 116.8 | 1.4 | 0.0 |
| `reverse_take_select` | 0.1 | 115.1 | 1.5 | 0.0 |
| `select_count` | 0.2 | 3.3 | 45.1 | 0.0 |
| `select_where` | 158.0 | 183.4 | 422.3 | 5.5 |
| `select_where_count` | 53.4 | 6.7 | 82.0 | 0.6 |
| `select_where_order_take` | 61.3 | 22.2 | 106.3 | 1.2 |
| `select_where_sum` | 65.7 | 8.4 | 122.7 | 0.8 |
| `single_match` | 0.0 | 5.5 | 1.4 | 0.8 |
| `skip_take` | 0.4 | 12.9 | 2.2 | 0.0 |
| `skip_while_match` | 6.4 | 8.9 | 44.5 | 0.5 |
| `sort_first` | 68.4 | 16.2 | 96.0 | 0.8 |
| `sort_take` | 68.4 | 20.1 | 97.2 | 1.2 |
| `sort_take_select` | 67.4 | 18.2 | 196.1 | 1.1 |
| `sum_aggregate` | 43.0 | 4.4 | 139.8 | 0.6 |
| `sum_where` | 48.1 | 6.7 | 112.7 | 0.8 |
| `take_count` | 2.6 | 18.0 | 8.9 | 0.2 |
| `take_count_filtered` | 1.9 | 6.4 | 3.6 | 0.0 |
| `take_sum_aggregate` | 1.4 | 12.9 | 3.4 | 0.0 |
| `take_where_count` | 1.4 | 13.1 | 2.9 | 0.0 |
| `take_while_match` | 16.6 | 9.5 | 46.6 | 0.2 |
| `to_array_filter` | 68.9 | 20.2 | 158.6 | 3.3 |
| `where_join_count` | 58.9 | 12.2 | 137.0 | 10.3 |
| `zip_count_pred` | 63.5 | 7.7 | 88.6 | 0.1 |
| `zip_dot_product` | 74.6 | 6.9 | 93.9 | 0.1 |
| `zip_dot_product_3arg` | 76.7 | 6.9 | 95.4 | 0.1 |
<!-- BENCH:TABLES END -->

## How to re-run

From this folder, with the packages installed (see [README.md](README.md)):

```bash
cd examples/benchmarks/sql
# INTERP sweep
for f in sqlite duckdb postgres array; do
    daslang -project_root . ../../../dastest/dastest.das -- --bench --bench-format json \
        --test $f.das >> _bench_interp.json 2>&1
done
# JIT sweep (-jit before dastest.das)
for f in sqlite duckdb postgres array; do
    daslang -jit -project_root . ../../../dastest/dastest.das -- --bench --bench-format json \
        --test $f.das >> _bench_jit.json 2>&1
done
# regenerate the tables below
daslang _update_results.das -- --results results.md \
    --interp _bench_interp.json --jit _bench_jit.json --date YYYY-MM-DD
```
