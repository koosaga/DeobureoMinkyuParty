import random

T = 10
print(T)
for _ in range(T):
	N = 10
	M = 6
	Q = 100
	print(N, M, Q)
	print("a"*N)
	print("ab"*(M//2))
	for i in range(Q):
		print(random.randint(1,N-M+1)+1, random.randint(1, int(1e18)))
