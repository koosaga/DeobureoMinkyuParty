#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

const int MAXN = 200005;
const int MAXM = 200005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
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
			for(int i=0; i<n; i++){
				if(l[i] == -1 && dfs(i)){
					ret++;
				}
			}
		}
		return ret;
	}
}bpm;

int n;
vector<int> ver[205];
map<string, int> id;
vector<vector<pi>> part;

int main(){
	scanf("%d",&n);
	set<pi> remain;
	for(int i=0; i<n; i++){
		string s; cin >> s;
		id[s] = i;
		int q; scanf("%d",&q); ver[i].resize(q);
		for(auto &j : ver[i]){
			scanf("%d",&j);
			remain.insert(pi(i, j));
		}
	}
	int m; scanf("%d",&m);
	for(int i=0; i<m; i++){
		int q; scanf("%d",&q);
		char buf[50]; int x;
		vector<pi> v;
		while(q--){
			scanf("%s %d", buf, &x);
			pi p(id[string(buf)], x);
			v.push_back(p);
			remain.erase(p);
		}
		part.push_back(v);
	}
	for(auto &i : remain){
		vector<pi> v = {i};
		part.push_back(v);
	}
	map<pi, int> to_part_num;
	for(int i=0; i<part.size(); i++){
		for(auto &j : part[i]){
		//	printf("(%d, %d) = partition %d\n", j.first, j.second, i);
			to_part_num[j] = i;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<ver[i].size(); j++){
			int nxt = to_part_num[pi(i, ver[i][j])];
			bpm.add_edge(i, nxt);
		//	printf("ADD EDGE %d %d\n", i, nxt);
		}
	}
	int x = bpm.match(n);
	if(x != n) puts("No");
	else{
		puts("Yes");
		for(int i=0; i<n; i++){
			int r = bpm.l[i];
			for(auto &j : part[r]){
				if(j.first == i){
					printf("%d ", j.second);
					break;
				}
			}
		}
	}
}
