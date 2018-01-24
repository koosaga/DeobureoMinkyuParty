#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1010101;
int N, K, P;
bool conn[MAXN][7];
int DP[MAXN][2];
const int MOD = 1e9+7;
int isAdj(int a, int b, bool rev = false)
{
    if(abs(a-b)>P) return false;
    if(rev) return conn[b][a-b-3];
    return conn[a][b-a-3];
}
int main()
{
    scanf("%d%d%d", &N, &K, &P);
    for(int i=0; i<N; ++i)
    {
        for(int j = i-P; j<= i+P; ++j)
        {
            if(i==j) continue;
            if(j<0) continue;
            if(j>=N) continue;
            conn[i][j-i-3] = 1;
        }
    }
    for(int i=0; i<K; ++i)
    {
        int u, v; scanf("%d%d", &u, &v); --u; --v;
        if(abs(u-v)<=P)
            conn[u][v-u-3] = 0;
    }
    
    
    for(int swap = 0; swap<2; ++swap)
    {
        if(isAdj(0, 1, !swap)) DP[1][swap] = 1;
        if(isAdj(0, 2, !swap) && isAdj(2, 1, !swap) && isAdj(1, 4, !swap)
           && isAdj(0, 3, swap)) DP[4][swap] = 1;
        
        if(isAdj(0, 2, !swap) && isAdj(2, 5, !swap) &&
           isAdj(0, 3, swap) && isAdj(3, 1, swap) && isAdj(1, 4, swap))
            DP[5][swap] = 1;
    }
    for(int i=0; i<N-1; ++i)
    {
        for(int swap=0; swap<2; ++swap)
        {
            if(isAdj(i, i+2, !swap)) DP[i+2][swap] = (DP[i+2][swap]+DP[i+1][!swap])%MOD;
            if(isAdj(i, i+3, !swap) &&
               isAdj(i+1, i+2, swap)) DP[i+3][swap] = (DP[i+3][swap]+DP[i+1][!swap])%MOD;
            if(isAdj(i, i+3, !swap) && isAdj(i+3, i+2, !swap) && isAdj(i+2, i+5, !swap) &&
               isAdj(i+1, i+4, swap)) DP[i+5][swap] = (DP[i+5][swap]+DP[i+1][!swap])%MOD;
            if(isAdj(i, i+3, !swap) && isAdj(i+3, i+6, !swap) &&
               isAdj(i+1, i+4, swap) && isAdj(i+4, i+2, swap) && isAdj(i+2, i+5, swap))
                DP[i+6][swap] = (DP[i+6][swap]+DP[i+1][!swap])%MOD;
        }
    }
    long long ans = 0;
    for(int swap = 0; swap<2; ++swap)
    {
        if(isAdj(N-1, N-2, !swap)) ans += DP[N-1][swap];
        if(isAdj(N-1, N-3, !swap) && isAdj(N-3, N-2, !swap) && isAdj(N-2, N-5, !swap)
           && isAdj(N-1, N-4, swap)) ans += DP[N-4][swap]; 
        
        if(isAdj(N-1, N-3, !swap) && isAdj(N-3, N-6, !swap) &&
           isAdj(N-1, N-4, swap) && isAdj(N-4, N-2, swap) && isAdj(N-2, N-5, swap))
            ans += DP[N-5][swap];
    }
    
    if(N==1)
        ans = 1;
    else if(N<=10)
    {
        ans = 0;
        vector<int> x; for(int i=0; i<N; ++i) x.push_back(i);
        do
        {
            bool flag = false;
            for(int i=0; i<N; ++i)
            {
                if(!isAdj(x[i], x[(i+1)%N]))
                {
                    flag = true;
                    break;
                }
            }
            if(!flag) ++ans;
        }while(next_permutation(x.begin(), x.end()));
        ans /= N;
    }
    
    ans %= MOD;
    printf("%lld\n", ans);
    return 0;
}






