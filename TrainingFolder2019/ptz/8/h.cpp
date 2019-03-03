#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const int MOD = int(1e9) + 7;

struct modint {
	int v;
	modint(lint v_ = 0): v(v_ % MOD) { }
	modint operator+ (const modint &m) const {
		return modint(v + m.v);
	}
	modint operator- (const modint &m) const {
		return modint(v - m.v + MOD);
	}
	modint operator+= (const modint &m) {
		(v += m.v) %= MOD;
		return *this;
	}
	modint operator* (const modint &m) const {
		return modint((lint)v * m.v);
	}
	modint operator*= (const modint &m) {
		v = (lint)v * m.v % MOD;
		return *this;
	}
};

const int N_ = 305;

modint comb[N_][N_], fac[N_];

int N, K;
int T[N_];

int _T[N_];

modint tb[N_];

modint ans1[N_], ans2[N_];

int main() {
	scanf("%d%d", &N,&K);
	if(N == 1) {
		puts("0");
		return 0;
	}

	comb[0][0] = 1;
	fac[0] = 1;
	for(int i = 1; i <= N; i++) {
		fac[i] = fac[i-1] * i;
		comb[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
		}
	}

	for(int i = 1; i <= N; i++) {
		scanf("%d", &T[i]);
		_T[i] = T[i];
	}
	sort(T+1, T+N+1);

	for(int j = 2; j <= N; j++) {
		modint ways = 0;			
		for(int p = 1; p <= N; p++) {
			modint cur = 0;
			for(int c = K-1; c <= p-1; c++) {
				cur += comb[N-j][c] * comb[j-2][p-1-c];
			}
			cur *= fac[p] * fac[N-p-1];
			ways += cur;
		}
		tb[j] = ways;

		for(int i = 1; i < j; i++) {
			ans2[i] += ways;
		}
		//printf("loop1[%d] = %d\n", j, ways.v);
	}

	for(int i = 1; i <= N; i++) {
		modint tot = fac[N] * T[i];

		// t_j < t_i
		for(int j = 1; j < i; j++) {
			tot += (fac[N] - tb[i]) * T[j];
		}

		// t_j > t_i
		for(int j = i+1; j <= N; j++) {
			tot += tb[j] * T[j];
		}

		ans1[i] = tot;
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			if(_T[i] == T[j]) {
//				printf("%d %d %d\n", ans1[j].v, ans2[j].v, (ans1[j] * ans2[j]).v);
				printf("%d%c", (ans1[j] * ans2[j]).v, (i+1 <= N) ? ' ' : '\n');
				break;
			}
		}
	}


	return 0;
}

/*
loop1[2] = 22
loop1[3] = 14
loop1[4] = 0
722 0 0
882 0 0
48 36 1728
1096 14 15344

loop1[2] = 5
loop1[3] = 5
33 5 165
6 10 60
26 0 0

*/