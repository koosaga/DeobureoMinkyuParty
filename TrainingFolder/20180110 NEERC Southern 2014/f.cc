#include<bits/stdc++.h>
using namespace std;
const int MAXN = 262144;
int N, K;
int idx[MAXN*2];
int arr[MAXN];
void setv(int a, int v)
{
    a += MAXN; idx[a] = v;
    while(a = a/2)
        idx[a] = idx[2*a+1] + idx[2*a];
}
int getv(int a, int b)
{
    a += MAXN; b += MAXN;
    int ans = 0;
    while(a<=b)
    {
        if(a%2==1) ans += idx[a++];
        if(b%2==0) ans += idx[b--];
        a/=2; b/=2;
    }
    return ans;
}
int mK[MAXN];
int prmax[MAXN];
int sfmax[MAXN];
int solve()
{
    for(int i=0; i<N; ++i) setv(i, arr[i]);
    for(int i=0; i<=N-K; ++i)
        mK[i] = getv(i, i+K-1);
    prmax[0] = mK[0];
    for(int i=1; i<=N-K; ++i)
        prmax[i] = max(prmax[i-1], mK[i]);
    sfmax[N-K   ] = mK[N-K];
    for(int i=N-K-1; i>=0; --i)
        sfmax[i] = max(sfmax[i+1], mK[i]);
    int ans = 0;
    for(int i=0; i<=N-2*K; ++i)
        ans = max(ans, prmax[i] + sfmax[i+K]);
    return ans;
}
int main()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i) scanf("%d", arr+i);
    if(N<=2*K)
    {
        int ans = 0;
        for(int i=0; i<N; ++i) ans += arr[i];
        printf("%d\n", ans);
        return 0;
    }
    printf("%d\n", solve());
}
