#include<bits/stdc++.h>
using namespace std;
int N;
int d[2020202];
vector<pair<int, int> > ans;
int main()
{
    scanf("%d", &N);
    long long k = 0;
    for(int i=1; i<=N; ++i)
    {
        scanf("%d", d+i);
        k += d[i];
    }
    if(k != 2*N-2)
    {
        puts("BRAK");
        return 0;
    }
    set<pair<int, int> > S;
    for(int i=1; i<=N; ++i)
        S.insert(make_pair(d[i], i));
    for(int i=0; i<N-1; ++i)
    {
        int minv, mini; tie(minv, mini) = *S.begin();
        int maxv, maxi; tie(maxv, maxi) = *S.rbegin();
        S.erase(S.begin()); S.erase(*S.rbegin());
        ans.emplace_back(mini, maxi);
        minv--; maxv--;
        if(minv) S.insert(make_pair(minv, mini));
        if(maxv) S.insert(make_pair(maxv, maxi));
    }
    for(auto x: ans)
    {
        printf("%d %d\n", x.first, x.second);
    }
}
