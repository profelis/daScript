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

A PostgreSQL `—` in *every* row just means no server was reachable (the lane
self-skips). The six formerly-dashed DuckDB/PostgreSQL families
(`distinct_by_*`, `distinct_count_pred`, `groupby_first`,
`groupby_select_order`, `reverse_distinct_by`) were a dialect gap this suite
exposed; it's closed — `_distinct_by` now lowers via the provider's
`caps.distinct_on` (`DISTINCT ON` on DuckDB/PostgreSQL, SQLite keeps its
bare-aggregate `GROUP BY`), and renamed projection entries declare
`AS "<alias>"` so ordering over them resolves on strict engines.

<!-- BENCH:TABLES BEGIN -->
*Generated 2026-07-05 by `examples/benchmarks/sql/_update_results.das` — ns/op; `—` = absent lane (e.g. no PostgreSQL server was reachable). Edit the prose around the markers, not the tables.*

## INTERP

| Benchmark | SQLite | DuckDB | PostgreSQL | Array |
|---|---:|---:|---:|---:|
| `aggregate_match` | 52.2 | 6.4 | 145.3 | 9.7 |
| `all_match` | 39.0 | 3.5 | 72.4 | 6.0 |
| `any_match` | 0.1 | 5.2 | 1.4 | 0.0 |
| `average_aggregate` | 43.4 | 4.4 | 142.4 | 9.3 |
| `bare_order_where` | 425.7 | 480.5 | 880.5 | 198.3 |
| `chained_where` | 50.9 | 7.3 | 88.7 | 9.5 |
| `contains_match` | 0.1 | 5.1 | 1.4 | 3.0 |
| `count_aggregate` | 42.1 | 5.5 | 81.4 | 6.4 |
| `cross_join` | 20444.9 | 18077.6 | 47026.9 | 5909.9 |
| `distinct_by_count` | 66.6 | 23.7 | 136.7 | 23.4 |
| `distinct_by_order_take` | 394.2 | 116.2 | 673.7 | 29.9 |
| `distinct_by_order_to_array` | 398.8 | 115.0 | 676.9 | 30.4 |
| `distinct_count` | 67.6 | 26.5 | 147.5 | 24.0 |
| `distinct_count_pred` | 409.1 | 53.2 | 821.7 | 23.7 |
| `distinct_take` | 0.1 | 26.7 | 152.8 | 0.0 |
| `element_at_match` | 0.1 | 5.5 | 1.4 | 0.0 |
| `first_match` | 0.1 | 5.6 | 1.4 | 0.0 |
| `first_or_default_match` | 0.1 | 5.5 | 1.4 | 0.0 |
| `groupby_average` | 293.7 | 9.4 | 229.0 | 63.1 |
| `groupby_count` | 256.6 | 8.1 | 160.0 | 47.4 |
| `groupby_first` | 405.7 | 107.7 | 712.6 | 31.4 |
| `groupby_having_count` | 250.6 | 9.4 | 154.3 | 36.0 |
| `groupby_having_hidden_sum` | 301.1 | 11.0 | 228.9 | 53.4 |
| `groupby_having_post_where` | 289.8 | 10.7 | 223.4 | 47.7 |
| `groupby_max` | 300.3 | 8.9 | 161.4 | 53.8 |
| `groupby_min` | 306.4 | 9.0 | 163.5 | 56.3 |
| `groupby_multi_reducer` | 335.4 | 11.1 | 245.8 | 54.7 |
| `groupby_select_order` | 294.3 | 10.9 | 223.8 | 48.2 |
| `groupby_select_sum` | 309.1 | 36.1 | 257.9 | 65.9 |
| `groupby_sum` | 298.3 | 9.3 | 221.7 | 42.1 |
| `groupby_where_count` | 135.4 | 9.8 | 128.9 | 21.7 |
| `groupby_where_sum` | 143.5 | 10.4 | 161.0 | 21.3 |
| `join_count` | 58.2 | 8.8 | 173.1 | 68.9 |
| `join_groupby_count` | 276.2 | 14.8 | 252.2 | 123.9 |
| `join_groupby_to_array` | 315.2 | 15.7 | 336.8 | 114.1 |
| `join_select` | 237.6 | 398.3 | 429.7 | 106.7 |
| `join_where_count` | 59.4 | 12.2 | 137.1 | 86.7 |
| `last_match` | 0.1 | 37.0 | 1.5 | 9.5 |
| `long_count_aggregate` | 41.7 | 5.8 | 74.0 | 6.4 |
| `max_aggregate` | 54.1 | 4.5 | 74.4 | 9.0 |
| `min_aggregate` | 55.5 | 4.5 | 75.8 | 9.1 |
| `order_by_multi_key` | 501.1 | 487.4 | 1008.7 | 500.6 |
| `order_distinct_take` | 242.2 | 28.0 | 130.2 | 23.4 |
| `order_reverse_normalized` | 68.5 | 18.7 | 98.8 | 21.2 |
| `order_take_desc` | 70.7 | 18.3 | 98.5 | 21.7 |
| `reverse_distinct_by` | 475.7 | 215.6 | 693.1 | 40.3 |
| `reverse_take` | 0.1 | 114.0 | 1.5 | 0.0 |
| `reverse_take_select` | 0.1 | 113.1 | 1.5 | 0.0 |
| `select_count` | 0.2 | 3.0 | 44.4 | 0.0 |
| `select_where` | 308.9 | 409.9 | 597.6 | 27.5 |
| `select_where_count` | 51.7 | 6.4 | 81.3 | 7.6 |
| `select_where_order_take` | 60.4 | 20.9 | 102.1 | 17.2 |
| `select_where_sum` | 64.8 | 8.1 | 120.9 | 9.9 |
| `single_match` | 0.1 | 5.3 | 1.4 | 4.9 |
| `skip_take` | 0.8 | 12.4 | 2.7 | 0.2 |
| `skip_while_match` | 6.6 | 8.5 | 45.3 | 7.4 |
| `sort_first` | 69.0 | 14.7 | 96.7 | 13.5 |
| `sort_take` | 68.0 | 19.3 | 98.8 | 21.4 |
| `sort_take_select` | 68.3 | 17.3 | 198.5 | 21.8 |
| `sum_aggregate` | 42.9 | 4.2 | 136.2 | 2.4 |
| `sum_where` | 47.3 | 6.6 | 111.7 | 6.7 |
| `take_count` | 5.8 | 21.8 | 13.0 | 0.4 |
| `take_count_filtered` | 1.8 | 6.0 | 3.6 | 0.2 |
| `take_sum_aggregate` | 1.4 | 11.5 | 3.4 | 0.1 |
| `take_where_count` | 1.4 | 12.1 | 3.0 | 0.1 |
| `take_while_match` | 16.7 | 9.2 | 44.9 | 3.6 |
| `to_array_filter` | 106.0 | 58.2 | 203.3 | 19.7 |
| `where_join_count` | 60.3 | 11.2 | 137.3 | 40.6 |
| `zip_count_pred` | 63.6 | 7.6 | 90.1 | 27.3 |
| `zip_dot_product` | 76.6 | 6.5 | 95.0 | 19.6 |
| `zip_dot_product_3arg` | 76.9 | 6.6 | 95.6 | 19.5 |

## JIT

| Benchmark | SQLite | DuckDB | PostgreSQL | Array |
|---|---:|---:|---:|---:|
| `aggregate_match` | 55.7 | 6.5 | 143.8 | 0.4 |
| `all_match` | 50.3 | 3.5 | 69.8 | 0.5 |
| `any_match` | 0.1 | 5.2 | 1.3 | 0.0 |
| `average_aggregate` | 54.4 | 4.3 | 140.4 | 0.8 |
| `bare_order_where` | 407.3 | 261.4 | 689.1 | 61.8 |
| `chained_where` | 61.0 | 7.6 | 88.3 | 0.6 |
| `contains_match` | 0.0 | 5.0 | 1.3 | 0.2 |
| `count_aggregate` | 55.3 | 5.5 | 80.8 | 0.4 |
| `cross_join` | 9783.8 | 6437.4 | 33556.3 | 1325.8 |
| `distinct_by_count` | 78.6 | 23.6 | 135.1 | 1.4 |
| `distinct_by_order_take` | 520.8 | 113.4 | 681.3 | 2.4 |
| `distinct_by_order_to_array` | 541.2 | 113.0 | 667.2 | 2.6 |
| `distinct_count` | 77.9 | 25.7 | 145.6 | 1.4 |
| `distinct_count_pred` | 527.6 | 52.7 | 817.9 | 1.4 |
| `distinct_take` | 0.1 | 25.9 | 150.1 | 0.0 |
| `element_at_match` | 0.1 | 5.4 | 1.3 | 0.0 |
| `first_match` | 0.1 | 5.4 | 1.3 | 0.0 |
| `first_or_default_match` | 0.1 | 5.4 | 1.3 | 0.0 |
| `groupby_average` | 316.5 | 9.5 | 231.9 | 1.9 |
| `groupby_count` | 256.4 | 8.0 | 158.7 | 1.6 |
| `groupby_first` | 411.4 | 108.7 | 757.6 | 1.6 |
| `groupby_having_count` | 253.1 | 9.3 | 157.5 | 1.6 |
| `groupby_having_hidden_sum` | 311.4 | 11.0 | 229.3 | 1.8 |
| `groupby_having_post_where` | 300.6 | 10.7 | 221.8 | 1.6 |
| `groupby_max` | 309.8 | 8.9 | 162.8 | 1.7 |
| `groupby_min` | 304.4 | 8.7 | 163.2 | 2.1 |
| `groupby_multi_reducer` | 333.1 | 11.0 | 245.2 | 2.0 |
| `groupby_select_order` | 294.4 | 10.7 | 223.4 | 1.8 |
| `groupby_select_sum` | 305.2 | 34.9 | 265.8 | 3.9 |
| `groupby_sum` | 293.4 | 8.9 | 223.1 | 1.6 |
| `groupby_where_count` | 134.3 | 9.7 | 132.5 | 1.2 |
| `groupby_where_sum` | 149.3 | 10.1 | 163.1 | 1.1 |
| `join_count` | 59.4 | 8.7 | 183.9 | 19.6 |
| `join_groupby_count` | 283.6 | 14.5 | 256.3 | 28.4 |
| `join_groupby_to_array` | 324.7 | 15.5 | 336.6 | 36.6 |
| `join_select` | 153.9 | 231.0 | 373.3 | 33.1 |
| `join_where_count` | 60.7 | 12.1 | 146.5 | 25.5 |
| `last_match` | 0.1 | 37.7 | 1.5 | 0.8 |
| `long_count_aggregate` | 42.3 | 5.7 | 94.2 | 0.4 |
| `max_aggregate` | 52.7 | 4.5 | 98.3 | 0.4 |
| `min_aggregate` | 54.3 | 4.4 | 83.1 | 0.4 |
| `order_by_multi_key` | 353.4 | 259.1 | 818.5 | 96.1 |
| `order_distinct_take` | 237.8 | 29.4 | 134.9 | 1.4 |
| `order_reverse_normalized` | 67.1 | 18.3 | 103.7 | 0.8 |
| `order_take_desc` | 66.9 | 18.3 | 103.2 | 0.7 |
| `reverse_distinct_by` | 484.5 | 221.6 | 689.5 | 2.1 |
| `reverse_take` | 0.1 | 117.0 | 1.3 | 0.0 |
| `reverse_take_select` | 0.1 | 116.4 | 1.4 | 0.0 |
| `select_count` | 0.2 | 3.0 | 44.2 | 0.0 |
| `select_where` | 162.6 | 186.0 | 414.8 | 5.3 |
| `select_where_count` | 52.8 | 6.3 | 81.3 | 0.4 |
| `select_where_order_take` | 61.6 | 21.1 | 101.6 | 0.9 |
| `select_where_sum` | 64.7 | 8.1 | 121.6 | 0.4 |
| `single_match` | 0.0 | 5.1 | 1.3 | 0.4 |
| `skip_take` | 0.4 | 12.0 | 2.1 | 0.0 |
| `skip_while_match` | 6.5 | 8.5 | 44.5 | 0.5 |
| `sort_first` | 67.9 | 14.6 | 95.7 | 0.5 |
| `sort_take` | 66.6 | 18.5 | 96.8 | 0.8 |
| `sort_take_select` | 66.3 | 16.8 | 197.2 | 0.8 |
| `sum_aggregate` | 42.6 | 4.0 | 133.7 | 0.5 |
| `sum_where` | 47.4 | 6.5 | 111.8 | 0.4 |
| `take_count` | 2.6 | 16.4 | 8.5 | 0.1 |
| `take_count_filtered` | 1.8 | 5.8 | 3.5 | 0.0 |
| `take_sum_aggregate` | 1.4 | 11.5 | 3.2 | 0.0 |
| `take_where_count` | 1.4 | 11.7 | 2.9 | 0.0 |
| `take_while_match` | 17.1 | 9.0 | 44.9 | 0.2 |
| `to_array_filter` | 68.0 | 19.5 | 157.9 | 3.2 |
| `where_join_count` | 59.0 | 11.6 | 139.1 | 10.3 |
| `zip_count_pred` | 62.3 | 7.4 | 88.6 | 0.1 |
| `zip_dot_product` | 75.3 | 6.4 | 94.3 | 0.1 |
| `zip_dot_product_3arg` | 74.7 | 6.4 | 94.6 | 0.1 |
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
