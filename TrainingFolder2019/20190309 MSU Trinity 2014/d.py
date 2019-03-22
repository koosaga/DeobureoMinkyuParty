n, k = map(int, input().split())

if k == 1:
	ans = n * (n + 1) // 2
else:
	ans = 0
	for i in range(1,min(n+1,1001)):
		ans += (1/k) ** (i//2) * (n - i + 1)

print("%.10f" % ans)