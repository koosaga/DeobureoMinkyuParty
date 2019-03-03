#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 500005;

int n;
vector<pi> gph[MAXN];
lint dep[MAXN];
int sub[MAXN];
__int128 dsum[MAXN];
__int128 dp[MAXN][2];

void dfs(int x, int p){
	sub[x] = 0;
	dsum[x] = 0;
	if(x > 1 && gph[x].size() == 1){
		sub[x] = 1;
		dsum[x] = dep[x];
	}
	for(auto &i : gph[x]){
		if(i.second != p){
			dep[i.second] = dep[x] + i.first;
			dfs(i.second, x);
			sub[x] += sub[i.second];
			dsum[x] += dsum[i.second];
		}
	}
}

void solve(int x, int p){
	dp[x][0] = dp[x][1] = 0;
	for(auto &i : gph[x]){
		if(i.second != p){
			solve(i.second, x);
		}
	}
	dp[x][0] = dsum[x];
	if(x > 1 && gph[x].size() == 1){
		dp[x][1] = dep[x];
		return;
	}
	vector<__int128> cnds;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		auto hang1 = dp[i.second][1];
		auto hang2 = dp[i.second][0] - (__int128)sub[i.second] * dep[x];
		dp[x][1] += hang2;
		cnds.push_back(hang1 - hang2);
	}
	sort(cnds.begin(), cnds.end());
	if(cnds.empty()){
		dp[x][1] = dsum[x];
		return;
	}
	dp[x][1] += cnds[0];
	for(int i=1; i<sz(cnds); i++){
		if(cnds[i] < 0) dp[x][1] += cnds[i];
	}
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=1; i<n; i++){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(x, s);
		}
		dfs(1, 0);
		solve(1, 0);
		printf("%lld\n", (lint)dp[1][1]);
		for(int i=1; i<=n; i++) gph[i].clear();
	}
}

