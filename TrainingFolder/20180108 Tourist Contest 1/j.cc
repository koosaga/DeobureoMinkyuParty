#include<bits/stdc++.h>
using namespace std;
long long solve(long long s)
{
    if(s==0) return 1;
    long long ans = 1;
    for(long long i=2; i*i<=s; ++i)
    {
        if(s%i==0)
        {
            int cnt = 1;
            while(s%i==0)
            {
                ++cnt;
                s/=i;
            }
            ans *= cnt;
        }
    }
    if(s != 1) ans *= 2;
    return ans;
}
int main()
{
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);
    long long N; scanf("%lld", &N);
    long long ans = 0;
    for(long long i=1; i*i<=N; ++i)
    {
        if(N%i==0)
        {
            ans += solve((N/i)-1);
            if(i*i != N)
                ans += solve(i-1);
        }
    }
    printf("%lld\n", ans);
}
