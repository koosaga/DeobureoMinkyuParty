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


lint ans;

void dfs(int x, int p, int d, int l, int r){
	if(r - l == d) ans++;
	for(auto &i : gph[x]){
		if(vis[i] || i == p) continue;
		dfs(i, x, d+1, min(l, i), max(r, i));
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		dfs(i, -1, 0, i, i);
	}
	printf("%lld", (ans + n) /2);
}
