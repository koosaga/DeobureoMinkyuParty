#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400;

int n, a[MAXN], dp[MAXN];

bool ok(int l, int r){
	int ret = 0;
	for(int i=l; i<=r; i++){
		ret += a[r] - a[i];
	}
	return ret < 20;
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++){
		dp[i] = 1e9;
		for(int j=0; j<i; j++){
			if(ok(j+1, i)) dp[i] = min(dp[i], dp[j] + 1);
		}
	}
	cout << dp[n] << endl;
}
