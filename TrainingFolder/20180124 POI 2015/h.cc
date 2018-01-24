#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
int N;
int cost[50005];
vector<int> conn[50005];
int parent[50005];
int sparse[17][50005];
int height[50005];
int t[50005];
int k[50005];
const int UK = 16;
int sumk[50005][UK][UK];

int LCA(int u, int v)
{
    while(height[u] != height[v])
    {
        if(height[u] > height[v])
            u = parent[u];
        else
            v = parent[v];
    }
    if(u==v) return u;
    for(int i=16; i>=0; --i)
    {
        if(sparse[i][u] != sparse[i][v])
        {
            u = sparse[i][u];
            v = sparse[i][v];
        }
    }
    return parent[u];
}

int s(int u, int x, int k)
{
    int hdiff = height[u] - height[x];
    int iter = (hdiff + k - 1)/k;
    int c = 0;
    //printf("%d %d %d %d %d\n", u, x, k, hdiff, iter);
    
    int fuck[16], tp = 0;
    for(int i=0; i<17; ++i)
        if(k&(1<<i))
        {
            fuck[tp++] = i;
            //printf("%d, ", fuck[tp-1]);
        }
    //puts("");
    for(int i=0; i<iter; ++i)
    {
        //printf("U%d\n", u);
        c += cost[u];
        for(int j=0; j<tp; ++j)
            u = sparse[fuck[j]][u];
    }
    //printf("RET%d\n",c);
    return c;
}

int solve(int u, int v, int k)
{
    int x = LCA(u, v);
    //printf("%d %d %d\n", u, v, x);
    if(k<UK)
    {
        int ans =   ( sumk[u][k][height[u]%k] - sumk[x][k][height[u]%k] )
                  + ( sumk[v][k][height[v]%k] - sumk[x][k][height[v]%k] );
        if(height[u]%k == height[x]%k)
            ans += cost[x];
        return ans;
    }
    return s(u, x, k) + s(v, x, k) + ((height[u]%k==height[x]%k)?cost[x]:0);
    
}

void makeSparse()
{
    for(int i=1; i<=N; ++i)
        sparse[0][i] = parent[i];
    for(int j=1; j<=16; ++j)
        for(int i=1; i<=N; ++i)
            sparse[j][i] = sparse[j-1][sparse[j-1][i]];
    return;
}

void dfs(int a, int pa)
{
    parent[a] = pa;
    if(pa==-1)
        height[a] = 0;
    else
        height[a] = height[pa] + 1;
    
    for(int i=1; i<UK; ++i)
    {
        for(int j=0; j<i; ++j)
        {
            sumk[a][i][j] = sumk[pa][i][j];
            if(height[a]%i==j)
                sumk[a][i][j] += cost[a];
        }
    }
    
    for(auto x: conn[a])
    {
        if(x==pa) continue;
        dfs(x, a);
    }
}



int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; ++i) scanf("%d", cost+i);
    for(int i=0; i<N-1; ++i)
    {
        int a, b; scanf("%d%d", &a, &b); 
        conn[a].push_back(b);
        conn[b].push_back(a);
    }
    dfs(1, 0);
    makeSparse();
    for(int i=0; i<N; ++i) scanf("%d", t+i);
    for(int i=0; i<N-1; ++i) scanf("%d", k+i);
    for(int i=0; i<N-1; ++i)
        printf("%d\n", solve(t[i], t[i+1], k[i]));
    return 0;
}
