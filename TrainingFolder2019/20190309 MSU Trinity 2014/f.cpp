#include <bits/stdc++.h>

using namespace std;

using lint = long long;
using pi = pair<lint, lint>;

const int n_ = 2050;
int n;
lint a[n_], s[n_];

lint dp[n_][n_];
lint ans = 0;

struct cht{
	vector<pi> v;
	bool ccw(pi a, pi b, pi c){
		return (a.second - b.second) * (c.first - b.first) >= (b.second - c.second) * (b.first - a.first);
	}
	void add(pi x){
		if(v.size() && v.back().first == x.first){
			v.pop_back();
		}
		while(v.size() >= 2 && ccw(v[v.size()-2], v.back(), x)) v.pop_back();
		v.push_back(x);
	}
	lint query(int x){
		int s = 0, e = v.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(v[m].first * x + v[m].second < v[m+1].first * x + v[m+1].second) s = m + 1;
			else e = m;
		}
		return v[s].first * x + v[s].second;
	}
	void clear() { v.clear(); }
}cht;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s[i] = s[i-1] + a[i];
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j<=n; j++){
			dp[i][j] = -1e18;
		}
	}
	for(int i=1; i<=n; i++){
		vector<pi> v;
		for(int j=0; j<i; j++){
			v.emplace_back(s[i] - s[j], dp[j][i] - s[i] * (s[i] - s[j]));
		}
		sort(v.begin(), v.end());
		for(auto &i : v) cht.add(i);
		for(int k=i+1; k<=n; k++){
			dp[i][k] = cht.query(s[k]);
		}
		cht.clear();
	}

	for(int j = 0; j < n; j++) {
		ans = max(ans, dp[j][n]);
	}
	printf("%lld\n", ans);
	return 0;
}