#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 605;
const int MAXM = 2005;

namespace WGM{
	static const int INF = INT_MAX;
	static const int N = 605;
	struct edge{
		int u, v, w;
		edge(){}
		edge(int ui, int vi, int wi)
		:u(ui), v(vi), w(wi){}
	};
	int n, n_x;
	edge g[N*2][N*2];
	int lab[N*2];
	int match[N*2], slack[N*2], st[N*2], pa[N*2];
	int flo_from[N*2][N+1], S[N*2], vis[N*2];
	vector<int> flo[N*2];
	queue<int> q;
	int e_delta(const edge &e){
		return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2;
	}
	void update_slack(int u,int x){
		if(!slack[x]||e_delta(g[u][x])<e_delta(g[slack[x]][x]))slack[x]=u;
	}
	void set_slack(int x){
		slack[x] = 0;
		for(int u=1; u<=n; u++)
			if(g[u][x].w > 0 && st[u] != x && S[st[u]] == 0)
				update_slack(u, x);
	}
	void q_push(int x){
		if(x <= n) q.push(x);
		else for(size_t i=0; i<flo[x].size(); i++)
			q_push(flo[x][i]);
	}
	void set_st(int x, int b){
		st[x] = b;
		if(x > n) for(size_t i=0; i<flo[x].size(); i++)
			set_st(flo[x][i], b);
	}
	int get_pr(int b, int xr){
		int pr = find(flo[b].begin(), flo[b].end(), xr) - flo[b].begin();
		if(pr % 2 == 1){
			reverse(flo[b].begin()+1, flo[b].end());
			return (int)flo[b].size() - pr;
		}else return pr;
	}
	void set_match(int u, int v){
		match[u] = g[u][v].v;
		if(u<=n) return;
		edge e = g[u][v];
		int xr = flo_from[u][e.u], pr = get_pr(u, xr);
		for(int i=0; i<pr; i++) set_match(flo[u][i], flo[u][i^1]);
		set_match(xr, v);
		rotate(flo[u].begin(), flo[u].begin() + pr, flo[u].end());
	}
	void augment(int u, int v){
		for(;;){
			int xnv = st[match[u]];
			set_match(u, v);
			if(!xnv) return;
			set_match(xnv, st[pa[xnv]]);
			u = st[pa[xnv]], v = xnv;
		}
	}
	int get_lca(int u, int v){
		static int t=0;
		for(++t; u || v; swap(u, v)){
			if(u == 0) continue;
			if(vis[u] == t) return u;
			vis[u] = t;
			u = st[match[u]];
			if(u) u = st[pa[u]];
		}
		return 0;
	}
	void add_blossom(int u, int lca, int v){
		int b = n + 1;
		while(b <= n_x && st[b]) ++b;
		if(b > n_x) ++n_x;
		lab[b] = 0, S[b] = 0;
		match[b] = match[lca];
		flo[b].clear();
		flo[b].push_back(lca);
		for(int x = u, y; x != lca; x = st[pa[y]])
			flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
		reverse(flo[b].begin() + 1, flo[b].end());
		for(int x = v, y; x != lca; x = st[pa[y]])
			flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
		set_st(b, b);
		for(int x = 1; x <= n_x; ++x) g[b][x].w = g[x][b].w = 0;
		for(int x = 1; x <= n; ++x) flo_from[b][x] = 0;
		for(size_t i=0; i<flo[b].size(); i++){
			int xs = flo[b][i];
			for(int x=1; x<=n_x; ++x)
				if(g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x]))
					g[b][x] = g[xs][x], g[x][b] = g[x][xs];
			for(int x=1; x<=n; ++x)
				if(flo_from[xs][x]) flo_from[b][x] = xs;
		}
		set_slack(b);
	}
	void expand_blossom(int b){
		for(size_t i=0; i<flo[b].size(); ++i)
			set_st(flo[b][i], flo[b][i]);
		int xr = flo_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
		for(int i=0; i<pr; i += 2){
			int xs = flo[b][i], xns = flo[b][i+1];
			pa[xs] = g[xns][xs].u;
			S[xs] = 1, S[xns] = 0;
			slack[xs] = 0, set_slack(xns);
			q_push(xns);
		}
		S[xr] = 1, pa[xr] = pa[b];
		for(size_t i = pr+1; i<flo[b].size(); i++){
			int xs = flo[b][i];
			S[xs] = -1, set_slack(xs);
		}
		st[b] = 0;
	}
	bool on_found_edge(const edge &e){
		int u = st[e.u], v = st[e.v];
		if(S[v] == -1){
			pa[v] = e.u, S[v] = 1;
			int nu = st[match[v]];
			slack[v] = slack[nu] = 0;
			S[nu] = 0, q_push(nu);
		}else if(S[v] == 0){
			int lca = get_lca(u, v);
			if(!lca) return augment(u,v),augment(v,u),true;
			else add_blossom(u,lca,v);
		}
		return false;
	}
	bool matching(){
		memset(S+1,-1,sizeof(int)*n_x);
		memset(slack+1,0,sizeof(int)*n_x);
		q=queue<int>();
		for(int x=1;x<=n_x;x++){
			if(st[x]==x&&!match[x])pa[x]=0,S[x]=0,q_push(x);
		}
		if(q.empty())return false;
		for(;;){
			while(q.size()){
				int u=q.front();q.pop();
				if(S[st[u]]==1)continue;
				for(int v=1;v<=n;v++){
					if(g[u][v].w>0 && st[u]!=st[v]){
						if(e_delta(g[u][v])==0){
							if(on_found_edge(g[u][v]))return true;
						}else {
							update_slack(u,st[v]);
						}
					}
				}
			}
			int d=INF;
			for(int b=n+1;b<=n_x;b++){
				if(st[b]==b&&S[b]==1)d=min(d,lab[b]/2);
			}
			for(int x=1;x<=n_x;x++){
				if(st[x]==x&&slack[x]){
					if(S[x]==-1)d=min(d,e_delta(g[slack[x]][x]));
					else if(S[x]==0) d=min(d,e_delta(g[slack[x]][x])/2);
				}
			}
			for(int u=1;u<=n;u++){
				if(S[st[u]]==0){
					if(lab[u]<=d)return 0;
					lab[u]-=d;
				}else if(S[st[u]]==1)lab[u]+=d;
			}
			for(int b=n+1;b<=n_x;b++){
				if(st[b]==b){
					if(S[st[b]]==0) lab[b]+=d*2;
					else if(S[st[b]]==1) lab[b]-=d*2;
				}
			}
			q=queue<int>();
			for(int x=1;x<=n_x;x++){
				if(st[x]==x&&slack[x]&&st[slack[x]]!=x&&e_delta(g[slack[x]][x])==0) {
					if(on_found_edge(g[slack[x]][x])) return true;
				}
			}
			for(int b=n+1;b<=n_x;b++){
				if(st[b]==b&&S[b]==1&&lab[b]==0) expand_blossom(b);
			}
		}
		return false;
	}
	pair<long long,int>solve() {
		memset(match+1,0,sizeof(int)*n);
		n_x=n;
		int n_matches=0;
		long long tot_weight=0;
		for(int u=0;u<=n;u++)st[u]=u,flo[u].clear();
		int w_max=0;
		for(int u=1;u<=n;u++)for(int v=1;v<=n;v++) {
			flo_from[u][v]=(u==v?u:0);
			w_max=max(w_max,g[u][v].w);
		}
		for(int u=1;u<=n;u++) lab[u]=w_max;
		while(matching()) ++n_matches;
		for(int u=1;u<=n;u++) {
			if(match[u]&&match[u]<u){
				tot_weight+=g[u][match[u]].w;
			}
		}
		return make_pair(tot_weight,n_matches);
	}
	void add_edge(int u, int v, int w){ 
		g[u][v].w=g[v][u].w=max(g[u][v].w, w);
	}
	void init(int _n) {
		n = _n;
		for(int u=1;u<=n;u++) for(int v=1;v<=n;v++) {
			g[u][v] = edge(u, v, 0);
		}
	}
};

struct disj{
	int pa[MAXM];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x]== x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edge{ int first, second, idx; };
struct edhe{ int s, e, x;};
vector<edhe> drg;
vector<edge> gph[MAXN];

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int adj[MAXN][MAXN];
int trk[MAXN][MAXN];
int num[MAXN][MAXN];
int col[MAXN];
pi a[MAXN];

void trace(int x, int y, vector<int> &v){
	if(trk[x][y] == 0){
		v.push_back(num[x][y]);
		return;
	}
	trace(x, trk[x][y], v);
	trace(trk[x][y], y, v);
}

int n, m;
vector<int> bgph[MAXN];

void dfs_real(int x, int c){
	if(col[x]){
		assert(col[x] == c);
		return;
	}
	col[x] = c;
	for(auto &i : bgph[x]) dfs_real(i, 3 - c);
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		if(x == 0){
			i--;
			m--;
			continue;
		}
		gph[s].push_back({x, e, i});
		gph[e].push_back({x, s, ~i});
		drg.push_back({s, e, x});
	}
	disj.init(2 * m);
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end(), [&](const edge &x, const edge &y){
			int p = i, q = x.second, r = y.second;
			bool mode1 = (a[p] > a[q]);
			bool mode2 = (a[p] > a[r]);
			if(mode1 != mode2) return mode1 < mode2;
			return ccw(a[p], a[q], a[r]) > 0;
		});
		for(int j=0; j<gph[i].size(); j++){
			if(gph[i][j].idx < 0){
				gph[i][j].idx = ~gph[i][j].idx;
				gph[i][j].idx += m;
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j<gph[i].size(); j++){
			int dir1 = gph[i][j].idx;
			int dir2 = gph[i][(j+1)%gph[i].size()].idx;
			if(dir1 >= m) dir1 -= m;
			else dir1 += m;
			disj.uni(dir1, dir2);
		}
	}
	int lbl[MAXM] = {};
	int deg[MAXM] = {};
	int piv = 0;
	for(int i=0; i<2*m; i++) if(disj.find(i) == i) lbl[i] = ++piv;
	memset(adj, 0x3f, sizeof(adj));
	for(int i=0; i<m; i++){
		int l = lbl[disj.find(i)];
		int r = lbl[disj.find(i+m)];
		if(adj[l][r] > drg[i].x){
			adj[l][r] = adj[r][l] = drg[i].x;
			num[l][r] = num[r][l] = i;
		}
		deg[l] ^= 1;
		deg[r] ^= 1;
	}
	vector<int> v;
	for(int i=1; i<=piv; i++){
		if(deg[i]) v.push_back(i);
	}
	if(v.size()){
		for(int i=1; i<=piv; i++){
			for(int j=1; j<=piv; j++){
				for(int k=1; k<=piv; k++){
					if(adj[j][k] > adj[j][i] + adj[i][k]){
						adj[j][k] = adj[j][i] + adj[i][k];
						trk[j][k] = i;
					}
				}
			}
		}
		WGM::init(v.size());
		for(int i=0; i<v.size(); i++){
			for(int j=i+1; j<v.size(); j++){
			//	puts("this problem is wgs");
			//	printf("wgs add %d %d %d\n", i + 1, j + 1, 696969696 - adj[v[i]][v[j]]);
				WGM::add_edge(i + 1, j + 1, 696969696 - adj[v[i]][v[j]]);
			}
		}
		auto ans = WGM::solve();
		assert(ans.second == v.size() / 2);
		vector<int> elist;
		for(int i=1; i<=v.size(); i++){
			if(WGM::match[i] > i){
				trace(v[i-1], v[WGM::match[i]-1], elist);
			}
		}
		sort(elist.rbegin(), elist.rend());
		for(auto &i : elist){
	//		printf("%d\n", i);
			drg.erase(drg.begin() + i);
		}
	}
	int ans = 0;
	for(int i=0; i<drg.size(); i++){
//		printf("ans = %d %d\n", drg[i].s, drg[i].e);
		bgph[drg[i].s].push_back(drg[i].e);
		bgph[drg[i].e].push_back(drg[i].s);
		ans += drg[i].x;
	}
	cout << ans << endl;
	for(int i=1; i<=n; i++){
		if(!col[i]) dfs_real(i, 1);
		cout << col[i] - 1 << " ";
	}
	return 0;
}
