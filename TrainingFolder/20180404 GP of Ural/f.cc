#include<bits/stdc++.h>
using namespace std;
//#define DEBUG
vector<int> P;
vector<int> Pinv;
int N;
int cnt = 0;
void Init()
{
    #ifdef DEBUG
    P.resize(N);
    Pinv.resize(N);
    for(int i=0; i<N; ++i)
        P[i] = i;
    random_shuffle(P.begin(), P.end());
    for(int i=0; i<N; ++i)
        Pinv[P[i]] = i;
    #endif
}
void ok(vector<int> x)
{
    printf("!");
    for(auto y: x)
        printf(" %d",y);
    puts("");
    fflush(stdout);
    #ifdef DEBUG
    for(auto x: P)
        printf("%d ", x);
    assert(P == x);
    printf("REAL: %d\n", cnt);
    #endif
    return;
}
int query(int a, int b, int c)
{
    printf("? %d %d %d\n", a, b, c);
    fflush(stdout);
    #ifdef DEBUG
    ++cnt;
    return Pinv[(P[a]*P[b]+P[c])%N];
    #endif
    int x;
    scanf("%d", &x);
    return x;
}
int eph(int N)
{
    int cnt= 0 ;
    for(int i=1; i<=N; ++i)
        if(__gcd(i, N)==1) cnt++;
    return cnt;
}
int ipow(int a, int b, int zero)
{
    if(b==1) return a;
    int res = ipow(a, b/2, zero);
    res = query(res, res, zero);
    if(b%2==1)
        res = query(res, a, zero);
    return res;
}
vector<int> fperm(int pinv1)
{
    vector<int> Q;
    vector<int> ans(N);
    Q.push_back(pinv1);
    for(int i=2; i<=N; ++i)
        Q.push_back(query(Q[Q.size()-1], pinv1, pinv1));
    for(int i=0; i<N; ++i)
        ans[Q[i]] = (i+1)%N;
    return ans;
}
int findinv1(vector<int> posd2, int pinv0)
{
    int phi = eph(N);
    while(true)
    {
        int v = rand()%N;
        while(v == pinv0) v = rand()%N;
        int ans = ipow(v, phi, pinv0);
        if(ans == pinv0) continue;
        bool flag = true;
        for(int i=0; i<20; ++i)
        {
            int u = rand()%N;
            if(u != query(ans, u, pinv0))
            {
                flag = false;
                break;
            }
        }
        if(flag) return ans;
    }
    return 1;
}
pair<vector<int>, int> findinv0()
{
    vector<int> V;
    for(int i=0; i<N; ++i)
    {
        int q = query(i, i, 0);
        if(q==0) V.push_back(i);
    }
    vector<int> nv = V;
    while(V.size() != 1)
    {
        vector<int> V2;
        for(auto v: V)
        {
            int q = query(v, rand()%N, 0);
            if(q==0) V2.push_back(v);
        }
        V = V2;
    }
    return make_pair(nv, V[0]);
}
int main()
{
    scanf("%d", &N);
    if(N==1)
    {
        puts("! 0");
        return 0;
    }
    Init();
    auto pinv0 = findinv0();
    #ifdef DEBUG
    printf("%d\n", pinv0.second);
    #endif
    int pinv1 = findinv1(pinv0.first, pinv0.second);
    #ifdef DEBUG
    printf("%d\n", pinv1);
    #endif
    vector<int> findperm = fperm(pinv1);
    ok(findperm);
    return 0;
}



















