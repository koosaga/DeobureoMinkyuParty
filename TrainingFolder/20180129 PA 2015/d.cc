#include<bits/stdc++.h>
using namespace std;
set<int> conn[202020];
bool visit[202020];
int N, M, D;
vector<int> ans;
vector<int> res;
int dfs(int a)
{
    if(visit[a]) return 0;
    res.push_back(a);
    visit[a] = true;
    int ans = 1;
    for(int i: conn[a])
        ans += dfs(i);
    return ans;
}
int main()
{
    scanf("%d%d%d", &N, &M, &D);
    for(int i=0; i<M; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        conn[u].insert(v);
        conn[v].insert(u);
    }
    queue<int> Q;
    for(int i=1; i<=N; ++i)
        if(conn[i].size() < D)
            Q.push(i);
            
    while(!Q.empty())
    {
        int x = Q.front(); Q.pop();
        for(auto y: conn[x])
        {
            conn[y].erase(x);
            if(conn[y].size() < D)
                Q.push(y);
        }
        conn[x].clear();
    }
    int MAXSIZE = 0;
    for(int i=1; i<=N; ++i)
    {
        res.clear();
        int r = dfs(i);
        if(MAXSIZE<r)
        {
            MAXSIZE = r;
            ans = res;
        }
    }
    if(MAXSIZE == 1) puts("NIE");
    else
    {
        printf("%d\n", (int)ans.size());
        sort(ans.begin(), ans.end());
        for(auto x: ans)
            printf("%d ", x);
        puts("");
    }
    return 0;
}





