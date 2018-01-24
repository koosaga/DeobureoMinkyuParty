#include<bits/stdc++.h>
using namespace std;
int N, M;
const int MAXN = 131072;
int indeg[2*MAXN];
vector<int> conn[2*MAXN];
int main()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        char a; int b; char c; int d;
        scanf(" %c%d %c%d", &a, &b, &c, &d);
        if(a=='+') b += MAXN;
        if(c=='+') d +=MAXN;
        conn[b].push_back(d^MAXN);
        conn[d].push_back(b^MAXN);
        indeg[d^MAXN]++;
        indeg[b^MAXN]++;
        //a b > -c d
        //c d > -a b
    }
    queue<int> Q;
    for(int i=0; i<2*MAXN; ++i)
        if(!indeg[i])
            Q.push(i);
    int cnt = 0;
    while(!Q.empty())
    {
        ++cnt;
        int x = Q.front(); Q.pop();
        for(auto y: conn[x])
        {
            indeg[y]--;
            if(!indeg[y])
                Q.push(y);
        }
    }
    if(cnt==2*MAXN) puts("TAK");
    else puts("NIE");
}
