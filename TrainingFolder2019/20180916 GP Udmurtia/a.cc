#include <bits/stdc++.h>

const int N_ = 100500;

char S[100500];
int L[N_];

const int MOD = int(1e9) + 7;
int ways[11][1<<10]; // ways[i][mask]: last=i, mask: alive
int prv[11][1<<10];

int main() { 
	scanf("%s", S+1);
	int N = strlen(S+1);
	std::vector<int> last(10, -1);
	for(int i = 1; i <= N; i++) {
		S[i] -= '0';
		L[i] = last[S[i]];
		last[S[i]] = i;
	}

	ways[10][0] = 1;
	for(int i = 1; i <= N; i++) {
		for(int mask = 0; mask < (1<<10); mask++) {
			prv[10][mask] = ways[10][mask];
			prv[S[i]][mask] = ways[S[i]][mask];
			(ways[S[i]][mask] += ways[10][mask]) %= MOD;
		}
		for(int mask = 0; mask < (1<<10); mask++) {
			(ways[10][mask] = prv[S[i]][mask]) %= MOD;
			if((mask >> S[i]) & 1) {
				(ways[10][mask] += prv[10][mask ^ (1 << S[i])]) %= MOD;
			}
		}
	}

	int ans = 0;
	for(int mask = 1; mask < (1<<10); mask++) {
		(ans += ways[10][mask]) %= MOD;
	}
	printf("%d\n", ans);
	return 0;
}