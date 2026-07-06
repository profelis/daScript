// Fixture for test_inline_errors.das — intentionally fails to compile: [inline]
// on an operator overload. `_`-prefix keeps dastest from auto-running it; the
// `expect` directive makes lint skip it.
expect 50501

options gen2

struct SVec {
    x : int;
    y : int;
}

[inline]
def operator +(l, r : SVec) : int {
    return l.x + r.x;
}

[export]
def main() {
    let a = SVec(x = 1, y = 2);
    let b = SVec(x = 3, y = 4);
    let c = a + b;
    feint("{c}\n");
}
