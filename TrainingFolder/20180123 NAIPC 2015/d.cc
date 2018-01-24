#include<bits/stdc++.h>
using namespace std;
int N, M;
int A[5050500], X[5050505];
long long fact[5050505];
long long invfact[5050505];
long long pow2[5050505];
long long invpow2[5050505];
long long invipow2m2[5050505];
long long dp[5050505][4];
const int MOD = 1e9+7;
long long zdp[5050505][3];
long long C(long long, int);
long long ipow(long long, long long);
long long zerocalc(int x, int y)
{
    if(x<2) return 0;
    if(zdp[x][y] != -1) return zdp[x][y];
    if(y==1) return zdp[x][y] = 0;
    if(y==2)
        return zdp[x][y] = C(pow2[x], 3) * invpow2[x] % MOD * pow2[x-2] % MOD;
    if(y==3)
    {
        return zdp[x][y] = ((C(pow2[x], 6) + 4*zerocalc(x-1, 2) )%MOD
                            * invpow2[x] % MOD - 4*zerocalc(x-1, 2)%MOD + MOD )%MOD;
    }
}
long long nonzerocalc(int x, int y)
{
    return (MOD + C(pow2[x], y*2) - zerocalc(x, y)) * invipow2m2[x] % MOD;
}
long long ipow(long long a, long long b)
{
    a %= MOD;
    long long ans = 1;
    while(b)
    {
        if(b&1) ans = (ans*a)%MOD;
        a = a*a%MOD;
        b /= 2;
    }
    return a;
}

long long C(long long a, int b)
{
    long long ans = 1;
    for(int i=0; i<b; ++i)
        ans = (ans*(a-i))%MOD;
    return (ans * invfact[b])%MOD;
}

long long solveodd()
{
    long long ans = 0;
    for(int k=1; k<=N; k+=2)
    {
        long long upper = C(pow2[M-1], k) * invpow2[M-1] % MOD;
        long long lower = C(X[0], N-k);
        ans = (ans + upper*lower)%MOD;
    }
    return ans;
}

long long solveeven()
{
    for(int i=M-1; i>=0; --i)
    {
        dp[i][0] = 1;
        for(int k=2; k<=N; k += 2)
        {
            //printf("%d %d, %lld\n", i, k, dp[i][k/2]);
            dp[i][k/2] = dp[i+1][k/2];
            if(A[i] != 1) continue;
            for(int s=2; s<=k; s += 2)
            {
                long long upperzero = zerocalc(M-1-i, s/2);
                long long lowerzero = dp[i+1][(k-s)/2];
                long long uppernonzero = nonzerocalc(M-1-i, s/2);
                long long lowernonzero = (C(X[i], k-s) - lowerzero + MOD) % MOD;
                dp[i][k/2] = (dp[i][k/2] + upperzero*lowerzero%MOD 
                              + uppernonzero * lowernonzero % MOD)%MOD;
                //printf("%d %d %d\n", i, k, s);
                //printf("%lld %lld %lld %lld\n", upperzero, lowerzero, uppernonzero, lowernonzero);
            }
            //printf("%d %d: %lld\n", i, k, dp[i][k/2]);
        }
    }
    //printf("%lld %lld %lld\n", dp[0][0], dp[0][1], dp[0][2]);
    return dp[0][N/2];
}

long long solve()
{
    //printf("%d %d\n", N, M);
    //for(int i=0; i<M; ++i)
    //    printf("%d ", A[i]);
    //puts("");
    //for(int i=0; i<M; ++i)
    //    printf("%d ", X[i]);
    //puts("");
    if(N%2==1) return solveodd();
    else return solveeven();
}

void Init()
{
    memset(zdp, -1, sizeof(zdp));
    fact[0] = invfact[0] = pow2[0] = invpow2[0] = 1;
    const int MAXK = 5050505;
    for(int i=1; i<MAXK; ++i)
    {
        fact[i] = fact[i-1]*i%MOD;
        pow2[i] = pow2[i-1]*2%MOD;
        invipow2m2[i] = ipow(pow2[i]-1, MOD-2);
    }
    invfact[MAXK-1] = ipow(fact[MAXK-1], MOD-2);
    invpow2[MAXK-1] = ipow(pow2[MAXK-1], MOD-2);
    for(int i=MAXK-2; i>=1; --i)
    {
        invfact[i] = invfact[i+1]*(i+1)%MOD;
        invpow2[i] = invpow2[i+1]*2%MOD;
    }
    return;
}

void genA(int K, char s[])
{
    int X = strlen(s);
    M = K*X;
    for(int i=0; i<M; i+= X)
    {
        for(int j=i; j<i+X; ++j)
        {
            A[j] = s[j-i]-'0';
        }
    }
    for(int i=M-2; i>=0; --i)
    {
        ::X[i] = (::X[i+1] + A[i+1] * pow2[M-i-2])%MOD;
    }
    
}
int main()
{
    Init();
    int K; char s[101];
    scanf("%d%d%s", &N, &K, s);
    genA(K, s);
    printf("%lld\n", solve());
}

