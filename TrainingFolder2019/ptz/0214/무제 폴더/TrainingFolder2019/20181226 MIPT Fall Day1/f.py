n = 10
m = 25

import numpy as np

a = np.matrix([[1 if abs(j-i) == 1 else 0 for j in range(n)] for i in range(n)])


for i in range(m):
	print(a ** i)
	print()



exit(0)
tb = [[0] * (n+2) for _ in range(m+1)]

tb[0][1] = 1
for i in range(1, m+1):
	for j in range(1, n+1):
		tb[i][j] = tb[i-1][j-1] + tb[i-1][j+1]
	print("".join(("%7d" % x for x  in tb[i][1:n+1])))