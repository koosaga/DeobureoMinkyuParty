#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 50000;

int n, m, k;

struct maxflow{
	struct edg{ int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1});
	}
	int dis[MAXN], pnt[MAXN];
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front(); que.pop();
			for(auto &e : gph[x]){
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	lint match(int src, int sink){
		lint ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}mf;

struct circ{
	maxflow mf;
	lint lsum;
	void add_edge(int s, int e, int l, int r){
		lsum += l;
		mf.add_edge(s + 2, e + 2, r - l);
		mf.add_edge(0, e + 2, l);
		mf.add_edge(s + 2, 1, l);
	}
	bool solve(int s, int e){
		mf.add_edge(e + 2, s + 2, 1e9);
		return lsum == mf.match(0, 1);
		mf.match(s + 2, e + 2);
	}
}circ;

struct edg{ int l, r, idx; };
vector<edg> elist[10005];
map<int, int> new_vtx[10005];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1; i<=k; i++){
		int x, y, l;
		scanf("%d %d %d",&x,&y,&l);
		elist[l].push_back({x, y, i});
	}
	for(int i=1; i<=n; i++){
		circ.add_edge(0, i, 1, 1e9);
	}
	for(int i=1; i<=m; i++){
		circ.add_edge(i + n, m + n + 1, 1, 1e9);
	}
	int piv = n + m + 1;
	for(int i=1; i<=k; i++){
		for(auto &j : elist[i]){
			j.r += n;
			if(new_vtx[i].find(j.l) == new_vtx[i].end()) new_vtx[i][j.l] = ++piv;
			if(new_vtx[i].find(j.r) == new_vtx[i].end()) new_vtx[i][j.r] = ++piv;
		}
		set<int> ldid, rdid;
		for(auto &j : elist[i]){
			if(ldid.find(j.l) == ldid.end()){
				circ.add_edge(j.l, new_vtx[i][j.l], 0, 1);
				ldid.insert(j.l);
			}
			if(rdid.find(j.r) == rdid.end()){
				circ.add_edge(new_vtx[i][j.r], j.r, 0, 1);
				rdid.insert(j.r);
			}
			circ.add_edge(new_vtx[i][j.l], new_vtx[i][j.r], 0, 1);
		}
	}
	if(!circ.solve(0, n + m + 1)){
		puts("-1");
		return 0;
	}
	vector<int> dap;
	for(int i=1; i<=k; i++){
		vector<int> lside;
		for(auto &j : elist[i]){
			lside.push_back(new_vtx[i][j.l]);
		}
		sort(lside.begin(), lside.end());
		lside.resize(unique(lside.begin(), lside.end()) - lside.begin());
		vector<pi> E;
		for(auto &j : lside){
			for(auto &k : circ.mf.gph[j+2]){
				if(k.cap == 0 && k.pos > n + m + 3){
					E.emplace_back(j, k.pos - 2);
				}
			}
		}
		for(auto &j : E){
			for(auto &k : new_vtx[i]){
				if(k.second == j.first){
					j.first = k.first;
					break;
				}
			}
			for(auto &k : new_vtx[i]){
				if(k.second == j.second){
					j.second = k.first;
					break;
				}
			}
		}
		for(auto &j : E){
			for(int k=0; k<elist[i].size(); k++){
				if(pi(elist[i][k].l, elist[i][k].r) == j){
					dap.push_back(elist[i][k].idx);
					elist[i].erase(elist[i].begin() + k);
					break;
				}
			}
		}
	}
	sort(dap.begin(), dap.end());
	cout << dap.size() << endl;
	for(auto &i : dap) cout << i << " ";
}
