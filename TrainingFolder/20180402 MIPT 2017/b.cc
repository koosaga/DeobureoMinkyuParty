#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1050000;
typedef pair<int, int> pi;

int n, a[MAXN], dp[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] ^= a[i-1];
	}
	memset(dp, 0x3f, sizeof(dp));
	for(int i=n; i>=0; i--){
		dp[a[i]] = i;
	}
	for(int i=0; i<20; i++){
		for(int j=0; j<(1<<20); j++){
			if((j >> i) % 2 == 0){
				dp[j] = min(dp[j], dp[j + (1<<i)]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		int msk = 0;
		for(int j=19; j>=0; j--){
			if((a[i] >> j) % 2 == 0 && dp[msk | (1<<j)] <= i){
				msk |= (1<<j);
			}
		}
		printf("%d ", msk * 2 + a[i]);
	}
}
