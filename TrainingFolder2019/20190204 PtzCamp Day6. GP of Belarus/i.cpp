#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<lint, int>;

namespace FIO{
	static char buf[1 << 19];
	static int idx = 0;
	static int bytes = 0;
	static inline int _read(){
		if(!bytes || idx == bytes){
			bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
			idx = 0;
		}
		return buf[idx++];
	}
	static inline int _readInt(){
		int x = 0, s = 1;
		int c = _read();
		while(c <= 32) c = _read();
		while(c > 32) x = 10 * x + (c - '0'), c = _read();
		if(s < 0) x = -x;
		return x;
	}
}

int n, q;
vector<pi> gph[MAXN];
int sz[MAXN], dfn[MAXN], chn[MAXN], piv;
int par[18][MAXN], pae[MAXN], dep[MAXN];
int A[2 * MAXN];

void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), pi(i.first, x)));
		par[0][i.second] = x;
		pae[i.second] = i.first;
		dep[i.second] = dep[x] + 1;
		dfs(i.second);
		sz[x] += sz[i.second];
	}
	sort(gph[x].begin(), gph[x].end(), [&](const pi &a, const pi &b){
		return sz[a.second] > sz[b.second];
	});
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=17; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void hld(int x){
	dfn[x] = ++piv;
	if(x > 1){
		A[piv] = pae[x];
	}
	if(gph[x].empty()) return;
	chn[gph[x][0].second] = chn[x];
	hld(gph[x][0].second);
	for(int i=1; i<gph[x].size(); i++){
		chn[gph[x][i].second] = gph[x][i].second;
		hld(gph[x][i].second);
	}
}

int lg[MAXN * 2];
int up[19][2 * MAXN];
lint aug[19][2 * MAXN];

pi Query(int l, int r, int v){
	lint ret = 0;
	if(A[l] <= v){
		int lgv = lg[r - l + 1];
		int prevp = l;
		for(int i=lgv; i>=0; i--){
			if(up[i][l] <= r && A[up[i][l]] <= v) l = up[i][l];
		}
		if(up[0][l] > r) return pi(1ll * (r - prevp + 1) * v, v);
		l = up[0][l];
		ret += 1ll * (l - prevp) * v;
	}
	int lgv = lg[r - l + 1];
	for(int i=lgv; i>=0; i--){
		if(up[i][l] <= r){
			ret += aug[i][l];
			l = up[i][l];
		}
	}/*
	while(up[0][l] <= r){
		ret += 1ll * (up[0][l] - l) * A[l];
		v = A[l];
		l = up[0][l];
	}*/
	ret += 1ll * (r + 1 - l) * A[l];
	return pi(ret, A[l]);
}

int main(){
	n = FIO::_readInt();
	q = FIO::_readInt();
	{
		int p = 0;
		for(int i=1; i<2 * MAXN; i++){
			while((2 << p) <= i) p++;
			lg[i] = p;
		}
	}
	for(int i=1; i<n; i++){
		int s, e, x;
	s = FIO::_readInt();
	e = FIO::_readInt();
	x = FIO::_readInt();
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	dfs(1);
	chn[1] = 1;
	hld(1);
	for(int i=2; i<=n; i++) A[i + n] = A[i];
	reverse(A + n + 1, A + n + n + 1);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	vector<int> stk;
	up[0][2*n] = 2*n;
	for(int i=2*n-1; i; i--){
		while(!stk.empty() && A[stk.back()] <= A[i]) stk.pop_back();
		if(stk.empty()) up[0][i] = 2 * n;
		else up[0][i] = stk.back();
		aug[0][i] = 1ll * (up[0][i] - i) * A[i];
		stk.push_back(i);
	}
	for(int i=1; i<19; i++){
		for(int j=1; j<=2*n; j++){
			aug[i][j] = aug[i-1][j] + aug[i-1][up[i-1][j]];
			up[i][j] = up[i-1][up[i-1][j]];
		}
	}
	auto query = [&](int x, int y, int s){
		if(x == y){
			return pi(max(A[x], s), max(A[x], s));
		}
		if(x < y) return Query(x, y, s);
		return Query(2*n+1-x, 2*n+1-y, s);
	};
	while(q--){
		int s, e; 
		s = FIO::_readInt();
		e = FIO::_readInt();
		int l = lca(s, e);
		int shoot = 0;
		lint ret = 0;
		while(chn[s] != chn[l]){
			auto ans = query(dfn[s], dfn[chn[s]], shoot);
			ret += ans.first;
			shoot = ans.second;
			s = par[0][chn[s]];
		}
		if(s != l){
			auto ans = query(dfn[s], dfn[l] + 1, shoot);
			ret += ans.first;
			shoot = ans.second;
			s = l;
		}
		vector<pi> seq;
		while(chn[e] != chn[l]){
			seq.emplace_back(dfn[chn[e]], dfn[e]);
			e = par[0][chn[e]];
		}
		if(l != e) seq.emplace_back(dfn[l] + 1, dfn[e]);
		reverse(seq.begin(), seq.end());
		for(auto &i : seq){
			auto ans = query(i.first, i.second, shoot);
			ret += ans.first;
			shoot = ans.second;
		}
		printf("%lld\n", ret);
	}
}
