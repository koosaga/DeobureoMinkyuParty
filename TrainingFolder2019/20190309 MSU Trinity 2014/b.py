from decimal import Decimal, getcontext

getcontext().prec = 50

from math import sin,cos,tan,pi

K = int(input())

alcohol = pi / 2 / K
ang = [(alcohol * i) for i in range(K+K)]
_sin = [sin(ang[i]) for i in range(K+K)]
_cos = [cos(ang[i]) for i in range(K+K)]
_cot = [1/tan(ang[i]) if i > 0 else -1 for i in range(K+K)]

pos = [[] for i in range(K+K)]

for alpha in range(1,K+K):
	for beta in range(1,K+K-alpha):
		for gamma in range(alpha+1, K+K-beta):
			x =  _sin[alpha] * _sin[beta] / _sin[alpha + beta] * (_cot[alpha] - _cot[gamma])
			pos[gamma].append(x)

for gamma in range(K+K):
	pos[gamma].sort()

eps = 1e-12

import bisect

ans = 0
for i in range(1,K+K):
	j = K+K-i
	for x in pos[i]:
		#for y in pos[j]:
		#	if abs(x + y - 1) < eps:
		#		ans += 1
		#continue
		l = bisect.bisect_left(pos[j], 1-x-eps)
		r = bisect.bisect_right(pos[j], 1-x+eps)
		for y in pos[j][l:r]:
			if abs(x + y - 1) < eps:
				ans += 1

print(ans)