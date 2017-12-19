#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
std::vector<int> dp[201][61];
void init()
{
    for(int i=1; i<=200; ++i)
        for(int j=0; j<=60; ++j)
            dp[i][j].resize(i*j+1);
    for(int i=1; i<=200; ++i)
    {
        dp[i][0][0] = 1;
        for(int j=0; j<=i; ++j)
            dp[i][1][j] = 1; 
        
        for(int j=2; j<=60; ++j)
        {
            //0~i
            dp[i][j][0] = dp[i][j-1][0];
            for(int k=1; k<=i; ++k)
            {
                dp[i][j][k] = dp[i][j][k-1] + dp[i][j-1][k];
                if(dp[i][j][k] >= MOD) dp[i][j][k] -= MOD;
            }
            for(int k=i+1; k<=i*j; ++k)
            {
                dp[i][j][k] = dp[i][j][k-1] - dp[i][j-1][k-(i+1)];
                if(k<=i*(j-1)) 
                    dp[i][j][k] += dp[i][j-1][k];
                if(dp[i][j][k] < 0) dp[i][j][k] += MOD;
                if(dp[i][j][k] >= MOD) dp[i][j][k] -= MOD;
            }
         }
    }
    return;
}
int main()
{
    init();
    while(true)
    {
        int N, M; scanf("%d%d", &N, &M);
        if(N==0 && M==0) return 0;
        long long ans = 0;
        for(int i=0; i<=M; ++i)
            ans += dp[M][N-1][(N-1)*i];
        ans %= MOD;
        ans *= N;
        ans %= MOD;
        printf("%lld\n", ans);
    }
}



