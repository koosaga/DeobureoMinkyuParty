#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int n, m, a, b;
vector<vector<pi>> gph;
vector<vector<pi>> f, g;
vector<pi> v;
vector<int> nei;

int main(){
	scanf("%d %d",&n,&m);
	f.resize(n+1); g.resize(n+1); gph.resize(n+1);
	v.resize(m+1);
	nei.resize(n+1);
	for(int i=1; i<=m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].emplace_back(i, e);
		gph[e].emplace_back(i, s);
		v[i] = pi(s, e);
	}
	scanf("%d %d",&a,&b);
	for(auto &i : gph[a]){
		nei[i.second] = i.first;
	}
	for(int i=1; i<=n; i++){
		if(i == a || i == b) continue;
		for(auto &j : gph[i]){
			if(nei[j.second] && j.second != b){
				f[i].emplace_back(max(nei[j.second], j.first), j.second);
			}
		}
	}
	fill(nei.begin(), nei.end(), 0);
	for(auto &i : gph[b]){
		nei[i.second] = i.first;
	}
	for(int i=1; i<=n; i++){
		if(i == a || i == b) continue;
		for(auto &j : gph[i]){
			if(nei[j.second] && j.second != a){
				g[i].emplace_back(max(nei[j.second], j.first), j.second);
			}
		}
	}
	for(int i=1; i<=n; i++){
		sort(f[i].begin(), f[i].end());
		sort(g[i].begin(), g[i].end());
		if(f[i].size() > 4) f[i].resize(4);
		if(g[i].size() > 4) g[i].resize(4);
	}
	int ret = 1e9;
	for(int i=1; i<=m; i++){
		for(auto &j : f[v[i].first]){
			for(auto &k : g[v[i].second]){
				if(j.second == k.second) continue;
				if(j.second == v[i].second || k.second == v[i].first) continue;
				ret = min(ret, max({i, j.first, k.first}));
			}
		}
		for(auto &j : g[v[i].first]){
			for(auto &k : f[v[i].second]){
				if(j.second == k.second) continue;
				if(j.second == v[i].second || k.second == v[i].first) continue;
				ret = min(ret, max({i, j.first, k.first}));
			}
		}
	}
	if(ret > m) ret = -1;
	cout << ret << endl;
}

