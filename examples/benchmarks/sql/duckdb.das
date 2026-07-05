options gen2
options persistent_heap

require _common public
require _sql_families public
require duckdb/duckdb_boost public

// DuckDB engine lane: in-memory DB, fixtures built once in [init]; every family
// body lives in _sql_families.das. Needs the dasDuckDB package installed —
// see README.md and .das_package.

var g_db : duckdb_boost::SqlRunner <- open_duckdb(":memory:")

[init]
def duckdb_bench_init {
    fixture_db(g_db, N)
    fixture_db_brands(g_db, N)
}

[finalize]
def duckdb_bench_fini {
    delete g_db
}

[benchmark]
def aggregate_match_duckdb(b : B?) {
    bench_aggregate_match(b, g_db)
}

[benchmark]
def all_match_duckdb(b : B?) {
    bench_all_match(b, g_db)
}

[benchmark]
def any_match_duckdb(b : B?) {
    bench_any_match(b, g_db)
}

[benchmark]
def average_aggregate_duckdb(b : B?) {
    bench_average_aggregate(b, g_db)
}

[benchmark]
def bare_order_where_duckdb(b : B?) {
    bench_bare_order_where(b, g_db)
}

[benchmark]
def chained_where_duckdb(b : B?) {
    bench_chained_where(b, g_db)
}

[benchmark]
def contains_match_duckdb(b : B?) {
    bench_contains_match(b, g_db)
}

[benchmark]
def count_aggregate_duckdb(b : B?) {
    bench_count_aggregate(b, g_db)
}

[benchmark]
def distinct_by_count_duckdb(b : B?) {
    bench_distinct_by_count(b, g_db)
}

[benchmark]
def distinct_by_order_take_duckdb(b : B?) {
    bench_distinct_by_order_take(b, g_db)
}

[benchmark]
def distinct_by_order_to_array_duckdb(b : B?) {
    bench_distinct_by_order_to_array(b, g_db)
}

[benchmark]
def distinct_count_duckdb(b : B?) {
    bench_distinct_count(b, g_db)
}

[benchmark]
def distinct_count_pred_duckdb(b : B?) {
    bench_distinct_count_pred(b, g_db)
}

[benchmark]
def distinct_take_duckdb(b : B?) {
    bench_distinct_take(b, g_db)
}

[benchmark]
def element_at_match_duckdb(b : B?) {
    bench_element_at_match(b, g_db)
}

[benchmark]
def first_match_duckdb(b : B?) {
    bench_first_match(b, g_db)
}

[benchmark]
def first_or_default_match_duckdb(b : B?) {
    bench_first_or_default_match(b, g_db)
}

[benchmark]
def groupby_average_duckdb(b : B?) {
    bench_groupby_average(b, g_db)
}

[benchmark]
def groupby_count_duckdb(b : B?) {
    bench_groupby_count(b, g_db)
}

[benchmark]
def groupby_first_duckdb(b : B?) {
    bench_groupby_first(b, g_db)
}

[benchmark]
def groupby_having_count_duckdb(b : B?) {
    bench_groupby_having_count(b, g_db)
}

[benchmark]
def groupby_having_hidden_sum_duckdb(b : B?) {
    bench_groupby_having_hidden_sum(b, g_db)
}

[benchmark]
def groupby_having_post_where_duckdb(b : B?) {
    bench_groupby_having_post_where(b, g_db)
}

[benchmark]
def groupby_max_duckdb(b : B?) {
    bench_groupby_max(b, g_db)
}

[benchmark]
def groupby_min_duckdb(b : B?) {
    bench_groupby_min(b, g_db)
}

[benchmark]
def groupby_multi_reducer_duckdb(b : B?) {
    bench_groupby_multi_reducer(b, g_db)
}

[benchmark]
def groupby_select_order_duckdb(b : B?) {
    bench_groupby_select_order(b, g_db)
}

[benchmark]
def groupby_select_sum_duckdb(b : B?) {
    bench_groupby_select_sum(b, g_db)
}

[benchmark]
def groupby_sum_duckdb(b : B?) {
    bench_groupby_sum(b, g_db)
}

[benchmark]
def groupby_where_count_duckdb(b : B?) {
    bench_groupby_where_count(b, g_db)
}

[benchmark]
def groupby_where_sum_duckdb(b : B?) {
    bench_groupby_where_sum(b, g_db)
}

[benchmark]
def join_count_duckdb(b : B?) {
    bench_join_count(b, g_db)
}

[benchmark]
def join_groupby_count_duckdb(b : B?) {
    bench_join_groupby_count(b, g_db)
}

[benchmark]
def join_groupby_to_array_duckdb(b : B?) {
    bench_join_groupby_to_array(b, g_db)
}

[benchmark]
def join_select_duckdb(b : B?) {
    bench_join_select(b, g_db)
}

[benchmark]
def join_where_count_duckdb(b : B?) {
    bench_join_where_count(b, g_db)
}

[benchmark]
def last_match_duckdb(b : B?) {
    bench_last_match(b, g_db)
}

[benchmark]
def long_count_aggregate_duckdb(b : B?) {
    bench_long_count_aggregate(b, g_db)
}

[benchmark]
def max_aggregate_duckdb(b : B?) {
    bench_max_aggregate(b, g_db)
}

[benchmark]
def min_aggregate_duckdb(b : B?) {
    bench_min_aggregate(b, g_db)
}

[benchmark]
def order_by_multi_key_duckdb(b : B?) {
    bench_order_by_multi_key(b, g_db)
}

[benchmark]
def order_distinct_take_duckdb(b : B?) {
    bench_order_distinct_take(b, g_db)
}

[benchmark]
def order_reverse_normalized_duckdb(b : B?) {
    bench_order_reverse_normalized(b, g_db)
}

[benchmark]
def order_take_desc_duckdb(b : B?) {
    bench_order_take_desc(b, g_db)
}

[benchmark]
def reverse_distinct_by_duckdb(b : B?) {
    bench_reverse_distinct_by(b, g_db)
}

[benchmark]
def reverse_take_duckdb(b : B?) {
    bench_reverse_take(b, g_db)
}

[benchmark]
def reverse_take_select_duckdb(b : B?) {
    bench_reverse_take_select(b, g_db)
}

[benchmark]
def select_count_duckdb(b : B?) {
    bench_select_count(b, g_db)
}

[benchmark]
def select_where_duckdb(b : B?) {
    bench_select_where(b, g_db)
}

[benchmark]
def select_where_count_duckdb(b : B?) {
    bench_select_where_count(b, g_db)
}

[benchmark]
def select_where_order_take_duckdb(b : B?) {
    bench_select_where_order_take(b, g_db)
}

[benchmark]
def select_where_sum_duckdb(b : B?) {
    bench_select_where_sum(b, g_db)
}

[benchmark]
def single_match_duckdb(b : B?) {
    bench_single_match(b, g_db)
}

[benchmark]
def skip_take_duckdb(b : B?) {
    bench_skip_take(b, g_db)
}

[benchmark]
def skip_while_match_duckdb(b : B?) {
    bench_skip_while_match(b, g_db)
}

[benchmark]
def sort_first_duckdb(b : B?) {
    bench_sort_first(b, g_db)
}

[benchmark]
def sort_take_duckdb(b : B?) {
    bench_sort_take(b, g_db)
}

[benchmark]
def sort_take_select_duckdb(b : B?) {
    bench_sort_take_select(b, g_db)
}

[benchmark]
def sum_aggregate_duckdb(b : B?) {
    bench_sum_aggregate(b, g_db)
}

[benchmark]
def sum_where_duckdb(b : B?) {
    bench_sum_where(b, g_db)
}

[benchmark]
def take_count_duckdb(b : B?) {
    bench_take_count(b, g_db)
}

[benchmark]
def take_count_filtered_duckdb(b : B?) {
    bench_take_count_filtered(b, g_db)
}

[benchmark]
def take_sum_aggregate_duckdb(b : B?) {
    bench_take_sum_aggregate(b, g_db)
}

[benchmark]
def take_where_count_duckdb(b : B?) {
    bench_take_where_count(b, g_db)
}

[benchmark]
def take_while_match_duckdb(b : B?) {
    bench_take_while_match(b, g_db)
}

[benchmark]
def to_array_filter_duckdb(b : B?) {
    bench_to_array_filter(b, g_db)
}

[benchmark]
def where_join_count_duckdb(b : B?) {
    bench_where_join_count(b, g_db)
}

[benchmark]
def zip_count_pred_duckdb(b : B?) {
    bench_zip_count_pred(b, g_db)
}

[benchmark]
def zip_dot_product_duckdb(b : B?) {
    bench_zip_dot_product(b, g_db)
}

[benchmark]
def zip_dot_product_3arg_duckdb(b : B?) {
    bench_zip_dot_product_3arg(b, g_db)
}

[benchmark]
def cross_join_duckdb(b : B?) {
    bench_cross_join(b, g_db)
}

