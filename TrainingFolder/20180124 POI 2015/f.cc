#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 500005;

int n, par[19][MAXN], dep[MAXN];
vector<int> gph[MAXN];
vector<int> dfn;

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<19; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=18; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int get_path_center(int s, int e){
	int l = lca(s, e);
	if(dep[s] < dep[e]) swap(s, e);
	int dist = dep[s] + dep[e] - 2 * dep[l];
	dist /= 2;
	for(int i=0; i<19; i++){
		if((dist >> i) & 1) s = par[i][s];
	}
	return s;
}

pi far[MAXN], ufar[MAXN];

void dfs(int x, int p){
	dfn.push_back(x);
	far[x] = pi(0, x);
	for(auto &i : gph[x]){
		if(i == p) continue;
		par[0][i] = x;
		dep[i] = dep[x] + 1;
		dfs(i, x);
		far[x] = max(far[x], pi(far[i].first + 1, far[i].second));
	}
}

struct tuple1{
	int first, second, third;
	bool operator<(const tuple1 &t)const{
		return make_tuple(first, second, third) <
		make_tuple(t.first, t.second, t.third);
	}
};

vector<tuple1> flist[MAXN];
struct diam{
	int st, ed, len;
	bool operator<(const diam &d)const{
		return len < d.len;
	}
	bool operator>(const diam &d)const{
		return len > d.len;
	}
}dp[MAXN], pp[MAXN];

diam make_diam(pi a, pi b){
	return (diam){a.second, b.second, a.first + b.first};
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(j == par[0][i]) continue;
			flist[i].push_back((tuple1){far[j].first + 1, far[j].second, j});
		}
		sort(flist[i].rbegin(), flist[i].rend());
		if(flist[i].size() > 3) flist[i].resize(3);
	}
	for(int i=1; i<dfn.size(); i++){
		int x = dfn[i];
		ufar[x] = pi(0, par[0][x]);
		for(auto &j : flist[par[0][x]]){
			if(j.third == x) continue;
			pi t = pi(j.first, j.second);
			ufar[x] = max(ufar[x], t);
		}
		if(par[0][x] != 1){
			pi t = pi(ufar[par[0][x]].first + 1, ufar[par[0][x]].second);
			ufar[x] = max(ufar[x], t);
		}
	}
	for(int i=dfn.size()-1; i>=0; i--){
		int x = dfn[i];
		if(flist[x].size() > 1){
			pi v1(flist[x][0].first, flist[x][0].second);
			pi v2(flist[x][1].first, flist[x][1].second);
			dp[x] = make_diam(v1, v2);
		}
		if(flist[x].size() == 1){
			pi v1(flist[x][0].first, flist[x][0].second);
			pi v2(0, x);
			dp[x] = make_diam(v1, v2);
		}
		if(flist[x].empty()) dp[x] = (diam){x, x, 0};
		for(auto &j : gph[x]){
			if(j == par[0][x]) continue; 
			dp[x] = max(dp[x], dp[j]);
		}
	}
	for(int i=1; i<dfn.size(); i++){
		int x = dfn[i];
		vector<pi> diam_cand;
		for(auto &j : flist[par[0][x]]){
			if(j.third == x) continue;
			diam_cand.push_back(pi(j.first, j.second));
		}
		if(par[0][x] != 1){
			pi t = pi(ufar[par[0][x]].first + 1, ufar[par[0][x]].second);
			diam_cand.push_back(t);
		}
		sort(diam_cand.rbegin(), diam_cand.rend());
		if(diam_cand.size() >= 2) pp[x] = make_diam(diam_cand[0], diam_cand[1]);
		if(diam_cand.size() == 1) pp[x] = make_diam(diam_cand[0], pi(0, par[0][x]));
		if(diam_cand.size() == 0) pp[x] = (diam){par[0][x], par[0][x], 0};
		if(par[0][x] != 1) pp[x] = max(pp[x], pp[par[0][x]]);
	}
	int maxv = -1; pi maxins, maxdel;
	int minv = 1e9; pi minins, mindel;
	for(int i=2; i<=n; i++){
		auto up = pp[i], dn = dp[i];
		if(up.len + dn.len + 1 > maxv){
			maxdel = pi(par[0][i], i);
			maxins = pi(up.st, dn.st);
			maxv = up.len + 1 + dn.len;
		}
		int nxtdiam = max({up.len, dn.len, (up.len + 1) / 2 + (dn.len + 1) / 2 + 1});
		if(nxtdiam < minv){
			mindel = pi(par[0][i], i);
			minins = pi(get_path_center(up.st, up.ed), get_path_center(dn.st, dn.ed));
			minv = nxtdiam;
		}
	}
	swap(maxins, maxdel);
	swap(minins, mindel);
	printf("%d %d %d %d %d\n", minv, minins.first, minins.second, mindel.first, mindel.second);

	printf("%d %d %d %d %d\n", maxv, maxins.first, maxins.second, maxdel.first, maxdel.second);
}
