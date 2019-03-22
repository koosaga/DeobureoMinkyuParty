#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
const int MAXT = 1050000;
using lint = long long;
using pi = pair<int, int>;

int n, m;

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, 2e9);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = min(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 2e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

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
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}e[MAXN];

vector<pi> gph[MAXN];
vector<edg> lis[MAXN];
int par[19][MAXN], dep[MAXN];
int din[MAXN], dout[MAXN], rev[MAXN], piv;

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<19; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=18; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void dfs(int x, int p){
	din[x] = ++piv;
	rev[din[x]] = x;
	for(auto &i : gph[x]){
		if(i.second != p){
			par[0][i.second] = x;
			dep[i.second] = dep[x] + 1;
			gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), pi(i.first, x)));
			dfs(i.second, x);
		}
	}
	dout[x] = piv;
}

vector<edg> ALT;
int ans[MAXN];

struct query{ int l, r, idx; };
vector<query> prefixReq[MAXN], suffixReq[MAXN];
vector<pi> pointUpd[MAXN];

void solve(){
	multiset<int> gansun_list;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(j.second > i){
				gansun_list.insert(j.first);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			gansun_list.erase(gansun_list.find(j.first));
		}
		if(gansun_list.size()) ans[i] = max(ans[i], *gansun_list.rbegin());
		for(auto &j : gph[i]){
			gansun_list.insert(j.first);
		}
	}
	dfs(1, 0);
	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(auto &i : ALT){
		int l = lca(i.s, i.e);
		if(l != i.s && l != i.e){
		lis[lca(i.s, i.e)].push_back(i);
		}
		pointUpd[din[i.s]].emplace_back(din[i.e], i.x);
		pointUpd[din[i.e]].emplace_back(din[i.s], i.x);
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(din[i] > 1){
				prefixReq[din[i] - 1].push_back({din[j.second], dout[j.second], i});
			}
			if(dout[i] < n){
				suffixReq[dout[i] + 1].push_back({din[j.second], dout[j.second], i});
			}
		}
	}
	seg.init(n);
	for(int i=1; i<=n; i++){
		for(auto &j : pointUpd[i]){
			seg.upd(j.first, j.second);
		}
		for(auto &j : prefixReq[i]){
			int val = seg.query(j.l, j.r);
			if(val < 1.01e9){
				lis[j.idx].push_back({par[0][j.idx], rev[j.l], val});
			}
		}
	}
	seg.init(n);
	for(int i=n; i; i--){
		for(auto &j : pointUpd[i]){
			seg.upd(j.first, j.second);
		}
		for(auto &j : suffixReq[i]){
			int val = seg.query(j.l, j.r);
			if(val < 1.01e9){
				lis[j.idx].push_back({par[0][j.idx], rev[j.l], val});
			}
		}
	}
	for(int i=1; i<=n; i++){
		sort(lis[i].begin(), lis[i].end());
		auto relabel = [&](int x){
			if(par[0][i] == x) return x;
			auto y = --upper_bound(gph[i].begin(), gph[i].end(), pi(69, x), [&](const pi &a, const pi &b){
				return din[a.second] < din[b.second];
			});
			return y->second;
		};
		vector<int> v;
		for(auto &j : lis[i]){
			j.s = relabel(j.s);
			j.e = relabel(j.e);
			v.push_back(j.s);
			v.push_back(j.e);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		disj.init(v.size());
		int deg = gph[i].size() + (i > 1) - 1;
		for(auto &j : lis[i]){
			int s = lower_bound(v.begin(), v.end(), j.s) - v.begin();
			int e = lower_bound(v.begin(), v.end(), j.e) - v.begin();
			if(disj.uni(s, e)){
				deg--;
				ans[i] = max(ans[i], j.x);
			}
		}
		if(deg > 0) ans[i] = 2e9;
	}
}

int main(){
	int FUCK = 0;
	while(~scanf("%d %d",&n,&m)){
		fill(ans, ans + n + 2, 2e9);
		piv = 0;
		for(int i=0; i<m; i++){
			scanf("%d %d %d",&e[i].s,&e[i].e,&e[i].x);
			ans[e[i].s] = min(ans[e[i].s], e[i].x);
			ans[e[i].e] = min(ans[e[i].e], e[i].x);
		}
		sort(e, e + m);
		ALT.clear();
		disj.init(n);
		int cnt = 0;
		for(int i=0; i<m; i++){
			if(disj.uni(e[i].s, e[i].e)){
				cnt++;
				gph[e[i].s].emplace_back(e[i].x, e[i].e);
				gph[e[i].e].emplace_back(e[i].x, e[i].s);
			}
			else{
				ALT.push_back(e[i]);
			}
		}
		printf("Case %d: ", ++FUCK);
		if(cnt != n - 1){
			for(int i=1; i<=n; i++) printf("-1 ");
		}
		else{
			solve();
			for(int i=1; i<=n; i++){
				if(ans[i] > 1.1e9) ans[i] = -1;
				printf("%d ", ans[i]);
			}
		}
		puts("");
		for(int i=1; i<=n; i++){
			gph[i].clear();
			lis[i].clear();
			prefixReq[i].clear();
			suffixReq[i].clear();
			pointUpd[i].clear();
		}
	}
}
