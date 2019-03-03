

n = int(input())
a = list(map(int, input().split()))

print(2 * n - 1)
for i in range(2 * n - 1):
	print(" ".join(map(str, [a[(i + j) % n] for j in range(2 * n - 1)])))
