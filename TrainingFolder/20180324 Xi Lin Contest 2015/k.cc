#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int mod = 1e9 + 7;
typedef long long lint;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d",&n);
		int w = n/2 + (n-1)/2;
		printf("%lld\n", (ipow(2, w) + mod - 1) % mod);
	}
}
