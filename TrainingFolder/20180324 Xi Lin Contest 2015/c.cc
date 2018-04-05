#include<bits/stdc++.h>
using namespace std;

vector<int> store[100];
bool fuck[100];
int ms[100];
void mysolve(int N, int M)
{
    memset(fuck, 0, sizeof(fuck));
    memset(ms, 0, sizeof(ms));
    int desired = (N+1)*N/2/M;
    //printf("%d\n", desired);
    for(int i=0; i<M; ++i)
    {
        for(int j=N; j>=1; --j)
        {
            if(!fuck[j] && ms[i] + j <= desired)
            {
                fuck[j] = true;
                ms[i] += j; 
                store[i].push_back(j);
                //printf("%d on %d -> %d\n", j, i, ms[i]);
            }
        }
        assert(ms[i] == desired);
    }
}
void solve(int N, int M)
{
    if((1LL*N*(N+1)/2)%M != 0)
    {
        puts("NO"); return;
    }
    if(N<2*M-1)
    {
        puts("NO"); return;
    }
    for(int i=0; i<M; ++i) store[i].clear();
    int oN = N;
    while(N-2*M >= 2*M-1) N -= 2*M;
    mysolve(N, M);
    for(int i=N; i<oN; )
    {
        for(int j=0; j<M; ++j)
            store[j].push_back(++i);
        for(int j=M-1; j>=0; --j)
            store[j].push_back(++i);
    }
    puts("YES");
    for(int i=0; i<M; ++i)
    {
        printf("%d ", (int)store[i].size());
        for(auto x: store[i]) printf("%d ", x);
        puts("");
    }
    return;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int N, M;
        scanf("%d%d", &N, &M);
        solve(N, M);
    }
}
