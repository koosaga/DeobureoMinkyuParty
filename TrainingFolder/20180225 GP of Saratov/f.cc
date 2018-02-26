#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101010;
int N, K;
long long a[MAXN];
long long solve(long long x)
{
    vector<long long> tar;
    for(int i=0; i<N; ++i)
        tar.push_back(__gcd(x, a[i]));
    sort(tar.begin(), tar.end());
    vector<pair<long long, int> > V;
    long long p = tar[0];
    int c = 1;
    for(int i=1; i<N; ++i)
    {
        if(p != tar[i])
        {
            V.emplace_back(p, c);
            p = tar[i];
            c = 0;
        }
        c++;
    }
    V.emplace_back(p, c);
    for(int i=V.size()-1; i>=0; --i)
    {
        int cnt = 0;
        for(int j=i; j<V.size(); ++j)
        {
            if(V[j].first%V[i].first == 0) cnt += V[j].second;
        }
        //printf(">%lld %d\n", V[i].first, cnt);
        if(cnt >= N-K) return V[i].first;
    }
    return 1;
}
int main()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i)
        scanf("%lld", a+i);
    
    mt19937 rng(0x14004);
    long long ans = 0;
    while(clock()<3*CLOCKS_PER_SEC)
    {
    ans = max(ans, 
        solve(a[uniform_int_distribution<int>(0, N-1)(rng)]));
    }
    printf("%lld\n", ans);
    
}
