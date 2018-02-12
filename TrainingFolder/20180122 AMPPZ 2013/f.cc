#include<bits/stdc++.h>
using namespace std;

#define count ddlc

const int MAXN = 1e6 + 10;
int N, K;
vector<int> conn[MAXN];
int count[MAXN];
int dist[MAXN];

int main()
{
    scanf("%d%d", &N, &K);
    if(N == 1)
    {
        puts("1");
        puts("1");
        return 0;
    }
    for(int i=0; i<N-1; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    vector<int> ans;
    vector<int> pleaf;
    for(int i=1; i<=N; ++i)
        if(conn[i].size() == 1)
            pleaf.push_back(i);
    for(int i=0; i<K/2; ++i)
    {
        vector<int> nleaf;
        for(int x: pleaf)
        {
            ans.push_back(x);
            for(auto y: conn[x])
            {
                count[y]++;
                if(count[y] + 1 == conn[y].size())
                    nleaf.push_back(y);
            }
        }
        pleaf = nleaf;
    }
    if(K%2==1 && pleaf.size() >= 1)
    {
        ans.push_back(pleaf[0]);
    }
    
    printf("%d\n", (int)ans.size());
    for(auto x: ans)
        printf("%d ", x);
    puts("");
}
