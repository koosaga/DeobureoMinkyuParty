
y=[40,112,440,728]
x=[5,7,11,13]

x=[i//2 for i in x]

xxxxx = range(-10,10)

for i in [0]:
	for j in xxxxx:
		for k in xxxxx:
			for l in xxxxx:
				for m in xxxxx:
					good = True
					for x0, y0 in zip(x,y):
						if y0 != (x0 ** 4) * i + (x0 ** 3) * j + (x0 ** 2) * k + (x0 ** 1) * l + m:
							good = False
					if good:
						print(i,j,k,l,m)
