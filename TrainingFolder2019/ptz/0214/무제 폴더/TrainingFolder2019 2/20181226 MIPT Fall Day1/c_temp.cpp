#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

char s[101];

pair<int, int> a[101];
inline int C(int i, int j) {
	return (a[i].second - a[j].second) == +1 ? 0 : 1;
}
inline int D(int i, int j) {
	return (a[i].second - a[j].second) == -1 ? 0 : 1;
}

int dp[101][101];

char t[101];

int main() {
	scanf("%s", t);
	int m = strlen(t);

	s[0] = t[0];
	for(int i = 0, j = 1; j < m; j++) {
		if(s[i] != t[j]) {
			s[++i] = t[j];
		}
	}
	int n = strlen(s);

	for(int i = 0; i < n; i++) {
		a[i] = make_pair(s[i], -i);
	}
	sort(a, a+n, greater<pii>());

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			dp[i][j] = 1e9;
		}
	}

	dp[0][0] = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(j+1 != i) {
				if(a[j].first >= a[j+1].first) dp[i][j+1] = min(dp[i][j+1], dp[i][j] + D(j, j+1));
				if(i < j+1 && a[i].first >= a[j+1].first) dp[j+1][j] = min(dp[j+1][j], dp[i][j] + C(i, j+1));
			}
			if(i+1 != j) {
				if(a[i].first >= a[i+1].first) dp[i+1][j] = min(dp[i+1][j], dp[i][j] + C(i, i+1));
				if(j < i+1 && a[j].first >= a[i+1].first) dp[i][i+1] = min(dp[i][i+1], dp[i][j] + D(j, i+1));
			}
		}
	}

	int ans = 1e9;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i==n-1 || j==n-1) {
				ans = min(ans, dp[i][j]);
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}