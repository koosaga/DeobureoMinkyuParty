#include<bits/stdc++.h>
using namespace std;
inline long long next_perm(long long v)
{
    long long t = v | (v-1);
    return (t+1) | (((~t & -~t) -1) >> (__builtin_ctzll(v)+1));
}
void method1(long long n, long long m, int nbit)
{ // O(m)
    for(int i=1; i<=nbit; ++i)
    {
        long long gen = (1LL<<i)-1;
        long long ans = 1e16;
        long long cnt = 0;
        for(;gen<(1LL<<nbit); gen = next_perm(gen))
        {
            if((n^gen)%m==0)
            {
                ans = min(ans, n^gen);
                cnt++;
            }
        }
        if(cnt)
        {
            printf("%d %lld %lld\n", i, cnt, ans);
            return ;
        }
    }   
}

void method2(long long n, long long m, int nbit)
{   // O(n/m)
    int ans = nbit;
    long long cnt = 0;
    long long np = 0;
    for(long long idx = 0; idx<(1LL<<nbit); idx += m)
    {
        int a = __builtin_popcountll(idx^n);
        if(ans > a)
        {
            cnt = 0;
            ans = a;
            np = idx;
        }
        if(ans == a)
            ++cnt;
    }
    printf("%d %lld %lld\n", ans, cnt, np);
    return;
}

int main()
{
    long long n, m;
    scanf("%lld%lld", &n, &m);
    if(m==0)
    {
        printf("%lld\n", next_perm(n));
        return 0;    
    }
    if(n%m==0)
    {
        printf("%lld %lld %lld\n", 0LL, 1LL, n);
        return 0;
    }
    
    int x = 0;
    while(n >= (1LL<<x)) ++x;
    if(n/m >= (long long )1e8) method1(n, m, x);
    else method2(n, m, x);
}
