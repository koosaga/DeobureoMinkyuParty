#include<bits/stdc++.h>
using namespace std;

#define WIN 1
#define LOSE 0
const int MAXSZ = 3095037;

using quad = tuple<int, int, int, int>;


quad state[MAXSZ];

int state2int(quad x)
{
    return lower_bound(state, state+MAXSZ, x) - state;
}
int state2int(int a, int b, int c, int d)
{
    return state2int(quad(a,b,c,d));
}
quad int2state(int sz){ return state[sz]; }


//quad, parity
int dp[MAXSZ][2];

/////////////0//////1//////2//////3//////////
int bktk(int a, int b, int c, int d, int par)
{
    //printf("<%d %d %d %d %d>\n", a, b, c, d, par);
    int ST = state2int(a,b,c,d);
    if(dp[ST][par] != -1)
        return dp[ST][par];
    if(a+b+c+d <= 1) return dp[ST][par] = LOSE;
    if(a>=2 &&         bktk(a-2+1, b, c, d, par^1)   == LOSE) return dp[ST][par] = WIN;
    if(b>=2 &&         bktk(a, b-2, c+1, d, par^0)   == LOSE) return dp[ST][par] = WIN;
    if(c>=2 &&         bktk(a+1, b, c-2, d, par^1)   == LOSE) return dp[ST][par] = WIN;
    if(d>=2 &&         bktk(a, b, c+1, d-2, par^0)   == LOSE) return dp[ST][par] = WIN;
    if(a>=1 && b>=1 && bktk(a-1, b-1+1, c, d, par^1) == LOSE) return dp[ST][par] = WIN;
    if(a>=1 && c>=1 && bktk(a-1, b, c-1+1, d, par^1) == LOSE) return dp[ST][par] = WIN;
    if(a>=1 && d>=1 && bktk(a-1, b, c, d-1+1, par^1) == LOSE) return dp[ST][par] = WIN;
    if(b>=1 && c>=1 && bktk(a, b-1, c-1, d+1, par^1) == LOSE) return dp[ST][par] = WIN;
    if(b>=1 && d>=1 && bktk(a+1, b-1, c, d-1, par^0) == LOSE) return dp[ST][par] = WIN;
    if(c>=1 && d>=1 && bktk(a, b+1, c-1, d-1, par^1) == LOSE) return dp[ST][par] = WIN;
    
    if(par==1)
        if(bktk(a, b, c, d, par^1) == LOSE) return dp[ST][par] = WIN;
    
    return dp[ST][par] = LOSE;

}
void init()
{
    //a 4 b 1 c 2 d 3
    int tp = 0;
    for(int a=0; a<=200/4; ++a)
        for(int b=0; b<=(200-4*a)/1; ++b)
            for(int c=0; c<=(200-4*a-1*b)/2; ++c)
                for(int d=0; d<=(200-4*a-1*b-2*c)/3; ++d)
                    state[tp++] = quad(a, b, c, d);
    assert(tp == MAXSZ);
}
int N, M;
int adj[201][201];
int mod4[4];
int ufd[201];
int sz[201];
set<pair<int, int> > S;

int Find(int u)
{
    if(ufd[u] == u) return u;
    else return ufd[u] = Find(ufd[u]);
}
pair<int, int> pp(int a, int b)
{
    return make_pair(min(a, b), max(a, b));
}
void merge(int u, int v)
{
    assert(1<=u && u<=N && 1<=v&& v<=N);
    int ru = u, rv = v;
    u = Find(u);
    v = Find(v);
    if(u == v)
    {
        S.erase(pp(ru, rv));
        return;
    }
    else
    {
        for(int i=1; i<=N; ++i)
            for(int j=1; j<=N; ++j)
                if(Find(i) == u && Find(j) == v)
                    S.insert(pp(i, j));
        S.erase(pp(ru, rv));
        mod4[sz[u]%4]--; mod4[sz[v]%4]--;
        mod4[(sz[u]+sz[v])%4]++;
        ufd[v] = u;
        sz[u] = sz[u] + sz[v];
        sz[v] = 0;
    }
}
void mymerge(int a, int b)
{
    int va = 0, vb = 0;
    for(int i=1; i<=N; ++i)
        if(sz[i]!=0 && sz[i]%4==a)
            va = i;
    for(int i=N; i>=1; --i)
        if(sz[i]!=0 && sz[i]%4==b)
            vb = i;
    assert(va !=0 && vb != 0);
    merge(va, vb);
    printf("%d %d\n", va, vb);
    return;
}
int mymerge()
{
    int a, b; tie(a, b) = *S.begin(); S.erase(S.begin());
    merge(a, b);
    assert(1 <=a && a<=N && 1<=b&&b<=N);
    printf("%d %d\n", a, b);
}
int main()
{
    memset(dp, -1, sizeof(dp));
    init();
    scanf("%d%d", &N, &M);
    mod4[1] = N;
    for(int i=1; i<=N; ++i)
    {
        ufd[i] = i;
        sz[i] = 1;
    }
    for(int i=0; i<M; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
        merge(u, v);
    }
    bool myturn = (bktk(mod4[0], mod4[1], mod4[2], mod4[3], S.size()%2) == WIN);
    if(myturn) puts("1");
    else puts("2");
    fflush(stdout);
    while(true)
    {
        int a = mod4[0], b = mod4[1], c = mod4[2], d = mod4[3], par = S.size()%2;
        if(a+b+c+d == 1) return 0;
        if(myturn)
        {
            if(a>=2 &&         bktk(a-2+1, b, c, d, par^1)   == LOSE) mymerge(0, 0);
            else if(b>=2 &&         bktk(a, b-2, c+1, d, par^0)   == LOSE) mymerge(1, 1);
            else if(c>=2 &&         bktk(a+1, b, c-2, d, par^1)   == LOSE) mymerge(2, 2);
            else if(d>=2 &&         bktk(a, b, c+1, d-2, par^0)   == LOSE) mymerge(3, 3);
            else if(a>=1 && b>=1 && bktk(a-1, b-1+1, c, d, par^1) == LOSE) mymerge(0, 1);
            else if(a>=1 && c>=1 && bktk(a-1, b, c-1+1, d, par^1) == LOSE) mymerge(0, 2);
            else if(a>=1 && d>=1 && bktk(a-1, b, c, d-1+1, par^1) == LOSE) mymerge(0, 3);
            else if(b>=1 && c>=1 && bktk(a, b-1, c-1, d+1, par^1) == LOSE) mymerge(1, 2);
            else if(b>=1 && d>=1 && bktk(a+1, b-1, c, d-1, par^0) == LOSE) mymerge(1, 3);
            else if(c>=1 && d>=1 && bktk(a, b+1, c-1, d-1, par^1) == LOSE) mymerge(2, 3);
            else if(par == 1 && bktk(a, b, c, d, par^1) == LOSE) mymerge();
            else assert(false);
            fflush(stdout);
        }
        else
        {
            int u, v; scanf("%d%d", &u, &v);
            if(u==0 && v==0) return 0;
            merge(u, v);
        }
        myturn = !myturn;
    }
    return 0;
}




















