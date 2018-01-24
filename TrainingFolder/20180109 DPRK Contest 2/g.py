
def naiveJ(a, b):
    if b==0: return 1
    return a**naiveJ(a, b-1)

def naiveboundJ(a, b):
    if b==0: return 1
    t =  naiveboundJ(a, b-1)
    if t<100:
        return a**t
    else:
        return float("inf")


def DeepInspection(n, a, m, b):
    assert a<b and n>m    
    x = 1
    y = naiveboundJ(m, b-a)
    if y==float("inf"): return "<"
    return ">"
T = int(input())
for _ in range(T):
    n, a, m, b = list(map(int, input().split()))
    if n==m and a<b and n!=1:
        print("<")
    elif n==m and a>b and n!=1:
        print(">")
    elif n==m: 
        print("=")
    elif a==b and n<m:
        print("<")
    elif a==b and n>m:
        print(">")
    elif a<=b and n<=m:
        print("<")
    elif a>=b and n>=m:
        print(">")
    elif n==1:
        print("<")
    elif m==1:
        print(">")
    else:
        Jna = naiveboundJ(n, a)
        Jmb = naiveboundJ(m, b)
        if Jna<Jmb: print("<")
        elif Jna>Jmb: print(">")
        elif Jna==Jmb and Jna!=float("inf"):
            print("=")
        else:
            swapresult = False
            if a>b:
                (n,a,m,b)=(m,b,n,a)
                swapresult = True
            res = DeepInspection(n,a,m,b)
            if swapresult:
                if res==">": res = "<"
                else: res = ">"
            print(res)
            
            
            
            
            
            
            
            
            
