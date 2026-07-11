options gen2
require test_env_serializer_module

[export]
def test {
    assert(add_numbers(2, 3) == 5)
}
