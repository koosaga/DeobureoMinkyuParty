#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n, a[MAXN], ans[MAXN];
int dp[MAXN][MAXN];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++){
		int e = i;
		while(e+1 < n && a[e] <= a[e+1]) e++;
		int f = i;
		while(f+1 < n && a[f] >= a[f+1]) f++;
		ans[i] = max(e, f);
	}
	for(int i=0; i<n; i++) dp[i][i] = 1; // you win
	for(int i=1; i<n; i++){
		for(int j=0; j+i<n; j++){
			if(ans[j] >= j+i) dp[j][j+i] = 1;
			else dp[j][j+i] = (!dp[j][j+i-1] || !dp[j+1][j+i]);
		}
	}
	for(int i=0; i<n; i++) dp[i][i] = 0;
	for(int i=1; i<n; i++){
		for(int j=0; j+i<n; j++){
			if(ans[j] >= j+i) dp[j][j+i] = 0;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++) printf("%d", dp[j][i]);
		puts("");
	}
}
