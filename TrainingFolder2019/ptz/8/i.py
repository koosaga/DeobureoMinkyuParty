for _ in range(int(input())):
	n, m = map(int, input().split())
	print(pow(m, n**2 - (2*n - 1 + (1 if n % 2 == 1 else 0)), int(1e9) + 7))
