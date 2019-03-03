from decimal import Decimal, Overflow

INF = Decimal("1" + "0" * 500000000)

N = 5

ARR = [INF]
for i in range(1, N+2):
	ARR.append(ARR[-1].ln())

res = []

"""
res = []
for a, b in [(2, 4), (4, 3)]:
	try:
		cur = ARR[a+1] * ARR[b]
		res.append((cur, a, b))
	except:
		pass

res.sort()

for x in res:
	print(x)
	continue

exit(0)
res = []
"""

for a in range(1, N+1):
	for b in range(1, N+1):
		try:
			cur = ARR[a+1] * ARR[b]
			res.append((cur, a, b))
		except:
			pass

res.sort()

for x in res:
	print(x[1], x[2])
	print()
	print(2, 2)
	print(x[1], x[2])

exit(0)

res = []
for a in range(1, N+1):
	for b in range(1, N+1):
		for c in range(1, N+1):
			try:
				cur = ARR[a+1] * (ARR[b]**ARR[c])
				res.append((cur, a, b, c))
			except:
				pass

res.sort()

last = 0
for x in res:
	print(x)
	continue
	print(0 if x[0] - last < 1e-9 else -1)
	last = x[0]
	continue
	print(x[1], x[2], x[3])
	print()
	print(3, 3)
	print(x[1], x[2], x[3])
	continue
	print(x)