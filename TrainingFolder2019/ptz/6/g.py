from math import sin ,cos, tan, pi

def f(x):
	return x * cos(x) - sin(x)

low, high = 0, pi/4
for _ in range(50):
	mid = (low + high) / 2
	if f(mid) > 0:
		low = mid
	else:
		high = mid

print(0, f(0))
print()
print(low, f(low))