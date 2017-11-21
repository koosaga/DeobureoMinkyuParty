#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
vector<pi> gph[MAXN];

int n, k;
int dp[MAXN][2];

void dfs(int x, int p){
	vector<pi> v1;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfs(i.second, x);
		v1.push_back(pi(dp[i.second][0] + i.first, i.second));
		dp[i.second][1] += i.first;
	}
	sort(v1.begin(), v1.end());
	reverse(v1.begin(), v1.end());
	for(int i=0; i<k-1 && i<v1.size(); i++){
		dp[x][0] += v1[i].first;
	}
	int nxt = (v1.size() >= k ? v1[k-1].first : 0);
	dp[x][1] = dp[x][0];
	int cnt = 0;
	for(auto &i : v1){
		cnt++;
		if(cnt >= k){
			dp[x][1] = max(dp[x][1], dp[x][0] + dp[i.second][1]);
			continue;
		}
		dp[x][1] = max(dp[x][1], dp[x][0] + nxt - i.first + dp[i.second][1]);
	}
}

int main(){
	cin >> n >> k;
	for(int i=1; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		s++, e++;
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	dfs(1, 0);
	cout << dp[1][1];
}
