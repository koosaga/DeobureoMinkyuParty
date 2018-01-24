#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> >V;
int main()
{
    int X;
    scanf("%d", &X);
    int a, b;
    while(2==scanf("%d%d", &a, &b))
        V.emplace_back(a, b);
    V.push_back(V[0]);
    V.push_back(V[1]);
    int N = V.size()-2;
    int ans = 0;
    for(int i=0; i<N; ++i)
    {
        assert(0<=V[i].first && V[i].first<=10000);
        assert(0<=V[i].second && V[i].second<=10000);
        int a = V[i].first-V[i+1].first;
        int b = V[i].second-V[i+1].second;
        int c = V[i+2].first-V[i+1].first;
        int d = V[i+2].second-V[i+1].second;
        if(a*c+b*d==0 && a*d-b*c<0) ++ ans;
    }
    printf("%d %d\n", X, ans);
    assert(X==ans);
}
