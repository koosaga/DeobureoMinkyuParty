#include<bits/stdc++.h>
using namespace std;
const int BIAS = 1000;
int dp[101010][BIAS*2+1]; // BIAS 100
int N, K;
int A[101010];
int B[101010];
int bktk(int a, int b)
{
    if(dp[a][b-a+BIAS] != -1) return dp[a][b-a+BIAS];
    if(a==N && b==N) return dp[a][b] = 0;
    if(a==N) return dp[a][b] = bktk(a, b+1) + 1;
    if(b==N) return dp[a][b] = bktk(a+1, b) + 1;
    if(abs(A[a]-B[b]) > K) return dp[a][b] = bktk(a+1, b+1) + 1;
    if(a-b==BIAS) return dp[a][b] = bktk(a, b+1) + 1;
    if(b-a==BIAS) return dp[a][b] = bktk(a+1, b) + 1;
    return dp[a][b] = min(bktk(a+1, b), bktk(a, b+1)) +1;
}
int main()
{
    memset(dp, -1, sizeof(dp));
    scanf("%d%d",&N,&K);
    for(int i=0; i<N; ++i)
        scanf("%d", A+i);
    for(int i=0; i<N; ++i)
        scanf("%d", B+i);       
    printf("%d\n", bktk(0, 0));
}
