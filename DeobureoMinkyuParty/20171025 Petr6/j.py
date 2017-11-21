fi = open("tiling.in", "r")
fo = open("tiling.out", "w")

n, k = map(int, fi.readline().split())



if n%2==1 and k%2==1:
    fo.write("0\n")
    
    quit()


if n > k: n, k = k, n

if n == 1:
    fo.write("1\n")
    quit()
    
F = []
G = []

if n==2:
    F.append(1)
    G.append(0)
    for i in range(1, k+1):
        Fi = F[i-1] + G[i-1]
        Gi = 0
        if i>=2: Gi = F[i-2]
        F.append(Fi)
        G.append(Gi)
elif n%2==0:
    F.append(1)
    G.append(1)
    for i in range(1, k+1):
        Fi = 0
        if i-(n-2) >= 0: Fi += G[i-(n-2)]
        if i-n >= 0: Fi += G[i-n]
        Gi = F[i-1]
        F.append(Fi)
        G.append(Gi)
else:
    F.append(2)
    G.append(0)
    for i in range(1, k+1):
        Fi = 0
        if i-(n-1)>=0: Fi += F[i-(n-1)]
        if i-(n+1)>=0: Fi += F[i-(n+1)]
        F.append(Fi)

fo.write("%d\n"%(F[-1]+G[-1]))
        
        
        
        
        
        
