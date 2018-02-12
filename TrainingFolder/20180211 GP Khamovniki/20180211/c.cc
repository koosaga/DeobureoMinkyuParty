#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 1005;

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
					que.push(r[i]);
					dis[r[i]] = dis[x] + 1;
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 &&
				dfs(r[i]))){
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

int n, m;
vector<int> gph[MAXN];

bool solve(int r){
	int chk[MAXN] = {};
	for(auto &i : gph[r]) chk[i] = 1;
	vector<int> lv, rv;
	for(int i=1; i<=n; i++){
		if(i == r) continue;
		if(chk[i]) lv.push_back(i);
		else rv.push_back(i);
	}
	if(lv.size() < rv.size()) return 0;
	bpm.clear();
	for(int i=0; i<rv.size(); i++){
		for(auto &j : gph[rv[i]]){
			if(chk[j]) bpm.add_edge(i, j);
		}
	}
	if(bpm.match(rv.size()) != (int)rv.size()) return 0;
	vector<int> honbab;
	vector<pi> inssa;
	memset(chk, 0, sizeof(chk));
	for(int i=0; i<rv.size(); i++){
		int pos = bpm.l[i];
		chk[pos] = 1;
		inssa.push_back(pi(rv[i], pos));
	}
	for(auto &i : lv) if(!chk[i]) honbab.push_back(i);
	puts("Yes");
	printf("%d %d\n", r, honbab.size() + inssa.size());
	for(auto &i : inssa) printf("%d %d\n", i.first, i.second);
	for(auto &i : honbab) printf("%d -1\n", i);
	return 1;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e;
		cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		if((int)gph[i].size() >= n / 2 - 2){
			if(solve(i)){
				return 0;
			}
		}
	}
	puts("No");
}
