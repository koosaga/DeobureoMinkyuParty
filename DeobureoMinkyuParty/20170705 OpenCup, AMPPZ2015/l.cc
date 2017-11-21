#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1010101;
int N;
vector<int> conn[MAXN];
int size[MAXN];
int dfs1(int a, int pa)
{
    int ans = 1;
    for(int x: conn[a])
    {
        if(x==pa) continue;
        ans += dfs1(x, a);
    }
    return size[a] = ans;
}
long long ans = 1e15;
void dfs2(int a, int pa, long long val)
{
    ans = min(ans, val);
    for(int x: conn[a])
    {
        if(x==pa) continue;
        dfs2(x, a, val+2*size[x]-N);
    }
    return;
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N-1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    dfs1(0, -1);
    long long xx = 1LL*N*N;
    for(int i=0; i<N; ++i)
        xx -= size[i];
    dfs2(0, -1, xx);
    printf("%lld\n", ans);
    return 0;
}
