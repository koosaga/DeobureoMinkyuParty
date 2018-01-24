#include <bits/stdc++.h>
using namespace std;
const int MAXN = 262144;

long long idx[2*MAXN];
long long lazy[2*MAXN];
int N, K;
void push(int id, int le)
{
    if(lazy[id] ==0x3f3f3f3f) return;
    idx[id] = lazy[id] * le;
    if(id<MAXN)
    {
        lazy[2*id] = lazy[id];
        lazy[2*id+1] = lazy[id];
    }
    lazy[id] = 0x3f3f3f3f;
}
long long getv(int id, int l, int r, int a, int b)
{
    if(a>b) return 0;
    push(id,r-l+1);
    if(r<a || l>b) return 0;
    if(a<=l && r<=b) return idx[id];
    int m = (l+r)/2;
    return getv(2*id, l, m, a, b)
        + getv(2*id+1, m+1, r, a, b);
}
void setv(int id, int l, int r, int a, int b, long long v)
{
    if(a>b) return;
    push(id,r-l+1);
    if(r<a || l>b) return;
    if(a<=l && r<=b)
    {
        lazy[id] = v;
        push(id, r-l+1);
        return;
    }
    int m = (l+r)/2;
    setv(2*id, l, m, a, b, v);
    setv(2*id+1, m+1, r, a, b, v);
    idx[id] = idx[2*id] + idx[2*id+1];
    return;
}

int arr[MAXN];
int main()
{
    scanf("%d%d", &N, &K);
    long long int minv = 0;
    for(int i=0; i<N; ++i)
    {
        scanf("%d", arr+i);
        setv(1, 0, MAXN-1, i, i, arr[i]);
        minv = min(minv, 1LL*arr[i]);
    }
    long long ans = 0;
    for(int i=0; i<=N-K; ++i)
    {
        long long r = getv(1, 0, MAXN-1, i, i+K-1);
        if(r<0) continue;
        long long targ = r-(-1);
        ans += targ;
        int lo = i-1;
        int hi = i+K;
        while(lo+1!=hi)
        {
            int mi = (lo+hi)/2;
            long long x = getv(1, 0, MAXN-1, i, mi);
            if(x+(i+K-mi-1)*minv < 0) lo = mi;
            else hi = mi;
        }
        long long t = getv(1, 0, MAXN-1, lo+2, i+K-1) - (i+K-lo-2)*minv;
        targ-=t;
        long long arrlo = getv(1, 0, MAXN-1, lo+1, lo+1);
        setv(1, 0, MAXN-1, lo+2, i+K-1, minv);
        setv(1, 0, MAXN-1, lo+1, lo+1, arrlo-targ);

    
    }
    printf("%lld\n", ans);
    for(int i=0; i<N; ++i)
        printf("%lld ", getv(1, 0, MAXN-1, i, i));
    puts("");
    return 0;
}



















