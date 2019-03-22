#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,  int>;
const int MAXN = 200005;

vector<int> gph[MAXN];
vector<int> bcc[MAXN];
vector<int> cmp[MAXN];
vector<pi>  edg[MAXN];

int dfn[MAXN], low[MAXN], piv, c;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			if(!dfn[i]){
				dfs(i, x);
				low[x] = min(low[x], low[i]);
			}
			else low[x] = min(low[x], dfn[i]);
		}
	}
}

void color(int x, int p){
	if(p){
		 bcc[p].push_back(x);
		 cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()){
			continue;
		}
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else{
			color(i, p);
		}
	}
}

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

vector<int> g2[MAXN];
int dep[MAXN], par[MAXN], deg[MAXN];

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	while(dep[x] < dep[y]) y = par[y];
	while(x != y) x = par[x], y = par[y];
	return x;
}

void dfs2(int x, int p){
	for(auto &i : g2[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[i] = x;
			dfs2(i, x);
		}
	}
}

int n, m;

bool send(vector<int> vtx, vector<pi> edg){
	for(auto &i : edg){
		deg[i.first]++;
		deg[i.second]++;
	}
	for(auto &i : vtx){
		if(deg[i] >= 3){
			vector<int> path_cand;
			disj.init(n);
			for(auto &j : edg){
				if(j.first == i) path_cand.push_back(j.second);
				else if(j.second == i) path_cand.push_back(j.first);
				else{
					if(disj.uni(j.first, j.second)){
						g2[j.first].push_back(j.second);
						g2[j.second].push_back(j.first);
					}
				}
			}
			assert(path_cand.size() == deg[i]);
			path_cand.resize(3);
			dfs2(path_cand[0], -1);
			int l = lca(path_cand[1], path_cand[2]);
			dfs2(l, -1);
			printf("%d %d\n", i, l);
			for(auto &j : path_cand){
				vector<int> w = {i, j};
				while(w.back() != l){
					w.push_back(par[w.back()]);
				}
				printf("%d ", (int)w.size());
				for(auto &i : w) printf("%d ", i);
				puts("");
			}
			return true;
		}
	}
	for(auto &i : vtx) deg[i] = 0;
	return false;
}

int main(){
	freopen("grand.in", "r", stdin);
	freopen("grand.out", "w", stdout);
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		for(int i=0; i<m; i++){
			int s, e;
			scanf("%d %d",&s,&e);
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		bool ok = 0;
		for(int i=1; i<=n; i++){
			if(!dfn[i]){
				dfs(i, 0);
				color(i, 0);
			}
		}
		for(int i=1; i<=n; i++){
			for(auto &j : gph[i]){
				if(dfn[i] < dfn[j]){
					int w = cmp[j][0];
					edg[w].emplace_back(i, j);
				}
			}
		}
		for(int i=1; i<=c; i++){
			if(send(bcc[i], edg[i])){
				ok = true;
				break;
			}
		}
		if(!ok) puts("-1");
		for(int i=1; i<=max(n, c) + 1; i++){
			gph[i].clear();
			cmp[i].clear();
			g2[i].clear();
			bcc[i].clear();
			edg[i].clear();
			deg[i] = 0;
			dep[i] = par[i] = 0;
			dfn[i] = low[i] = 0;
		}
		piv = c = 0;
	}
}
