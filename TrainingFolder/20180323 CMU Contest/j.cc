#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 2005;
const int inf = 1e9 + 100;

int n, m, a[MAXN], b[MAXN];
pi dp[MAXN][MAXN];
int FuckYou[MAXN][MAXN];


int solve(){
	for(int i=0; i<MAXN; i++) dp[0][i] = dp[i][0] = pi(0, inf);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(dp[i-1][j].first != dp[i][j-1].first){
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
			else{
				if(dp[i-1][j].first % 2 == 1){
					dp[i][j] = min(dp[i-1][j], dp[i][j-1]);
				}
				else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
			if(a[i] == b[j]){
				auto k = dp[i-1][j-1];
				if(k.first % 2 == 1){
					if(k.second < a[i]) k = pi(k.first + 1, a[i]);
					else k = pi(k.first, a[i]);
				}
				else{
					if(k.second > a[i]) k = pi(k.first + 1, a[i]);
					else k = pi(k.first, a[i]);
				}
				if(k.first > dp[i][j].first) dp[i][j] = k;
				else if(k.first == dp[i][j].first){
					if(k.first % 2 == 1) dp[i][j] = min(dp[i][j], k);
					else dp[i][j] = max(dp[i][j], k);
				}
			}
		}
	}
	return dp[n][m].first;
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	cin >> m;
	for(int i=1; i<=m; i++) cin >> b[i];
	int ans = solve();
	for(int i=1; i<=n; i++) a[i] = -a[i];
	for(int i=1; i<=m; i++) b[i] = -b[i];
	ans = max(ans, solve());
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			FuckYou[i][j] = max(FuckYou[i-1][j], FuckYou[i][j-1]);
			if(a[i] == b[j]) FuckYou[i][j] = max(FuckYou[i][j], 
				FuckYou[i-1][j-1] + 1);
		}
	}
	if(FuckYou[n][m] >= 1) ans = max(ans, 1);
	if(FuckYou[n][m] >= 2) ans = max(ans, 2);
	cout << ans << endl;
}

