#include<bits/stdc++.h>
int N;
char a[101010];
const int mod = 1e9+7;
int main()
{
    scanf("%s", a);
    N = strlen(a);
    long long p = 0;
    long long ans = 0;
    for(int i=0; i<N; ++i)
    {
        int multiplier = abs((N-i-1)*9-1);
        //printf("%lld %d\n", p, multiplier);
        ans += (p* 9 + a[i] - '0') * multiplier;
        
        ans %= mod;
        
        p *= 10;
        p += a[i] - '0';
        p %= mod;
    }
    ans = ans + mod - 1;
    ans %= mod;
    printf("%lld\n", ans);
}
