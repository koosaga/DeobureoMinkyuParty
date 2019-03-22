#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;

int n, q;
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

vector<int> gph[MAXN];
int par[18][MAXN], dep[MAXN];
int rev[MAXN];
int din[MAXN], dout[MAXN], piv, sz[MAXN], chn[MAXN];

void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		par[0][i] = x;
		dep[i] = dep[x] + 1;
		dfs(i);
		sz[x] += sz[i];
	}
	sort(gph[x].begin(), gph[x].end(), [&](const int &a, const int &b){
		return sz[a] > sz[b];
	});
}

void hld(int x){
	din[x] = ++piv;
	rev[din[x]] = x;
	if(gph[x].empty()){
		dout[x] = piv;
		return;
	}
	chn[gph[x][0]] = chn[x];
	hld(gph[x][0]);
	for(int i=1; i<gph[x].size(); i++){
		chn[gph[x][i]] = gph[x][i];
		hld(gph[x][i]);
	}
	dout[x] = piv;
}

int gs(int x, int l){
	return dep[x] - dep[l] - (bit.query(din[x]) - bit.query(din[l]));
}

void add_subtree(int x, int v){
	bit.add(din[x], v);
	bit.add(dout[x] + 1, -v);
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

set<int> not_in;
set<pi> cross_chain;

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1);
	chn[1] = 1;
	hld(1);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=1; i<=n; i++){
		if(chn[i] != i) not_in.insert(din[i]);
	}
	int q; scanf("%d",&q);
	while(q--){
		int t, a, b; scanf("%d %d %d",&t,&a,&b);
		int l = lca(a, b);
		if(t == 0){
			printf("%d\n", gs(a, l) + gs(b, l));
		}
		else{
			auto path_coalescing = [&](int s, int e){
				int st = din[s], ed = din[e];
				auto l2 = not_in.lower_bound(st + 1);
				while(l2 != not_in.end() && *l2 <= ed){
					add_subtree(rev[*l2], 1);
					l2 = not_in.erase(l2);
				}
				if(chn[rev[ed + 1]] == chn[s] && not_in.find(ed + 1) == not_in.end()){
					add_subtree(rev[ed + 1], -1);
					not_in.insert(ed + 1);
				}
			};
			vector<pi> next_cross_chain;
			while(chn[a] != chn[l]){
				int st = din[chn[a]];
				int ed = din[a];
				auto l = cross_chain.lower_bound(pi(st, -1));
				while(l != cross_chain.end() && l->first <= ed){
					add_subtree(l->second, -1);
					l = cross_chain.erase(l);
				}
				path_coalescing(chn[a], a);
				a = chn[a];
				next_cross_chain.push_back(pi(din[par[0][a]], a));
				a = par[0][a];
			}
			while(chn[b] != chn[l]){
				int st = din[chn[b]];
				int ed = din[b];
				auto l = cross_chain.lower_bound(pi(st, -1));
				while(l != cross_chain.end() && l->first <= ed){
					add_subtree(l->second, -1);
					l = cross_chain.erase(l);
				}
				path_coalescing(chn[b], b);
				b = chn[b];
				next_cross_chain.push_back(pi(din[par[0][b]], b));
				b = par[0][b];
			}
			if(a == l) a = b;
			int st = din[l];
			int ed = din[a];
			int sex = l;
			auto l = cross_chain.lower_bound(pi(st, -1));
			while(l != cross_chain.end() && l->first <= ed){
				add_subtree(l->second, -1);
				l = cross_chain.erase(l);
			}
			path_coalescing(sex, a);
			if(chn[sex] != sex && not_in.find(din[sex]) == not_in.end()){
				add_subtree(sex, -1);
				not_in.insert(din[sex]);
			}
			else if(sex != 1){
				if(cross_chain.find(pi(din[par[0][sex]], sex)) != cross_chain.end()){
					add_subtree(sex, -1);
					cross_chain.erase(pi(din[par[0][sex]], sex));
				}
			}
			for(auto &i : next_cross_chain){
				cross_chain.insert(i);
				add_subtree(i.second, 1);
			}
		}
	}
}
