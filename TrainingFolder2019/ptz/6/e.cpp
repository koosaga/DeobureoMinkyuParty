#include <bits/stdc++.h>

using lint = long long;

int n;
lint p;
lint comb[5050][5050];

lint mypow (lint a, lint b) {
	lint ret = 1;
	while(b > 0) {
		if(b & 1) ret = (ret * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ret;
}

int main() {
	scanf("%d%lld", &n, &p);
	comb[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		comb[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % p;
		}
	}


	lint ans = 0;
	for(int a = 1; a <= n / 2; a++) {
		lint cur = comb[n-2][a-1];
		(cur *= mypow(a, a - 2)) %= p;
		(cur *= mypow(n - a, n - a - 2)) %= p;
		(cur *= a) %= p;
		if(a * 2 == n) (cur *= mypow(2, p - 2)) %= p;
		(ans += cur) %= p;
	}

	(ans *= n-1) %= p;
	(ans *= mypow(mypow(n, n-3), p-2)) %= p;

	printf("%lld\n", ans);
	return 0;
}