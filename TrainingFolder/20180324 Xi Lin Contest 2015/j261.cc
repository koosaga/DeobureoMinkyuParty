#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2010;

using base = complex<double>;

namespace fft
{
void fft(vector<base>& a, bool inv)
{
    int n = a.size(), j =0;
    vector<base> roots(n/2);
    for(int i=1; i<n; ++i)
    {
        int bit = (n>>1);
        while(j>=bit) 
        {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i<j) swap(a[i], a[j]);
    }
    double ang = 2*acos(-1)/n * (inv?-1:1);
    for(int i=0; i<n/2; ++i)
    {
        roots[i] = base(cos(ang*i), sin(ang*i));
    }
    for(int i=2; i<=n; i<<=1)
    {
        int step = n/i;
        for(int j=0; j<n; j+=i)
        {
            for(int k=0; k<i/2; ++k)
            {
                base u = a[j+k], v = a[j+k+i/2]*roots[step*k];
                a[j+k] = u+v;
                a[j+k+i/2] = u-v;
            }
        }
    }
    if(inv) for(int i=0; i<n; ++i) a[i] /= n;
}

vector<base> F[2];

vector<long long> multiply(vector<long long> &v, int num, long long mod)
{
    int n=2048;
    vector<base>v1(n), v2(n), r1(n), r2(n);
    for(int i=0; i<v.size(); ++i)
    {
        v1[i] = base(v[i]>>15, v[i]&32767);
    }
    fft(v1, 0);
    v2 = F[num];
    for(int i=0; i<n; ++i)
    {
        int j = i?(n-i):i;
        base ans1 = (v1[i]+conj(v1[j]))*base(0.5, 0);
        base ans2 = (v1[i]-conj(v1[j]))*base(0, -0.5);
        base ans3 = (v2[i]+conj(v2[j]))*base(0.5, 0);
        base ans4 = (v2[i]-conj(v2[j]))*base(0, -0.5);
        r1[i] = (ans1*ans3)+(ans1*ans4)*base(0, 1);
        r2[i] = (ans2*ans3)+(ans2*ans4)*base(0, 1);
    }
    fft(r1, 1);
    fft(r2, 1);
    vector<long long>ret(n);
    for(int i=0; i<n; ++i)
    {
        long long av = (long long)round(r1[i].real());
        long long bv = (long long)round(r1[i].imag()) + (long long)round(r2[i].real());
        long long cv = (long long)round(r2[i].imag());
        av %= mod; bv %= mod; cv %= mod;
        ret[i] = (av<<30)+(bv<<15)+cv;
        ret[i] %= mod;
        ret[i] += mod;
        ret[i] %= mod;
    }
    return ret;
}
};
int comb[MAXN+2][MAXN+2];
int fact[MAXN+2];
int invfact[MAXN+2];
int ipow(long long a, long long b)
{
    long long ans = 1;
    while(b)
    {
        if(b&1) ans *= a;
        a *= a;
        b /= 2;
        ans %= MOD;
        a %= MOD;
    }
    return ans;
}
namespace Kara
{
    vector<__int128> naive(const vector<__int128>&A, const vector<__int128> &B)
    {
        int N = A.size();
        vector<__int128> res(N*2);
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                res[i+j] += A[i]*B[j];
        return res;
    }
    vector<__int128> minus(const vector<__int128>& A, const vector<__int128>& B)
    {
        int N = A.size();
        vector<__int128> res(N);
        for(int i=0; i<N; ++i)
            res[i] = A[i] - B[i];
        return res;
    }
    vector<__int128> multiply(const vector<__int128>& AxB, const vector<__int128>& CxD)
    {
        int N = AxB.size();
        if(N<=128) return naive(AxB, CxD);
        vector<__int128> A(N/2), B(N/2), C(N/2), D(N/2), ApB(N/2), CpD(N/2);
        for(int i=0; i<N/2; ++i)
        {
            A[i] = AxB[i+N/2];
            B[i] = AxB[i];
            C[i] = CxD[i+N/2];
            D[i] = CxD[i];
            ApB[i] = A[i] + B[i];
            CpD[i] = C[i] + D[i];
        }
        auto AC = multiply(A, C);
        auto BD = multiply(B, D);
        auto BCAD = minus(minus(multiply(ApB,CpD), AC), BD);
        vector<__int128> res(N*2);
        for(int i=0; i<N; ++i)
        {
            res[i+N] += AC[i];
            res[i+N/2] += BCAD[i];
            res[i] += BD[i];
        }
        return res;
    }
}
int dp[MAXN+2][MAXN+2]; //N character, M charset
void init()
{
    comb[0][0] = 1;
    for(int i=1; i<=MAXN; ++i)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j=1; j<i; ++j)
            comb[i][j] = (comb[i-1][j-1]+comb[i-1][j])%MOD;
    }
    fact[0] = 1, invfact[0] = 1;
    for(int i=1; i<=MAXN; ++i)
    {
        fact[i] = fact[i-1]*1LL*i%MOD;
        invfact[i] = ipow(fact[i], MOD-2);
    }
    dp[0][0] = 1;
    for(int i=0; i<=MAXN; ++i) dp[i][1] = 1;
    vector<__int128> FFF[2];
    for(int i=0; i<=MAXN; i+=2) FFF[0].push_back(invfact[i+1]);
    for(int i=0; i<=MAXN; i+=2) FFF[1].push_back(invfact[i]);
    FFF[0].resize(1024); FFF[1].resize(1024);
    for(int j=2; j<=MAXN; ++j)
    {
        vector<__int128> mm3, mm4;
        {
            vector<__int128> mm1;
            for(int i=0; i<=MAXN; i += 2) mm1.push_back(1LL*dp[i][j-1]*invfact[i]%MOD);
            mm1.resize(1024);
            mm3 = Kara::multiply(mm1, FFF[0]);
        }
        {
            vector<__int128> mm1;
            mm1.resize(1024);
            for(int i=0; i<=MAXN; i += 2) mm1.push_back(1LL*dp[i][j-1]*invfact[i]%MOD);
            mm4 = Kara::multiply(mm1, FFF[1]);
        }
        for(int i=0; i<=MAXN; i += 2)
            dp[i][j] = mm4[i/2]%MOD*fact[i]%MOD;
        for(int i=1; i<=MAXN; i += 2)
            dp[i][j] = mm3[i/2]%MOD*fact[i]%MOD*j%MOD;
    }
}


int bigsolve(int N, int M)
{
    long long ans = N*ipow(M, N)%MOD; //i = 1
    for(int i=2; i<=N; ++i)
        ans += 1LL*(N-i+1)*dp[i][M]%MOD*ipow(M, N-i)%MOD;
    ans %= MOD;
    return ans;
}
int main()
{
    init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int N, M;
        scanf("%d%d", &N, &M);
        printf("%d\n", bigsolve(N, M));
    }
}
