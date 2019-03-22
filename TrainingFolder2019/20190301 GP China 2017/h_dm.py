import random, itertools, os

permutations = itertools.permutations([1,2,3,4])
permutations = list(permutations)
random.shuffle(permutations)

for perm in permutations:
	with open("h_perm.txt","w") as f:
		f.write(" ".join(map(str, perm)))
	if os.system("./h_run.sh"):
		print(perm, "wa")
		break
	print(perm, "ok")
