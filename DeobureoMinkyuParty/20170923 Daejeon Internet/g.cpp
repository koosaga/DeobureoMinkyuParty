#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <tuple>
#include <complex>
#include <bitset>
#include <random>

using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
pi a[10005];
lint p[10005], l[10005], s[10005];
short dp[10005][10005];
vector<pi> v;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].first;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i].second;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		p[i] = a[i].first;
		l[i] = a[i].second;
		s[i] = a[i].second + s[i - 1];
		v.push_back(pi(p[i] - s[i], i));
	}
	sort(v.begin(), v.end());

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			lint pos = p[j] + s[i] - s[j];
			int ok = 0;
			if (pos - l[i] <= p[i] && p[i] <= pos) {
				ok++;
			}
			dp[i][j] = dp[i - 1][j] + ok;
		}
		int mx = 0;
		for (auto &j : v) {
			if (j.second < i) mx = max(mx, (int)dp[i - 1][j.second]);
			else dp[i][j.second] = mx;
		}
		for (int j = i; j <= n; j++) {
			lint pos = p[j] - s[j] + s[i];
			int ok = 0;
			if (pos - l[i] <= p[i] && p[i] <= pos) {
				ok++;
			}
			dp[i][j] += ok;
		}
	}
	short ret = 0;
	for (int i = 1; i <= n; i++) ret = max(ret, dp[n][i]);
	cout << n - ret;
}