#include <bits/stdc++.h>

using namespace std;

int go(int n, int l, int k, char *a, char mode) {
	unordered_map<int, int> tb;
	queue<int> que;
	int ret = mode == '1' ? 1e9 : -1e9;

	que.push(n);
	tb[n] = 0;
	while(!que.empty()) {
		int u = que.front();
		int d = tb[u]; que.pop();

		ret = (mode == '1') ? min(ret, u) : max(ret, u);

		static char s[12];
		sprintf(s, "%d", u);	

		for(int i = 0; i < l; i++) {
			if(s[i] != a[i]) {
				for(int j = l-1; j >= 0; j--) {
					if(s[j] == a[i]) {
						swap(s[i], s[j]);
						int v; sscanf(s, "%d", &v);
						if(tb.find(v) == tb.end() && d+1 <= k) {
							tb[v] = d + 1;
							que.push(v);
						}
						swap(s[i], s[j]);
					}
				}
				break;
			}
		}
	}
	return ret;
}

void solve() {

	int n, k; scanf("%d%d", &n, &k);
	k = min(k, 10);

	static char a[11];
	sprintf(a, "%d", n);
	int l = strlen(a);
	sort(a, a+l);
	if(a[0] == '0') {
		for(int i = 1; i < l; i++) {
			if(a[i] != '0') {
				swap(a[0], a[i]);
				break;
			}
		}
	}


	int ans1 = go(n, l, k, a, '1');

	sort(a, a+l);
	reverse(a, a+l);
	int ans2 = go(n, l, k, a, '2');

	printf("%d %d\n", ans1, ans2);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
}