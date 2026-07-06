// Fixture for test_inline_errors.das — intentionally fails to compile: a second
// return violates the [inline] single-exit shape. `_`-prefix keeps dastest from
// auto-running it; the `expect` directive makes lint skip it.
expect 50501

options gen2

[inline]
def bad(x : int) : int {
    if (x > 0) {
        return 1;
    }
    return 2;
}

[export]
def main() {
    let y = bad(1);
    feint("{y}\n");
}
