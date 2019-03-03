import random, os


n = 100
edges = []
for i in range(n):
	for j in range(i):
		edges.append((i, j))

with open("i_dm.in", "w") as f: