#include<bits/stdc++.h>
using namespace std;
int N, M;
vector<pair<int, int> > adj[2525];
long long ep[9494];
long long X[5050];
long long Y[5050];
long long comb[2525][2525];
const int MOD = 1e9+7;    
int dfs(int a, int pa)
{
    int sz = 1;
    for(pair<int, int> tmp: adj[a])
    {
        int x = tmp.first; int l = tmp.second;
        if(x==pa) continue;
        int szx = dfs(x, a);
        X[0] = Y[0] = 1;
        for(int i=1; i<=2*M; ++i)
        {
            X[i] = szx*X[i-1]%MOD;
            Y[i] = (N-szx)*Y[i-1]%MOD;
        }
        for(int i=0; i<=2*M; ++i)
        {
            ep[i] += X[i] * Y[2*M-i] % MOD * l % MOD;
            ep[i] %= MOD;
        }
        sz += szx;
    }
    return sz;
    
}
void precompute()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<N-1; ++i)
    {
        int x, y, l; scanf("%d%d%d",&x,&y,&l);
        adj[x].emplace_back(y, l);
        adj[y].emplace_back(x, l);
    }
    dfs(1, -1);
    comb[0][0] = 1;
    for(int i=1; i<=M; ++i)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j=1; j<i; ++j)
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j])%MOD;
    }
}
int solve()
{
    long long ans = 0;
    for(int a=0; a<=M; ++a)
    {
        for(int b=0; b<=M; ++b)
        {
            int mpy = min(a, M-b) + min(b, M-a);
            int xaya = ep[a+b];
            int mcamcb = 1LL * comb[M][a] * comb[M][b] % MOD;
            ans += 1LL*mpy*xaya%MOD * mcamcb% MOD;
            ans %= MOD;
        }
    }
    return (int) ans;
}

int main()
{
    precompute();
    printf("%d\n", solve());
    return 0;
}
