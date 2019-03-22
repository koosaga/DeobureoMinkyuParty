./b < b.in > b.out
./b_slow < b.in > b_slow.out
diff b.out b_slow.out
