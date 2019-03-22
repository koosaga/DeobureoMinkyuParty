#include <bits/stdc++.h>

using namespace std;

namespace DINIC
{
	const int MAXN = 1222;
	struct edg
	{
		int pos, cap, rev;
	};

	vector<edg> gph[MAXN];
	void clear() {
		for(int i=0; i<MAXN; i++)
			gph[i].clear();
	}
	void add_edge(int s, int e, int x) {
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1});
	}
	int dis[MAXN], pnt[MAXN];
	bool bfs(int src, int sink) {
		memset(dis, 0, sizeof dis);
		memset(pnt, 0, sizeof pnt);
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()) {
			int x = que.front();
			que.pop();
			for(auto &e : gph[x]) {
				if(e.cap > 0 && !dis[e.pos]) {
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
	int dfs(int x, int sink, int f) {
		if(x == sink)
			return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++) {
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1) {
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w) {
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	long long match(int src, int sink) {
		long long ret = 0;
		while(bfs(src, sink)) {
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
};

int deg[610], p[610];
int col[610];
pair<int, int> a[1000];

void solve()
{
	int n, m, k, i;
	scanf("%d%d%d", &n, &m, &k);
	DINIC::clear();
	memset(deg, 0, sizeof(deg));
	for(int i=0; i<m; i++){
		cin >> a[i].first >> a[i].second;
		deg[a[i].first]++;
		deg[a[i].second]++;
		DINIC::add_edge(a[i].first, i + n + 1, 1);
		DINIC::add_edge(a[i].second, i + n + 1, 1);
		DINIC::add_edge(i + n + 1, n + m + 1, 1);
	}
	for(int i=1; i<=n; i++){
		p[i] = max(deg[i] - k, 0);
		DINIC::add_edge(0, i, p[i] * 2);
	}
	int sum = accumulate(p + 1, p + n + 1, 0) * 2;
	if(DINIC::match(0, n + m + 1) != sum){
		for(int i=1; i<=m; i++) printf("0 ");
		puts("");
		return;
	}
	for(int i=0; i<m; i++) col[i] = i + 1;
	for(int i=1; i<=n; i++){
		vector<int> v;
		for(auto &j : DINIC::gph[i]){
			if(j.pos == 0) continue;
			if(j.cap == 0) v.push_back(j.pos - n - 1);
		}
		for(int i=0; i<v.size(); i+=2){
			col[v[i+1]] = col[v[i]];
		}
	}
	for(int i=0; i<m; i++) printf("%d ", col[i]);
	puts("");
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}
