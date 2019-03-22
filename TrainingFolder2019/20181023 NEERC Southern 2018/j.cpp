#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30005;

int n, m;
int dp[MAXN], nxt[MAXN];

int solve(vector<int> v, int rem){
	fill(dp, dp + n + 1, -1e9);
	dp[0] = 0;
	for(auto &i : v){
		fill(nxt, nxt + n + 1, -1e9);
		for(int j=0; j<=n; j++){
			nxt[j] = max(dp[j] + i, dp[max(0, j - i)]);
		}
		for(int j=0; j<=n; j++) dp[j] = nxt[j];
	}
	int ret = 1e9;
	for(int j=0; j<=n; j++){
		if(dp[j] < 0) continue;
		if(n - j + max(0, m - dp[j]) > rem) continue;
		ret = min(ret, (n - j) * max(0, m - dp[j]));
	}
	return ret;
}

char str[200005];
int cnt[276];
void solve(){
	scanf("%d %d %*d %s",&n,&m,str);
	memset(cnt, 0, sizeof(cnt));
	for(int i=0; str[i]; i++){
		cnt[str[i] - 'A']++;
	}
	int ret = 1e9;
	for(int i=0; i<26; i++){
		if(cnt[i]){
			vector<int> v;
			for(int j=0; j<26; j++){
				if(i != j && cnt[j]){
					v.push_back(cnt[j]);
				}
			}
			ret = min(ret, solve(v, cnt[i]));
		}
	}
	printf("%d\n", ret);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
