import random

with open("i.in", "w") as f:
	n = int(10**8 + 123)
	s = random.randint(0, n-1)
	k = random.randint(1, n-1)
	m = int(1e6)
	f.write("%d %d\n" % (n, m))
	f.write(" ".join(map(str, sorted([(s + k * i) % n for i in range(m)]))))
	#g.write("%d %d\n" % (s, k))
