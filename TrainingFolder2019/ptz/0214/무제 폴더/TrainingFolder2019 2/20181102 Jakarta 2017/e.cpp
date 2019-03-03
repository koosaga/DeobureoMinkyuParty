#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;
using lint = long long;

int n, m;
int C[2][3][3];

lint solve(vector<int> v, int target, int fuck){
	lint dp[44][3] = {};
	lint dp2[44][3][3] = {};
	for(int i=1; i<=v.size(); i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				if(j != k){
					int midp = 3 - j - k;
					dp2[i][j][k] = min(
					dp2[i-1][j][midp] + C[fuck][j][k] + dp2[i-1][midp][k],
					dp2[i-1][j][k] + C[fuck][j][midp] + dp2[i-1][k][j] + C[fuck][midp][k] + dp2[i-1][j][k]);
				}
			}
		}
		for(int j=0; j<3; j++){
			if(j == v[i-1]) dp[i][j] = dp[i-1][j];
			else{
				int mid = 3 - j - v[i-1];
				// v[i] -> j
				dp[i][j] = min(
				dp[i-1][mid] + C[fuck][v[i-1]][j] + dp2[i-1][mid][j],
				dp[i-1][j] + C[fuck][v[i-1]][mid] + dp2[i-1][j][v[i-1]] + C[fuck][mid][j] + dp2[i-1][v[i-1]][j]);
			}
		}
	}
	return dp[v.size()][target];
}

lint solve(vector<int> a, vector<int> b){
	for(int i=n-1; i>=0; i--){
		if(a[i] != b[i]){
			int midp = 3 - a[i] - b[i];
			vector<int> suba(a.begin(), a.begin() + i);
			vector<int> subb(b.begin(), b.begin() + i);
			vector<int> as(i, a[i]);
			vector<int> bs(i, b[i]);
			lint val1 = solve(suba, midp, 0) + solve(subb, midp, 1) + C[0][a[i]][b[i]];
			lint val2 = solve(suba, b[i], 0) + C[0][a[i]][midp] + solve(bs, a[i], 0) + C[0][midp][b[i]] + solve(subb, a[i], 1);
			return min(val1, val2);
		}
	}
	return 0;
}

lint adj[20][20], dp[1<<18][18];
vector<int> v[20];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<3; i++) for(int j=0; j<3; j++){
		cin >> C[0][i][j];
		C[1][j][i] = C[0][i][j];
	}
	for(int i=0; i<=m; i++){
		v[i].resize(n);
		for(int j=0; j<3; j++){
			int x; scanf("%d",&x);
			for(int k=0; k<x; k++){
				int w; scanf("%d",&w);
				v[i][w-1] = j;
			}
		}
	}
	for(int i=0; i<=m; i++){
		for(int j=0; j<i; j++){
			adj[i][j] = solve(v[i], v[j]);
			adj[j][i] = solve(v[j], v[i]);
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[1][0] = 0;
	m++;
	for(int i=2; i<(1<<m); i++){
		for(int j=0; j<m; j++){
			if((i >> j) & 1){
				for(int k=0; k<m; k++){
					if((i >> k) % 2 == 1 && j != k){
						dp[i][j] = min(dp[i][j], dp[i ^ (1<<j)][k] + adj[k][j]);
					}
				}
			}
		}
	}
	lint ret = 1e18;
	for(int i=0; i<3; i++){
		for(int j=0; j<m; j++){
			ret = min(ret, dp[(1<<m)-1][j] + solve(v[j], i, 0));
		}
	}
	cout << ret << endl;
}

