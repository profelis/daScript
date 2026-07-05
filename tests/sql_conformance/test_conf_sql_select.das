options gen2
options indenting = 4
options no_unused_block_arguments = false
options no_unused_function_arguments = false

// Contract area: the `_sql` read chain — _where translation with captured-var binds,
// _order_by, take/skip, distinct, _first/_first_opt terminals, and the _sql_text
// analyzer surface (placeholder style is provider-rendered, so only shape is asserted).

require dastest/testing_boost public
require _conformance_provider
require strings

[sql_table(name = "ConfNums")]
struct ConfNum {
    @sql_primary_key Id : int
    Val : int
    Tag : string
}

def private seed(db) {
    db |> create_table(type<ConfNum>)
    db |> insert([
        ConfNum(Id = 0, Val = 10, Tag = "a"),
        ConfNum(Id = 0, Val = 20, Tag = "b"),
        ConfNum(Id = 0, Val = 30, Tag = "a"),
        ConfNum(Id = 0, Val = 40, Tag = "c"),
        ConfNum(Id = 0, Val = 40, Tag = "a")])
}

[test]
def test_conf_where_binds(t : T?) {
    t |> run("captured-var predicate binds and filters") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let cutoff = 25
            let rows <- _sql(db |> select_from(type<ConfNum>) |> _where(_.Val > cutoff))
            t |> equal(length(rows), 3)
            let both <- _sql(db |> select_from(type<ConfNum>)
                |> _where(_.Val > cutoff && _.Tag == "a"))
            t |> equal(length(both), 2)
        }
    }
    t |> run("two _where calls compose with AND") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let rows <- _sql(db |> select_from(type<ConfNum>)
                |> _where(_.Val >= 20)
                |> _where(_.Tag == "a"))
            t |> equal(length(rows), 2)
        }
    }
    t |> run("string predicates: starts_with / contains") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let rows <- _sql(db |> select_from(type<ConfNum>) |> _where(_.Tag |> starts_with("a")))
            t |> equal(length(rows), 3)
        }
    }
}

[test]
def test_conf_order_page_distinct(t : T?) {
    t |> run("_order_by + skip/take paginate deterministically") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let page <- _sql(db |> select_from(type<ConfNum>)
                |> _order_by(_.Val)
                |> skip(1) |> take(2))
            t |> equal(length(page), 2)
            t |> equal(page[0].Val, 20)
            t |> equal(page[1].Val, 30)
        }
    }
    t |> run("_order_by_descending") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let top <- _sql(db |> select_from(type<ConfNum>)
                |> _order_by_descending(_.Val)
                |> take(1))
            t |> equal(top[0].Val, 40)
        }
    }
    t |> run("distinct over a single-column projection") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let tags <- _sql(db |> select_from(type<ConfNum>) |> _select(_.Tag) |> distinct())
            t |> equal(length(tags), 3)
        }
    }
}

[test]
def test_conf_terminals(t : T?) {
    t |> run("_first / _first_opt") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let first_a = _sql(db |> select_from(type<ConfNum>)
                |> _where(_.Tag == "a") |> _order_by(_.Val) |> _first())
            t |> equal(first_a.Val, 10)
            let missing = _sql(db |> select_from(type<ConfNum>)
                |> _where(_.Val > 1000) |> _first_opt())
            t |> success(missing |> is_none, "_first_opt on an empty result is none")
        }
    }
}

[test]
def test_conf_sql_text_shape(t : T?) {
    t |> run("_sql_text emits SELECT/WHERE with quoted identifiers") @(t : T?) {
        with_conf_db() $(db) {
            seed(db)
            let cutoff = 5
            let sql = _sql_text(db |> select_from(type<ConfNum>) |> _where(_.Val > cutoff))
            t |> success(sql |> starts_with("SELECT "), "starts with SELECT")
            t |> success(find(sql, "FROM \"ConfNums\"") >= 0, "table name is quoted")
            t |> success(find(sql, "WHERE") >= 0, "predicate renders a WHERE clause")
            t |> success(find(sql, "{cutoff}") < 0, "captured var is bound, not inlined")
        }
    }
}
