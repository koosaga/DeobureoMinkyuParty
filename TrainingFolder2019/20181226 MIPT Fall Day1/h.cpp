#include <bits/stdc++.h>

const int MOD = int(1e9) + 9;

/*
struct modint {
	int v;
	modint(long long v_ = 0): v(v_) { }
	modint operator+ (modint t) { return modint(v + t.v); }
	modint operator* (modint t) { return }
};
*/

int bits[150][1050];
int ways[150][1050];

int K, B;

int main() {
	while(scanf("%d%d", &K, &B) == 2) {
		ways[1][0 % K] += 1;
		bits[1][1 % K] += 1;
		ways[1][1 % K] += 1;
		for(int b = 1; b <= B; b++) {
			for(int v = 0; v < K; v++) {
				(ways[b+1][(v * 2) % K] += ways[b][v]) %= MOD;
				(ways[b+1][(v * 2 + 1) % K] += ways[b][v]) %= MOD;
				(bits[b+1][(v * 2) % K] += bits[b][v]) %= MOD;
				(bits[b+1][(v * 2 + 1) % K] += (bits[b][v] + ways[b][v]) % MOD) %= MOD;
			}
		}
		printf("%d\n", bits[B][0]);

		for(int i = 0; i < 150; i++) for(int j = 0; j < 1050; j++) bits[i][j] =  ways[i][j] = 0;
	}
	return 0;
}