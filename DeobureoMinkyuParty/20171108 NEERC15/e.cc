#include<bits/stdc++.h>
using namespace std;
int N, K;
vector<int> arr[10];
int tp[10];
int main()
{
    freopen("easy.in","r",stdin);
    freopen("easy.out", "w", stdout);
    int ans = 0;
    int cnt = 0;
    int maxv = 0;
    scanf("%d%d",&N,&K);
    for(int i=0; i<N; ++i)
    {
        int t; scanf("%d", &t);
        for(int j=0; j<t; ++j)
        {
            int x; scanf("%d", &x);
            arr[i].push_back(x);
        }
    }
    for(int i=0;cnt<K;i=(i+1)%N)
    {
        int targ;
        if(tp[i]>=arr[i].size()) targ = 50;
        else targ = arr[i][tp[i]++];
        if(targ!=50&&targ<ans) continue;
        maxv = targ;
        //printf("%d\n", targ);
        ans += targ;
        ++cnt;
    }
    printf("%d\n", ans);
}
