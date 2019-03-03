from decimal import getcontext
getcontext().prec = 1000

from decimal import Decimal

a = [0, Decimal(1)]
b = [0, Decimal(1)]
d = [0, Decimal(0)]

for n in range(2,10):
	a.append(a[-1] * pow(2, pow(2, n-1)) - a[-1] * a[-1])
	b.append(4 * b[-1] * b[-1])
	d.append((b[-1] - a[-1]).sqrt())
print(a)
print(b)
print(d)