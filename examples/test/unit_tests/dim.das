options gen2
let {
    N = 2
    M = 3
}

var {
    a : float[N][M]
}

[export]
def test {
    for (y in range(2)) {
        for (x in range(3)) {
            var f = float(y * 10 + x)
            a[y][x] = f
        }
    }

    for (y in range(2)) {
        for (x in range(3)) {
            var f = float(y * 10 + x)
            assert(a[y][x] == f)
        }
    }

    unsafe {
        var pa = addr(a[0][0])
        for (y in range(2)) {
            for (x in range(3)) {
                var o = x + y * 3
                var f = float(y * 10 + x)
                assert(pa[o] == f)
            }
        }
    }

    // print("a = {a}\n")
    assert("{a}" == "[[ [[ 0; 1; 2]]; [[ 10; 11; 12]]]]")
    var a0 = a[0]
    assert("{a0}" == "[[ 0; 1; 2]]")
    var a1 = a[1]
    assert("{a1}" == "[[ 10; 11; 12]]")

    return true
}

