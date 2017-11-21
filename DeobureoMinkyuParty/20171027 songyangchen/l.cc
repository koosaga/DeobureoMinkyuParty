#include<bits/stdc++.h>
using namespace std;
char str[1010101];
const int MOD = 1e9+7;
const int INV2 = (MOD+1)/2;


long long dpt[1024];
int N = 0;

long long ipow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        b /= 2;
    }
    return res;
}


long long solve(int x)
{
    int anstable[11];
    int invtable[11];
    int tp = 0;
    
    for(int i=0; i<=10; ++i) anstable[i] = invtable[i] = -1;
    
    for(int j=0; j<10; ++j)
    {
        if(x&(1<<j))
        {
            invtable[j] = tp;
            anstable[tp++] = j;
        }
    }
    
    long long dp[11];
    for(int i=0; i<=10; ++i) dp[i] = 0;
    dp[0] = ipow(2, N);
    
    for(int i=0; i<N; ++i)
    {
        int v = invtable[str[i]-'0']; if(v==-1) continue;
        
        long long ans = dp[v] * INV2 % MOD;
        dp[v] = ans;
        dp[v+1] = (dp[v+1] + ans)%MOD;
    }
    return dp[tp];
}


long long ans[1000];
int main()
{
    scanf("%s", str);
    N = strlen(str);
    for(int i=0; i<1024; ++i)
    {
        dpt[i] = solve(i);
        if(dpt[i]) printf("<%d %lld>\n", i, dpt[i]);
    }
    for(int y=10;y>=0;--y)
    {
        for(int i=1023; i>=0; --i)
        {
            if(y!=__builtin_popcount(i)) continue;
            int x = i;
            while(x)
            {
                int lb = x&(-x);
                dpt[i-lb] += MOD - dpt[i];
                dpt[i-lb] %= MOD;
                x -= lb;
            }
            ans[y] += dpt[i];
            ans[y] %= MOD;
        }
    }
    for(int i=1; i<=10; ++i)
        printf("%lld ", ans[i]);
    puts("");
    return 0;
}
