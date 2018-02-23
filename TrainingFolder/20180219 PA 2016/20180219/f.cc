#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;

int n, m, lev[MAXN], sz[MAXN], par[17][MAXN];
lint dep[MAXN];
vector<pi> gph[MAXN];

void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		dep[i.second] = dep[x] + i.first;
		lev[i.second] = lev[x] + 1;
		par[0][i.second] = x;
		gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), pi(i.first, x)));
		dfs(i.second);
		sz[x] += sz[i.second];
	}
}

int chn[MAXN], chd[MAXN], num[MAXN], piv, cidx;

struct seg{
	lint pos, s, e;
	int idx;
};

vector<seg> cup[MAXN]; // ascending chain
vector<seg> cdn[MAXN]; // descening chain

void hld(int x){
	chn[x] = cidx;
	num[x] = ++piv;
	sort(gph[x].begin(), gph[x].end(), [&](const pi &a, const pi &b){
		return sz[a.second] > sz[b.second];
	});
	if(gph[x].size()){
		hld(gph[x][0].second);
		for(int i=1; i<gph[x].size(); i++){
			chn[gph[x][i].second] = ++cidx;
			chd[cidx] = gph[x][i].second;
			hld(gph[x][i].second);
		}
	}
}

int ans[MAXN];

void solve(){

}

void addup(int s, int l, lint t){
	while(chn[s] != chn[l]){
		int nxt = par[0][chd[chn[s]]];
		cup[chn[s]].push_back({pos,
	}
}

void adddown(int e, int l, lint t){
	while(chn[e] != chn[l]){

	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	dfs(1, -1);
	cidx = 1, chd[1] = 1;
	hld(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	auto lca = [&](int s, int e){
		if(lev[s] > lev[e]) swap(s, e);
		int dx = lev[e] - lev[s];
		for(int i=0; i<17; i++){
			if((dx >> i) & 1) e = par[i][e];
		}
		for(int i=16; i>=0; i--){
			if(par[i][s] != par[i][e]){
				s = par[i][s];
				e = par[i][e];
			}
		}
		if(s == e) return s;
		return par[0][s];
	};
	for(int i=0; i<m; i++){
		int s, e;
		lint x;
		scanf("%d %d %lld",&s,&e,&x);
		int l = lca(s, e);
		if(s != l) addup(s, l, x);
		if(e != l) adddown(e, l, x + dep[s] - dep[l] + dep[e] - dep[l]);
	}
	solve();
	for(int i=0; i<m; i++) printf("%d\n", ans[i]);
}
