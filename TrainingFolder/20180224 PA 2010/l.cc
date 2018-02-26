#include<bits/stdc++.h>
using namespace std;

const int MAXN = 505050;
vector<int> incl[MAXN];
int minv[MAXN];
int N;
int u[MAXN], v[MAXN];
int main()
{
    int N;
    scanf("%d", &N);
    for(int i=0; i<N-1; ++i)
    {
        scanf("%d%d", u+i, v+i);
        incl[u[i]].push_back(i);
        incl[v[i]].push_back(i);
    }
    for(int i=1; i<=N; ++i)
    {
        incl[i].push_back(N+1);
        incl[i].push_back(N+2);
    }
    for(int i=1; i<=N; ++i)
    {
        for(int j=0; j<incl[i].size(); ++j)
        {
            if(incl[i][j]%2 != incl[i][0]%2)
            {
                minv[i] = incl[i][j-1];
                break;
            }
        }
    }
    for(int i=0; i<N-1; ++i)
    {
        if(minv[u[i]] < i && minv[v[i]] < i)
        {
            printf("%d\n", i+1);
            return 0;
        }
    }
    puts("-1");
    return 0;
    
    
}
