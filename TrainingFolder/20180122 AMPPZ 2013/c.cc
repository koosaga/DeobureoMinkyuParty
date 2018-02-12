#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, a[MAXN][MAXN];
int dp[4][MAXN][MAXN];

int xmx[MAXN][4];
int xmn[MAXN][4];
int ymx[MAXN][4];
int ymn[MAXN][4];
int pmx[MAXN][4];
int pmn[MAXN][4];
int qmx[MAXN][4];
int qmn[MAXN][4];

void Do(){
	memset(xmx, 0xcf, sizeof(xmx));
	memset(ymx, 0xcf, sizeof(ymx));
	memset(pmx, 0xcf, sizeof(pmx));
	memset(qmx, 0xcf, sizeof(qmx));
	memset(xmn, 0x3f, sizeof(xmn));
	memset(ymn, 0x3f, sizeof(ymn));
	memset(pmn, 0x3f, sizeof(pmn));
	memset(qmn, 0x3f, sizeof(qmn));
	for(int i=0; i<4; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=m; k++){
				if(a[j][k]){
					int d = dp[i][j][k];
					xmn[d][i] = min(xmn[d][i], j);
					xmx[d][i] = max(xmx[d][i], j);
					ymn[d][i] = min(ymn[d][i], k);
					ymx[d][i] = max(ymx[d][i], k);
					pmn[d][i] = min(pmn[d][i], j + k);
					pmx[d][i] = max(pmx[d][i], j + k);
					qmn[d][i] = min(qmn[d][i], j - k);
					qmx[d][i] = max(qmx[d][i], j - k);
				}
			}
		}
		for(int j=1003; j>=0; j--){
			xmx[j][i] = max(xmx[j][i], xmx[j+1][i]);
			xmn[j][i] = min(xmn[j][i], xmn[j+1][i]);
			ymx[j][i] = max(ymx[j][i], ymx[j+1][i]);
			ymn[j][i] = min(ymn[j][i], ymn[j+1][i]);
			pmx[j][i] = max(pmx[j][i], pmx[j+1][i]);
			pmn[j][i] = min(pmn[j][i], pmn[j+1][i]);
			qmx[j][i] = max(qmx[j][i], qmx[j+1][i]);
			qmn[j][i] = min(qmn[j][i], qmn[j+1][i]);
		}
	}
	for(int i=0; i<=1004; i++){
		xmx[i][0] = max(xmx[i][0], xmx[i][1]);
		xmn[i][0] = min(xmn[i][0], xmn[i][1]);
		ymx[i][1] = max(ymx[i][1], ymx[i][3]);
		xmx[i][2] = max(xmx[i][2], xmx[i][3]);
	}
}

bool trial(int x){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(a[i][j] && dp[0][i][j] >= x){
				if(pmn[x][0] < i + j - x + 1) return 1;
				if(pmx[x][0] > i + j + x - 1) return 1;
				if(xmn[x][0] < i - x + 1) return 1;
				if(xmx[x][0] > i + x - 1) return 1;
				if(ymn[x][0] < j - x + 1) return 1;
				if(ymx[x][0] > j + x - 1) return 1;

				if(pmn[x][1] < i + j - 2 * x + 2) return 1;
				if(qmx[x][1] > i - j + 2 * x - 2) return 1;
				if(ymx[x][1] > j) return 1;

				if(pmn[x][2] < i + j - 2 * x + 2) return 1;
				if(qmn[x][2] < i - j - 2 * x + 2) return 1;
				if(ymn[x][2] < j - x + 1) return 1;
				if(ymx[x][2] > j + x - 1) return 1;
				if(xmx[x][2] > i) return 1;
				if(pmn[x][3] <= i - 2 * x + 2 + j) return 1;
			}
		}
	}
	return 0;
}

int solve(){
	memset(dp, 0, sizeof(dp));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int l = (a[i-1][j] != a[i][j] ? dp[0][i-1][j] : 0);
			int r = (a[i][j-1] != a[i][j] ? dp[0][i][j-1] : 0);
			dp[0][i][j] = min(l, r) + 1;
		}
		for(int j=m; j; j--){
			int l = (a[i-1][j] != a[i][j] ? dp[1][i-1][j] : 0);
			int r = (a[i][j+1] != a[i][j] ? dp[1][i][j+1] : 0);
			dp[1][i][j] = min(l, r) + 1;
		}
	}
	for(int i=n; i; i--){
		for(int j=1; j<=m; j++){
			int l = (a[i+1][j] != a[i][j] ? dp[2][i+1][j] : 0);
			int r = (a[i][j-1] != a[i][j] ? dp[2][i][j-1] : 0);
			dp[2][i][j] = min(l, r) + 1;
		}
		for(int j=m; j; j--){
			int l = (a[i+1][j] != a[i][j] ? dp[3][i+1][j] : 0);
			int r = (a[i][j+1] != a[i][j] ? dp[3][i][j+1] : 0);
			dp[3][i][j] = min(l, r) + 1;
		}
	}
	Do();
	int s = 0, e = min(n, m);
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	return s;
}

int b[MAXN][MAXN];

void rotate(){
	for(int i=1; i<=n; i++) reverse(a[i] + 1, a[i] + m + 1);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) b[j + 1][i + 1] = a[i + 1][j + 1];
	}
	swap(n, m);
	memcpy(a, b, sizeof(a));
}

void flip(){
	for(int i=0; i<n; i++) for(int j=0; j<m; j++) a[i+1][j+1] ^= 1;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	int ans = 0;
	for(int i=0; i<4; i++){
		ans = max(ans, solve());
		flip();
		ans = max(ans, solve());
		rotate();
	}
	cout << ans;
}
