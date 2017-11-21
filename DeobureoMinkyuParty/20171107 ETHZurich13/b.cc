#include <bits/stdc++.h>

using namespace std;
const int MAXN = 505;
typedef long long lint;

namespace TN
{
    struct edg{int pos, cap, rev;};
    vector<edg> gph[MAXN];
    void clear(){for(int i=0;i<MAXN;i++)gph[i].clear();}
    void add_edge(int s, int e, int x)
    {
        gph[s].push_back({e, x, (int)gph[e].size()});
        gph[e].push_back({s, 0, (int)gph[s].size() - 1});
    }
    
    int dis[MAXN], pnt[MAXN];
    bool bfs(int src, int sink)
    {
        memset(dis, 0, sizeof dis);
        memset(pnt, 0, sizeof pnt);
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while(!que.empty())
        {
            int x = que.front();
            que.pop();
            for(auto &e : gph[x])
            {
                if(e.cap > 0 && !dis[e.pos])
                {
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }
    
    int dfs(int x, int sink, int f)
    {
        if(x == sink) return f;
        for(; pnt[x] < gph[x].size(); pnt[x]++){
            edg e = gph[x][pnt[x]];
            if(e.cap > 0 && dis[e.pos] == dis[x] + 1)
            {
                int w = dfs(e.pos, sink, min(f, e.cap));
                if(w)
                {
                    gph[x][pnt[x]].cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }
    lint match(int src, int sink)
    {
        lint ret = 0;
        while(bfs(src, sink)) {
            int r;
            while((r = dfs(src, sink, 2e9))) ret +=r;
            }
            return ret;
   }    
}

int cst[MAXN];
int pay[MAXN];
vector<int> need[MAXN];

int main()
{
    int n, m, a, t, i, j;
    scanf("%d%d", &n, &m);
    for(i=1;i<=n;i++)
        scanf("%d", &cst[i]);
    for(i=1;i<=m;i++)
        scanf("%d", &pay[i]);
    for(i=1;i<=m;i++)
    {
        scanf("%d", &a);
        for(j=0;j<a;j++)
        {
            scanf("%d", &t);
            need[i].push_back(t);
        }
    }
    TN::clear();
    for(i=1;i<=m;i++)
    {
        TN::add_edge(1, i+1, pay[i]);
        for(int t : need[i])
            TN::add_edge(i+1, t+m+1, 2e9);
    }
    for(i=1;i<=n;i++)
        TN::add_edge(i+m+1, m+n+2, cst[i]);
    
    lint res = 0;
    for(i=1;i<=m;i++)
        res += pay[i];
    res -= TN::match(1, m+n+2);
    printf("%lld", res); 
    return 0;
}
