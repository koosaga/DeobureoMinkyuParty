#include <bits/stdc++.h>
using namespace std;
const int MAXN = 102;

int n, m;
short dp[MAXN][MAXN][MAXN][MAXN];
short G[MAXN][MAXN];
char str[MAXN][MAXN], A[MAXN];
int L[MAXN];

int main(){
	cin >> A;
	n = strlen(A); cin >> m;
	for(int i=0; i<m; i++) cin >> str[i];
	for(int i=0; i<m; i++){
		L[i] = strlen(str[i]);
	}
	for(int i=0; i<=n; i++){
		G[i][i] = 0;
		for(int j=0; j<=m; j++){
			for(int k=0; k<L[j]; k++) dp[i][i][j][k] = 1e2;
			dp[i][i][j][L[j]] = 1;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j+i<=n; j++){
			int s = j, e = j + i;
			G[s][e] = 1e2;
			for(int k=0; k<m; k++){
				int st = max(0, L[k] - e + s);
				for(int l=st; l<=L[k] && l <= s; l++){
					dp[e][s][k][l] = 1e2;
					if(A[s] == str[k][l]){
						dp[e][s][k][l] = dp[e][s+1][k][l+1];
					}
					for(int m=s+1; m<=e; m++){
						if(e - m < L[k] - l) break;
						dp[e][s][k][l] = min(dp[e][s][k][l], (short)(G[s][m] + dp[e][m][k][l]));
					}
				}
			}
			for(int k=0; k<m; k++){
				if(e - s < L[k]) continue;
				G[s][e] = min(G[s][e], dp[e][s][k][0]);
			}
		}
	}
	cout << (int)G[0][n] << endl;
}


