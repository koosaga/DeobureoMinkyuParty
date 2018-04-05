#include<bits/stdc++.h>
using namespace std;
const int MAXN = 252525;
const int MOD = 1e9+7;
int fact[MAXN+1];
int invfact[MAXN+1];
int binom(int n, int k)
{
    return 1LL*fact[n]*invfact[k]%MOD*invfact[n-k]%MOD;
}
int ipow(long long a, int b)
{
    long long ans = 1;
    while(b)
    {
        if(b&1) ans *= a;
        a *= a;
        b /= 2;
        ans %= MOD;
        a %= MOD;
    }
    return ans;
}
void init()
{
    fact[0] = invfact[0] = 1;
    for(int i=1; i<MAXN; ++i)
    {
        fact[i] = 1LL*i*fact[i-1]%MOD;
        invfact[i] = ipow(fact[i], MOD-2);
    }
}
int N, M;
int deg[MAXN];
int revdeg[MAXN];
long long count(int ind)
{
    if(ind == 0) return 1;
    --ind;
    int V = 0, W = 0;
    for(int i=0; i<N; ++i)
        if(deg[ind] == deg[i])
        {
            V++;
            if(i<=ind) W++;
        }
    //printf("%d %d %d\n", ind, V, W);
    
    return binom(V, W);
}
int main()
{
    init();
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        deg[u-1]++; deg[v-1]++;
    }
    sort(deg, deg+N);
    reverse(deg, deg+N);
    int degsum = 0;
    long long ans = 0;
    for(int i=0; i<=N; ++i)
    {
        if(degsum == M+1LL*i*(i-1)/2)
            ans += count(i);
        degsum += deg[i];
    }
    printf("%lld\n", ans%MOD);
    return 0;
}





















