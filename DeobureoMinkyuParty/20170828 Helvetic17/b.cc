#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

long long mod_inv(long long x, long long p){
p -= 2;
    long long ret = 1, piv = x % mod;
    while(p){
        if(p & 1) ret = (ret * piv) % mod;
        piv = (piv * piv) % mod;
        p >>= 1;
    }
    return ret;
}

int N;
vector<pair<int, int> > adj[101010];
bool vis[101010];
int kv[101010];
queue<int> Q;

int main()
{
    memset(vis, 0, sizeof(vis));
    scanf("%d", &N);
    for(int i=0; i<N-1; ++i)
    {
        int u, v,c; scanf("%d%d%d",&u,&v,&c);
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
    }
    long long ans = 0;
    Q.push(0);
    kv[0] = 1;
    long long int pk = 1;
    while(!Q.empty())
    {    
        int c = Q.front(); Q.pop();
        vis[c] = true;
        long long int k = kv[c];
        long long int n = adj[c].size() - (c!=0);
        for(pair<int, int> a: adj[c])
        {
            if(vis[a.first]) continue;
            Q.push(a.first);
            ans += k*mod_inv(n, mod)%mod * a.second%mod;
            ans %=mod;
            kv[a.first] = k*mod_inv(n, mod)%mod;
        }
        pk *= (mod+1-k*mod_inv(n,mod)%mod)%mod;
        pk %= mod;
    }
    printf("%lld\n",ans*pk%mod);
}



