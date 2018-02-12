#include<bits/stdc++.h>
using namespace std;
long long A[10];
pair<int, int> Do(int v2, int v3, int v4, int v6, int v8, int v9)
{
    int t2=v2+2*v4+v6+3*v8;
    int t3=v3+v6+2*v9;
    return make_pair(t2, t3);
}
int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
    {
        for(int i=0; i<10; ++i)
            scanf("%lld", A+i);
        if(A[0] >= 2)
        {
            puts("TAK");
            continue;
        }
        if(A[0] >= 1)
        {
            puts("NIE");
            continue;
        }
        long long cnt2 = 0, cnt3 = 0;
        if(A[7] % 2 == 1)
        {
            puts("NIE");
            continue;
        }
        if(A[5] % 2 == 1)
        {
            puts("NIE");
            continue;
        }
        for(int i=0; i<10; ++i)
        {
            if(A[i] >= 6)
                A[i] = A[i]%2 + 6;
        }
        int s = (A[1]+A[2]+A[3]+A[4]+A[6]+A[8]+A[9])/2;
        pair<int, int> x = Do(A[2],A[3],A[4],A[6],A[8],A[9]);
        if(x.first%2==1||x.second%2==1)
        {
            puts("NIE");
            continue;
        }
        for(int v1=0;v1<=A[1];++v1)
        for(int v2=0;v2<=A[2];++v2)
        for(int v3=0;v3<=A[3];++v3)
        for(int v4=0;v4<=A[4];++v4)
        for(int v6=0;v6<=A[6];++v6)
        for(int v8=0;v8<=A[8];++v8)
        {
            int v9 = s-v1-v2-v3-v4-v6-v8;
            if (v9<0 || v9>A[9]) continue;
            pair<int, int> y = Do(v2,v3,v4,v6,v8,v9);
            if(y.first*2==x.first&&y.second*2==x.second)
            {
                puts("TAK");
                goto fuck;
            }
        }
        puts("NIE");
        fuck:
            0;
    }
}
