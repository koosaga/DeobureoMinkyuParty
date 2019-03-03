#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 10050;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct mf{
	struct edg{int pos, cap, rev; };
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
}Sex, mf;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear(); 
	}
	void add_edge(int l, int r) { gph[l].push_back(r); }
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0 ;i<n; i++){
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
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i;
				r[i] = x;
				return 1;
			}
		}
		return 0;
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

int n, m;
char str[222][222];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && isalpha(str[x][y]);
}

int get(int x, int y){
	return x * m + y;
}


int solve(int c, int r = 0){
	Sex = mf;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(ok(i, j) == 0) continue;
			if((i + j) % 2 == 1){
				if(str[i][j] == 'a' + c) Sex.add_edge(get(i, j) + 1, n * m + 1, 1);
			}
			else{
				if(str[i][j] == 'a' + c) Sex.add_edge(0, get(i, j) + 1, 1);
			}
		}
	}
	return Sex.match(0, n * m + 1);
}

int SEX(){
	mf.clear();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(ok(i, j) == 0) continue;
			if((i + j) % 2 == 1){
				mf.add_edge(get(i, j) + 1, n * m + 1, 42000);
			}
			else{
				mf.add_edge(0, get(i, j) + 1, 42000);
				for(int k=0; k<4; k++){
					if(ok(i +dx[k], j + dy[k]) && str[i][j] != str[i + dx[k]][j + dy[k]]){
						mf.add_edge(get(i, j) + 1, 1 +  get(i + dx[k], j + dy[k]), 1e9);
					}
				}
			}
		}
	}
	return mf.match(0, n * m + 1) / 42000;
}

int cnt[26];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(ok(i, j) == 0) continue;
			cnt[str[i][j] - 'a']++;
		}}
	cout << SEX() << endl;
	for(int i=0; i<26; i++){
		if(cnt[i] == 0) continue;
		int dap = solve(i);
		if(dap != cnt[i]) putchar(i + 'a');
	}
	puts("");
}
