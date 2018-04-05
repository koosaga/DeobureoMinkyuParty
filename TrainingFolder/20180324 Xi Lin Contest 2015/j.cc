#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2010;

using base = complex<double>;

#pragma GCC target("avx2")
#include <smmintrin.h>
#include <immintrin.h>

__m256d mult(__m256d a, __m256d b){
    __m256d c = _mm256_movedup_pd(a);
    __m256d d = _mm256_shuffle_pd(a, a, 15);
    __m256d cb = _mm256_mul_pd(c, b);
    __m256d db = _mm256_mul_pd(d, b);
    __m256d e = _mm256_shuffle_pd(db, db, 5);
    __m256d r = _mm256_addsub_pd(cb, e);
    return r;
}


namespace fft
{

void fft(__m128d a[], bool invert)
{
    int n = 2048, j =0;
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
    for(int len = 2; len <= n; len <<= 1){
        double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        __m256d wlen; wlen[0] = cos(ang), wlen[1] = sin(ang);
        for(int i=0; i<n; i+=len){
            __m256d w; w[0] = 1; w[1] = 0;
            for(int j=0; j<len/2; j++){
                w = _mm256_permute2f128_pd(w, w, 0);
                wlen = _mm256_insertf128_pd(wlen, a[i+j+len/2], 1);
                w = mult(w, wlen);
                __m128d vw = _mm256_extractf128_pd(w, 1);
                __m128d u = a[i+j];
                a[i+j] = _mm_add_pd(u, vw);
                a[i+j+len/2] = _mm_sub_pd(u, vw);
            }
        }
    }
    if(invert){
        __m128d inv;
        inv[0] = inv[1] = 1.0 / n;
        for(int i=0; i<n; i++){
        a[i] = _mm_mul_pd(a[i], inv);
        }
    }
}

void fft(vector<base>& v, bool inv)
{
    int n = 2048;
    __m128d* fv = new __m128d[2048];
    for(int i=0; i<n; ++i){
        fv[i][0] = v[i].real();
        fv[i][1] = v[i].imag();
    }
    fft(fv, inv);
    for(int i=0; i<n; ++i)
        v[i] = base(fv[i][0], fv[i][1]);
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
    vector<long long> FFF[2];
    for(int i=0; i<=MAXN; i+=2) FFF[0].push_back(invfact[i+1]);
    for(int i=0; i<=MAXN; i+=2) FFF[1].push_back(invfact[i]);
    for(int i=0; i<2; i++){
        vector<base> v(2048);
        for(int j=0; j<FFF[i].size(); j++) v[j] = base(FFF[i][j] >> 15, FFF[i][j] & 32767);
        fft::fft(v, 0);
        fft::F[i] = v;
    }
    for(int j=2; j<=MAXN; ++j)
    {
        vector<long long> mm3, mm4;
        {
            vector<long long int> mm1;
            for(int i=0; i<=MAXN; i += 2) mm1.push_back(1LL*dp[i][j-1]*invfact[i]%MOD);
            mm3 = fft::multiply(mm1, 0, MOD);
        }
        {
            vector<long long int> mm1, mm2;
            for(int i=0; i<=MAXN; i += 2) mm1.push_back(1LL*dp[i][j-1]*invfact[i]%MOD);
            mm4 = fft::multiply(mm1, 1, MOD);
        }
        for(int i=0; i<=MAXN; i += 2)
            dp[i][j] = mm4[i/2]*fact[i]%MOD;
        for(int i=1; i<=MAXN; i += 2)
            dp[i][j] = mm3[i/2]*fact[i]%MOD*j%MOD;
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
