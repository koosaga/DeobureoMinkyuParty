#include<bits/stdc++.h>
using namespace std;
const int N = 100000;
const int mod=1000000007;
#define mul(x,y) ((long long)(x)*(y)%mod)
vector<int> adj[N];
int d[N][2];
void dfs(int u,int p = -1){
    d[u][0]=d[u][1]=1;
    int cnt=0;
    for(auto &x:adj[u]){
        if(x==p)continue;
        cnt++;
        dfs(x,u);
        d[u][0]=mul(d[u][0],d[x][0]+d[x][1]);
        d[u][1]=mul(d[u][1],d[x][0]+d[x][1]);
    }
    if(cnt==0)d[u][1]=0;
}
int ans[N];
void dp(int u,int p=-1,int O=1, int E=1){
    printf("%d %d %d\n",u,O,E);
    ans[u]=mul(O,d[u][1])+mul(E,d[u][0]);
    ans[u]%=mod;
    vector<int> ch;
    for(auto &x:adj[u])if(x!=p)ch.push_back(x);
    int sz = ch.size();
    vector<int> LO,LE,RO,RE;
    LO.push_back(1);
    for(int i=0;i<sz;i++){
        int x=ch[i];
        LO.push_back(d[x][1]+d[x][0]);
    }
    for(int i=sz;i--;){
        int x=ch[i];
        RO.push_back(d[x][1]+d[x][0]);
    }
    RO.push_back(1);
    for(int i=0;i<sz;i++){
        LO[i+1]=mul(LO[i],LO[i+1]);
    }
    for(int i=sz-1;i>=0;i--){
        RO[i]=mul(RO[i],RO[i+1]);
    }
    for(int i=0;i<sz;i++){
        int C = mul(mul(O,LO[i]),RO[i+1])+mul(mul(E,LO[i]),RO[i+1]);
        C%=mod;
        int x=ch[i];
        dp(x,u,C,C);
    }
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }   
    dfs(0);
    for(int i=0;i<n;i++)printf("%d %d\n",d[i][0],d[i][1]);
    dp(0,-1,1,1);
    int ans=0;
    for(int i=0;i<n;i++){
        printf("%d: %d\n",i,::ans[i]);
        ans += ::ans[i];
        if(ans>=mod)ans-=mod;
    }
    printf("%d\n",ans);
}   
