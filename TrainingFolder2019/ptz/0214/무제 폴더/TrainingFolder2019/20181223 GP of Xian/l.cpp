#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[int(1.1e5)];
vector<int> gph[int(1.1e5)];

bool chk[2][int(1.1e5)];
int cnt[2], nxt[2];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		cnt[a[i]] += 1;
	}

	for(int i = 0; i < m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		gph[u].push_back(v);
		gph[v].push_back(u);
	}

	for(int u = 1; u <= n; u++) {
		for(int v : gph[u]) {
			if(a[u] != a[v]) {
				chk[a[u]][v] = true;
			}
		}
	}

	for(int u = 1; u <= n; u++) for(int i = 0;i < 2; i++) if(chk[i][u]) nxt[i] += 1;

	for(int u = 1; u <= n; u++) {
		int num_jumps = 0;
		for(int v : gph[u]) {
			if(a[u] != a[v]) num_jumps += 1;
		}

		int d1 = num_jumps + cnt[a[u]] - 1;	

		long long ret = 0;
		if(num_jumps > 0) {
			ret += 1 * d1;
			ret += 2 * (n - 1 - d1); // d = 2
		}else {
			ret += 1 * d1; // d = 1
			ret += 2 * nxt[a[u]]; // d = 2
			ret += 3 * (n - 1 - d1 - nxt[a[u]]);
		}

		printf("%lld%c", ret, u == n ? '\n' : ' ');
	}
	return 0;
}