#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MOD = (int)1e9 + 7;

int R, C;


long long ways[2][3][16][1<<14];
int tot[2];

char tmp[2000];
int A[2000];

int main() {
	scanf("%d%d", &R, &C);
	for(int i = 0; i<  R; i++) {
		scanf("%s", tmp);
		for(int j = 0; j < C; j++) if(tmp[j] == '.') A[j + 1] |= 1<<i;
	}
	ways[0][0][R][0] = 1; 
	for(int j = 1; j <= C; j++) {
		memset(ways[j&1], 0, sizeof(ways[j&1]));
		for(int mask = 0; mask < (1<<R); mask++){
			ways[j&1][1][0][mask] = ways[(j-1)&1][0][R][mask] % MOD;
			ways[j&1][2][0][mask] = ways[(j-1)&1][1][R][mask] % MOD;
		}
		for(int i = 0; i < R; i++){
			for(int mask = 0; mask < (1<<R); mask++) {
				ways[j&1][0][i+1][mask] += ways[j&1][0][i][mask];
				ways[j&1][1][i+1][mask] += ways[j&1][1][i][mask];
				ways[j&1][2][i+1][mask] += ways[j&1][2][i][mask];
				if((A[j] >> i) & 1){
					ways[j&1][0][i+1][mask | (1 << i)] += ways[j&1][0][i][mask];
					ways[j&1][0][i+1][mask | (1 << i)] += ways[j&1][1][i][mask];
					ways[j&1][0][i+1][mask | (1 << i)] += ways[j&1][2][i][mask];
				}
			}
		}
	}
	long long ret = 0;
	ret += ways[C&1][0][R][(1<<R)-1];
	ret += ways[C&1][1][R][(1<<R)-1];
	ret %= MOD;
	printf("%lld\n", ret);
	return 0;
}
