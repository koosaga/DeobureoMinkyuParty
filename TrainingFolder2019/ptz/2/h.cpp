#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;

int n;
char str[MAXN];
int dp[13][MAXN], v[13], sz = 0;
int trk[13][MAXN];

void opt_sol(int x, int y){
	sz = 0;
	for(int i=0; i<=x; i++) v[sz++] = i;
	for(int i=y; i>=x; i--) v[sz++] = i;
	for(int i=y; i<10; i++) v[sz++] = i;
	for(int i=0; i<sz; i++){
		for(int j=1; j<=n; j++){
			trk[i][j] = 0;
			dp[i][j] = dp[i][j-1] + (str[j-1] - '0' == v[i]);
			if(i && dp[i][j] < dp[i-1][j]){
				dp[i][j] = dp[i-1][j];
				trk[i][j] = 1;
			}
		}
	}
	int t1 = sz - 1, t2 = n;
	vector<int> dap;
	while(t2 > 0){
		while(trk[t1][t2]){
			t1--;
		}
		dap.push_back(t1);
		t2--;
	}
	assert(dap.size() == n);
	reverse(dap.begin(), dap.end());
	auto l = lower_bound(dap.begin(), dap.end(), x + 1);
	auto r = lower_bound(dap.begin(), dap.end(), x + 1 + (y - x + 1));
	if(l == r){
		printf("%d %d\n", 1, 1);
	}
	else{
		printf("%d %d\n", l - dap.begin() + 1, r - dap.begin());
	}
}

int solve(int x, int y){
	sz = 0;
	for(int i=0; i<=x; i++) v[sz++] = i;
	for(int i=y; i>=x; i--) v[sz++] = i;
	for(int i=y; i<10; i++) v[sz++] = i;
	for(int i=0; i<sz; i++){
		for(int j=1; j<=n; j++){
			dp[i][j] = dp[i][j-1] + (str[j-1] - '0' == v[i]);
			if(i) dp[i][j] = max(dp[i][j], dp[i-1][j]);
		}
	}
	return dp[sz - 1][n];
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %s",&n,str);
		tuple<int, int, int> hae = make_tuple(solve(0, 0), 0, 0);
		for(int i=0; i<=9; i++){
			for(int j=i+1; j<=9; j++){
				hae = max(hae, make_tuple(solve(i, j), i, j));
			}
		}
		printf("%d ", get<0>(hae));
		opt_sol(get<1>(hae), get<2>(hae));
	}
}
