from math import cos, sin, gcd,pi

from decimal import Decimal

for n in range(1, 100): #1, 100):
	cur = [complex(Decimal(1), Decimal(0))]
	for k in range(1, n+1):
		if gcd(n, k) == 1:
			nxt = [complex(Decimal(0), Decimal(0))] + cur
			mul = complex(Decimal(cos(2*pi/n*k)), Decimal(sin(2*pi/n*k)))
			for i in range(len(cur)):
				nxt[i] -= cur[i] * mul
			cur = nxt
	print("n = %d: " % n)
	for i, v in reversed(list(enumerate(cur))):
		if v.real > 0.9:
			v = 1
		elif v.real < -0.9:
			v = -1
		else:
			v = 0
		if v != 0:
			print("(%d x^%d) +" % (v, i), end="")
	print()