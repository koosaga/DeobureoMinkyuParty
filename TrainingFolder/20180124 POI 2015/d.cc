#include<bits/stdc++.h>
using namespace std;
const int THRES = 25;
const int OVERGROWN[31] = {2, 3, 6, 7, 8, 11, 12, 15, 18, 19, 22, 23, 24, 27, 28, 31, 32, 33, 43, 44, 47, 48, 60, 67, 72, 76, 92, 96, 108, 112, 128};
long long k[131010];
long long mthres[131010];
int main()
{
    memset(k, 0x3f, sizeof(k));
    k[0] = 0;
    for(int i=1; i<=THRES*2; ++i)
    {
        for(int j=THRES*THRES*THRES*8; j>=0; --j)
        {
            k[j+i*i] = min(k[j+i*i], max(k[j], 1LL*i));
        }
    }
    mthres[0] = 0;
    long long cnt = 0;
    long long ans = 0;
    for(int i=1; i<=THRES; ++i)
    {
        for(int j=cnt+1; j<=cnt+i*i; ++j)
        {
            mthres[j] = i;
            if(k[j] > mthres[j])
                ++ans;
        }
        cnt += i*i;
    }
    long long int N; scanf("%lld", &N);
    if(N<25*26*51/6)
    {
        if(k[N]>0x3f3f3f3f)
            printf("- ");
        else
            printf("%lld ",k[N]);
        int a = 0;
        for(int i=0; i<=N; ++i)
            if(k[i]>mthres[i])
                ++a;
        printf("%d\n", a);
        return 0;
    }
    
    int i;
    for(i=THRES+1;cnt<N;++i)
    {
        ans += 31; cnt += 1LL*i*i;
    }
    --i;
    for(int x=0; x<31; ++x)
    {
        if(cnt - OVERGROWN[x] > N)
            --ans;
        else if(cnt - OVERGROWN[x] == N)
        {
            ++i;
        }
        else break;
    }
    if(N<10000 && k[N] <0xf3f3f3)
        i = k[N];
    printf("%d %lld\n", i, ans);
}
