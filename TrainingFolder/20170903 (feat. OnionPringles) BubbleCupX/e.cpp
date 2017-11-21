#include <bits/stdc++.h>
using namespace std;
const int N = 101010;
const int mod = 1000000007;
#define mul(x,y) ((long long)(x)*(y)%mod)
int pp[N];vector<int> adj[N];
int main(){
	int L=0;
	pp[0]=1;
	for(int i=1;i<N;i++)pp[i]=mul(pp[i-1],2);
	int n;scanf("%d",&n);
	if(n==1)return puts("1"),0;
	for(int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);u--;v--;adj[u].push_back(v);adj[v].push_back(u);
		}
		int ans=0;for(int i=0;i<n;i++)if(adj[i].size()==1)L++;
		for(int i=0;i<n;i++){
ans+=pp[n-L+((adj[i].size()==1)?1:0)];if(ans>=mod)ans-=mod;
		}printf("%d\n",ans);

}
