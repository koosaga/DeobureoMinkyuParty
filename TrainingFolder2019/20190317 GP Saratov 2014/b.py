n = int(input())
a = list(map(int,input().split()))

ans = 2 * (2**n - 1)

a[0], a[1] = a[1], a[0]
for i in range(0, 2*n, 2):
	if a[i] < a[i+1]:
		if i+2 < 2*n:
			ans += 2 ** (n - i // 2) 
			a[i+2], a[i+3] = a[i+3], a[i+2]
		else:
			ans += 1

print(ans)
