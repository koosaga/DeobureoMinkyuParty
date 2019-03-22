#include <bits/stdc++.h>

using namespace std;

const int N_ = int(2.1e5);

int n, m;
vector<int> gph[N_];
int col[N_];

bool dfs(int u) {
	bool good = true;
	for(int v : gph[u]) {
		if(col[v] == -1) {
			col[v] = 1-col[u];
			dfs(v);
		}else {
			good &= (col[v] == 1-col[u]);
		}
	}
	return good;
}

int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= m; i++) {
			int u, v; scanf("%d%d", &u, &v);
			gph[u].push_back(v);
			gph[v].push_back(u);
		}
		
		for(int i = 1; i <= n; i++) col[i] = -1;
		col[1] = 0;
		dfs(1);
		
		// TODO init
		bool good = true;
		for(int i = 1; i <= n; i++) {
			assert(col[i] >= 0);
			for(int j : gph[i]) {
				good &= col[i] != col[j];
			}
		}
		
		puts(good ? "1" : "0");
		
		for(int i = 1; i <= n; i++) gph[i].clear();
		
	}	
	return 0;
}
