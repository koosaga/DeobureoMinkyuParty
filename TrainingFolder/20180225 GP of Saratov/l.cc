#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 400005;

namespace dtree{
	vector<int> E[MAXN], RE[MAXN], rdom[MAXN];
	int S[MAXN], RS[MAXN], cs;
	int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

	void add_edge(int s, int e){ E[s].push_back(e); }
	void Union(int x, int y){ par[x] = y; }
	int Find(int x, int c = 0){
		if(par[x] == x) return c ? -1 : x;
		int p = Find(par[x], 1);
		if(p == -1) return c ? par[x] : val[x];
		if(sdom[val[x]] > sdom[val[par[x]]]){
			val[x] = val[par[x]];
		}
		par[x] = p;
		return c ? p : val[x];
	}
	void dfs(int x){
		RS[S[x] = ++cs] = x;
		par[cs] = sdom[cs] = val[cs] = cs;
		for(int e : E[x]){
			if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
			RE[S[e]].push_back(S[x]);
		}
	}
	int solve(int s, int *up){
		dfs(s);
		for(int i=cs; i; i--){
			for(int e : RE[i]){
				sdom[i] = min(sdom[i], sdom[Find(e)]);
			}
			if(i > 1) rdom[sdom[i]].push_back(i);
			for(int e : rdom[i]){
				int p = Find(e);
				if(sdom[p] == i) dom[e] = i;
				else dom[e] = p;
			}
			if(i > 1) Union(i, rp[i]);
		}
		for(int i=2; i<=cs; i++) if(sdom[i] != dom[i]){
			dom[i] = dom[dom[i]];
		}
		for(int i=2; i<=cs; i++){
			up[RS[i]] = RS[dom[i]];
		}
		return cs;
	}
}

int n, m;
vector<pi> gph[MAXN];
vector<int> tr[MAXN];
lint dist[MAXN];

int mp[MAXN];
int ret[MAXN];
int par[MAXN];

int dfs(int x){
	int r = (x <= n);
	for(auto &i : tr[x]){
		r += dfs(i);
	}
	if(x > n){
		ret[mp[x]] = r;
	}
	return r;
}

int main(){
	scanf("%d %d",&n,&m);
	map<pi, int> edgs;
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
		edgs[pi(s, e)] = edgs[pi(e, s)] = i;
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	pq.push(pi(0, 1));
	dist[1] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > dist[x.second] + i.first){
				dist[i.second] = dist[x.second] + i.first;
				pq.push(pi(dist[i.second], i.second));
			}
		}
	}
	vector<pi> e;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(dist[i] + j.first == dist[j.second]){
				mp[e.size() + n + 1] = edgs[pi(i, j.second)];
				dtree::add_edge(i, e.size() + n + 1);
				dtree::add_edge(e.size() + n + 1, j.second);
				e.push_back(pi(i, j.second));
			}
		}
	}
	dtree::solve(1, par);
	for(int i=2; i<=n + e.size(); i++){
		tr[par[i]].push_back(i);
	}
	dfs(1);
	for(int i=0; i<m; i++) printf("%d\n", ret[i]);
}
