#include<bits/stdc++.h>
using namespace std;
int N, M;
int arr[101][101];
int vis[101];
int tri[101];
int ttt[101];

vector<int> ppap;

void dfs(int a, int c)
{
    if(vis[a]+c == 3)
    {
        puts("NO");
        exit(0);
        return;
    }
    if(vis[a]) return;
    
    ppap.push_back(a);
    vis[a] = c;
    
    for(int i=0; i<N; ++i)
    {
        
        if(arr[a][i] == 0)
        {
            dfs(i, 3-c);
            
        }
    }
    
    return;
}
bool emi[10101];
int main()
{
    freopen("maxclique.in", "r", stdin);
    freopen("maxclique.out", "w", stdout);
    scanf("%d%d", &N, &M);
    if(N%3!=0)
    {
        puts("NO");
        return 0;
    }
    for(int i=0; i<M; ++i)
    {
        int u, v; scanf("%d%d",&u,&v);
        --u; --v; arr[u][v] = arr[v][u] = 1;
    }
    for(int i=0; i<N; ++i) arr[i][i] = 1;
    int compcnt = 0;
    for(int i=0; i<N; ++i)
        for(int j=0; j<i; ++j)
            for(int k=0; k<j; ++k)
            {
                int v1 = arr[i][j];
                int v2 = arr[j][k];
                int v3 = arr[k][i];
                if(v1==1 || v2==1 || v3==1) continue;
                
                
                if(v1==2 || v2==2 || v3==2)
                {
                    puts("NO");
                    return 0;
                }
                
                tri[i] = tri[j] = tri[k] = compcnt;
                ++compcnt;
                arr[i][j] = arr[j][i] = 
                arr[j][k] = arr[k][j] = 
                arr[k][i] = arr[i][k] = 2;
                emi[i] = emi[j] = emi[k] = true;
            }
    if(compcnt*3 != N)
    {
        puts("NO");
        return 0;
    }
    for(int i=0; i<N; ++i)
    {
        if(!emi[i])
        {
            puts("NO");
            return 0;
        }
    }
    
    int xx = 1;
    for(int i=0; i<N; ++i)
    {
        if(vis[i]) continue;
        
        ppap.clear();
        dfs(i, 1);
        for(int i=0; i<ppap.size(); ++i)
        {
            for(int j=0; j<i; ++j)
            {
                if(tri[ppap[i]]==tri[ppap[j]])
                {
                    puts("NO");
                    return 0;
                }
                if(vis[ppap[i]]!= vis[ppap[j]] && arr[ppap[i]][ppap[j]] != 0)
                {
                    puts("NO");
                    return 0;
                }
                
            }
        }
        
    }
    puts("YES");
}















