#include<bits/stdc++.h>
using namespace std;
long long get_score(long long a, long long b, long long c)
{
    return 1LL*a*a+1LL*b*b+1LL*c*c+7LL*min({a, b, c});
}
long long solve(int _a, int _b, int _c, int d)
{
    long long a = max({_a, _b, _c});
    long long c = min({_a, _b, _c});
    long long b = (long long)_a+_b+_c-a-c;
    long long ans = get_score(a+d, b, c);
    if(d<100)
    {
        for(int i=0; i<=d; ++i)
            for(int j=0; j<=d-i; ++j)
            {
                int k = d-i-j;
                ans = max(ans, get_score(a+i, b+j, c+k));
            }
    }
    return ans;
}
int main()
{
    int T; scanf("%d", &T);
    for(int i=0; i<T; ++i)
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%lld\n", solve(a, b, c, d));
    }
}
