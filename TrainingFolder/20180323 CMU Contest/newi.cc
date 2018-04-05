#include<bits/stdc++.h>
using namespace std;
int N, V;
int v[5050];

int dp[5050];
int minknapsack()
{
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for(int i=0; i<N; ++i)
        for(int k=V-v[i]; k>=0; --k)
            if(dp[k] != -1)
                dp[k+v[i]] = max(dp[k]+1, dp[k+v[i]]);
    return dp[V];
}
int mdp[5050][5050];
int rmdp[5050][5050];
int medknapsack()
{
    memset(mdp, -1, sizeof(mdp));
    memset(rmdp, 0x3f, sizeof(rmdp));
    mdp[0][0] = 0;
    mdp[0][v[0]] = 1;
    for(int i=1; i<N; ++i)
    {
        for(int k=0; k<=V; ++k)
            mdp[i][k] = mdp[i-1][k];
        for(int k=0; k<=V-v[i]; ++k)
            if(mdp[i-1][k] != -1)
                mdp[i][k+v[i]] = max(mdp[i][k+v[i]], mdp[i-1][k] + 1);
    }
    rmdp[N-1][0] = 0;
    rmdp[N-1][v[N-1]] = 1;
    for(int i=N-2; i>=0; --i)
    {
        for(int k=0; k<=V; ++k)
            rmdp[i][k] = rmdp[i+1][k];
        for(int k=0; k<=V-v[i]; ++k)
            rmdp[i][k+v[i]] = min(rmdp[i][k+v[i]], rmdp[i+1][k] + 1);
    }
    int ans = 0 ;
    for(int i=0; i<N-1; ++i)
        for(int k=0; k<=V; ++k)
            if(mdp[i][k] >= rmdp[i+1][V-k])
                return v[i]; 
    return v[N-1];
}
bool can(int count)
{
    vector<int> rv;
    int cnt = 0;
    for(int i=0; i<N; ++i)
    {
        if(i==0 || v[i-1] != v[i]) cnt = 0;
        ++cnt;
        if(cnt<=count) rv.push_back(v[i]); 
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i=0; i<rv.size(); ++i)
        for(int k=V-rv[i]; k>=0; --k)
            if(dp[k]) dp[k+rv[i]] = 1;
    return dp[V];
}
int maxknapsack()
{
    int lo = 0; // imp
    int hi = 5000; // pos
    while(lo+1!= hi)
    {
        int mi = (lo+hi)/2;
        if(can(mi)) hi = mi;
        else lo = mi;
    }
    return hi;
}
bool ddp[5050];
bool c(int from, int to)
{
    priority_queue<int> Q;
    for(int i=from; i<=to; ++i) Q.push(v[i]);
    vector<int> mv;
    while(!Q.empty())
    {
        int v = Q.top(); 
        int cnt = 0;
        while(!Q.empty() && Q.top() == v) Q.pop(), ++cnt;
        if(cnt<=2)
        {
            mv.push_back(v);
            if(cnt==2) mv.push_back(v);
            continue;
        }
        for(int i=0;; ++i)
        {
            if(cnt>=(1<<i))
            {
                cnt -= (1<<i);
                if((v<<i)<=V)
                Q.push(v<<i);
            } else break;
        }
        if(cnt && v*cnt<=V) Q.push(v*cnt);
    }
    using line = bitset<5050>;
    line L = 0; L[0] = true;
    for(auto x: mv)
    {
        L |= (L << x);
        if(L[V]) return true;
    }
    return false;
    
}
int diffknapsack()
{
    int ptr = 0;
    int ptr2 = 0;
    int ans = 99999;
    while(ptr2 < N)
    {
        if(ptr<=ptr2&&c(ptr, ptr2))
        {
            ans = min(ans, v[ptr2]-v[ptr]);
            ++ptr;
        } else ++ptr2;
    }
    return ans;
}


int main()
{   
    scanf("%d%d", &N, &V);
    for(int i=0; i<N; ++i) scanf("%d", v+i);
    sort(v, v+N);
    int A = minknapsack();
    if(A == -1) 
    {
        puts("-1");
        return 0;
    }
    printf("%.12f %d %d %d\n", 1.0*V/A, medknapsack(), maxknapsack(), diffknapsack());
    
    
}
