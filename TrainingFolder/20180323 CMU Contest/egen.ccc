#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 50005;

int n;
bool vis[MAXN];
vector<int> gph[MAXN];
vector<int> dfn;
int sz[MAXN], msz[MAXN];

void dfs2(int x, int p){
	msz[x] = 0;
	sz[x] = 1;
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(i == p || vis[i]) continue;
		dfs2(i, x);
		msz[x] = max(msz[x], sz[i]);
		sz[x] += sz[i];
	}
}

int get_center(int x){
	dfs2(x, -1);
	pi ans(1e9, 1e9);
	for(auto &i : dfn){
		int cursz = max(msz[i], (int)dfn.size() - sz[i]);
		ans = min(ans, pi(cursz, i));
	}
	dfn.clear();
	return ans.second;
}

struct Fuck{
	int lo, hi, dep;
}cur[MAXN], aux[MAXN];

int ptr1, ptr2;

void dfs(int x, int p, int d, int l, int r){
	aux[ptr2++] = {l, r, d};
	for(auto &i : gph[x]){
		if(vis[i] || i == p) continue;
		dfs(i, x, d+1, min(l, i), max(r, i));
	}
}

int solve(int x){
	ptr1 = 1;
	cur[0] = {x, x, 0};
	int ans = 0;
	for(auto &i : gph[x]){
		if(!vis[i]){
			ptr2 = 0;
			dfs(i, x, 1, min(i, x), max(i, x));
			for(int a=0; a<ptr1; a++){
				for(int b=0; b<ptr2; b++){
					if(cur[a].dep + aux[b].dep == max(aux[b].hi, cur[a].hi) - min(aux[b].lo, cur[a].lo)){
						ans++;
					}
				}
			}
			for(int i=0; i<ptr2; i++) cur[ptr1++] = aux[i];
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	queue<int> que;
	que.push(1);
	int ans = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		vis[x] = 1;
		ans += solve(x);
		for(auto &i : gph[x]){
			if(!vis[i]) que.push(i);
		}
	}
	printf("%d", ans + n);
}
