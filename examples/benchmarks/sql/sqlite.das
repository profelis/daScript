options gen2
options persistent_heap

require _common public
require _sql_families public
require sqlite/sqlite_boost public

// SQLite engine lane: in-memory DB, fixtures built once in [init]; every family
// body lives in _sql_families.das. See README.md for how to run the sweep.

var g_db : sqlite_boost::SqlRunner <- open_sqlite(":memory:")

[init]
def sqlite_bench_init {
    g_db |> exec("PRAGMA foreign_keys = ON")
    fixture_db(g_db, N)
    fixture_db_brands(g_db, N)
}

[finalize]
def sqlite_bench_fini {
    delete g_db
}

[benchmark]
def aggregate_match_sqlite(b : B?) {
    bench_aggregate_match(b, g_db)
}

[benchmark]
def all_match_sqlite(b : B?) {
    bench_all_match(b, g_db)
}

[benchmark]
def any_match_sqlite(b : B?) {
    bench_any_match(b, g_db)
}

[benchmark]
def average_aggregate_sqlite(b : B?) {
    bench_average_aggregate(b, g_db)
}

[benchmark]
def bare_order_where_sqlite(b : B?) {
    bench_bare_order_where(b, g_db)
}

[benchmark]
def chained_where_sqlite(b : B?) {
    bench_chained_where(b, g_db)
}

[benchmark]
def contains_match_sqlite(b : B?) {
    bench_contains_match(b, g_db)
}

[benchmark]
def count_aggregate_sqlite(b : B?) {
    bench_count_aggregate(b, g_db)
}

[benchmark]
def distinct_by_count_sqlite(b : B?) {
    bench_distinct_by_count(b, g_db)
}

[benchmark]
def distinct_by_order_take_sqlite(b : B?) {
    bench_distinct_by_order_take(b, g_db)
}

[benchmark]
def distinct_by_order_to_array_sqlite(b : B?) {
    bench_distinct_by_order_to_array(b, g_db)
}

[benchmark]
def distinct_count_sqlite(b : B?) {
    bench_distinct_count(b, g_db)
}

[benchmark]
def distinct_count_pred_sqlite(b : B?) {
    bench_distinct_count_pred(b, g_db)
}

[benchmark]
def distinct_take_sqlite(b : B?) {
    bench_distinct_take(b, g_db)
}

[benchmark]
def element_at_match_sqlite(b : B?) {
    bench_element_at_match(b, g_db)
}

[benchmark]
def first_match_sqlite(b : B?) {
    bench_first_match(b, g_db)
}

[benchmark]
def first_or_default_match_sqlite(b : B?) {
    bench_first_or_default_match(b, g_db)
}

[benchmark]
def groupby_average_sqlite(b : B?) {
    bench_groupby_average(b, g_db)
}

[benchmark]
def groupby_count_sqlite(b : B?) {
    bench_groupby_count(b, g_db)
}

[benchmark]
def groupby_first_sqlite(b : B?) {
    bench_groupby_first(b, g_db)
}

[benchmark]
def groupby_having_count_sqlite(b : B?) {
    bench_groupby_having_count(b, g_db)
}

[benchmark]
def groupby_having_hidden_sum_sqlite(b : B?) {
    bench_groupby_having_hidden_sum(b, g_db)
}

[benchmark]
def groupby_having_post_where_sqlite(b : B?) {
    bench_groupby_having_post_where(b, g_db)
}

[benchmark]
def groupby_max_sqlite(b : B?) {
    bench_groupby_max(b, g_db)
}

[benchmark]
def groupby_min_sqlite(b : B?) {
    bench_groupby_min(b, g_db)
}

[benchmark]
def groupby_multi_reducer_sqlite(b : B?) {
    bench_groupby_multi_reducer(b, g_db)
}

[benchmark]
def groupby_select_order_sqlite(b : B?) {
    bench_groupby_select_order(b, g_db)
}

[benchmark]
def groupby_select_sum_sqlite(b : B?) {
    bench_groupby_select_sum(b, g_db)
}

[benchmark]
def groupby_sum_sqlite(b : B?) {
    bench_groupby_sum(b, g_db)
}

[benchmark]
def groupby_where_count_sqlite(b : B?) {
    bench_groupby_where_count(b, g_db)
}

[benchmark]
def groupby_where_sum_sqlite(b : B?) {
    bench_groupby_where_sum(b, g_db)
}

[benchmark]
def join_count_sqlite(b : B?) {
    bench_join_count(b, g_db)
}

[benchmark]
def join_groupby_count_sqlite(b : B?) {
    bench_join_groupby_count(b, g_db)
}

[benchmark]
def join_groupby_to_array_sqlite(b : B?) {
    bench_join_groupby_to_array(b, g_db)
}

[benchmark]
def join_select_sqlite(b : B?) {
    bench_join_select(b, g_db)
}

[benchmark]
def join_where_count_sqlite(b : B?) {
    bench_join_where_count(b, g_db)
}

[benchmark]
def last_match_sqlite(b : B?) {
    bench_last_match(b, g_db)
}

[benchmark]
def long_count_aggregate_sqlite(b : B?) {
    bench_long_count_aggregate(b, g_db)
}

[benchmark]
def max_aggregate_sqlite(b : B?) {
    bench_max_aggregate(b, g_db)
}

[benchmark]
def min_aggregate_sqlite(b : B?) {
    bench_min_aggregate(b, g_db)
}

[benchmark]
def order_by_multi_key_sqlite(b : B?) {
    bench_order_by_multi_key(b, g_db)
}

[benchmark]
def order_distinct_take_sqlite(b : B?) {
    bench_order_distinct_take(b, g_db)
}

[benchmark]
def order_reverse_normalized_sqlite(b : B?) {
    bench_order_reverse_normalized(b, g_db)
}

[benchmark]
def order_take_desc_sqlite(b : B?) {
    bench_order_take_desc(b, g_db)
}

[benchmark]
def reverse_distinct_by_sqlite(b : B?) {
    bench_reverse_distinct_by(b, g_db)
}

[benchmark]
def reverse_take_sqlite(b : B?) {
    bench_reverse_take(b, g_db)
}

[benchmark]
def reverse_take_select_sqlite(b : B?) {
    bench_reverse_take_select(b, g_db)
}

[benchmark]
def select_count_sqlite(b : B?) {
    bench_select_count(b, g_db)
}

[benchmark]
def select_where_sqlite(b : B?) {
    bench_select_where(b, g_db)
}

[benchmark]
def select_where_count_sqlite(b : B?) {
    bench_select_where_count(b, g_db)
}

[benchmark]
def select_where_order_take_sqlite(b : B?) {
    bench_select_where_order_take(b, g_db)
}

[benchmark]
def select_where_sum_sqlite(b : B?) {
    bench_select_where_sum(b, g_db)
}

[benchmark]
def single_match_sqlite(b : B?) {
    bench_single_match(b, g_db)
}

[benchmark]
def skip_take_sqlite(b : B?) {
    bench_skip_take(b, g_db)
}

[benchmark]
def skip_while_match_sqlite(b : B?) {
    bench_skip_while_match(b, g_db)
}

[benchmark]
def sort_first_sqlite(b : B?) {
    bench_sort_first(b, g_db)
}

[benchmark]
def sort_take_sqlite(b : B?) {
    bench_sort_take(b, g_db)
}

[benchmark]
def sort_take_select_sqlite(b : B?) {
    bench_sort_take_select(b, g_db)
}

[benchmark]
def sum_aggregate_sqlite(b : B?) {
    bench_sum_aggregate(b, g_db)
}

[benchmark]
def sum_where_sqlite(b : B?) {
    bench_sum_where(b, g_db)
}

[benchmark]
def take_count_sqlite(b : B?) {
    bench_take_count(b, g_db)
}

[benchmark]
def take_count_filtered_sqlite(b : B?) {
    bench_take_count_filtered(b, g_db)
}

[benchmark]
def take_sum_aggregate_sqlite(b : B?) {
    bench_take_sum_aggregate(b, g_db)
}

[benchmark]
def take_where_count_sqlite(b : B?) {
    bench_take_where_count(b, g_db)
}

[benchmark]
def take_while_match_sqlite(b : B?) {
    bench_take_while_match(b, g_db)
}

[benchmark]
def to_array_filter_sqlite(b : B?) {
    bench_to_array_filter(b, g_db)
}

[benchmark]
def where_join_count_sqlite(b : B?) {
    bench_where_join_count(b, g_db)
}

[benchmark]
def zip_count_pred_sqlite(b : B?) {
    bench_zip_count_pred(b, g_db)
}

[benchmark]
def zip_dot_product_sqlite(b : B?) {
    bench_zip_dot_product(b, g_db)
}

[benchmark]
def zip_dot_product_3arg_sqlite(b : B?) {
    bench_zip_dot_product_3arg(b, g_db)
}

[benchmark]
def cross_join_sqlite(b : B?) {
    bench_cross_join(b, g_db)
}

