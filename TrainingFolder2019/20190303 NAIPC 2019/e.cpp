#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const int MOD = int(1e9) + 7;

const int N_ = 20;

int R, C;
int A[N_][N_];

int ways[N_][3*N_];

int mapping[1<<N_];
int when[1<<N_];

bitset<(1<<N_)> up[N_];
bitset<(1<<N_)> down[N_];
int trans[N_][N_];

int bit[1<<N_];
bool good[N_];

lint ans;

int main() {
	scanf("%d%d", &R, &C);
	for(int i = 0; i < R; i++) {
		for(int j = 0; j < C; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	
	for(int j = 0; j < C; j++) {
		for(int k = j+1; k < C; k++) {
			int cur = 0;
			for(int i = 0; i < R; i++) {
				cur |= (A[i][j] < A[i][k]) << i;
			}
			trans[j][k] = cur;
		}
	}
	
	for(int i = 0; i < R; i++) {
		bit[1<<i] = i;
	}
	
	for(int j = 0; j < C; j++) {
		for(int mask = 1; mask < (1<<R); mask++) {
			int i = bit[mask & -mask];
			if(mask == (1<<i)) {
				up[j][mask] = down[j][mask] = true;
			}else {
				int submask = mask ^ (1<<i);
				int i2 = bit[submask & -submask];
				up[j][mask] = up[j][submask] && (A[i][j] < A[i2][j]);
				down[j][mask] = down[j][submask] && (A[i][j] > A[i2][j]);
			}
		}
		for(int mask = 1; mask < (1<<R); mask++) {
			up[j][mask] = up[j][mask] || down[j][mask];
		}
	}
	
	
	for(int mask = 1; mask < (1<<R); mask++) {
		for(int j = 0; j < C; j++) good[j] = up[j][mask];
		
		int pos = 0;
		for(int j = 0; j < C; j++) if(good[j]) {
			for(int k = j+1; k < C; k++) if(good[k]) {
				int cur = trans[j][k] & mask;
				if(when[cur] != mask) {
					when[cur] = mask;
					mapping[cur] = pos++;
				}
				ways[k][mapping[cur]] += 1 + ways[j][mapping[cur]];
			}
		}
		
		for(int j = 0; j < C; j++) if(good[j]) {
			ans += 1;
			for(int k = 0; k <= pos; k++) {
				ans += ways[j][k];
				ways[j][k] = 0;
			}
		}
		
		/*
		for(int j : p) {
			for(int k : p) if(j < k) {
				ways[k][trans[j][k] & mask] += 1 + ways[j][trans[j][k] & mask];
			}
		}
		for(int j = 0; j < C; j++) {
			for(auto &it : ways[j]) ans += it.second;
			ways[j].clear();
		}*/
	}
	
	printf("%lld\n", ans);
	return 0;
}
