import random
print(500000, 0)
a = [i for i in range(500000)]
b = [i for i in range(500000)]
random.shuffle(a)
random.shuffle(b)
print( " ".join(map(str,a)))
print( " ".join(map(str,b)))
