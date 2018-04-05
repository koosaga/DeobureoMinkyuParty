#include<bits/stdc++.h>
using namespace std;
int N, M, Q;
pair<int, int> ans[101];

inline bool comp(const pair<int, int>& A, const pair<int, int>& B)
{
    long long AA = 1LL*A.first*B.second;
    long long BB = 1LL*A.second*B.first;
    if(AA>BB) return true;
    if(AA<BB) return false;
    return A.first+A.second < B.first+B.second;
    
}
pair<int, int> Varr[1020202];
pair<int, int> mysolve(int size, int tp)
{
    pair<int, int> dest;
    if(tp<N) dest = make_pair(M-1, tp);
    else dest = make_pair(N+M-2-tp, N-1);
    
    pair<int, int> pdest;
    int ptp = tp-1;
    if(ptp<N) pdest=make_pair(M-1, ptp);
    else pdest = make_pair(N+M-2-ptp, N-1);
    
    
    int vptr = 0;
    
    if(tp == 0)
    {
        for(int i=1; i<M; ++i) Varr[vptr++] = make_pair(i, 0);        
    }
    else if(tp==N+M-2)
    {
        for(int i=1; i<N; ++i) Varr[vptr++] = make_pair(0, i);
    }
    else
    {
        for(int i=1; i<M; ++i)
        {
            for(long long j=(1LL*i*pdest.second)/pdest.first+1;
                j<=min(N-1LL, 1LL*i*dest.second/dest.first); ++j)
                    Varr[vptr++] = make_pair(i, j);
        }
    }
    assert(vptr <= 1020202);
    
    //printf("%d %d\n", size, tp);
    //printf("(%d, %d)\n", dest.first, dest.second);
    //puts("");
    //sort(V.begin(), V.end(), comp);
    //for(auto x: V)
    //printf("(%d, %d)\n", x.first, x.second);
    //puts("");
    auto b = Varr;
    auto e = Varr+vptr;
    auto k = e-size-1;
    nth_element(b, k, e, comp);
    //printf("(%d, %d)\n", k->first, k->second);
    //puts("");
    return *k;
}

long long getPoint(int tp)
{
    if(tp == 0) return M;
    pair<int, int> dest;
    long long Area2;
    long long Exterior;
    if(tp<N)
    {
        dest = make_pair(M-1, tp);
        Area2 = 1LL*tp*(M-1);
        Exterior = __gcd(dest.first, dest.second) - 1
                + tp + M;
    }
    else
    {
        dest = make_pair(N+M-2-tp, N-1);
        Area2 = 1LL*(M-1)*(N-1)+1LL*(tp-(N-1))*(N-1);
        Exterior = __gcd(dest.first, dest.second) - 1
                + tp + M;
    }
    long long Points = (Area2+Exterior+2)/2;
    return Points;
}

void solve(vector<pair<long long, int> > V)
{
    int tp1 = 0;
    int tp2 = 0;
    while(tp1<=N+M-2)
    {
        long long inside = getPoint(tp1);
        while(tp2 < V.size() && V[tp2].first<inside)
        {
            ans[V[tp2].second] = mysolve(inside-V[tp2].first-1, tp1);
            ++tp2;
        }
        ++tp1;
    }
}
int main()
{
    scanf("%d%d%d", &N, &M, &Q);
    if(M==1)
    {
        for(int i=0; i<Q; ++i)
        {
            int x; scanf("%d", &x);
            printf("%d %d\n", x+1, 1);
        }
        return 0;
    }
    vector<pair<long long, int> > V;
    for(int i=0; i<Q; ++i)
    {
        long long x;
        scanf("%lld", &x);
        V.emplace_back(x, i);
    }
    sort(V.begin(), V.end());
    solve(V);
    for(int i=0; i<Q; ++i)
        printf("%d %d\n", ans[i].second+1,ans[i].first+1 );
}
