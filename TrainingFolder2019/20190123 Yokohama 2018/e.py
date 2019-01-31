import random,os

rep = 0
while True:
	n = random.randint(10, 100)
	m = random.randint(0, 10)
	e = []
	for i in range(n):
		for j in range(i):
			e.append((i+1, j+1))
	edges = random.sample(e, m)
	with open("e.tmp.in", "w") as f:
		f.write("%d %d\n" % (n, m))
		for u, v in edges:
			f.write("%d %d\n" % (u, v))
	rep += 1
	if rep % 20 == 0:
		print(rep)
	if os.system("./e < e.tmp.in > e.tmp.out"):
		print("tt")
		break