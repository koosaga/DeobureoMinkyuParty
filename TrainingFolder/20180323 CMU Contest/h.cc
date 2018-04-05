#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 24;

int n, s;
int a[24];
pi dp[1<<24];

int main(){
	cin >> n >> s;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=1; i<(1<<n); i++){
		dp[i] = pi(50, 1e9);
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				auto k = dp[i ^ (1<<j)];
				if(k.second + a[j] > s) k = pi(k.first + 1, a[j]);
				else k.second += a[j];
				dp[i] = min(dp[i], k);
			}
		}
	}
	cout << dp[(1<<n)-1].first + 1 << endl;
}
