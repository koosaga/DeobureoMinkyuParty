#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101010;
int N, M;
int from[MAXN], to[MAXN];
vector<int> conn[MAXN];
int deg[MAXN];
int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        scanf("%d%d", from+i, to+i);
        conn[from[i]].push_back(to[i]);
        deg[to[i]]++;
    }
    int cnt = 0;
    queue<int> Q;
    for(int i=1; i<=N; ++i)
        if(!deg[i])
        {
            Q.push(i);
            ++cnt;
        }
    while(!Q.empty())
    {
        int x = Q.front(); Q.pop();
        for(auto y: conn[x])
        {
            if(--deg[y] == 0)
            {
                ++cnt;
                Q.push(y);
            }
        }
    }
    if(cnt == N)
    {
        puts("1");
        printf("%d", M);
        for(int i=1; i<=M; ++i) printf(" %d", i);
        puts("");
    }
    else
    {
        printf("%d\n", 2);
        vector<int> ulv;
        vector<int> vlu;
        for(int i=0; i<M; ++i)
        {
            if(from[i]<to[i]) ulv.push_back(i+1);
            else vlu.push_back(i+1);
        }
        printf("%d", (int)ulv.size());
        for(auto x: ulv) printf(" %d", x);
        puts("");
        printf("%d", (int)vlu.size());
        for(auto x: vlu) printf(" %d", x);
        puts("");
    }
    return 0;
}





















