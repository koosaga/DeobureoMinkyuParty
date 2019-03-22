#include <bits/stdc++.h>

using namespace std;

const int MAXN = int(1e7);

const int MOD = int(1e9) + 7;

using lint = long long;

int fac[MAXN+1];
int inv[2*MAXN+1];
int invfac[MAXN+1];
int minp[MAXN + 1];
int phi[MAXN + 1];

int gcd (int a, int b) {
	return b ? gcd(b, a%b)  :a;
}

inline lint comb (int n, int r) {
	return (lint(fac[n]) * lint(invfac[r]) % MOD) * invfac[n-r] % MOD;
}

inline lint sum0 (int n, int k) {
	return comb(n + k + 1, k);
}

inline lint sum1 (int n, int k) {
	if(k <= 0) {
		return 0;
	}
	return (sum0(n, k) * lint(k) % MOD - sum0(n + 1, k - 1) + MOD) % MOD;
}

int main() {
	fac[0] = 1;
	invfac[0] = 1;
	inv[1] = 1;
	fac[1] = 1;
	invfac[1] = 1;
	for(int i = 2; i <= MAXN; i++) {
		fac[i] = lint(fac[i-1]) * i % MOD;
		inv[i] = lint(MOD - MOD / i) * inv[MOD % i] % MOD;
		invfac[i] = lint(invfac[i-1]) * inv[i] % MOD;
	}
	for(int i = 2; i <= 2*MAXN; i++) {
		inv[i] = lint(MOD - MOD / i) * inv[MOD % i] % MOD;
	}
	
	for(int p = 2; p <= MAXN; p++) {
		if(minp[p] == 0) {
			minp[p] = p;
			for(int i = 2 * p; i <= MAXN; i += p) {
				if(minp[i] == 0) minp[i] = p;
			}
		}
	}
	
	phi[1] = 1;
	for(int i = 2; i <= MAXN; i++) {
		if(i == minp[i]) {
			phi[i] = i - 1;
		}else if((i / minp[i]) % minp[i] != 0) {
			phi[i] = phi[i / minp[i]] * (minp[i] - 1);
		}else {
			phi[i] = phi[i / minp[i]] * minp[i];
		}
	}
	
	int T; scanf("%d", &T);
	while(T--) {
		int N, M; scanf("%d%d", &N, &M);
		int S = N - M;
		
		lint tot = 0;
		
		auto go = [&](int d) {
			if(S % d == 0) {
				tot += phi[d] * comb(M / d + S / d - 1, S / d) % MOD;
				tot %= MOD;
			}
		};
		
		for(int d = 1; d * d <= M; d++) {
			if(M % d == 0) {
				go(d);
				if(d * d != M) go(M / d);
			}	
		}
/*
		{
			lint naive = 0;
			for(int i = 1; i <= M; i++) {
				int d = M / gcd(i, M);
				if(S % d == 0)
				naive += comb(M / d + S / d - 1, S / d);
				//printf("%d %d %lld\n", i, d, comb(M / d + S / d - 1, S / d));
			}
			naive %= MOD;
			//printf("%lld %lld\n", naive, tot);
			assert(naive == tot);
			
		}*/
		
		if(M % 2 == 0) {
			if(S % 2 == 0) {
				tot += comb(S / 2 + M / 2 - 1, S / 2) * (M / 2) % MOD;
				tot %= MOD;
			}
			tot += ((S + 1) * sum0(M / 2 - 2, S / 2) % MOD) * (M / 2) % MOD;
			tot %= MOD;
			tot -= (2 * (M / 2) * sum1(M / 2 - 2, S / 2)) % MOD;
			tot += MOD;
			tot %= MOD;
		}else {
			tot += sum0((M - 1) / 2 - 1, S / 2) * M % MOD;
		}
		tot %= MOD;
		//printf("tot1 = %lld\n", tot);
		tot *= inv[2 * M];
		tot %= MOD;
		//printf("-> after div, tot = %lld\n", tot);0
		
		lint ext = 0;
		int S2 = (S - ((N + 1) / 2) + 1);
		if(S2 >= 0) {
			ext += sum0(M - 2, S2);
			if((M - 1) % 2 == 0) {
				ext += sum0((M - 1) / 2 - 1, S2 / 2);
			}else {
				if(S2 % 2 == 0) {
					ext += comb((M - 2) / 2 + S2 / 2, S2 / 2);
					S2 -= 1;
				}
				if(S2 >= 0) {
					ext += sum0((M - 2) / 2, S2 / 2) * 2;
				}
			}
			ext %= MOD;
			ext *= inv[2];
			ext %= MOD;
		}
		//printf(" -> S2 = %d\n", S2);
		//printf("-> tot = %lld, ext = %lld\n", tot, ext);
		
		lint ans = (tot - ext + MOD) % MOD;
		printf("%lld\n", ans);
	}
	
	return 0;
}
