#include<bits/stdc++.h>
using namespace std;
using real_t = long double;
int N;
real_t a[101010], b[101010];
real_t solve(real_t x)
{
    vector<real_t> V;
    for(int i=0; i<N; ++i)
        V.push_back(a[i]*x+b[i]);
    sort(V.begin(), V.end());
    real_t mi = V[V.size()/2];
    real_t ans = 0;
    for(int i=0; i<V.size(); ++i)
        ans += abs(V[i] - mi);
    return ans;
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%Lf%Lf", a+i, b+i);
    real_t lo = -1e18;
    real_t hi = 1e18;
    for(int i=0; i<200; ++i)
    {
        real_t mi1 = (lo*2+hi)/3;
        real_t mi2 = (lo+hi*2)/3;
        real_t sm1 = solve(mi1);
        real_t sm2 = solve(mi2);
        if(sm1 < sm2)
            hi = mi2;
        else
            lo = mi1;
    }
    printf("%.12Lf\n", solve((lo+hi)/2));
}
