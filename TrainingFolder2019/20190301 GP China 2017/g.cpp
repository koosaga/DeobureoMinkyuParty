#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;
using pi = pair<lint, int>;

int n, a[MAXN], b[MAXN];
lint dp[MAXN][2];

lint f(int x, int prv){
	if(x == n) return prv ? b[n] : 0;
	if(~dp[x][prv]) return dp[x][prv];
	return dp[x][prv] = 
	min(f(x + 1, 1) + b[x],
	f(x + 1, 0) + a[x] + (prv ? b[x] : 0));
}

lint g(int x, int prv){
	if(x == n + 1) return 0;
	if(~dp[x][prv]) return dp[x][prv];
	lint ret = g(x + 1, 1) + b[x];
	if(x < n){
		ret = min(ret, g(x + 1, 0) + a[x] + 
		((x == 1 || x == n || prv) ? b[x] : 0));
	}
	return dp[x][prv] = ret;
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		for(int i=1; i<=n; i++) scanf("%d",&b[i]);
		// case 1. kill a_n
		for(int i=0; i<=n+2; i++){
			dp[i][0] = dp[i][1] = -1;
		}
		lint ret = a[n] + f(1, 0);
		// case 2. save a_n
		for(int i=0; i<=n+2; i++){
			dp[i][0] = dp[i][1] = -1;
		}
		ret = min(ret, g(1, 0));
		printf("%lld\n", ret);
	}
}
