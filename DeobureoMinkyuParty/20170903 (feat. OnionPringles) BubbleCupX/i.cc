#include <bits/stdc++.h>
using namespace std;
const int N=100000;
const int LG=17;
const int S=450;
int a[N<<1],b[N],c[N],m,f[N],d[N];
vector<int> adj[N];
int anc[N][LG],rnk[N];
int in[N],cnt[N][2]; long long ans[N];
long long x=0;
void ins(int i){
    int u=a[i];
    if(in[u]){
    x-=cnt[f[u]][d[u]^1];
    cnt[f[u]][d[u]]--;
    }
    else {
    x+=cnt[f[u]][d[u]^1];
    cnt[f[u]][d[u]]++;
    }
    in[u]^=1;
}
void pd(int u,int p=-1){
    anc[u][0]=p;
    b[u]=m;
    a[m++]=u;
    for(auto &x:adj[u]){
        if(x==p)continue;
        rnk[x]=rnk[u]+1;
        pd(x,u);
    }
    c[u]=m;
    a[m++]=u;
}
int up(int u,int d){
    for(int i=0;i<LG;i++)if(d&(1<<i))u=anc[u][i];
    return u;
}
int LCA(int u,int v){
    if(rnk[u]<rnk[v])swap(u,v);
    int d=rnk[u]-rnk[v];
    u=up(u,d);
    if(u==v)return u;
    for(int i=LG;i--;){
        if(anc[u][i]!=anc[v][i]){
            u=anc[u][i],v=anc[v][i];
        }
    }
    return anc[u][0];
}
typedef pair<int,int> pii;
typedef pair<pii,pii> E;
int main(){
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",d+i);
    for(int i=0;i<n;i++)scanf("%d",f+i);
    vector<int> F;
    for(int i=0;i<n;i++)F.push_back(f[i]);
    sort(F.begin(),F.end());
    F.erase(unique(F.begin(),F.end()),F.end());
    for(int i=0;i<n;i++)f[i]=lower_bound(F.begin(),F.end(),f[i])-F.begin();
    for(int i=0;i<n-1;i++){
        int u,v;scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pd(0);
    for(int j=1;j<LG;j++){
        for(int i=0;i<n;i++){
            int a=anc[i][j-1];
            if(a==-1)anc[i][j]=-1;
            else anc[i][j]=anc[a][j-1];
        }
    }
    int Q;scanf("%d",&Q);
    vector<pair<pii,pii>> Event;
    for(int i=0;i<Q;i++){
        int u,v;scanf("%d%d",&u,&v);
        u--;v--;
        if(c[u]>c[v])swap(u,v);
        int L = LCA(u,v);
        Event.push_back({{c[u],c[v]},{L,i}});
    }
    sort(Event.begin(),Event.end(),[](const E& a,const E& b){
        auto p=a.first;auto q=b.first;
        return p.first/S<q.first/S || p.first/S==q.first/S&&p.second<q.second;
    });
    int l=0,r=0;
    for(auto &x:Event){
        int L=x.first.first;
        int R=x.first.second;
        int lca=x.second.first;
        int ii=x.second.second;
        while(l>L)ins(--l);
        while(l<L)ins(l++);
        while(r<R)ins(r++);
        while(r>R)ins(--r);
        ans[ii]=::x+cnt[f[lca]][d[lca]^1];
    }
    for(int i=0;i<Q;i++)printf("%lld\n",ans[i]);
}
