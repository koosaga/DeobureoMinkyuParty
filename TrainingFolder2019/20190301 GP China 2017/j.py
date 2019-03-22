n, k = map(int, input().split())

if k == 1:
	print(-1)
	exit(0)
	
gph = [[False]*n for i in range(n)]

for diff in range(1, k//2 + 1):
	for i in range(n):
		j = (i+diff) % n
		gph[i][j] = True
		gph[j][i] = True
	k -= 2

if k == 1:
	if n % 2 == 0:
		diff = n // 2
		for i in range(n):
			j = (i + diff) % n
			gph[i][j] = True
			gph[j][i] = True
	else:
		diff = n // 2
		for i in range(n//2+1):
			j = (i + diff) % n
			gph[i][j] = True
			gph[j][i] = True

deg = [row.count(True) for row in gph]
assert sum(deg) % 2 == 0

print(sum(deg) // 2)
for i in range(n):
	for j in range(i+1, n):
		if gph[i][j]:
			print(i+1, j+1)
print(*range(1,n+1))
