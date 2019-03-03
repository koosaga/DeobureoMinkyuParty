#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

namespace Fuck{
	static char buf[1<<19];
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
		if(c == '-') s = -1, c = _read();
		while(c > 32) x = 10 * x + (c - '0'), c = _read();
		if(s < 0) x = -x;
		return x;
	}
}

const int MAXN = 200005;
int n;
vector<int> gph[MAXN];
bitset<MAXN> mark;

namespace CentroidDecomposition{
	vector<int> gph[MAXN]; 
	void add_edge(int s, int e){
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int sz[MAXN], msz[MAXN];
	vector<int> dfn;
	vector<int> info[MAXN];
	vector<vector<int>> pinfo[MAXN];
	int dep[MAXN], dist[MAXN][18];
	pi par[MAXN];
	void dfs(int x, int p){
		dfn.push_back(x);
		sz[x] = 1; msz[x] = 0;
		for(auto &i : gph[x]){
			if(i != p && !par[i].first){
				dfs(i, x);
				sz[x] += sz[i];
				msz[x] = max(msz[x], sz[i]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, -1);
		for(auto &i : dfn){
			int szv = max((int)dfn.size() - sz[i], msz[i]);
			ret = min(ret, pi(szv, i));
		}
		return ret.second;
	}
	struct node{
		int pos, par, pidx, dep;
	};
	void dfs2(int x, int p, int d, vector<int> &v, int ptr){
		dist[x][ptr] = d;
		if(mark[x]) v.push_back(d);
		for(auto &i : gph[x]){
			if(i != p && !par[i].first){
				dfs2(i, x, d + 1, v, ptr);
			}
		}
	}
	void regen(vector<int> &v){
		if(v.empty()) return;
		int mx = *max_element(v.begin(), v.end());
		vector<int> nxt(mx + 1);
		for(auto &i : v) nxt[i]++;
		for(int i=0; i<mx; i++) nxt[i+1] += nxt[i];
		v = nxt;
	}
	void make(int v){
		queue<node> que;
		que.push({1, -1, -1, 0});
		while(!que.empty()){
			auto nd = que.front();
			que.pop();
			int x = nd.pos;
			x = get_center(x);
			par[x] = pi(nd.par, nd.pidx);
			dep[x] = nd.dep;
			for(auto &i : gph[x]){
				pinfo[x].emplace_back();
				if(!par[i].first){
					dfs2(i, x, 1, pinfo[x].back(), dep[x]);
					for(auto &j : pinfo[x].back()) info[x].push_back(j);
				}
			}
			if(mark[x]) info[x].push_back(0);
			regen(info[x]);
			for(int i=0; i<gph[x].size(); i++) regen(pinfo[x][i]);
			int idx = 0;
			for(auto &i : gph[x]){
				if(!par[i].first){
					que.push({i, x, idx, dep[x] + 1});
				}
				idx++;
			}
		}
	}
	int query(vector<int> &v, int q){
		if(v.empty()) return 0;
		q = min(q, (int)v.size() - 1);
		return v[q];
	}
	int query(int x, int d){
		int ret = 0;
		for(int i=x; i!=-1; i=par[i].first){
			if(d - dist[x][dep[i]] >= 0){
				ret += query(info[i], d - dist[x][dep[i]]);
			}
			if(par[i].first != -1){
				int nx = par[i].first;
				int ni = par[i].second;
				if(d >= dist[x][dep[nx]]){
					ret -= query(pinfo[nx][ni], d - dist[x][dep[nx]]);
				}
			}
		}
		return ret;
	}
	void clear(int v){
		for(int i=1; i<=v; i++){
			gph[i].clear(); 
			info[i].clear();
			pinfo[i].clear();
			par[i] = pi(0, 0);
            memset(dist[i], 0, sizeof(dist[i]));
		}
	}
}

int query(int x, int d){ return CentroidDecomposition::query(x, d); }

int par[18][MAXN], dep[MAXN];

void dfs(int x){
	for(auto &i : gph[x]){
		dep[i] = dep[x] + 1;
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		par[0][i] = x;
		dfs(i);
	}
}

int anc(int x, int v){
	for(int i=0; i<18; i++){
		if((v >> i) & 1) x = par[i][x];
	}
	return x;
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	y = anc(y, dep[y] - dep[x]);
	for(int i=17; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

vector<int> gggph[MAXN];
vector<int> dfn;

void dddfs(int x, int p){
	dfn.push_back(x);
	for(auto &i : gggph[x]){
		if(i != p){
			dddfs(i, x);
		}
	}
}

vector<int> relabel(vector<pi> v){
	for(int i=0; i<=2*n; i++) gggph[i].clear();
	for(auto &i : v){
		gggph[i.first].push_back(i.second);
		gggph[i.second].push_back(i.first);
	}
	dfn.clear();
	dddfs(1, 0);
	vector<int> p(n*2);
	for(int i=0; i<dfn.size(); i++) p[dfn[i]] = i + 1;
	return p;
}

int main(){
	int tc = Fuck::_readInt();
	while(tc--){
		n = Fuck::_readInt();
		int m = Fuck::_readInt();
		for(int i=1; i<=n*2; i++){
			gph[i].clear();
		}
		vector<pi> drog;
		for(int i=0; i<n-1; i++){
			int s, e; 
			s = i + 2;
			e = s - 1;
			s = Fuck::_readInt();
			e = Fuck::_readInt();
			drog.emplace_back(s, i + n + 1);
			drog.emplace_back(e, i + n + 1);
		}
		auto p = relabel(drog);
		for(int i=0; i<2*n-2; i++){
			int s, e; tie(s, e) = drog[i];
			s = p[s];
			e = p[e];
			gph[e].push_back(s);
			gph[s].push_back(e);
			CentroidDecomposition::add_edge(s, e);
		}
		for(int i=1; i<=n; i++) mark[p[i]] = 1;
		CentroidDecomposition::make(2 * n - 1);
		for(int i=1; i<=n; i++) mark[p[i]] = 0;
		dfs(1);
		for(int i=1; i<18; i++){
			for(int j=1; j<=2*n-1; j++) par[i][j] = par[i-1][par[i-1][j]];
		}
		int last = 0;
		while(m--){
			int x, y, d;
			x = rand() % n;
			y = rand() % n;
			d = rand() % 100;
			x = Fuck::_readInt();
			y = Fuck::_readInt();
			d = Fuck::_readInt();
			x = (x + last) % n + 1; 
			y = (y + last) % n + 1;
			d = (d + last) % n;
			x = p[x];
			y = p[y];
			last = CentroidDecomposition::query(x, d+d) + CentroidDecomposition::query(y, d+d);
			int l = lca(x, y);
			if(dep[x] > dep[y]) swap(x, y);
			int dv = dep[x] + dep[y] - 2 * dep[l];
			if(dv <= d * 4) last -= CentroidDecomposition::query(anc(y, dv / 2), 2 * d - dv / 2);
			printf("%d\n", last);
		}
		CentroidDecomposition::clear(n+n-1);
	}
}


