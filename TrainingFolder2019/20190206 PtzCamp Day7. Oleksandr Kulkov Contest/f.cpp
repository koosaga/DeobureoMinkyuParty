#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m;
vector<pi> gph[MAXN];
int par[18][MAXN], minv[18][MAXN];
int dep[MAXN];

struct disj{
	set<int> v[MAXN];
	int pa[MAXN], marked[MAXN];
	void init(int n){
		for(int i=1; i<=n; i++){
			v[i].insert(i);
			pa[i] = i;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(v[p].size() < v[q].size()) swap(p, q);
		pa[q] = p;
		for(auto &i : v[q]) v[p].insert(i);
		return 1;
	}
	void mark(int x){
		x = find(x);
		for(auto &i : v[x]) marked[i] = 1;
		v[x].clear();
	}
}disj;

struct edge{
	int s, e, x, type;
	bool operator<(const edge &e)const{
		if(x != e.x) return x > e.x;
		return type > e.type;
	}
};

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dep[i.second] = dep[x] + 1;
		par[0][i.second] = x;
		minv[0][i.second] = i.first;
		dfs(i.second, x);
	}
}

int query(int s, int e){
	int ret = 1e9;
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1){
			ret = min(ret, minv[i][e]);
			e = par[i][e];
		}
	}
	for(int i=17; i>=0; i--){
		if(par[i][s] != par[i][e]){
			ret = min({ret, minv[i][s], minv[i][e]});
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) ret = min({ret, minv[0][s], minv[0][e]});
	return ret;
}

vector<edge> edg, tre;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=m; i++){
		int t; scanf("%d",&t);
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		if(t == 1){
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(x, s);
			tre.push_back({s, e, x, 1});
		}
		else{
			edg.push_back({s, e, x});
		}
	}
	memset(minv, 0x3f, sizeof(minv));
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
			minv[i][j] = min(minv[i-1][j], minv[i-1][par[i-1][j]]);
		}
	}
	for(auto &i : edg){
		if(query(i.s, i.e) < i.x){
			tre.push_back({i.s, i.e, query(i.s, i.e), 2});
		}
	}
	sort(tre.begin(), tre.end());
	disj.init(n);
	for(auto &i : tre){
		disj.uni(i.s, i.e);
		if(i.type == 2){
			disj.mark(i.s);
		}
	}
	vector<int> v;
	for(int i=1; i<=n; i++) if(!disj.marked[i]) v.push_back(i);
	cout << v.size() << endl;
	for(int i=0; i<v.size(); i++) printf("%d ", v[i]);
}
