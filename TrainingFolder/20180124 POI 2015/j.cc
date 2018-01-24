#include<bits/stdc++.h>
using namespace std;

struct edg
{
    int x, w;
};

vector<edg> adj[300010];
vector<edg> rar[300010];

int ans[300010];
int inp[300010];
int mem[300010];
int deg[300010];
int cnt;

void init(int x, int l, int r)
{
    if(r < l)
        return;
    
    for(int i = l; i<=r; i++)
    {
        adj[i].push_back({cnt, 0});
        rar[cnt].push_back({i, 0});
        deg[cnt]++;
    }
    mem[x] = cnt++;
    
    if(l < r)
    {
        init(2*x, l, (l+r)/2);
        init(2*x + 1, (l+r)/2+1, r);
    }
}

void add(int x, int l, int r, int s, int g, vector<int> &v)
{
    if(g < s || r < l || g < l || r < s)
        return;
    
    if(s <= l && r <= g)
    {
        for(int &t : v)
        {
            adj[mem[x]].push_back({t, 1});
            rar[t].push_back({mem[x], 1});
            deg[t]++;
        }
    }
    else
    {
        add(2*x, l, (l+r)/2, s, g, v);
        add(2*x+1, (l+r)/2+1, r, s, g, v);
    }
}

int main()
{
    int n, s, m, i, j;
    scanf("%d%d%d", &n, &s, &m);
    for(i=0;i<s;i++)
    {
        int p, d;
        scanf("%d%d", &p, &d);
        inp[p] = d;
    }
    
    cnt = n+1;
    
    init(1, 1, n);
    
    for(i=0;i<m;i++)
    {
        vector<int> v;
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        for(j=0;j<k;j++)
        {
            int t;
            scanf("%d", &t);
            v.push_back(t);
        }
        
        for(j=1;j<v.size();j++)
            add(1, 1, n, v[j-1]+1, v[j]-1, v);
        add(1, 1, n, l, v[0]-1, v);
        add(1, 1, n, v[v.size()-1] + 1, r, v);
    }
    
    queue<int> q;
    for(i=1;i<cnt;i++)
    {
        if(deg[i] == 0)
        {
            q.push(i);
        }
    }
    
    int cc = cnt - 1;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        cc--;
        
        int r = 1;
        for(edg &y : rar[x])
            r = max(r, ans[y.x] + y.w);
        
        if(x <= n && inp[x] && r > inp[x])
        {
            printf("NIE");
            return 0;
        }
        
        if(x <= n && r > 1000000000)
        {
            printf("NIE");
            return 0;
        }
        
        if(x <= n && inp[x])
        {
            ans[x] = inp[x];
        }
        else
            ans[x] = r;
        
        for(edg &e : adj[x])
        {
            deg[e.x]--;
            if(deg[e.x] == 0)
                q.push(e.x);
        }
    }
    
    if(cc)
    {
        printf("NIE");
        return 0;
    }
    
        printf("TAK\n");
    for(i=1;i<=n;i++)
           printf("%d ", ans[i]);
    
    return 0;
}



