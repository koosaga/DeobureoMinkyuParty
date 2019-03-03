#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const lint MOD = lint(1e9) + 7;

struct modint {
	int v;
	modint(lint v_ = 0): v((v_ + MOD) % MOD) { }
	modint operator+ (const modint &m) const {
		return modint(v + m.v);
	}
	modint operator- (const modint &m) const {
		return modint(v - m.v);
	}
	modint operator* (const modint &m) const {
		return modint((lint)v * m.v);
	}
};

const int n_ = 5050;

int N;

modint inv[n_], fac[n_], invfac[n_];

modint coef[n_];
modint pref[n_];

int a[n_];

modint comb (int n, int r) {
	return fac[n] * invfac[r] * invfac[n-r];
}

int main() {
	inv[1] = 1;
	fac[1] = fac[0] = 1;
	invfac[1] = invfac[0] = 1;
	for(int i = 2; i < n_; i++) {
		fac[i] = fac[i-1] * i;
		inv[i] = inv[MOD % i] * (MOD - MOD / i);
		assert((inv[i] * i).v == 1);
		invfac[i] = invfac[i-1] * inv[i];
		assert((fac[i] * invfac[i]).v == 1);
	}

	scanf("%d", &N);


	modint ans = 0;
	for(int n = 1; n <= N; n++) {
		int x; scanf("%d", &x);
		a[n] = x;
	}

	ans = (a[1] - a[2]);

	printf("%d\n", ans.v);

	return 0;
}