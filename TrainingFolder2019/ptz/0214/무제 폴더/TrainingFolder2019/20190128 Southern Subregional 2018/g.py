n = int(input())

cur = []
def good(s, e):
	if s < 1:
		return False
	assert s <= e
	for l, r in cur:
		if max(l, s) <= min(r, e):
			return False
	return True

for i in range(n):
	s, d = map(int, input().split())
	e = s+d-1
	if not good(s, e):
		s = int(2e9)
		if good(1, d):
			s = 1
		for l, r in cur:
			if good(l-d, l-1):
				s = min(s, l-d)
			if good(r+1, r+d):
				s = min(s, r+1)
	cur.append((s, s+d-1))
	cur.sort()
	print(s, s+d-1)