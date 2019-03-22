#include <bits/stdc++.h>

using namespace std;

using lint = long long;

char S[int(1.1e5)];
char T[int(1.1e2)];
int N, M;

int nxt[int(1.1e5)][26];

int last[26];

lint ans;

int main() {
	scanf("%s%s", S+1, T+1);
	N = strlen(S+1);
	M = strlen(T+1);
	
	for(int i = N; i > 0; i--) {
		for(int c = 0; c < 26; c++) nxt[i][c] = last[c];
		last[S[i] - 'a'] = i;	
	}

	int pi = 0;	
	for(int i = 1; i <= N; i++) {
		if(S[i] != T[1]) continue;
		
		int j = i;
		for(int x = 2; x <= M; x++) {
			j = nxt[j][T[x] - 'a'];
		}

		if(j == 0) continue;
		
		ans += (lint) (i - pi) * (N - j + 1);
		pi = i;
	}
	
	printf("%lld\n", ans);
	return 0;
}
