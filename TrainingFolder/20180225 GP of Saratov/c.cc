#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n;
vector<int> gph[MAXN];
vector<pi> pth[MAXN];
int dep[MAXN], par[17][MAXN], din[MAXN], dout[MAXN], piv;
vector<int> dfn;

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
	dout[x] = piv;
	dfn.push_back(x);
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int cnt(int s, int e){
	return bit.query(din[s]) + bit.query(din[e]);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	int m;
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		pth[lca(s, e)].push_back(pi(s, e));
	}
	vector<int> ret;
	for(auto &i : dfn){
		bool bad = 0;
		for(auto &j : pth[i]){
			if(cnt(j.first, j.second) == 0) bad = 1;
		}
		if(bad){
			ret.push_back(i);
			bit.add(din[i], 1);
			bit.add(dout[i] + 1, -1);
		}
	}
	printf("%d\n", ret.size());
	for(auto &i : ret) printf("%d ", i);
}
