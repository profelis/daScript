options gen2
options persistent_heap

require daslib/sql public
require daslib/linq_boost public
require daslib/sql_linq public
require dastest/testing_boost public
require daslib/fio public
require strings public
// all three engines' runtime surfaces, re-exported: the [sql_table] structs below
// generate per-table helpers INTO this module, and their interior calls
// (read_via_adapter, sql_bind_to_stmt) must see every runner's overload set
require sqlite/sqlite_boost public
require duckdb/duckdb_boost public
require postgres/postgres_boost public

// Shared schema + fixtures for the four-engine benchmark example (see README.md).
// Same Car/Dealer/Brand shape and deterministic row generator as benchmarks/sql,
// so numbers line up with the in-tree lane tables.

let public N = 100000
let public BRAND_COUNT = 5
let public DEALER_COUNT = 100

[sql_table(name = "Cars")]
struct public Car {
    @sql_primary_key id : int
    name : string
    price : int
    brand : int
    year : int
    dealer_id : int
}

[sql_table(name = "Dealers")]
struct public Dealer {
    @sql_primary_key id : int
    name : string
}

[sql_table(name = "Brands")]
struct public Brand {
    @sql_primary_key id : int
    value : int
}

// Multi-row VALUES seeding, 1000 rows per statement inside one transaction —
// per-row insert() would be 100k network round trips on the postgres lane.
// Values are trusted generator output (ints + "Car{i}"), inlined as literals.
let private SEED_CHUNK = 1000

def public fixture_db(db; n : int) {
    db |> _::create_table(type<Car>)
    db |> _::create_table(type<Dealer>)
    db |> _::with_transaction() {
        var i = 0
        while (i < n) {
            let hi = i + SEED_CHUNK > n ? n : i + SEED_CHUNK
            let sql = build_string() $(var w) {
                w |> write("INSERT INTO \"Cars\" (\"id\", \"name\", \"price\", \"brand\", \"year\", \"dealer_id\") VALUES ")
                for (j in range(i, hi)) {
                    if (j > i) {
                        w |> write(", ")
                    }
                    w |> write("({j + 1}, 'Car{j}', {(j * 37) % 1000}, {j % BRAND_COUNT}, {2010 + (j * 7) % 16}, {(j % DEALER_COUNT) + 1})")
                }
            }
            db |> _::exec(sql)
            i = hi
        }
        let dealer_sql = build_string() $(var w) {
            w |> write("INSERT INTO \"Dealers\" (\"id\", \"name\") VALUES ")
            for (j in range(DEALER_COUNT)) {
                if (j > 0) {
                    w |> write(", ")
                }
                w |> write("({j + 1}, 'Dealer{j}')")
            }
        }
        db |> _::exec(dealer_sql)
    }
}

def public fixture_db_brands(db; n : int) {
    db |> _::create_table(type<Brand>)
    db |> _::with_transaction() {
        var i = 0
        while (i < n) {
            let hi = i + SEED_CHUNK > n ? n : i + SEED_CHUNK
            let sql = build_string() $(var w) {
                w |> write("INSERT INTO \"Brands\" (\"id\", \"value\") VALUES ")
                for (j in range(i, hi)) {
                    if (j > i) {
                        w |> write(", ")
                    }
                    w |> write("({j + 1}, {j % BRAND_COUNT})")
                }
            }
            db |> _::exec(sql)
            i = hi
        }
    }
}

def public fixture_array(n : int) : array<Car> {
    var arr : array<Car>
    arr |> resize(n)
    for (i in range(n)) {
        arr[i] = Car(
            id = i + 1,
            name = "Car{i}",
            price = (i * 37) % 1000,
            brand = i % BRAND_COUNT,
            year = 2010 + (i * 7) % 16,
            dealer_id = (i % DEALER_COUNT) + 1
        )
    }
    return <- arr
}

def public fixture_dealers_array() : array<Dealer> {
    var arr : array<Dealer>
    arr |> resize(DEALER_COUNT)
    for (i in range(DEALER_COUNT)) {
        arr[i] = Dealer(id = i + 1, name = "Dealer{i}")
    }
    return <- arr
}

def public make_ints(n : int) : array<int> {
    var a : array<int>
    a |> resize(n)
    for (i in range(n)) {
        a[i] = i
    }
    return <- a
}

def public make_brands(n : int) : array<int> {
    var a : array<int>
    a |> resize(n)
    for (i in range(n)) {
        a[i] = i % BRAND_COUNT
    }
    return <- a
}
