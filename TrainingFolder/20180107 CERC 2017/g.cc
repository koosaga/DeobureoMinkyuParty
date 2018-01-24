#include<bits/stdc++.h>
using namespace std;

set<pair<double, int> > S;
int N, M;
vector<int> conn[303030];
const double INF = 7e300;
double DP[303030];
int xcount[303030];
double xsum[303030];
void update(int x)
{
    //printf("<%d: %f>\n", x, DP[x]);
    for(auto y: conn[x])
    {
        auto it = S.find({DP[y], y});
        if(it==S.end()) continue;
        xcount[y]++;
        xsum[y] += DP[x];
        S.erase(it);
        DP[y] = (conn[y].size() + xsum[y])/xcount[y];
        S.insert({DP[y], y});
    }
}
int main()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v); u--;v--;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    for(int i=0; i<N-1; ++i)
    {
        DP[i] = INF*2;
        S.insert({DP[i], i});
    }
    DP[N-1] = 0;
    update(N-1);
    while(true)
    {
        double x; int y; tie(x, y) = *S.begin(); S.erase(S.begin());
        //printf("%d: %f %f %d\n", y, x, xsum[y], xcount[y]);
        if(y==0)
        {
            printf("%.12f\n", x);
            /*for(int i=0; i<N; ++i)
            {
                printf("%d: %.12f\n", i, DP[i]);
                
            }*/
            return 0;
        }
        update(y);
    }
    return 0;
}
