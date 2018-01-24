#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 100005;

vector<int> gph[MAXN];
int n, k, dp[MAXN][2];

int solve(){
	for(int i=n; i; i--){
		dp[i][0] = 0;
		int upd = -1e9;
		for(auto &j : gph[i]){
			int mx = max(dp[j][0], dp[j][1]);
			dp[i][0] += mx;
			dp[i][1] += mx;
			upd = max(upd, dp[j][0] - mx + 1);
		}
		dp[i][1] += upd;
	}
	return max(dp[1][0], dp[1][1]);
}

void sdfasf(){
	scanf("%d %d",&n,&k);
	memset(dp, 0, sizeof(dp));
	for(int i=1; i<=n; i++) gph[i].clear();
	for(int i=2; i<=n; i++){
		int x;
		scanf("%d",&x);
		gph[x].push_back(i);
	}
	int s = solve();
	if(2 * s >= k) printf("%d\n", (k + 1) / 2);
	else printf("%d\n", k - s);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) sdfasf();
}
