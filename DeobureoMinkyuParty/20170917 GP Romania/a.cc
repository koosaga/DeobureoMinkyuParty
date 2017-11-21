#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;

struct edg{int pos, cap, rev;};
vector<edg> gph[MAXN];
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

int match(int src, int sink){
	lint ret = 0;
	while(bfs(src, sink)){
		while(dfs(src, sink, 2e9));
	}
	return 0;
}

int vis[MAXN];

void dfs2(int x, int p){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(i.cap > 0 && !vis[i.pos]) dfs2(i.pos);
	}
}

int n, a[MAXN][MAXN];
int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
		}
	}
	for(int i=1; i<n; i++){
		for(int j=1; j<n; j++){
			int needy = a[0][j] + a[i][0] - a[0][0];
			needy = a[i][j] - needy;
			if(needy > 0) add_edge(i, j + n, needy);
		}
		add_edge(0, i, 1e9);
		add_edge(i + n, 2 * n, 1e9);
	}
	match(0, 2*n);
	dfs2(0);
} 
