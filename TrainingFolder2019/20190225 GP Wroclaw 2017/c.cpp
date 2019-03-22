#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 1000005;
using pi = pair<int, int>;
using lint = long long;

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

struct edg{
	int pos, val, idx;
};

int n, m;
vector<edg> gph[MAXN];
vector<int> edglist;
bool vis[MAXN];
bool chk[MAXM];
bool rem[MAXM];
int dfn[MAXN], low[MAXN], sz[MAXN], piv;
int st[MAXM], ed[MAXM], cst[MAXM];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	sz[x] = gph[x].size();
	for(auto &i : gph[x]){
		if(i.pos == p) continue;
		edglist.push_back(i.idx);
		if(!dfn[i.pos]){
			dfs(i.pos, x);
			low[x] = min(low[x], low[i.pos]);
			sz[x] += sz[i.pos];
		}
		else low[x] = min(low[x], dfn[i.pos]);
	}
}

void reitr(int x, int p){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(i.pos == p) continue;
		if(!vis[i.pos]) reitr(i.pos, x); 
		if(low[i.pos] > dfn[x] && sz[i.pos] % 4 == 3){
			chk[i.idx] = 1;
		}
	}
}

vector<pi> tr[MAXN];
vector<int> aux[MAXN];
vector<pi> ret;

int dfs2(int x, int p){
	vis[x] = 1;
	for(auto &i : tr[x]){
		if(i.second != p){
			int w = dfs2(i.second, x);
			if(w != -1){
				ret.emplace_back(i.first, w);
			}
			else aux[x].push_back(i.first);
		}
	}
	for(int i=0; i<aux[x].size()/2; i++){
		ret.emplace_back(aux[x][i*2], aux[x][i*2+1]);
	}
	if(aux[x].size() % 2) return aux[x].back();
	return -1;
}

void solve(){
	memset(vis, 0, sizeof(vis));
	memset(chk, 0, sizeof(chk));
	memset(rem, 0, sizeof(rem));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(sz, 0, sizeof(sz));
	piv = 0;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		gph[i].clear();
		tr[i].clear();
		aux[i].clear();
	}
	lint score = 0;
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back({e, x, i});
		gph[e].push_back({s, x, i});
		st[i] = s, ed[i] = e;
		cst[i] = x;
		score += x;
	}
	for(int i=1; i<=n; i++){
		if(!dfn[i]){
			edglist.clear();
			dfs(i, 0);
			if(sz[i] % 4 == 2){
				reitr(i, 0);
				pi ret(2e9, -1);
				for(auto &i : edglist){
					if(chk[i]) continue;
					ret = min(ret, pi(cst[i], i));
				}
				score -= ret.first;
				rem[ret.second] = 1;
			}
		}
	}
	cout << score << endl;
	disj.init(n);
	for(int i=1; i<=m; i++){
		if(!rem[i]){
			if(disj.uni(st[i], ed[i])){
				tr[st[i]].emplace_back(i, ed[i]);
				tr[ed[i]].emplace_back(i, st[i]);
			}
			else{
				aux[st[i]].push_back(i);
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	ret.clear();
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs2(i, -1);
		}
	}
	cout << ret.size() << endl;
	for(auto &i : ret) printf("%d %d\n", i.first, i.second);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}

