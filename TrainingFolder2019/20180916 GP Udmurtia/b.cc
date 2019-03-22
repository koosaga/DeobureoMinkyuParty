#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;

int n;
vector<int> gph[MAXN];
int dp[MAXN][2][2];

void dfs(int x){
	if(gph[x].empty()){
		for(int c = 0; c < 2; c++){
			dp[x][c][0] = c;
			dp[x][c][1] = 0;
		}
		return;
	}
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
	for(int c = 0; c < 2; c++){
		vector<pi> dps;
		for(auto &i : gph[x]){
			int d[2] = {dp[i][1][0], dp[i][1][1]};
			if(c == 1){
				d[0] = min(d[0], dp[i][0][0]);
				d[1] = min(d[1], dp[i][0][1]);
			}
			dps.push_back(pi(d[0], d[1]));
		}
		// FIRST : NO UP GUY
		// SECOND : UP GUY
		dp[x][c][1] = 0;
		int incentive = 0;
		for(auto &i : dps){
			incentive = min(incentive, i.second - i.first);
			dp[x][c][1] += i.first;
		}
		dp[x][c][1] += incentive;
		// Case 1. Fuck any path
		dp[x][c][0] = c;
		for(auto &i : dps){
			dp[x][c][0] += i.first;
		}
		vector<int> v;
		int sums = 0;
		for(auto &i : dps){
			sums += i.first;
			v.push_back(i.second - i.first);
		}
		sort(v.begin(), v.end());
		// Case 2. Get only one path
		if(v.size() >= 1){
			dp[x][c][0] = min(dp[x][c][0], sums + v[0] + 1);
		}
		// Case 3. Merge two paths
		if(v.size() >= 2){
			dp[x][c][0] = min(dp[x][c][0], sums + v[0] + v[1] + 1);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	memset(dp, 0x3f, sizeof(dp));
	dfs(1);
	cout << min(dp[1][0][0], dp[1][1][0]) << endl;
}
