n = int(input())
a = list(map(int,input().split()))
good = [False]*(n+1)
for i in range(0,2*n,2):
	if a[i] < a[i+1]:
		good[n - i//2] = True

c = [0]*(n+1)
g = [0]*(n+1)

c[n] = 1
if good[n]:
	g[n] = 2
	add = 0
elif n == 1:
	g[n] = 3
	add = 1
else:
	g[n] = 4
	add = 1
	
	
for i in range(n-1, 0, -1):
	c[i] = 2 * c[i+1] + add
	g[i] = 2 * c[i]
	if (c[i] % 2 == 1) ^ good[i]:
		if i == 1:
			g[i] += 1
		else:
			g[i] += 2
		add = 1
	else:
		add = 0

print(sum(g))
