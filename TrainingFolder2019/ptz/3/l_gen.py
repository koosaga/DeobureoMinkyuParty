def f(x):
	return x * (x+1) // 2

def s(k, x):
	if k == 0:
		return x
	return s(k-1, f(x) + k)
"""
p = 17
for k in range(0,50):
	print("k = %d: " % k, end="")
	for x in range(1,20):
		v = s(k,x)
		print(v % p, end = " ")
	print()
"""

k = 5
ss = [s(k, x) for x in range(1,1000)]

for p in range(2,1000):
	a = set(x % p for x in ss)
	if 0 in a:
		print(p)
#	print(a, ",")
