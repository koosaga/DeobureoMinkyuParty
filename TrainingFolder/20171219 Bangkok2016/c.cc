#include<bits/stdc++.h>
using namespace std;

int moe(int a)
{
    int cnt = 1;
    if(a%2==0)
    {
        if(a%4==0) return 0;
        a /= 2; cnt *= -1;
    }
    for(int i=3; i*i<=a; ++i)
    {
        if(a%i==0)
        {
            if(a%(i*i)==0) return 0;
            a /= i; cnt *= -1;
        }
    }
    if(a != 1) cnt *= -1;
    return cnt;
}

int main()
{
    int T = 5;
    for(int i=0; i<T; ++i)
    {
        int N; scanf("%d", &N);
        __int128 ans = 0;
        for(int i=1; i<=N; ++i)
        {
            __int128 v = (N/i); v *= v; v *= v;
            ans += moe(i) * v;
        }
        std::vector<int> a;
        while(ans)
        {
            a.push_back(ans%10);
            ans /= 10;
        }
        reverse(a.begin(), a.end());
        for(int x: a) printf("%d", x);
        puts("");
    }
}
