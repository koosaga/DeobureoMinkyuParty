#include <bits/stdc++.h>
using namespace std;
using lint = long long;

int tc, n;
lint mod;
lint dp[100][66];
lint bino[105][105];
int a[696969];

lint gobhae(lint x, lint y){
	lint ret = 0;
	while(x){
		ret += (x & 65535) * y;
		ret %= mod;
		x >>= 16;
		y <<= 16;
		y %= mod;
	}
	return ret;
}
int main(){
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %lld",&n,&mod);
		mod *= 60;
		for(int i=0; i<n; i++){
			scanf("%d",&a[i]);
		}
		for(int i=0; i<100; i++){
			bino[i][0] = 1;
			for(int j=1; j<=i; j++){
				bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % mod;
			}
		}
		auto Pulja = [&](int n, int hang, int pwr){
			dp[0][0] = 1;
			for(int i=1; i<=n; i++){
				for(int j=0; j<=pwr; j++){
					dp[i][j] = 0;
					for(int k=0; k<=j; k++){
						if(hang * (j - k) < a[i-1]) continue;
						dp[i][j] += gobhae(dp[i-1][k], bino[j][k]);
						if(dp[i][j] >= mod) dp[i][j] -= mod;
					}
				}
			}
			return dp[n][pwr];
		};/*

		{
			lint dap;
			scanf("%lld", &dap);
			dap *= 60;
			dap %= mod;

			lint arr[] = {Pulja(n, 1, 60), 
		Pulja(n, 2, 30), 
		Pulja(n, 10, 6), 
		Pulja(n, 5, 12),
				Pulja(n, 3, 20),
				Pulja(n, 4, 15)};
				puts("!!123");
			for(int i = 0; i <= 60; i++) {
				for(int j = 0; i+j <= 60; j++) {
					for(int k = 0; i+j+k <= 60; k++) {
						for(int l = 0; i+j+k+l <= 60; l++) {
						for(int ll = 0; i+j+k+l+ll <= 60; ll++) {
						for(int lll = 0; i+j+k+l+lll <= 60; lll++) {
							lint v = i * arr[0] + j * arr[1] + k * arr[2] + l * arr[3] + ll * arr[4] + lll * arr[5];
							v %= mod;
							if(v == dap) {
								printf("!!!!!%d %d %d %d %d %d\n", i, j, k, l, ll, lll);
							}
						}
					}
				}
			}}}
		}*/
		lint ret = 0;
		ret += Pulja(n, 1, 60);
		ret += 15 * Pulja(n, 2, 30);
		ret += 0 * Pulja(n, 10, 6);
		ret += 24 * Pulja(n, 5, 12);
		ret += 20 * Pulja(n, 3, 20);
		
		assert(ret % 60 == 0);
		ret /= 60;
		mod /= 60;
		printf("%lld\n", ret % mod);
	}
}
