_integrate = dict()

def integrate(p, q):
	if (p, q) in _integrate:
		return _integrate[(p, q)]
	ret = [hang(p+1, q, 1/(p+1))]
	if q > 0:
		ret.extend([h * (-q / (p+1)) for h in integrate(p, q-1)])
	_integrate[(p, q)] = ret
	return ret

class hang:
	# x^p (ln x)^q
	def __init__(self, p, q, c = 1):
		self.p = p
		self.q = q
		self.c = c
	def __mul__(self, other):
		ret = hang(self.p, self.q, self.c)
		if type(c) is int or type(c) is float:
			ret.c *= other
		else:
			raise Exception("not implemented")
		return ret
	def integrate(self):
		if (self.p, self.q) not in _integrate:
			if q == 0:
				_integrate[(self.p, self.q)] = [hang(self.p + 1, self.q, self.c / (self.p + 1))]
			else:
				_integrate[(self.p, self.q)]
		return _integrate[(self.p, self.q)]

print(integrate(2, 1))