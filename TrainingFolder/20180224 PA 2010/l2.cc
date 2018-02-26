#include<bits/stdc++.h>
using namespace std;

struct edg
{
    int x, v;
};

const int MAXN = 505050;
vector<edg> arr[MAXN];
int minv[MAXN];
int N;
bool visit[MAXN];
bool visit2[MAXN];
pair<int, int> dfs2(int a)
{
    
    if(visit2[a]) return make_pair(0, 0);
    visit2[a] = true;
    int sum = 0; if(minv[a] % 2 == 0) --sum;
    int maxv = 0;
    for(auto x: arr[a])
    {
        if(x.v % 2 == 0) continue;
        auto res = dfs2(x.x);
        sum += res.first;
        maxv = max(maxv, x.v);
        maxv = max(maxv, res.second);
    }
    return make_pair(sum, maxv);
}
pair<int, int> dfs(int a)
{
    
    if(visit[a]) return make_pair(0, 0);
    visit[a] = true;
    int sum = 0; if(minv[a] % 2 != 0) --sum;
    int maxv = 0;
    for(auto x: arr[a])
    {
        if(x.v % 2 != 0) continue;
        auto res = dfs(x.x);
        sum += res.first;
        maxv = max(maxv, x.v);
        maxv = max(maxv, res.second);
    }
    return make_pair(sum, maxv);
}
int main()
{
    scanf("%d", &N);
    for(int i=0;i<N-1;i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        arr[a].push_back({b, i});
        arr[b].push_back({a, i});
    }
    for(int i=0; i<N; ++i)
    {
        minv[i] = N;
        for(auto x: arr[i])
            minv[i] = min(minv[i], x.v);
    }
    int ans = N;
    for(int i=0; i<N; ++i)
    {
        if(!visit[i])
        {
            auto res = dfs(i);
            //printf("EVEN %3d %3d %3d\n", i+1, res.first, res.second);
            if(res.first < -1)
            ans = min(ans, res.second);
        }
        if(!visit2[i])
        {
            auto res = dfs2(i);
            //printf("ODD  %3d %3d %3d\n", i+1, res.first, res.second);
            if(res.first < -1)
            ans = min(ans, res.second);
        }
    }
    if(ans==N) puts("-1");
    else printf("%d\n", ans+1);
    return 0;
}
