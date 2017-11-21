#include<bits/stdc++.h>
using namespace std;
int N; long long K;
long long int grand[1010101];
long long int ans[1010101];
long long int a, b;
int mini, maxi;
int mincnt, maxcnt, midcnt;
long long X, Xn;
bool can(long long d)
{
    __int128 dodo = (__int128) d*(N-mincnt);
    if(dodo > K) return true;
    X = (K - dodo) / N;
    Xn = (K - dodo) % N;
    long long minv = X, maxv = X+d;
    if(Xn!=0) minv++; 
    if(Xn>=mincnt+maxcnt) maxv++;
    long long mad = maxv / b;
    long long mid = (minv+a-1) / a; //mid-mad
    return (mid-mad<=d);
}
int main()
{
    scanf("%d%lld",&N,&K);
    for(int i=0; i<N; ++i)
    {
        scanf("%lld", grand+i);
    }
    a = *min_element(grand, grand+N);
    b = *max_element(grand, grand+N);
    mini = min_element(grand, grand+N)-grand;
    maxi = max_element(grand, grand+N)-grand;
    for(int i=0; i<N; ++i)
    {   
        if(grand[i]==a) ++mincnt;
        else if(grand[i]==b) ++maxcnt;
        else ++midcnt;
    }
    if(a==b)
    {
        if(K%(a*N)==0) puts("0");
        else puts("1");
        for(int i=0; i<N; ++i)
        {
            printf("%lld ", (K+i)/N);
        }
        puts("");
        return 0;
    }
    long long lo = 0;
    long long hi = 1e18;
    while(lo+1!=hi)
    {
        long long mi = (lo+hi)/2;
        if(can(mi)) hi = mi;
        else lo = mi;
    }
    printf("%lld\n", hi); can(hi);
    vector<pair<int, pair<long long, int> > > V;
    for(int i=0; i<N; ++i)
        V.emplace_back(-((grand[i] == a) || (grand[i] == b)), make_pair(grand[i],i));
    sort(V.begin(), V.end());
    
    
    for(int i=0; i<N; ++i)
    {
        if(V[i].second.first != a) ans[V[i].second.second] = X+hi;
        else ans[V[i].second.second] = X;
        if(Xn-->0) ans[V[i].second.second]++;
    }
    for(int i=0; i<N; ++i)
        printf("%lld ",ans[i]);
    puts("");
    return 0;
}

//Sn 

/*


    long long minv = ((__int128)K * (a*b+a) + (2*a*b+a+b+X*(b+1) - 1)) / (2*a*b+a+b+X*(b+1));
    long long maxv = ((__int128)K * (a*b+b)) / (2*a*b+a+b+X*(b+1));
    
    printf("%lld %lld %lld<<\n", X, minv, maxv);
    
    ans[mini] = minv, ans[maxi] = maxv;
    if(X != 0)
    {
        long long nK = K - minv - maxv;
        long long K1 = nK / X;
        long long K2 = nK % X;
        for(int i=0; i<N; ++i)
        {
            if(i==mini)
            {
                ans[i] = minv; continue;
            }
            if(i==maxi)
            {
                ans[i] = maxv; continue;
            }
            long long mv = min(K2, grand[i]);
            K2 -= mv;
            ans[i] = K1 * grand[i] + mv;
        }
    }
    long long md = (minv+a-1)/a - maxv/b;
    printf("%lld\n", md);
    for(int i=0; i<N; ++i) printf("%lld ", ans[i]);
    puts("");
    
*/
