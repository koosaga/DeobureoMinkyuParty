#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n, f[MAXN], d[MAXN];
vector<int> gph[MAXN];
int vis[MAXN], deg[MAXN];

int dfs(int x, int p){
	d[x] = 1;
	for(auto &i : gph[x]){
		if(!deg[i] && i != p){
			dfs(i, x);
			d[x] += d[i];
		}
	}
	return d[x];
}

void solve(){
	memset(vis, 0, sizeof(vis));
	memset(deg, 0, sizeof(deg));
	for(int i=1; i<=n; i++) gph[i].clear();
	for(int i=1; i<=n; i++){
		deg[f[i]]++;
		gph[f[i]].push_back(i);
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[f[x]]--;
		if(deg[f[x]] == 0) que.push(f[x]);
	}
	for(int i=1; i<=n; i++){
		if(deg[i] && !vis[i]){
			vector<int> cyc;
			for(int j=i; !vis[j]; j=f[j]){
				vis[j] = 1;
				cyc.push_back(j);
			}
			int sum = 0;
			for(auto &j : cyc) sum += dfs(j, -1);
			for(auto &j : cyc) d[j] = sum;
		}
	}
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = (ret * piv) % mod;
		piv = (piv * piv) % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&f[i]);
		memset(d, 0, sizeof(d));
		solve(); // d[i] = |v s.t there is a path from v -> i|
		lint ans = 1;
		for(int i=1; i<=n; i++){
			ans += d[i] * ipow(d[i] + 1, mod - 2) % mod;
		}
		ans %= mod;
		cout << ans << endl;
	}
}

