#include<bits/stdc++.h>
using namespace std;
long long solve(long long N, long long K)
{
    N -= 2*K;
    if(N<0) return 0;
    long long v1 = N/(2*K);
    long long v2 = N%(2*K);
    return (v1*K + max(0LL, v2-K+1))*K;
}
int main()
{
    int N;
    scanf("%d", &N);
    long long ans = 0;
    for(int i=0; i<30; ++i)
        ans += solve(N, (1LL<<i));
    printf("%lld\n", ans);
}
