#include<bits/stdc++.h>
using namespace std;
struct mat
{
    int dat[2][2];
};
const int MOD = 1e9+7;
int det(mat a)
{
    long long ans = 1LL*a.dat[0][0]*a.dat[1][1] - 1LL*a.dat[0][1]*a.dat[1][0];
    ans %= MOD; if(ans<0) ans += MOD;
    return ans;
}

mat mul(mat a, mat b)
{
    mat c;
    c.dat[0][0] = (1LL*a.dat[0][0]*b.dat[0][0] + 1LL*a.dat[0][1]*b.dat[1][0])%MOD;
    c.dat[0][1] = (1LL*a.dat[0][0]*b.dat[0][1] + 1LL*a.dat[0][1]*b.dat[1][1])%MOD;
    c.dat[1][0] = (1LL*a.dat[1][0]*b.dat[0][0] + 1LL*a.dat[1][1]*b.dat[1][0])%MOD;
    c.dat[1][1] = (1LL*a.dat[1][0]*b.dat[0][1] + 1LL*a.dat[1][1]*b.dat[1][1])%MOD;
    return c;
}

mat ipow(mat a, long long int b)
{
    if(b==1) return a;
    mat ans = ipow(a, b/2);
    ans = mul(ans, ans);
    if(b%2==1) ans = mul(ans, a);
    return ans;
}

int ipow(int a, long long int b)
{
    assert(a != 0);
    if(b==0) return 1;
    long long ans = ipow(a, b/2);
    ans *= ans; ans %= MOD;
    if(b%2==1) ans *= a;
    ans %= MOD;
    return ans;
}

void pmat(mat a)
{
    printf("%d %d\n%d %d\n", a.dat[0][0], a.dat[0][1], a.dat[1][0], a.dat[1][1]);
    
}

int invdet(mat a)
{
    return ipow(det(a), MOD-2);
}

mat inv(mat a)
{
    mat inv;
    int ans = invdet(a);
    inv.dat[0][0] = 1LL*a.dat[1][1]*ans%MOD;
    inv.dat[0][1] = -1LL*a.dat[0][1]*ans%MOD;
    inv.dat[1][0] = -1LL*a.dat[1][0]*ans%MOD;
    inv.dat[1][1] = 1LL*a.dat[0][0]*ans%MOD;
    if(inv.dat[0][1]<0) inv.dat[0][1] += MOD;
    if(inv.dat[1][0]<0) inv.dat[1][0] += MOD;
    return inv;
}
int main()
{
    int T;
    scanf("%d", &T);
    for(int i=0; i<T; ++i)
    {
        long long l, r; int k;
        scanf("%lld%lld%d", &l, &r, &k);
        mat X, Y;
        X.dat[0][0] = X.dat[0][1] = X.dat[1][0] = 1; X.dat[1][1] = 0;
        Y = ipow(X, k);
        r = r / k;
        l = (l-1)/k;
        //pmat(X); pmat(Y);
        mat YL = ipow(Y, l+1);
        YL.dat[0][0] = (YL.dat[0][0] + MOD - 1) % MOD; YL.dat[1][1] = (YL.dat[1][1] + MOD - 1) % MOD;
        mat YR = ipow(Y, r+1);
        YR.dat[0][0] = (YR.dat[0][0] + MOD - 1) % MOD; YR.dat[1][1] = (YR.dat[1][1] + MOD - 1) % MOD;
        

        
        mat YmI = Y;
        YmI.dat[0][0] = (YmI.dat[0][0] + MOD - 1) % MOD; YmI.dat[1][1] = (YmI.dat[1][1] + MOD - 1) % MOD;
        YmI= inv(YmI);
        //        pmat(YL); pmat(YR); pmat(YmI);
        YL = mul(YL, YmI);
        YR = mul(YR, YmI);
        long long ans = YR.dat[0][0] + YR.dat[0][1] - YL.dat[0][0] - YL.dat[0][1];
        ans %= MOD; if(ans<0) ans += MOD;
        printf("Case %d: %lld\n", i+1, ans);
    }
    return 0;
}



















