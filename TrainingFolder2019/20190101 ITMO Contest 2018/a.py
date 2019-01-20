import copy
from math import log

"""_integrate = dict()

def integrate(p, q):
	if (p, q) in _integrate:
		return _integrate[(p, q)]
	ret = [hang(p+1, q, 1/(p+1))]
	if q > 0:
		ret.extend([h * (-q / (p+1)) for h in integrate(p, q-1)])
	_integrate[(p, q)] = shik(ret)
	return ret
"""

class hang:
	def __init__(self, lin, log, c = 1):
		self.lin = lin
		self.log = log
		self.c = c
	def __repr__(self):
		return str(self.c) + " * " + "".join("%s^%d" % (var, n) for var, n in self.lin.items()) + " * " + \
				"".join("(ln %s)^%d" % (var, n) for var, n in self.log.items()) 
	def __mul__(self, other):
		ret = hang(self.lin, self.log, self.c)
		if type(other) is int or type(other) is float:
			ret.c *= other
		else:
			for var, n in other.lin.items():
				ret.lin[var] = ret.lin.get(var, 0) + n
			for var, n in other.log.items():
				ret.log[var] = ret.log.get(var, 0) + n
			ret.c *= other.c
		return ret
	def integrate(self, var):
		p = self.lin.get(var, 0)
		q = self.log.get(var, 0)
		ret = shik()
		ret.append(hang(copy.deepcopy(self.lin), copy.deepcopy(self.log), self.c / (p+1)))
		ret[-1].lin[var] = p + 1
		if q > 0:
			self.log[var] = q-1
			sh = self.integrate(var)
			ret.extend([h * (-q / (p+1)) for h in sh])
			self.log[var] = q+1
		return ret
	def substitute(self, var, val):
		ret = copy.deepcopy(self)
		if type(val) is float or type(val) is int:
			if var in ret.lin:
				ret.c *= val ** ret.lin[var]
				ret.lin.pop(var)
			if var in self.log:
				ret.c *= log(val) ** ret.log[var]
				ret.log.pop(var)
		else:
			if var in ret.lin:
				ret.lin[val] = ret.lin.get(val, 0) + ret.lin[var]
				ret.lin.pop(var)
			if var in self.log:
				ret.log[val] = ret.log.get(val, 0) + ret.log[var]
				ret.log.pop(var)
		return ret
	def divide(self, var):
		ret = copy.deepcopy(self)
		p = self.lin.get(var, 0)
		if p < 1:
			raise Exception("yakbun impossible")
		ret.lin[var] = p-1
		return ret
	def get(self):
		if min([0] + list(self.lin.values())) > 0 or min([0] + list(self.log.values())) > 0:
			raise Exception("not divided properly")
		return self.c


class shik(list):
	def __mul__(self, other):
		if type(other) is int or type(other) is float:
			ret = [i * other for i in self]
		else:
			ret = shik()
			for i in self:
				for j in other:
					cur = hang({}, {}, i.c * j.c)
					for var, n in i.lin.items():
						cur.lin[var] = cur.lin.get(var, 0) + n
					for var, n in j.lin.items():
						cur.lin[var] = cur.lin.get(var, 0) + n
					for var, n in i.log.items():
						cur.log[var] = cur.log.get(var, 0) + n
					for var, n in j.log.items():
						cur.log[var] = cur.log.get(var, 0) + n
					ret.append(cur)
		return ret
	def divide(self, var):
		ret = shik([])
		for h in self:
			if h.lin.get(var, 0) < 1:
				raise Exception("yakbun impossible")
			h2 = copy.deepcopy(h)
			h2.lin[var] = h.lin.get(var, 0) - 1
			ret.append(h2)
		return ret
	def integrate(self, var):
		ret = shik([])
		for h in self: ret.extend(h.integrate(var))
		return ret
	def substitute(self, var, val):
		ret = shik([])
		for h in self: ret.append(h.substitute(var, val))
		return ret
	def get(self):
		return sum(h.get() for h in self)

def solve(n, l, r):
	meet = shik([hang({}, {}, r), hang({'t1': 1}, {}, -1), hang({'x1': 1}, {}, -log(r)), hang({'x1': 1}, {'t1': 1}, +1)])
	s1 = meet
	print(s1)
	for i in range(n-2):
		s1 = s1 * meet
	print(s1)
	s2 = s1.integrate('x1').substitute('x1', 't1').divide('t1')
	print(s2)
	v2 = s2.substitute('t1', r).get()
	v1 = s2.substitute('t1', l).get()
	print(v2)
	print(v1)
	return (v2 - v1) / (r - l) ** n * n

#print(hang({'x': 1}, {'x': 1}, 1).integrate('x'))
print(solve(2, 1, 10))

"""a = shik([hang({'x': 1, 'y': 1}, {}, 2), hang({'x': 1, 'z': 2}, {})])
b = shik([hang({'x': 1, 'y': 1}, {}, 5), hang({'x': 1, 'z': 2}, {})])
print(a)
print(a.integrate('x'))
#a = shik([hang(1, 0), hang(2, 0)])
#b = shik([hang(1, 0, -1), hang(2, 0)])
#print(a * b)
"""
