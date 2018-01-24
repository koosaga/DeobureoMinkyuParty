import random

N = 50000

r = list(range(1, N+1))
random.shuffle(r)
r = [0] + r


print (N)
for i in range(1, N+1): print(10, end = " ") 
print ("")
for i in range(1, N):
    print(r[i], r[i+1])

for i in range(1, N, 2):
    print(r[i], r[N+1-i], end = " ")
print("")
for i in range(1, N):
    print(16, end = " ")
print("")
