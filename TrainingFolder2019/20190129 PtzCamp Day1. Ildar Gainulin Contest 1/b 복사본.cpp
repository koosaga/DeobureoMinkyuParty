#include <bits/stdc++.h>

using namespace std;

void solve() {
	unordered_map<int, int> tb;
	queue<int> que;

	int n, k; scanf("%d%d", &n, &k);
	que.push(n);
	while(!que.empty()) {
		static char tmp[15];
		int u = que.front(); que.pop();
		sprintf(tmp, "%d", u);
		int l = strlen(tmp);
		for(int i = 0; i < l; i++) {
			for(int j = i+1; j < l; j++) {
				swap(tmp[i], tmp[j]);
				if(tmp[0] != '0') {
					int v;
					sscanf(tmp, "%d", &v);
					if(tb.find(v) == tb.end()) {
						tb[v] = tb[u] + 1;
						que.push(v);
					}
				}
				swap(tmp[i], tmp[j]);
			}
		}
	}

	int ans1 = 1e9;
	int ans2 = -1e9;
	for(auto it : tb) {
		if(it.second <= k && (it.second - k) % 2 == 0) {
			ans1 = min(ans1, it.first);
			ans2 = max(ans2, it.first);
		}
	}

	assert(ans2 >= 0);
	printf("%d %d\n", ans1, ans2);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
}