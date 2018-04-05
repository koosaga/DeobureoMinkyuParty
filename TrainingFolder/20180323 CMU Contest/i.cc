#include<bits/stdc++.h>
using namespace std;
int V;
int dp[5050];
int ans;
int solve(const vector<int>& v)
{
    priority_queue<int, vector<int>, greater<int> > Q;
    for(auto x: v) Q.push(x);
    vector<int> mv;
    vector<int> mv2;
    while(!Q.empty())
    {
        int v = Q.top(), cnt = 0;
        while(!Q.empty() && Q.top() == v) Q.pop(), ++cnt;
        if(cnt <= 2)
        {
            mv.push_back(v);
            mv2.push_back(1);
            if(cnt==2)
            {
                mv.push_back(v);
                mv2.push_back(1);
            }
            continue;
        }
        for(int i=0;;++i)
        {
            if(cnt>=(1<<i))
            {
                cnt -= (1<<i);
                if((v<<i) <= V)
                {
                    mv.push_back(v<<i);
                    mv2.push_back(1<<i);
                }
            } else break;
        }
        if(cnt && v*cnt <= V)
        {
            mv.push_back(v*cnt);
            mv2.push_back(cnt);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i=0; i<mv.size(); ++i)
    {
        int x = mv[i];
        int y = mv2[i];
        for(int k=V-x; k>=0; --k)
            dp[k+x] = min(dp[k]+y, dp[k+x]);
    }
    return dp[V];
}
int mdp[5050][5050];
int rmdp[5050][5050];
int med(vector<int> v)
{
    int N = v.size();
    memset(mdp, 0x3f, sizeof(mdp));
    memset(rmdp, 0x3f, sizeof(rmdp));
    mdp[0][0] = 0;
    mdp[0][v[0]] = 1;
    for(int i=1; i<N; ++i)
    {
        for(int k=0; k<=V; ++k)
            mdp[i][k] = mdp[i-1][k];
        for(int k=0; k<=V-v[i]; ++k)
            mdp[i][k+v[i]] = min(mdp[i][k+v[i]], mdp[i-1][k] + 1);
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
    for(int i=0; i<N-1; ++i)
        for(int k=0; k<=V; ++k)
        {
            if(mdp[i][k] + rmdp[i+1][V-k] == ans && mdp[i][k] >= rmdp[i+1][V-k])
                return v[i];
        }
    return v[N-1];
}
bool can(int count, const vector<int>& v)
{
    int N = v.size();
    vector<int> rv;
    int cnt = 0;
    for(int i=0; i<N; ++i)
    {
        if(i==0 || v[i-1] != v[i]) cnt = 0;
        ++cnt;
        if(cnt<=count) rv.push_back(v[i]);
    }
    return ans == solve(rv);
}
int maxk(vector<int> v)
{
    int N = v.size();
    int lo = 0;
    int hi = 5000;
    while(lo+1!= hi)
    {
        int mi = (lo+hi)/2;
        if(can(mi, v)) hi = mi;
        else lo = mi;
    }
    return hi;
}
bool c(int from, int to, const vector<int>& v)
{
    vector<int> rv;
    for(int i=from; i<=to; ++i) rv.push_back(v[i]);
    return ans == solve(rv);
}
//firstsame, maxsecond (-minsecond)
int diff(const vector<int>& v)
{
    //mydp.first = mdp
    //mydp.second = rmdp
    int N = v.size();
    memset(mdp, 0x3f, sizeof(mdp));
    memset(rmdp, 0x3f, sizeof(rmdp));
    mdp[0][0] = 0;
    rmdp[0][0] = 0;
    mdp[0][v[0]] = 1;
    rmdp[0][v[0]] = v[0];
    if(v[0] == V) return 0;
    int myans = 999999;
    for(int i=1; i<N; ++i)
    {
        for(int k=0; k<=V; ++k)
        {
            mdp[i][k] = mdp[i-1][k];
            rmdp[i][k] = rmdp[i-1][k];
        }
        for(int k=0; k<=V-v[i]; ++k)
        {
            auto x = make_pair(mdp[i-1][k], rmdp[i-1][k]);
            x.first++;
            if(x.first==1) x.second = v[i];
            auto y = make_pair(mdp[i][k+v[i]], rmdp[i][k+v[i]]);
            if(y.first > x.first || y.first==x.first && y.second<x.second)
            {
                mdp[i][k+v[i]] = x.first;
                rmdp[i][k+v[i]] = x.second;
            } 
        }
        if(ans == mdp[i][V]) myans = min(myans, v[i] - rmdp[i][V]);
    } 
    return myans;
}
int main()
{
    int N;
    scanf("%d%d", &N, &V);
    vector<int> v;
    for(int i=0; i<N; ++i)
    {
        int t; scanf("%d", &t); v.push_back(t);
    }
    sort(v.begin(), v.end());
    ans = solve(v);
    if(ans > 9999)
    {
        puts("-1");
        return 0;
    }
    printf("%.12f %d %d %d\n", 1.0*V/ans, med(v), maxk(v), diff(v));
}






























