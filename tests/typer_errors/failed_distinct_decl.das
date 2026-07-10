options gen2

expect 30297 : 2

distinct Id = int
distinct Id2 = Id           // 30297: distinct of distinct
distinct Bad = array<int>   // 30297: non-workhorse underlying
