#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
typedef long long lint;
typedef pair<int, int> pi;

int v, e, mod;
lint dp[2505][55][55];

int main(){
	int q;
	cin >> q;
	while(q--){
		cin >> v >> e >> mod;
		memset(dp, 0, sizeof(dp));
		dp[0][1][1] = 1 % mod;
		for(int i=0; i<=e; i++){
			int ans = 0;
			for(int j=1; j<=v; j++){
				for(int k=1; k<=v+1; k++){
					dp[i][k][j] += dp[i][k-1][j];
					dp[i][k][j] %= mod;
					if(k <= j) ans = (ans + dp[i][k][j]) % mod;
				}
			}
			if(i != 0) printf("%d ", ans);
			for(int j=1; j<=v; j++){
				for(int k=j; k<=v; k++){
					if(!dp[i][j][k]) continue;
					dp[i+1][j+1][k] += dp[i][j][k];
					dp[i+1][k+1][k] += mod - dp[i][j][k];
					if(k < v){
						dp[i+1][j][k+1] += dp[i][j][k];
						dp[i+1][j+1][k+1] += mod - dp[i][j][k];
					}
					else{
						int iy = j * (j-1) / 2 + k * (k-1) / 2;
						if(iy >= i + 1){
							dp[i+1][j][k] += dp[i][j][k];
							dp[i+1][j+1][k] += mod - dp[i][j][k];
						}
					}
					/*for(int l=j+1; l<=k; l++){
					
						dp[i+1][l][k] += dp[i][j][k];
						dp[i+1][l][k] %= mod;
					}
					if(k < v){
						dp[i+1][j][k+1] += dp[i][j][k];
						dp[i+1][j][k+1] %= mod;
					}
					else{
						int iy = j * (j-1) / 2 + k * (k-1) / 2;
						if(iy >= i + 1){
							dp[i+1][j][k] += dp[i][j][k];
							dp[i+1][j][k] %= mod;
						}
					}*/
				}
			}
		}
	}
}

