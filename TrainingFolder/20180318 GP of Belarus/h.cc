#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
const int mod = 1e9 + 7;

int n;
lint dp[MAXN], up[MAXN];

vector<int> gph[MAXN];
vector<lint> pfx[MAXN], sfx[MAXN];
vector<int> dfn;
int par[MAXN], pae[MAXN];

void dfs(int x){
	dfn.push_back(x);
	int cnt = 0;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
		par[i] = x;
		pae[i] = cnt++;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1);
	lint ans1 = 0, ans2 = 0;
	for(int i=dfn.size()-1; i>=0; i--){
		int x = dfn[i];
		dp[x] = 1;
		for(auto &i : gph[x]){
			dp[x] *= (dp[i] + 1);
			dp[x] %= mod;
		}
		pfx[x].resize(gph[x].size());
		sfx[x].resize(gph[x].size());
		for(int i=0; i<gph[x].size(); i++){
			pfx[x][i] = dp[gph[x][i]] + 1;
			sfx[x][i] = dp[gph[x][i]] + 1;
		}
		for(int i=0; i<gph[x].size(); i++){
			if(i) pfx[x][i] *= pfx[x][i-1];
			pfx[x][i] %= mod;
		}
		for(int i=(int)gph[x].size()-1; i>=0; i--){
			if(i + 1 < gph[x].size()) sfx[x][i] *= sfx[x][i+1];
			sfx[x][i] %= mod;
		}
		ans1 += dp[x];
	}
	for(auto &x : dfn){
		if(x == 1){
			up[x] = 1;
			ans2 += up[x] * dp[x] % mod;
			continue;
		}
		up[x] = up[par[x]];
		if(pae[x] > 0){
			up[x] *= pfx[par[x]][pae[x] - 1];
			up[x] %= mod;
		}
		if(pae[x] + 1 < gph[par[x]].size()){
			up[x] *= sfx[par[x]][pae[x] + 1];
			up[x] %= mod;
		}
		up[x]++;
		up[x] %= mod;
		ans2 += up[x] * dp[x] % mod;
	}
	printf("%lld %lld\n", ans1 % mod, ans2 % mod);
}
