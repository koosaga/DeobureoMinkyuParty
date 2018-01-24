#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

vector<int> v[MAXN];
int n, a[MAXN], dp[MAXN];

int main(){
	freopen("gem.in", "r", stdin);
freopen("gem.out", "w", stdout);
	scanf("%d",&n);
	vector<int> p;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		p.push_back(a[i]);
	}
	sort(p.begin(), p.end());
	p.resize(unique(p.begin(), p.end()) - p.begin());
	for(int i=1; i<=n; i++){
		a[i] = lower_bound(p.begin(), p.end(), a[i]) - p.begin() + 1;
		v[a[i]].push_back(i);
	}
	int m = p.size();
	for(int i=m; i; i--){
		if(i == m){
			dp[i] = v[i].size();
			continue;
		}
		if(v[i].back() < v[i+1].front()) dp[i] = dp[i+1] + v[i].size();
		else{
			dp[i] = v[i+1].end() - lower_bound(v[i+1].begin(), v[i+1].end(), v[i].back());
			dp[i] += v[i].size();
		}
	}
	int ret = *max_element(dp + 1, dp + m + 1);
	for(int i=2; i<=m; i++){
		int cnt = lower_bound(v[i-1].begin(), v[i-1].end(), v[i][0]) - v[i-1].begin();
		ret = max(ret, dp[i] + cnt);
		for(int j=0; j<v[i].size(); j++){
			int cnt = lower_bound(v[i-1].begin(), v[i-1].end(), v[i][j]) - v[i-1].begin();
			ret = max(ret, cnt + (int)v[i].size() - j);
		}
	}
	cout << n - ret << endl;
}
