#include<bits/stdc++.h>
using namespace std;
long long L, R, Q;
int div(long long x)
{
    if(x==0) return -1;
    long long i=1;
    int cnt = 0;
    for(; i*i<x; ++i)
    {
        if(x%i==0) cnt += 2;
    }
    if(i*i==x) cnt++;
    return cnt;
}
int main()
{
    scanf("%lld%lld%lld", &L, &R, &Q);
    long long le = L / Q;
    long long re = R / Q;
    long long d;
    if(le == re)
        d = div(le*Q);
    else
        d = div(Q);
    if(d==-1) puts("infinity");
    else printf("%lld\n", d);
}
