#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 505;

int n;
lint w, a[MAXN], v[MAXN];
lint dp[50000005];

int main(){
	mt19937_64 rng(0x14004);
	cin >> n >> w;
	for(int i=0; i<n; i++) cin >> a[i] >> v[i];
	int shv = 0;
	while((__int128) n * (__int128) w > 1000000000 ||
		w >= 50000000){
		w >>= 1;
		shv++;
	}
	srand(0x14004);
	auto randint = [&](lint s, lint e){
		if(s == e) return s;
		lint FUCK = ((1ll * rand()) << 30) + (rand() & 0x3fffffff);
		return s + FUCK % (e - s + 1);
	};
	for(int i=0; i<n; i++){
		lint pwr = 1ll<<shv;
		lint x = ((a[i]+randint(pwr/4, pwr-1))/pwr);
		a[i] = min(x, w);
	}
	for(int i=0; i<n; i++){
		for(int j=w; j>=a[i]; j--){
			dp[j] = max(dp[j], dp[j-a[i]] + v[i]);
		}
	}
	cout << dp[w] << endl;
}
