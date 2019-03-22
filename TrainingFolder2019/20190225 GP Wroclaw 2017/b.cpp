#include <bits/stdc++.h>
using namespace std;

using lint = long long;
namespace DINIC
{
	const int MAXN = 210;
	struct edg{ int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}
	int dis[MAXN], pnt[MAXN];
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
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
};

struct edg
{
	int x, y, w;
};

void solve()
{
	int n, m, sw, tw, so, to, i;
	scanf("%d%d", &n, &m);
	vector<edg> v;
	for(i=0; i<m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		v.push_back({a, b, c});
	}
	scanf("%d%d%d%d", &sw, &tw, &so, &to);
	
	int S = n + 1;
	int T = n + 2;
	
	DINIC::clear();
	for(edg e : v)
	{
		DINIC::add_edge(e.x, e.y, e.w);
		DINIC::add_edge(e.y, e.x, e.w);
	}
	DINIC::add_edge(S, sw, 1e9);
	DINIC::add_edge(S, so, 1e9);
	DINIC::add_edge(tw, T, 1e9);
	DINIC::add_edge(to, T, 1e9);
	
	lint r1 = DINIC::match(S, T);
	
	
	DINIC::clear();
	for(edg e : v)
	{
		DINIC::add_edge(e.x, e.y, e.w);
		DINIC::add_edge(e.y, e.x, e.w);
	}
	DINIC::add_edge(S, sw, 1e9);
	DINIC::add_edge(S, to, 1e9);
	DINIC::add_edge(tw, T, 1e9);
	DINIC::add_edge(so, T, 1e9);
	
	lint r2 = DINIC::match(S, T);
	
	
	printf("%.10lf\n", (double)min(r1, r2));
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}

























