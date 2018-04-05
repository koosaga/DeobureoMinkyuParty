#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 505;

int n;
lint w, a[MAXN], v[MAXN];
lint dp[50000005];

int main(){
	srand(0x14004);
	cin >> n >> w;
	for(int i=0; i<n; i++) cin >> a[i] >> v[i];
	while((__int128) n * (__int128) w > 1000000000 ||
			w >= 50000000){
		w >>= 1;
		for(int i=0; i<n; i++) a[i] = (a[i] + rand()%2) >> 1;
		for(int i=0; i<n; i++) a[i] = min(a[i], w);
	}
	for(int i=0; i<n; i++){
		for(int j=w; j>=a[i]; j--){
			dp[j] = max(dp[j], dp[j-a[i]] + v[i]);
		}
	}
	cout << dp[w] << endl;
}
