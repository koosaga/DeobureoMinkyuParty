#include <bits/stdc++.h>
		}
using namespace std;
using lint = long long;
const int MAXN = 105;

int n, a[MAXN], b[MAXN], c[MAXN];
lint dp[2][MAXN][5100];

void SEX(int b){
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n*(n+1)/2; j++){
			dp[b][i][j] = -1e18;
		}
	}
}

int main(){
	int t;
	cin >> t; 
	while(t--){
		cin >> n;
		for(int i=1; i<=n; i++) cin >> a[i] >> b[i] >> c[i];
		int sum = 0;
		SEX(0);
		SEX(1);
		dp[n%2][0][0] = 0;
		for(int i=n; i; i--){
			SEX((i-1)%2);
			for(int j=0; j<=n-i; j++){
				for(int k=0; k<=sum; k++){
					lint nxt = max(1ll * b[i] * (k - i * j), 1ll * c[i] * j);
					dp[(i-1)%2][j][k] = max(dp[(i-1)%2][j][k], dp[i%2][j][k] + nxt);
					dp[(i-1)%2][j + 1][k + i] = max(dp[(i-1)%2][j+1][k+i], dp[i%2][j][k] + a[i]);
				}
			}
			sum += i;
		}
		lint ret = 0;
		for(int i=0; i<=n; i++) for(int j=0; j<=sum; j++) ret = max(ret, dp[0][i][j]);
		cout << ret << endl;
	}
}

