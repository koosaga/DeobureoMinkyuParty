#include<bits/stdc++.h>
using namespace std;

struct edg
{
    int x, v;
};

const int MAXN = 500050;
vector<edg> arr[MAXN];
int N;

int tim[MAXN];
int lis[MAXN][2];

void dfs(int x, int p, int d)
{
    tim[x] = d;
    for(edg &e : arr[x])
        if(e.x != p)
            dfs(e.x, x, d+1);
}
bool is_fail(int tar)
{
    dfs(lis[tar][0], lis[tar][1], 1);
    dfs(lis[tar][1], lis[tar][0], 1);
    
    for(int i=0;i<=tar;i++)
    {
        int x, y;
        x = lis[i][0];
        y = lis[i][1];
        
        if(!tim[x] && !tim[y])
            return true;
        
        if(!tim[x])
            tim[y] = 0;
        else if(!tim[y])
            tim[x] = 0;
        else
        {
            if(tar % 2 == i % 2)
                tim[tim[x] > tim[y] ? x : y] = 0;
            else
                tim[tim[x] < tim[y] ? x : y] = 0;
        }
    }
    return 0;
}

int main2(int ans)
{
    int real_ans = ans;
    //printf("%d\n", ans);
    int lo = 0; //is_fail == false
    int hi = ans; //is_fail == true
    while(lo+1 != hi)
    {
        int mi = (lo+hi)/2;
        if(is_fail(mi)) hi = mi;
        else lo = mi;
    }
    return hi;
    /*
    for(int tar = ans-1; clock() < endtime && tar >= 0; tar--)
    {
        //printf("%d %d\n", tar, is_fail(tar));
        if(is_fail(tar)) real_ans = tar;
    }
    return real_ans;
    */
}

int minx[MAXN];
bool visit[MAXN];
bool visit2[MAXN];

int u[MAXN], v[MAXN];

vector<int> incl[MAXN];
int minv[MAXN];

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
        u[i] = a; v[i] = b;
        incl[u[i]].push_back(i);
        incl[v[i]].push_back(i);
        --a; --b;
        lis[i][0] = a;
        lis[i][1] = b;
        arr[a].push_back({b, i});
        arr[b].push_back({a, i});
    }
    for(int i=1; i<=N; ++i)
    {
        incl[i].push_back(N+1);
        incl[i].push_back(N+2);
    }
    for(int i=1; i<=N; ++i)
    {
        for(int j=0; j<incl[i].size(); ++j)
        {
            if(incl[i][j]%2 != incl[i][0]%2)
            {
                minx[i] = incl[i][j-1];
                break;
            }
        }
    }
    int ans = N;
    for(int i=0; i<N-1; ++i)
    {
        if(minx[u[i]] < i && minx[v[i]] < i)
        {
            ans = i;
            break;
        }
    }
    
    for(int i=0; i<N; ++i)
    {
        minv[i] = N;
        for(auto x: arr[i])
            minv[i] = min(minv[i], x.v);
    }
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
    
    int v = main2(min(ans, N-1));
    if(v >= N-1) v = -2;
    printf("%d\n", 1+ v);
    fflush(stdout);
    _Exit(0);
    return 0;
}
