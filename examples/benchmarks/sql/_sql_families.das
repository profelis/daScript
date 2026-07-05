options gen2
options persistent_heap

require _common public

// Shared query families for the three SQL engine lanes (sqlite / duckdb / postgres).
// Bodies are provider-agnostic: the untyped `db` parameter monomorphizes per runner
// type, and the `_fold` chains inside dispatch through the provider registry. One
// source of truth; each engine file wraps these in thin [benchmark] functions named
// <family>_<engine> so the results collector pivots (family x engine).
// Bodies mirror benchmarks/sql/sql.das (the m1 lane) so numbers line up; N is fixed
// at 100000 (some probes hardcode mid-set ids).

def public bench_aggregate_match(b : B?; db) {
        b |> run("aggregate_match", N) {
            let total = _fold(db |> select_from(type<Car>) |> _where(_.price > 200)
                                |> _select(_.price) |> sum())
            b |> accept(total)
            if (total == 0) {
                b->failNow()
            }
        }
}

def public bench_all_match(b : B?; db) {
        b |> run("all_match", N) {
            let bad = _fold(db |> select_from(type<Car>) |> _where(_.price >= 9999) |> count())
            b |> accept(bad)
            if (bad != 0) {
                b->failNow()
            }
        }
}

def public bench_any_match(b : B?; db) {
        b |> run("any_match", N) {
            let opt = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> _first_opt())
            b |> accept(opt)
            if (!is_some(opt)) {
                b->failNow()
            }
        }
}

def public bench_average_aggregate(b : B?; db) {
        b |> run("average_aggregate", N) {
            let a = _fold(db |> select_from(type<Car>) |> _select(_.price) |> average())
            b |> accept(a)
            if (a == 0.0lf) {
                b->failNow()
            }
        }
}

def public bench_bare_order_where(b : B?; db) {
        b |> run("bare_order_where", N) {
            let rows <- _fold(db |> select_from(type<Car>)
                                |> _where(_.price > 500)
                                |> _order_by(_.price))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_chained_where(b : B?; db) {
        b |> run("chained_where", N) {
            let c = _fold(db |> select_from(type<Car>)
                            |> _where(_.price > 500)
                            |> _where(_.year >= 2015)
                            |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_contains_match(b : B?; db) {
        b |> run("contains_match", N) {
            // SQL doesn't have a direct CONTAINS for arbitrary values; use _any with _where.
            let opt = _fold(db |> select_from(type<Car>) |> _where(_.id == 50000) |> _first_opt())
            b |> accept(opt)
            if (!is_some(opt)) {
                b->failNow()
            }
        }
}

def public bench_count_aggregate(b : B?; db) {
        b |> run("count_aggregate", N) {
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_distinct_by_count(b : B?; db) {
        b |> run("distinct_by_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> _distinct_by(_.brand) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_distinct_by_order_take(b : B?; db) {
        b |> run("distinct_by_order_take", N) {
            let rows <- _fold(db |> select_from(type<Car>)
                                |> _distinct_by(_.dealer_id)
                                |> _order_by(_.price)
                                |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_distinct_by_order_to_array(b : B?; db) {
        b |> run("distinct_by_order_to_array", N) {
            let rows <- _fold(db |> select_from(type<Car>)
                                |> _distinct_by(_.dealer_id)
                                |> _order_by(_.price))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_distinct_count(b : B?; db) {
        b |> run("distinct_count", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _select(_.brand) |> distinct())
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_distinct_count_pred(b : B?; db) {
        b |> run("distinct_count_pred", N) {
            let c = _fold(db |> select_from(type<Car>) |> _distinct_by(_.brand) |> _count(_.year > 2009))
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_distinct_take(b : B?; db) {
        b |> run("distinct_take", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _select(_.brand) |> distinct() |> take(3))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_element_at_match(b : B?; db) {
        b |> run("element_at_match", N) {
            let row = _fold(db |> select_from(type<Car>) |> _where(_.price > 500)
                              |> skip(100) |> _first())
            b |> accept(row)
            if (row.price == 0) {
                b->failNow()
            }
        }
}

def public bench_first_match(b : B?; db) {
        b |> run("first_match", N) {
            let row = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> _first())
            b |> accept(row)
            if (row.price == 0) {
                b->failNow()
            }
        }
}

def public bench_first_or_default_match(b : B?; db) {
        b |> run("first_or_default_match", N) {
            let row = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> _first())
            b |> accept(row)
            if (row.price == 0) {
                b->failNow()
            }
        }
}

def public bench_groupby_average(b : B?; db) {
        b |> run("groupby_average", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              AvgPrice = _._1 |> select($(c : Car) => c.price) |> average())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_count(b : B?; db) {
        b |> run("groupby_count", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0, N = _._1 |> length)))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_first(b : B?; db) {
        b |> run("groupby_first", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              FirstCar = _._1 |> first())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_having_count(b : B?; db) {
        b |> run("groupby_having_count", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _having(_._1 |> length >= 5)
                                  |> _select((Brand = _._0, N = _._1 |> length)))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_having_hidden_sum(b : B?; db) {
        b |> run("groupby_having_hidden_sum", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _having(_._1 |> select($(c : Car) => c.price) |> sum > 50000)
                                  |> _select((Brand = _._0, N = _._1 |> length)))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_having_post_where(b : B?; db) {
        b |> run("groupby_having_post_where", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              Total = _._1 |> select($(c : Car) => c.price) |> sum()))
                                  |> _where(_.Total > 9000000))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_max(b : B?; db) {
        b |> run("groupby_max", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              MaxPrice = _._1 |> select($(c : Car) => c.price) |> max())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_min(b : B?; db) {
        b |> run("groupby_min", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              MinPrice = _._1 |> select($(c : Car) => c.price) |> min())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_multi_reducer(b : B?; db) {
        b |> run("groupby_multi_reducer", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              N = _._1 |> length,
                                              TotalPrice = _._1 |> select($(c : Car) => c.price) |> sum(),
                                              MaxPrice   = _._1 |> select($(c : Car) => c.price) |> max())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_select_order(b : B?; db) {
        b |> run("groupby_select_order", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              Total = _._1 |> select($(c : Car) => c.price) |> sum()))
                                  |> _order_by(_.Total))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_select_sum(b : B?; db) {
        b |> run("groupby_select_sum", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.price % 100)
                                  |> _select((K = _._0, S = _._1 |> select($(c : Car) => c.price) |> sum())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_sum(b : B?; db) {
        b |> run("groupby_sum", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              TotalPrice = _._1 |> select($(c : Car) => c.price) |> sum())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_where_count(b : B?; db) {
        b |> run("groupby_where_count", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _where(_.price > 500)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0, N = _._1 |> length)))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_groupby_where_sum(b : B?; db) {
        b |> run("groupby_where_sum", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                                  |> _where(_.price > 500)
                                  |> _group_by(_.brand)
                                  |> _select((Brand = _._0,
                                              TotalPrice = _._1 |> select($(c : Car) => c.price) |> sum())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_join_count(b : B?; db) {
        b |> run("join_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> _join(db |> select_from(type<Dealer>),
                                                               $(c : Car, d : Dealer) => c.dealer_id == d.id,
                                                               $(c : Car, d : Dealer) => (CarName = c.name, DealerName = d.name))
                                                      |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_join_groupby_count(b : B?; db) {
        b |> run("join_groupby_count", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                |> _join(db |> select_from(type<Dealer>),
                         $(c : Car, d : Dealer) => c.dealer_id == d.id,
                         $(c : Car, d : Dealer) => (Brand = c.brand, DealerId = d.id))
                |> _group_by(_.Brand)
                |> _select((Brand = _._0, N = _._1 |> count())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_join_groupby_to_array(b : B?; db) {
        b |> run("join_groupby_to_array", N) {
            let groups <- _fold(db |> select_from(type<Car>)
                |> _join(db |> select_from(type<Dealer>),
                         $(c : Car, d : Dealer) => c.dealer_id == d.id,
                         $(c : Car, d : Dealer) => (Brand = c.brand, Price = c.price))
                |> _group_by(_.Brand)
                |> _select((Brand = _._0,
                            Total = _._1 |> _select(_.Price) |> sum())))
            b |> accept(groups)
            if (empty(groups)) {
                b->failNow()
            }
        }
}

def public bench_join_select(b : B?; db) {
        b |> run("join_select", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _join(db |> select_from(type<Dealer>),
                                                                   $(c : Car, d : Dealer) => c.dealer_id == d.id,
                                                                   $(c : Car, d : Dealer) => (CarName = c.name)))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_join_where_count(b : B?; db) {
        b |> run("join_where_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> _join(db |> select_from(type<Dealer>),
                                                                $(c : Car, d : Dealer) => c.dealer_id == d.id,
                                                                $(c : Car, d : Dealer) => (CarPrice = c.price, DealerId = d.id))
                                                      |> _where(_.CarPrice > 500)
                                                      |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_last_match(b : B?; db) {
        b |> run("last_match", N) {
            let row = _fold(db |> select_from(type<Car>) |> _where(_.price > 500)
                              |> _order_by_descending(_.id) |> _first())
            b |> accept(row)
            if (row.price == 0) {
                b->failNow()
            }
        }
}

def public bench_long_count_aggregate(b : B?; db) {
        b |> run("long_count_aggregate", N) {
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> long_count())
            b |> accept(c)
            if (c == 0l) {
                b->failNow()
            }
        }
}

def public bench_max_aggregate(b : B?; db) {
        b |> run("max_aggregate", N) {
            let m = _fold(db |> select_from(type<Car>) |> _select(_.price) |> max())
            b |> accept(m)
            if (m == 0) {
                b->failNow()
            }
        }
}

def public bench_min_aggregate(b : B?; db) {
        b |> run("min_aggregate", N) {
            let m = _fold(db |> select_from(type<Car>) |> _select(_.price) |> min())
            b |> accept(m)
            if (m > 999) {
                b->failNow()
            }
        }
}

def public bench_order_by_multi_key(b : B?; db) {
        b |> run("order_by_multi_key", N) {
            let rows <- _fold(db |> select_from(type<Car>)
                                |> _where(_.price > 500)
                                |> _order_by_keys((_.brand, _.price), 0u))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_order_distinct_take(b : B?; db) {
        b |> run("order_distinct_take", N) {
            let rows <- _fold(db |> select_from(type<Brand>) |> _select((value = _.value)) |> distinct() |> _order_by(_.value) |> take(5))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_order_reverse_normalized(b : B?; db) {
        b |> run("order_reverse_normalized", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by_descending(_.price) |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_order_take_desc(b : B?; db) {
        b |> run("order_take_desc", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by_descending(_.price) |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_reverse_distinct_by(b : B?; db) {
        b |> run("reverse_distinct_by", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> reverse() |> _distinct_by(_.brand))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_reverse_take(b : B?; db) {
        b |> run("reverse_take", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by_descending(_.id) |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_reverse_take_select(b : B?; db) {
        b |> run("reverse_take_select", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by_descending(_.id) |> take(10) |> _select(_.name))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_select_count(b : B?; db) {
        b |> run("select_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_select_where(b : B?; db) {
        b |> run("select_where", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _where(_.price > 500))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_select_where_count(b : B?; db) {
        b |> run("select_where_count", N) {
            // SQL form folds projection into the WHERE filter — the engine evaluates
            // ``price * 2 > T`` per row and counts matches.
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price * 2 > 1000) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_select_where_order_take(b : B?; db) {
        b |> run("select_where_order_take", N) {
            let rows <- _fold(db |> select_from(type<Car>)
                                |> _where(_.price > 500)
                                |> _order_by(_.price)
                                |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_select_where_sum(b : B?; db) {
        // the m1 original spells this as raw SQL via query_scalar (sqlite-only
        // surface); the chain form is the engine-neutral equivalent
        b |> run("select_where_sum", N) {
            let s = _fold(db |> select_from(type<Car>) |> _where(_.price * 2 > 1000)
                            |> _select(_.price * 2) |> sum())
            b |> accept(s)
            if (s == 0) {
                b->failNow()
            }
        }
}

def public bench_single_match(b : B?; db) {
        b |> run("single_match", N) {
            let row = _fold(db |> select_from(type<Car>) |> _where(_.id == 42) |> _first())
            b |> accept(row)
            if (row.id == 0) {
                b->failNow()
            }
        }
}

def public bench_skip_take(b : B?; db) {
        b |> run("skip_take", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> skip(1000) |> take(100))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_skip_while_match(b : B?; db) {
        b |> run("skip_while_match", N) {
            let total = _fold(db |> select_from(type<Car>) |> _where(_.id >= 50000) |> count())
            b |> accept(total)
            if (total == 0) {
                b->failNow()
            }
        }
}

def public bench_sort_first(b : B?; db) {
        b |> run("sort_first", N) {
            let row = _fold(db |> select_from(type<Car>) |> _order_by(_.price) |> _first())
            b |> accept(row)
            if (row.id == 0) {
                b->failNow()
            }
        }
}

def public bench_sort_take(b : B?; db) {
        b |> run("sort_take", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by(_.price) |> take(10))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_sort_take_select(b : B?; db) {
        b |> run("sort_take_select", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> _order_by(_.price) |> take(10) |> _select(_.name))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_sum_aggregate(b : B?; db) {
        b |> run("sum_aggregate", N) {
            let s = _fold(db |> select_from(type<Car>) |> _select(_.price) |> sum())
            b |> accept(s)
            if (s == 0) {
                b->failNow()
            }
        }
}

def public bench_sum_where(b : B?; db) {
        b |> run("sum_where", N) {
            let s = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> _select(_.price) |> sum())
            b |> accept(s)
            if (s == 0) {
                b->failNow()
            }
        }
}

def public bench_take_count(b : B?; db) {
        b |> run("take_count", N) {
            let rows <- _fold(db |> select_from(type<Car>) |> take(1000))
            b |> accept(rows)
            if (empty(rows)) {
                b->failNow()
            }
        }
}

def public bench_take_count_filtered(b : B?; db) {
        b |> run("take_count_filtered", N) {
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> take(1000) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_take_sum_aggregate(b : B?; db) {
        b |> run("take_sum_aggregate", N) {
            let s = _fold(db |> select_from(type<Car>) |> _select(_.price) |> take(1000) |> sum())
            b |> accept(s)
            if (s == 0) {
                b->failNow()
            }
        }
}

def public bench_take_where_count(b : B?; db) {
        b |> run("take_where_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> take(1000) |> _where(_.price > 500) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_take_while_match(b : B?; db) {
        b |> run("take_while_match", N) {
            let total = _fold(db |> select_from(type<Car>) |> _where(_.id < 50000) |> count())
            b |> accept(total)
            if (total == 0) {
                b->failNow()
            }
        }
}

def public bench_to_array_filter(b : B?; db) {
        b |> run("to_array_filter", N) {
            let prices <- _fold(db |> select_from(type<Car>) |> _where(_.price > 500) |> _select(_.price))
            b |> accept(prices)
            if (empty(prices)) {
                b->failNow()
            }
        }
}

def public bench_where_join_count(b : B?; db) {
        b |> run("where_join_count", N) {
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price > 500)
                                                       |> _join(db |> select_from(type<Dealer>),
                                                                $(c : Car, d : Dealer) => c.dealer_id == d.id,
                                                                $(c : Car, d : Dealer) => (CarPrice = c.price, DealerId = d.id))
                                                       |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_zip_count_pred(b : B?; db) {
        b |> run("zip_count_pred", N) {
            let c = _fold(db |> select_from(type<Car>) |> _where(_.price * _.year > 1000000) |> count())
            b |> accept(c)
            if (c == 0) {
                b->failNow()
            }
        }
}

def public bench_zip_dot_product(b : B?; db) {
        b |> run("zip_dot_product", N) {
            let s = _fold(db |> select_from(type<Car>) |> _select(int64(_.price) * int64(_.year)) |> sum())
            b |> accept(s)
            if (s == 0l) {
                b->failNow()
            }
        }
}

def public bench_zip_dot_product_3arg(b : B?; db) {
        b |> run("zip_dot_product_3arg", N) {
            let s = _fold(db |> select_from(type<Car>) |> _select(int64(_.price) * int64(_.year)) |> sum())
            b |> accept(s)
            if (s == 0l) {
                b->failNow()
            }
        }
}

def public bench_cross_join(b : B?; db) {
    // 1000-car slice of the shared fixture (the original m1 lane builds a separate
    // 1000-row DB) — a full 100k x 100 cross product would materialize 10M rows
    b |> run("cross_join", 1000) {
        let rows <- _fold(db |> select_from(type<Car>)
                            |> _where(_.id <= 1000)
                            |> _cross_join(db |> select_from(type<Dealer>),
                                           $(ca : Car, de : Dealer) => (CarId = ca.id, DealerId = de.id)))
        let c = length(rows)
        b |> accept(c)
        if (c != 1000 * DEALER_COUNT) {
            b->failNow()
        }
    }
}
