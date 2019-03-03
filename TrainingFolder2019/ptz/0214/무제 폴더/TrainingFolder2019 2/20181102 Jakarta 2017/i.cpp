
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;


const int N_ = 1050;
const int K_ = 205;

int N, K;
string A[N_];
int P[N_];

char ans[N_][K_];

int nxt[int(2.1e5)][26];

int main(){
	scanf("%d%d", &N, &K);
	for(int i = 1; i <= N; i++) {
		static char tmp[int(2.1e5)];
		scanf("%s", tmp);
		A[i] = "?" + string(tmp);
		P[i] = i;
	}
	sort(P+1, P+N+1, [&](const int &p, const int &q) {
		return A[p] < A[q];
	});

	if(K == 1) {
		for(int i = 1; i <= N; i++) ans[i][1] = A[i][1];
	}else {
		for(int p = 1; p <= N; p++) {
			string &s = A[P[p]];
			int l = s.length() - 1;

			vector<int> cur(26, l+1);
			for(int c = 0; c < 26; c++) nxt[l+1][c] = l+1;
			for(int i = l; i >= 0; i--) {
				for(int c = 0; c < 26; c++) nxt[i][c] = cur[c];
				if(i > 0) cur[s[i] - 'A'] = i;
			}

			vector<int> walk;
			walk.push_back(0);
			bool equ = false;
			if(ans[P[p-1]][1] == s[1]) {
				for(int i = 1; i <= K; i++) {
					walk.push_back(nxt[walk.back()][ans[P[p-1]][i] - 'A']);
				}
				equ = true;
			}else {
				int i = 1;
				walk.push_back(nxt[walk.back()][s[1] - 'A']);
			}

			bool chk = false;
			for(int same = int(walk.size() - 1); same >= 1; same--) {
				int x = walk[same];
				if(same == K || x > l) {
					continue;
				}
				for(int i = same+1; i <= K; i++) {
					int y = -1;
					for(int c = (equ && i == same+1 ? ans[P[p-1]][i] - 'A' + 1 : 0); c < 26; c++) {
						if(nxt[x][c] + (K - i) <= l) {
							y = nxt[x][c];
							ans[P[p]][i] = c+'A';
							break;
						}
					}
					if(y < 0) {
						x = -1;
						break;
					}
					x = y;
				}
				if(x > 0) {
					for(int i = 1; i <= same; i++) {
						ans[P[p]][i] = ans[P[p-1]][i];
					}
					ans[P[p]][1] = s[1];
					chk = true;
					break;
				}
			}

			if(!chk) {
				puts("NO");
				return 0;
			}

		}
	}

	for(int p = 2; p <= N; p++) {
		if(string(ans[P[p-1]]+1) >= string(ans[P[p]]+1)) {
			puts("NO");
			return 0;
		}
	}

	puts("YES");
	for(int p = 1; p <= N; p++) {
		printf("%s\n", ans[p]+1);
	}

	return 0;
}

/*
1 0 1 0 2 0
1 0 2 2 3 0
2 1 2 2 5 1
2 1 2 2 4 2
3 1 2 3 5 3
3 1 2 3 5 4
3 1 2 3 5 5
3 1 2 3 5 6
3 1 2 3 5 7
3 1 2 3 5 8
3 1 2 3 5 9
3 1 2 3 5 10
3 1 2 3 5 11
3 1 2 3 5 12
3 1 2 3 5 13
3 1 2 3 5 14
3 1 2 3 5 15
3 1 2 3 5 16
3 1 2 3 5 17
3 1 2 3 5 18
3 1 2 3 5 19
3 1 2 3 5 20
3 1 2 3 5 21
3 1 2 3 5 22
3 1 2 3 5 23
3 1 2 3 5 24
3 1 2 3 5 25
3 0 1 0 2 1
3 0 2 2 3 0
YES
BA
AA
AC*/