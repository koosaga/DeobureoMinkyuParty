#include<bits/stdc++.h>
using namespace std;
int N, K;
set<int> Row; long long RowSum;
set<int> Col; long long ColSum;
int main()
{
    freopen("adjustment.in", "r", stdin);
    freopen("adjustment.out", "w", stdout);
    scanf("%d%d", &N, &K);
    RowSum = ColSum = 1LL * N * (N+1) / 2;
    for(int i=0; i<K; ++i)
    {
        char t; int x;
        scanf(" %c%d", &t, &x);
        if(t=='R')
        {
            if(Row.find(x) != Row.end())
                puts("0");
            else
            {
                printf("%lld\n", 1LL*(N-Col.size())*x + ColSum);
                RowSum -= x;
            }
            Row.insert(x);
        }
        else
        {
            if(Col.find(x) != Col.end())
                puts("0");
            else
            {
                printf("%lld\n", 1LL*(N-Row.size())*x + RowSum);
                ColSum -= x;
            }
            Col.insert(x);
        }
    }
    return 0;
}
