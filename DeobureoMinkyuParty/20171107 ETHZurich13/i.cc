#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 4005;

int n;
lint a[MAXN];
int dp[MAXN][MAXN];
vector<int> v;

int main(){
	cin >> n; 
	for(int i=1; i<=n; i++) cin >> a[i], a[i] += a[i-1];
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++) dp[i][j] = -1e9;
	}
	for(int i=1; i<=n; i++) dp[i][n] = 1;
	for(int j=n; j; j--){
		vector<pi> v, w;
		for(int i=1; i<j; i++){
			v.push_back(pi(2 * a[j-1] - a[i-1], i));
		}
		for(int k=j; k<=n; k++) w.push_back(pi(a[k], k));
		sort(v.begin(), v.end());
		sort(w.begin(), w.end());
		int ptr = w.size(), ans = -1e9;
		for(int i=(int)v.size()-1; i>=0; i--){
			auto x = v[i];
			while(ptr > 0 && w[ptr-1].first > x.first){
				ptr--;
				ans = max(ans, dp[j][w[ptr].second] + 1);
			}
			dp[x.second][j-1] = max(dp[x.second][j-1], ans);
		}
	}
	int ans = 0;
	int s = 1, e = -1;
	for(int i=1; i<=n; i++){
		if(ans < dp[1][i]){
			ans = dp[1][i];
			e = i;
		}
	}
	cout << ans << endl;
	while(ans > 1){
		v.push_back(e + 1);
		for(int i=e+1; i<=n; i++){
			if(a[e] - a[s-1] < a[i] - a[e] && dp[s][e] == dp[e+1][i] + 1){
				s = e+1;
				e = i;
				ans--;
				break;
			}
		}
	}
	for(int i=0; i<v.size(); i++) printf("%d ", v[i] - 1);
}
