#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;
using lint = long long;

string s1, s2;
int ans[MAXN];

int dp[MAXN][MAXN];
int nxt[MAXN][MAXN];
int n, m;

void reroot(int px){
	int origpx = px;
	int py = 1;
	while(py <= m && nxt[px][py] != 2) py++;
	nxt[px][py] = 1;
	while(px < 2 * n && py < m){
		if(nxt[px+1][py] == 3){
			px++;
			nxt[px][py] = 1;
		}
		else if(nxt[px+1][py+1] == 2){
			px++; py++; nxt[px][py] = 1;
		}
		else py++;
	}
	while(px < 2 * n && nxt[px + 1][py] == 3){
		px++;
		nxt[px][py] = 1;
	}
	for(int j=origpx + 1; j<=px; j++) ans[j]--;
	for(int j=origpx + 1; j<n; j++) printf("%d ", ans[j]);
	puts("");
}


int main(){
	cin >> s2 >> s1;
	s1 = "#" + s1;
	s2 = "#" + s2;
	n = s1.size();
	m = s2.size();
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			if(j == 0){
				nxt[i][j] = 3;
				continue;
			}
			if(i == 0){
				nxt[i][j] = 1;
				continue;
			}
			dp[i][j] = -1;
			if(dp[i][j] < dp[i][j-1]){
				dp[i][j] = dp[i][j-1];
				nxt[i][j] = 1;
			}
			if(dp[i][j] < dp[i-1][j-1] + (s1[i] == s2[j])){
				dp[i][j] = dp[i-1][j-1] + (s1[i] == s2[j]);
				nxt[i][j] = 2;
			}
			if(dp[i][j] < dp[i-1][j]){
				dp[i][j] = dp[i-1][j];
				nxt[i][j] = 3;
			}
		}
	}
	for(int i=1; i<=n; i++) ans[i] = dp[i][m];
	for(int i=1; i<n; i++) printf("%d ", dp[i][m]);
	puts("");
	for(int i=1; i<n; i++){
		reroot(i);
	}
}
