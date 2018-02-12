#include<bits/stdc++.h>
using namespace std;


int N, M;
vector<int> money, curve;


long long minvalue[1010101]; 
long long balance[1010101];


long long dfill[3010101];


long long leftm[1010101];
long long leftb[1010101];
long long rightm[1010101];
long long rightb[1010101];
void splitfill(long long x)
{
    //M
    leftb[M-1] = curve[1LL*(M-1)*N%M];
    leftm[M-1] = min(leftb[M-1], 0ll);
    for(int i=M-2; i>=0; --i)
    {
        long long b1 = curve[1LL*i*N%M];
        long long m1 = min(b1, 0ll);
        long long b2 = leftb[i+1];
        long long m2 = leftm[i+1];
        leftm[i] = min(m1, b1+m2);
        leftb[i] = b1+b2;
    }
    rightb[0] = curve[1LL*x*N%M];
    rightm[0] = min(rightb[0], 0ll);
    for(int i=1; i<M; ++i)
    {
        long long b1 = rightb[0];
        long long m1 = rightm[0];
        long long b2 = curve[1LL*(x+i)*N%M];
        long long m2 = min(b2, 0ll);
        rightm[i] = min(m1, b1+m2);
        rightb[i] = b1+b2;
    }
    
    long long midm = leftm[0];
    long long midb = leftb[0];
    //printf("%lld %lld\n", midm, midb);
    if((x-2*M)/M == 0)
    {
        midm = 0; midb = 0;
    }
    else
    {
        long long k = (x-2*M)/M;
        if(midb > 0)
            midm = (k-1)*midb + midm;
        midb *= k;
    }
    for(int i=0; i<x%M; ++i)
    {
        midb += curve[1LL*i*N%M];
        midm = min(midb, midm);
    }
    for(int i=0; i<M; ++i)
    {
        long long m1 = leftm[i];
        long long b1 = leftb[i];
        long long m2 = midm;
        long long b2 = midb;
        long long m3 = rightm[i];
        long long b3 = rightb[i];
        minvalue[i] = min({m1, b1+m2, b1+b2+m3});
        balance[i] = b1+b2+b3;
    }
    /*
    printf("=SPLITFILL=%lld\n", x);
    for(int i=0; i<N; ++i)
        printf("%d ", minvalue[i]);
    puts("");
    for(int i=0; i<N; ++i)
        printf("%d ", balance[i]);
    puts("");
    */
}

void dequefill(long long x)
{
    dfill[0] = 0;
    for(int i=1; i<x+M; ++i)
        dfill[i] = dfill[i-1] + curve[1LL*(i-1)*N%M];
    multiset<long long> S;
    
    //fflush(stdout);
    for(int i=1; i<=x; ++i)
        S.insert(dfill[i]);
    for(int i=0; i<M; ++i)
    {
        minvalue[1LL*i*N%M] = *S.begin() - dfill[i];
        balance[1LL*i*N%M] = dfill[i+x] - dfill[i];
        S.erase(S.find(dfill[i+1]));
        S.insert(dfill[i+x+1]);
    }
    /*
    printf("=DEQUEFILL=%lld\n", x);
    for(int i=0; i<N; ++i)
        printf("%d ", minvalue[i]);
    puts("");
    for(int i=0; i<N; ++i)
        printf("%d ", balance[i]);
    puts("");
    */
}


bool can(long long x)
{
    if(x==0)
    {
        for(int i=0; i<N; ++i) minvalue[i] = balance[i] = 0;
        return true;
    }
    if(x<=2*M+1)
        dequefill(x);
    else
        splitfill(x);
    for(int i=M; i<N; ++i)
    {
        minvalue[i] = minvalue[i%M];
        balance[i] = balance[i%M];
    }
    for(int i=0; i<N; ++i)
        if(minvalue[i] + money[i] <= 0) return false;
    
    return true;
}
long long solve(vector<int> money, vector<int> curve)
{
    ::money = money;
    ::curve = curve;
    N = money.size(), M = curve.size();
    long long lo = 0; //must feasible
    long long hi = ((long long)1e12+10); //must not feasible
    while(lo+1!=hi)
    {
        long long mi = (lo+hi)/2;
        if(can(mi)) lo = mi;
        else hi = mi;
    }
    //printf("%lld\n", lo);
    if(hi == ((long long)1e12+10))
        return 2e18;
    else
    {
        can(lo);
        for(int i=0; i<N; ++i) balance[i] += money[i];
        for(long long t = lo*N; t<(lo+1)*N; ++t)
        {
            balance[t%N] += curve[t%M];
            if(balance[t%N] == 0) return t;
        }
    }
    assert(false);
    return 0;
}



int main()
{
    int N, M;
    scanf("%d", &N);
    vector<int> money(N);
    for(int i=0; i<N; ++i)
        scanf("%d", &money[i]);
    
    scanf("%d", &M);
    vector<char> curve(M);
    for(int i=0; i<M; ++i)
        scanf(" %c", &curve[i]);
    
    int g = __gcd(N, M);
    vector<long long> ans; 
    for(int i=0; i<g; ++i)
    {
        vector<int> mon(N/g);
        vector<int> cur(M/g);
        for(int j=0; j<N/g; ++j)
            mon[j] = money[j*g+i];
        for(int j=0; j<M/g; ++j)
        {
            cur[j] = ((curve[j*g+i]=='W')?1:-1);
        }
        long long ansd = solve(mon, cur);
        if(ansd > 1.5e18) ans.push_back((long long)2e18);
        else ans.push_back(ansd*g+i+1);
    }
    if(*min_element(ans.begin(), ans.end()) > 1.5e18)
        puts("-1");
    else
        printf("%lld\n", *min_element(ans.begin(), ans.end()));
    return 0;
}
