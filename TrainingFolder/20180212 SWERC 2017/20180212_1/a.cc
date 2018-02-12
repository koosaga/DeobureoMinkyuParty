#include<bits/stdc++.h>
using namespace std;
vector<int> V;
int N, M;
int a[2020];
int b[2020];
int main()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<N; ++i)
        scanf("%d", a+i);
    for(int i=0; i<M; ++i)
        scanf("%d", b+i);
    for(int i=0; i<N; ++i)
        for(int j=0; j<M; ++j)
            if(b[j]>=a[i]) V.push_back(b[j]-a[i]);
    V.push_back(-1);
    V.push_back((int)1.5e9);
    sort(V.begin(), V.end());
    if(V.size() == 2)
    {
        puts("0");
        return 0;
    }
    int maxv = 0;
    int maxc = 0;
    int cnt = 0;
    for(int i=1; i<V.size(); ++i)
    {
        if(V[i]!=V[i-1])
        {
            if(maxc<cnt)
            {
                maxc = cnt;
                maxv = V[i-1];
            }
            cnt = 1;
        }
        else ++cnt;
    }
    printf("%d\n", maxv);
    return 0;
}
