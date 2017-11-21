#include<bits/stdc++.h>
using namespace std;
pair<pair<int, int> , pair<int, int> > query[101010];
long long dp[101][101][2];
long long ans[101010];
int main()
{
    int M;
    scanf("%d", &M);
    for(int i=0; i<M; ++i)
    {
        int a, b, c, d;
        scanf("%d%d%d",&a,&c,&d);
        query[i] = make_pair(make_pair(a,i), make_pair(c,d ));
    }
    int tp = 0;
    query[M].first.first=1010101;
    sort(query, query+M);
    for(int j=1; j<50505; ++j)
    {
        if(j==1) dp[1][1][1] = 1;
        else
        {
            for(int l=1; l<=100; ++l)
                for(int r=1; r<=l; ++r)
                {
                    dp[l][r][j&1] = dp[l-1][r][1-(j&1)] + (j-2)*dp[l][r][1-(j&1)] + dp[l][r-1][1-(j&1)];
                    dp[l][r][j&1] %= 1000000007;
                    dp[r][l][j&1] = dp[l][r][j&1];
                }
        }
        while(query[tp].first.first==j)
        {
            ans[query[tp].first.second] = dp[query[tp].second.first][query[tp].second.second][j&1];
            tp++;
        }
    }
    for(int i=0; i<M; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
