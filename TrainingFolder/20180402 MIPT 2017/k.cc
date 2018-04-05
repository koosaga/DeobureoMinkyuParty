#include<bits/stdc++.h>
using namespace std;
int N, K, M;
const int MOD = 1e9+7;
long long ipow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if(b&1) res *= a;
        a *= a; b /= 2;
        res %= MOD; a %= MOD;
    }
    return res;
}
int main()
{
    scanf("%d%d%d", &N, &K, &M);
    if(N<=K)
    {
        puts("0");
        return 0;
    }
    while(K!=M)
    {
        N--; K--;
    }
    --N;
    long long ans = 1;
    for(int i=1; i<=N; ++i)
        ans = (ans * i)%MOD;
    for(int i=1; i<=K; ++i)
        ans = (ans*ipow(i, MOD-2))%MOD;
    for(int i=1; i<=N-K; ++i)
        ans = (ans*ipow(i, MOD-2))%MOD;
    ans *= 2;
    ans %= MOD;
    ans -= N+1;
    ans += K;
    ans += MOD;
    ans %= MOD;
    printf("%lld\n", ans);
}
