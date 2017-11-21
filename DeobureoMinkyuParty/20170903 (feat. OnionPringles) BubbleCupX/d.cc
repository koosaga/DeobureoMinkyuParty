#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 605;
const int MAXM = 605;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int l, int r){
		gph[l].push_back(r);
	}
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				vis[r[i]] = 1;
				l[x] = i;
				r[i] = x;
				return true;
			}
		}
		return false;
	}
	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++) if(l[i] == -1 && dfs(i)) ret++;
		}
		return ret;
	}
}bpm;

vector<pi> gph[MAXN];
int dist[205][MAXN];
int n, m, p, q;
int a[MAXN];

bool trial(int x){
	bpm.clear();
	for(int i=1; i<=p; i++){
		for(int j=1; j<=n; j++){
			if(dist[i][j] <= x) bpm.add_edge(i-1, j-1);
		}
	}
	int w = bpm.match(p);
	return w >= q;
}

void dijk(int *d, int s){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	d[s] = 0;
	pq.push(pi(0, s));
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(d[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(d[i.second] > i.first + x.first){
				d[i.second] = i.first + x.first;
				pq.push(pi(d[i.second], i.second));
			}
		}
	}
}

int main(){
	scanf("%d %d %d %d",&n,&m,&p,&q);
	for(int i=1; i<=p; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=1; i<=p; i++){
		dijk(dist[i], a[i]);
	}
	int s = 0, e = 1731311;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	if(!trial(s)) s = -1;
	cout << s << endl;
}
