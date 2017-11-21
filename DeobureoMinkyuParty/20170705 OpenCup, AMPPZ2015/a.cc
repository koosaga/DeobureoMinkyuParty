#include<bits/stdc++.h>
using namespace std;
map<int, int> M;
int N;
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        char d;
        int a;
        scanf(" %c%d", &d, &a);
        if(d=='+') M[a] = M[a]+1;
        else
        {
            M[a] = M[a]-1;
            if(M[a]==0) M.erase(a);
        }
        double now = 1;
        double ans = 0;
        for(auto x: M)
        {
            if(now>1e18) break;
            now *= x.second+1;
            ans += (double)x.first * x.second / now;
        }
        if(now < 1e18)
            ans = ans * now/(now-1);
        printf("%.12lf\n", ans);
    }
}
