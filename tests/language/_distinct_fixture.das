options gen2

module _distinct_fixture shared public

distinct PubId = int
distinct private Secret = int

def make_pub_id(v : int) : PubId => PubId(v)

def pub_id_value(v : PubId) : int => *v
