#include<bits/stdc++.h>
using namespace std;
using real_t = long double;
const int MAXN = 1050;

real_t fact[MAXN];

real_t binom(int x, int y){
	return fact[x] - fact[y] - fact[x - y];
}

int main(){
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] + log(1.0L * i);
	}
	int n, k; cin >> n >> k;
	k = (1 << n) + 1 - k;;
	real_t ans = 0.0L;
	for(int i=0; i<n; i++){
		int l = (1 << i);
		if(k < l) break;
		real_t logv = binom(k - 1, l - 1) - binom((1<<n) - 1, l - 1);
		ans += exp(logv);
	}
	printf("%.15Lf\n", ans);
}

