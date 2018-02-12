#include<bits/stdc++.h>
using namespace std;
int t[101];
int c[11];

int ncp[1044*100][10];
int8_t pcp[1044*100][10];
int8_t dp[1044*100][1024];
int N, M, R;
int main()
{
    scanf("%d%d%d", &N, &M, &R);
    for(int i=0; i<N; ++i) scanf("%d", t+i);
    for(int i=0; i<M; ++i) scanf("%d", c+i);
    vector<int> cp;
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<(1<<M); ++j)
        {
            int ans = t[i] + R + 1;
            for(int k=0; k<M; ++k)
                if(j&(1<<k))
                    ans += c[k] + R;
            cp.push_back(ans);
        }
        for(int j=0; j<M; ++j)
            cp.push_back(t[i]-c[j]+1);
    }
    sort(cp.begin(), cp.end());
    cp.resize( unique(cp.begin(), cp.end()) - cp.begin() );
    while(cp.back()>4e8)
        cp.pop_back();
    for(int i=0; i<cp.size(); ++i)
    {
        for(int j=0; j<M; ++j)
        {
            auto ne = lower_bound(cp.begin(), cp.end(), cp[i] + c[j] + R);
            if(ne != cp.end() && *ne == cp[i] + c[j] + R)
            {
                ncp[i][j] = ne - cp.begin();
                pcp[i][j] = 
                    upper_bound(t, t+N, cp[i] + c[j] - 1) -
                    lower_bound(t, t+N, cp[i]);
            }
            else 
                ncp[i][j] = -1;
        }
    }
    
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for(int i=0; i<cp.size(); ++i)
    {
        for(int j=0; j<(1<<M); ++j)
        {
            if(i) dp[i][j] = max(dp[i-1][j], dp[i][j]);
            if(dp[i][j] < 0) continue;
            for(int k=0; k<M; ++k)
            {
                if(j&(1<<k)) continue;
                if(ncp[i][k] == -1) continue;
                int nextplace = ncp[i][k];
                int8_t nextvalue = dp[i][j] + pcp[i][k];
                dp[nextplace][j+(1<<k)]
                    = max(dp[nextplace][j+(1<<k)], nextvalue);
            }
        }
    }
    int ans = 0;
    for(int i=0; i<(1<<M); ++i)
        ans = max(ans, (int)dp[cp.size()-1][i]);
    printf("%d\n", ans);
}












