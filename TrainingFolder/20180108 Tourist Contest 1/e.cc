#include<bits/stdc++.h>
using namespace std;

void exgcd(long long a, long long b, long long &x, long long &y)
{
    if(a+b==1)
    {
        x = a;
        y = b;
    }
    else
    {
        exgcd(b, a%b, y, x);
        y -= x*(a/b);
    }
}

long long tmain(long long a, long long b, long long c)
{
    long long x, y;
    exgcd(a, b, x, y);
    if(x < 0)
    {
        x += b; y -= a;
    }
    x *= c; y *= c; x %= b; y %= a;
    
    //cout <<a << " " << b << " " << x << " " << y << endl;
    long long ans;
    if(c>a)
        ans = 2*(x-y); 
    else
        ans = 2*(x-y)-2;
    ans = min(ans, 2*((a+b)-(x-y))-2);
    return ans;
}

int main()
{
    freopen("end.in", "r", stdin);
    freopen("end.out", "w", stdout);
    int T; scanf("%d", &T);
    while(T--)
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        int g = __gcd(a, __gcd(b, c));
        a /= g; b /= g; c /= g;
        if(c==a || c==b) puts("1");
        else if(__gcd(a, b) != 1) puts("-1");
        else if(c > a && c > b) puts("-1");
        else printf("%lld\n", tmain(min(a,b),max(a,b),c));
    }
}
