#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n, m;
vector<int> gph[MAXN];
vector<int> rev[MAXN];
vector<int> ngph[MAXN];
vector<int> dfn;
bool vis[MAXN];
int g;
int cmp[MAXN], indeg[MAXN], dep[MAXN];

int gcd(int x, int y){ return y ? gcd(y, x%y) : x; }

void dfs(int x){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(!vis[i]) dfs(i);
	}
	dfn.push_back(x);
}

void rdfs(int x, int p){
	cmp[x] = p;
	for(auto &i : rev[x]){
		if(!cmp[i]) rdfs(i, p);
	}
}

void dfs2(int x){
	vis[x] = 1;
	for(auto &i : ngph[x]){
		if(!vis[i]){
			dep[i] = dep[x] + 1;
			dfs2(i);
		}
		else{
			int myH = dep[x] + 1;
			int yourH = dep[i];
			if(myH != yourH) g = gcd(g, abs(myH - yourH));
		}
	}
}

void solve(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		gph[i].clear();
		rev[i].clear();
		ngph[i].clear();
	}
	dfn.clear();
	memset(vis, 0, sizeof(vis));
	memset(cmp, 0, sizeof(cmp));
	memset(indeg, 0, sizeof(indeg));
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		rev[e].push_back(s);
	}
	if(n == 1){
		puts("YES");
		return;
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	reverse(dfn.begin(), dfn.end());
	int p = 0;
	for(auto &i : dfn){
		if(!cmp[i]){
			rdfs(i, ++p);
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(cmp[i] != cmp[j]){
				indeg[cmp[j]]++;
			}
		}
	}
	int cnt = 0, pos = 0, stp = 0;
	for(int i=1; i<=p; i++){
		if(!indeg[i]){
			cnt++;
			pos = i;
		}
	}
	if(cnt != 1){
		puts("NO");
		return;
	}
	for(int i=1; i<=n; i++){
		if(cmp[i] != pos) continue;
		stp = i;
		for(auto &j : gph[i]){
			if(cmp[j] == pos){
				ngph[i].push_back(j);
			}
		}
	}
	g = 0;
	memset(vis, 0, sizeof(vis));
	memset(dep, 0, sizeof(dep));
	dfs2(stp);
	puts(g == 1 ? "YES" : "NO");
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}

