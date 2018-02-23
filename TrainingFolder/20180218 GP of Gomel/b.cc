#include<bits/stdc++.h>
using namespace std;
long long can(long long y)
{
    long long v = 1;
    long long ans = 0;
    while(y)
    {
        ans += v*y*(y+1)/2;
        v *= 2;
        y /= 2;
    }
    return ans;
}
long long f(long long x)
{
    long long ans = 0;
    while(x)
    {
        ans += x;
        x /= 2;
    }
    return ans;
}
long long solve(long long x)
{
    long long lo = 0; // can(mi) <= x
    long long hi = 2e9; //can(mi) > x
    while(lo+1 != hi)
    {
        long long mi= (lo+hi)/2;
        if(can(mi) <= x) lo = mi;
        else hi = mi;
    }
    return f(lo) + (x-can(lo))/(lo+1);
}
int main()
{
    int T; scanf("%d", &T);
    while(T--)
    {
        long long x; scanf("%lld", &x);
        printf("%lld\n", solve(x));
    }
    return 0;
}

