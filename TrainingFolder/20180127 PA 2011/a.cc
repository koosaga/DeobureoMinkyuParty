#include<bits/stdc++.h>
using namespace std;
using HASH = uint64_t;
const int MAXN = 505050;
const int MOD = 1e9+7;
#define hash fuck 
HASH hash(int q, vector<pair<int, HASH > >& v)
{
    sort(v.begin(), v.end());
    HASH t = 1000000413 + 246810*q ;
    HASH p = 456456457;
    HASH res = (v.size()*6505616)^789797493;
    for(auto i: v)
    {
        res += i.second*p;
        p *= t;
    }
    return res;
}
int N;
vector<int> conn[MAXN];
int maxsize[MAXN];
int size[MAXN];

long long ans = 1;
pair<int, HASH> dfs2(int a, int pa, bool b)
{
    vector<pair<int, HASH> > childs;
    for(auto x: conn[a])
    {
        if(x==pa) continue;
        childs.push_back(dfs2(x, a, b));
    }

    int v = 1; for(auto x: childs) v += x.first;
    HASH res = hash(v, childs);
    if(b)
    {
        int cnt = 1;
        for(int i=1; i<childs.size(); ++i)
        {
            if(childs[i] == childs[i-1]) ++cnt;
            else
            {
                for(int j=1; j<=cnt; ++j)
                   ans = (ans*j)%MOD;
                cnt = 1;
            }
        }
        for(int j=1; j<=cnt; ++j) ans = (ans*j)%MOD;
    }
    return make_pair(v, res);
}
int dfs(int a, int pa)
{
    int res = 1;
    for(auto x: conn[a])
    {
        if(x==pa) continue;
        int r =  dfs(x, a);
        maxsize[a] = max(maxsize[a], r);
        res += r;
    }
    size[a] = res;
    maxsize[a] = max(maxsize[a], N-size[a]);
    return res;
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N-1; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    for(int i=1; i<=N; ++i) maxsize[i] = 0;
    dfs(1, 0);
    int centroid1 = min_element(maxsize+1, maxsize+N+1) - maxsize;
    int c1size = maxsize[centroid1];
    maxsize[centroid1] = 9999999;
    int centroid2 = min_element(maxsize+1, maxsize+N+1) - maxsize;  
    int c2size = maxsize[centroid2];
    
    
    pair<int, HASH> res1 = dfs2(centroid1, 0, true);
    pair<int, HASH> res2 = dfs2(centroid2, 0, false); 
    
    if(c1size == c2size && N%2==0 && c1size == N/2)
    {
        //dosomething
        if(res1==res2) ans = (ans*2)%MOD;
    }
    printf("%lld\n", ans);
    return 0;
}


















