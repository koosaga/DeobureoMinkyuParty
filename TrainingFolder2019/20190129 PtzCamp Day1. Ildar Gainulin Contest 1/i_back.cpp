#include <bits/stdc++.h>
const int MAXN = 100005;
const int mod = 998244353;
using namespace std;
using lint = long long;

int col[10], adj[10][10];
lint poss[10];

void bktk(int x, int n, int c){
	if(x == n){
		poss[c]++;
		return;
	}
	int chk[10] = {};
	for(int j=0; j<10; j++){
		chk[j] = 0;
	}
	for(int j=0; j<n; j++){
		if(adj[x][j]) chk[col[j]] = 1;
	}
	for(int i=1; i<=c+1; i++){
		if(!chk[i]){
			col[x] = i;
			bktk(x + 1, n, max(i, c));
		}
	}
}

int n;

int vis;
void dfs(int x) {
	vis |= 1<<x;
	for(int j = 0; j < n; j++) {
		if(adj[x][j] && (vis >> j) % 2 == 0) dfs(j);
	}
}

set<vector<lint>> s;

int main(){
	int cnt = 0;
	for(n = 1; n <= 6; n++) {
		int m = n * (n-1) / 2;
		for(int mask = 0; mask < (1<<m); mask++) {
			memset(adj, 0, sizeof adj);
			for(int i = 0, tmp = mask; i < n; i++) {
				for(int j = i+1; j < n; j++) {
					adj[i][j] = adj[j][i] = (tmp & 1);
					tmp >>= 1;
				}
			}
			vis = 0;
			dfs(0);
			if(vis < (1<<n)-1) {
				continue;
			}
			memset(col ,0,sizeof col);
			memset(poss, 0, sizeof poss);
			bktk(0, n, 0);
			vector<lint> a;
			for(int i = 1; i <= n; i++) {
				a.push_back(poss[i]);
			}
			s.insert(a);
		}
	}

	int maxv = 0;
	for(auto it : s) {
		for(int x : it) printf("%d ", x), maxv = max(maxv, x);
		puts("");
	}
	printf("s.size() = %ld, maxv = %d\n", s.size(), maxv);
	return 0;
}
