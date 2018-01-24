#include<bits/stdc++.h>
using namespace std;
long long n;
int p, r;
int ipow(int a, int b, int p)
{
    if(b==0) return 1%p;
    long long ans = ipow(a, b/2, p);
    ans *= ans; ans %= p;
    if(b&1) ans *= a; ans %= p;
    return ans;
}
int main()
{
    scanf("%lld%d%d", &n, &p, &r);
    if(n>=2*p)
    {
        if(r==0) puts("2 1");
        else puts("-1 -1");
        return 0;
    }
    if(p==2)
    {
        if(n==2)
        {
            if(r==0) puts("-1 -1");
            else puts("2 1");
        }
        else// (n==3)
        {
            if(r==0) puts("3 2");
            else puts("2 1");
        }
        return 0; 
    }
    if(n>=p)
    {
        if(r==0)
        {
            puts("2 1"); return 0;
        }
        long long x = 1;
        for(int i=1; i<=n; ++i)
            if(i!=p) x = (x*i)%p;
        long long ans = r;
        for(int i=0; i<p-2; ++i)
            ans = (ans*x)%p;
        printf("%d %lld\n", p, ans);
        return 0;
    }
    if(r==0)
    {
        puts("-1 -1");
        return 0;
    }
    long long x = 1;
    for(int i=1; i<=n; ++i) x = (x*i)%p;
    x = ipow(x, p-2, p);
    x *= r; x %= p;
    for(int i=2; i<=n; ++i)
    {
        long long target = x *i%p;
        if(target<i)
        {
            printf("%d %lld\n", i, target);
            return 0;
        }  
    }
    puts("-1 -1");
    return 0;
}





















