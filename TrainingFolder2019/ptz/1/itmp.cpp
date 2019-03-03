#include <bits/stdc++.h>
const int MAXN = 100005;
const int mod = 998244353;
using namespace std;
using lint = long long;

int n, m;
vector<int> gph[MAXN];
vector<int> dfn;
bool vis[MAXN];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	dfn.push_back(x);
	for(auto &i : gph[x]) dfs(i);
}

int col[10], adj[10][10];
lint poss[10], ans[MAXN], tmp[MAXN];
lint fact[MAXN], invf[MAXN];

void bktk(int x, int n, int c){
	if(x == n){
		poss[c]++;
		return;
	}
	int chk[10] = {};
	for(int j=0; j<x; j++){
		if(adj[x][j]) chk[col[j]] = 1;
	}
	for(int i=1; i<=c+1; i++){
		if(!chk[i]){
			col[x] = i;
			bktk(x + 1, n, max(i, c));
		}
	}
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	fact[0] = invf[0] = 1;
	for(int i=1; i<=n; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end());
	}
	auto has_edge = [&](int x, int y){
		return binary_search(gph[x].begin(), gph[x].end(), y);
	};
	fill(ans + 1, ans + n + 1, 1); 
	int cmp = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfn.clear();
			dfs(i);
			assert(dfn.size() <= 8);
			memset(col, 0, sizeof(col));
			memset(adj, 0, sizeof(adj));
			memset(poss, 0, sizeof(poss));
			for(int j=0; j<dfn.size(); j++){
				for(int k=0; k<j; k++){
					if(has_edge(dfn[j], dfn[k])) adj[j][k] = adj[k][j] = 1;
				}
			}
			bktk(0, dfn.size(), 0);
			memset(tmp, 0, sizeof(tmp));
			vector<lint> vect(poss, poss + dfn.size() + 1);
	//		pool.emplace(dfn.size() + 1, vect);
			for(int i=1; i<=dfn.size(); i++){
				for(int j=i; j<=n; j++){
					tmp[j] += poss[i] * invf[j - i] % mod;
					tmp[j] %= mod;
				}
			}
			for(int i=1; i<=n; i++) ans[i] *= tmp[i];
			for(int i=1; i<=n; i++) ans[i] %= mod;
			cmp++;
		}
	}
	for(int i=1; i<=n; i++){
		ans[i] *= ipow(fact[i], cmp);
		ans[i] %= mod;
		printf("%lld ", ans[i]);
	}
}
