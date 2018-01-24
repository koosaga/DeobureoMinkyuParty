#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int matsize = 200;
struct mat
{
    long long a[200][200];
};
mat mul(mat A, mat B)
{
    mat C;
    for(int i=0; i<matsize; ++i)
        for(int j=0; j<matsize; ++j)
            C.a[i][j] = 0;
            
    for(int k=0; k<matsize; ++k)        
        for(int i=0; i<matsize; ++i)
            for(int j=0; j<matsize; ++j)
            {
                C.a[i][j] += A.a[i][k]*B.a[k][j] % MOD;
            }
    for(int i=0; i<matsize; ++i)
        for(int j=0; j<matsize; ++j)
            C.a[i][j] %= MOD;
    return C;
}

mat ipow(mat A, long long int b)
{
    if(b==1) return A;
    mat res = ipow(A, b/2);
    res = mul(res, res);
    if(b&1) res = mul(res, A);
    return res;
}

vector<int> getfactor(int n, int k)
{
    vector<int> factors;
    for(int i=1; i*i<=k; ++i)
    {
        if(k%i==0)
        {
            if(i%2==1)
                if(k/i<=n)
                    factors.push_back(k/i);
            if(i*i != k && (k/i)%2==1)
                if(i<=n)
                    factors.push_back(i);
        }
    }
    return factors;
}

long long dp[10000001];
long long powtable[100001];
long long solvematrix(int N, int K)
{
    memset(dp, 0, (matsize+1)*sizeof(long long));
    vector<int> X = getfactor(N, K);
    mat A;
    memset(&A, 0, sizeof(A));
    for(auto x: X)
        A.a[0][x-1] = powtable[x];
    if(K%2==0 && K%4!=0)
        A.a[0][3] += 4;
    for(int i=0; i<matsize-1; ++i) 
        A.a[i+1][i] = 1;
    dp[0] = 1;
    for(int i=1; i<=matsize; ++i)
    {
        for(auto x: X)
        {
            if(i>=x) dp[i] += dp[i-x]*powtable[x]%MOD;
        }
        if(K%2==0 && K%4!=0)
        {
            if(i>=4) dp[i] += dp[i-4]*4;
        }
        dp[i] %= MOD;
    }
    mat B = ipow(A, N);
    
            
    long long ans = 0;
    for(int i=0; i<matsize; ++i)
        ans += B.a[matsize-1][i] * dp[matsize-i-1] % MOD;
    return ans % MOD;
}
long long solvelinear(int N, int K)
{
    memset(dp, 0, (N+1)*sizeof(long long) );
    vector<int> X = getfactor(N, K);
    
    bool havetwo = (K%2==0 && K%4 !=0);
    dp[0] = 1;
    for(int i=1; i<=N; ++i)
    {
        for(auto x: X)
        {
            if(i>=x) dp[i] += dp[i-x]*powtable[x]%MOD;
        }
        if(havetwo)
        {
            if(i>=4) dp[i] += dp[i-4]*4;
        }
        dp[i] %= MOD;
    }
    return dp[N];
}

long long solve(int N, int K)
{
    vector<int> X = getfactor(N, K);
    long long matrixET = 1LL*K*K*K*2*(31-__builtin_clz(N));
    long long linearET = 1LL*(X.size() + 1)*N;
    if(matrixET <= linearET && K<200)
    {
        matsize = max(4, K);
        return solvematrix(N, K);
    }
    else
    {
        return solvelinear(N, K);
    }
}

int main()
{
    powtable[0] = 1;
    for(int i=1; i<=100000; ++i)
        powtable[i] = (powtable[i-1]*2)%MOD;
    powtable[1] = 1; powtable[2] = 2;
    int T; scanf("%d", &T);
    while(T--)
    {
        int N, K;
        scanf("%d%d", &N, &K);
    printf("%lld\n", solve(N, K));
    }
}























