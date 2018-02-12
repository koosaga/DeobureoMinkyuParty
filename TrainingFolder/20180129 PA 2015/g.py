
def solve(k, x):
    cnt = 0
    for i in range(1, min(2500, x//k)+1):
        target = i * k
        s = 0
        while target > 0:
            s += (target % 10)**2
            target //= 10
        
        if s == i: cnt += 1
    return cnt


if __name__ == '__main__':
    k, a, b = map(int, input().split())
    print(solve(k, b) - solve(k, a-1))
