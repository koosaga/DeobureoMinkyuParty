from fractions import gcd


N, M = map(int, input(). split())

g = gcd(N-1, M-1)
a = (N-1)//g
b = (M-1)//g

ans = g*a*b+a+b+1 - (a+1)*(b+1)//2

print(ans%(10**18+9))

