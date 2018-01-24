#include <bits/stdc++.h>
using namespace std;

void EE(long long a, long long b, long long& x, long long& y)
{
    if(a==0)
        x = 0, y = 1;
    else if(b==0)
        x = 1, y = 0;
    else
    {
        EE(b, a%b, y, x);
        y -= (a/b)*x;
    }
}

void tmain()
{
    long long ax, ay, bx, by, k;
    scanf("%lld%lld%lld%lld%lld", &ax, &ay, &bx, &by, &k);
    long long gx, gy;
    EE(abs(bx-ax), abs(by-ay), gy, gx);
    if(bx-ax<0) gy *= -1;
    if(by-ay>=0) gx *= -1;
    for(int i=0; i<k; ++i)
    {
        printf("%lld %lld\n", ax+gx+(bx-ax)*i, ay+gy+(by-ay)*i);
    }
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    for(int i=0; i<T; ++i)
        tmain();
}
