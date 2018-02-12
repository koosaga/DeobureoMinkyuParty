#include<bits/stdc++.h>
using namespace std;
long long cost[11];
int st[10000];
int size[10000];
int N, K;
int lq;
int main()
{
    scanf("%d%d", &N, &K);    
    for(int i=0; i<N; ++i) scanf("%d", st+i);
    cost[0] = 0; cost[1] = 1; for(int i=2; i<=10; ++i) cost[i] = cost[i-1]*3;
    for(int i=0; i<N; ++i) size[i] = K;
    
    for(int iter=0; iter<50; ++iter)
    {
        if(iter != 0)
        {
            char buf[50];
            scanf("%s", buf);
            if(strcmp(buf, "End") == 0) return 0;
            for(int i=0; i<N; ++i)
            {
                if(size[i])
                {
                    if( st[i] >= lq && buf[0] == '>' ||
                        st[i] <= lq && buf[0] == '<')
                    {
                            -- size[i];
                    }
                }
                scanf("%d", st+i);
            }
        }
        long long totalcost = 0;
        for(int i=0; i<N; ++i)
            totalcost += cost[size[i]];
        vector<pair<int, long long> > V;
        for(int i=0; i<N; ++i)
            if(size[i]) V.emplace_back(st[i], cost[size[i]]);
        sort(V.begin(), V.end());
        long long c = 0;
        for(auto x: V)
        {
            c += x.second;
            if(c*2 >= totalcost)
            {
                lq = x.first;
                break;
            }
        }
        printf("%d\n", lq);
        fflush(stdout);
    }
    assert(false);
}
