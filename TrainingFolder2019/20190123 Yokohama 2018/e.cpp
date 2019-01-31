#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int n_ = 105;

int n, m;
bool gph[n_][n_];

bool ans[n_][n_]; int cnt;

int par[n_][n_];

bool vis[n_];

int deg[n_];

void dfs(int s, int u) {
	vis[u] = true;
	for(int v = 1; v <= n; v++) if(!gph[u][v] && !vis[v]) {
		par[s][v] = u;
		dfs(s, v);
	}
}

vector<int> cm;
int wh[n_];
void dfs2(int s, int u) {
	wh[u] = s;
	cm.push_back(u);
	vis[u] = true;
	for(int v = 1; v <= n; v++) if((gph[u][v] || ans[u][v]) && !vis[v]) {
		dfs2(s, v);
	}
}

void upd_ans(int x, int y){
	assert(x != y);
	assert(!gph[x][y]);
	ans[x][y] ^= 1;
	ans[y][x] ^= 1;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b; scanf("%d%d", &a, &b);
		gph[a][b] = gph[b][a] = true;
		deg[a] += 1; deg[b] += 1;
	}

	for(int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof vis);
		for(int j = 1; j <= n; j++) par[i][j] = -1;
		dfs(i, i);
	}

	vector<int> odd;
	for(int i = 1; i <= n; i++) {
		if(deg[i] % 2 == 1) {
			odd.push_back(i);
		}
	}

	assert(odd.size() % 2 == 0);

	while(!odd.empty()) {
		int u = -1, v = -1;
		for(int i = 0; i < odd.size(); i++) {
			for(int j = 0; j < i; j++) {
				if(par[odd[i]][odd[j]] != -1) {
					u = odd[i];
					v = odd[j];
					break;
				}
			}
		}
		if(u == -1) {
			puts("-1");
			return 0;
		}
		odd.erase(find(odd.begin(), odd.end(), u));
		odd.erase(find(odd.begin(), odd.end(), v));
		for(int x = v; x != u; ) {
			int y = par[u][x];
			upd_ans(x, y);
			x = y;
		}
	}

	for(int i = 1; i <= n; i++) {
		int d = 0;
		for(int j = 1; j <= n; j++) {
			if(gph[i][j] || ans[i][j]) d += 1;
		}
		assert(d % 2 == 0);
	}

	memset(vis, 0, sizeof vis);
		
	vector<pii> left;
	for(int i = 1; i <= n; i++) {
		cm.clear();
		if(!vis[i]) {
			dfs2(i, i);
			left.emplace_back(cm.front(), cm.size());
		}
	}

	if(left.size() == 2) {
		int c = wh[1];
		vector<int> tt[2];
		for(int i = 1; i <= n; i++) tt[wh[i] == c].push_back(i);

		bool good = false;

		for(int k = 0; k < 2; k++) {
			vector<int> &grp = tt[k];

			int u = -1, v = -1;
			for(int i = 0; i < grp.size(); i++) {
				for(int j = 0; j < i; j++) {
					if(!gph[grp[i]][grp[j]]) {
						u = grp[i];
						v = grp[j];
						break;
					}
				}
			}
			if(u > 0) {
				int w = tt[!k].front();
				upd_ans(u, v);
				upd_ans(v, w);
				upd_ans(w, u);
				good = true;
				break;
			}
		}

		if(!good) {
			if(tt[0].size() >= 2 && tt[1].size() >= 2) {
				int u = tt[0][0], v = tt[0][1];
				int x = tt[1][0], y = tt[1][1];
				upd_ans(u, x);
				upd_ans(u, y);
				upd_ans(v, x);
				upd_ans(v, y);
			}else {
				puts("-1");
				return 0;
			}
		}
	}else if(left.size() > 1) {
		for(int i = 0; i < left.size(); i++) {
			int j = (i+1) % left.size();
			upd_ans(left[i].first, left[j].first);
		}
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(ans[i][j]) {
				cnt += 1;
			}
		}
	}
	assert(cnt % 2 == 0);
	cnt /= 2;

	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) {
		for(int j = i+1; j <= n; j++) {
			if(ans[i][j]) printf("%d %d\n", i, j);
		}
	}
	
	memset(vis, 0, sizeof vis);
	cm.clear();
	dfs2(1, 1);
	assert(cm.size() == n);
	for(int i = 1; i <= n; i++) {
		int d = 0;
		for(int j = 1; j <= n; j++) {
			if(gph[i][j] || ans[i][j]) d += 1;
		}
		assert(d % 2 == 0);
	}
	return 0;
}