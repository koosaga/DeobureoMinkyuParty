N = int(input())
A = input()

for i in range(3):
    print('+'.join(list(A)))
    ans = 0
    for i in A:
        ans += int(i)
    A = str(ans)
