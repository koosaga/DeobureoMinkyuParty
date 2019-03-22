#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

char S[int(1.1e6)];
int pos[257];

int cnt[26][26];
int now[26];

int main() {
	freopen("consonant.in", "r", stdin);
	freopen("consonant.out", "w", stdout);

	scanf("%s", S);
	int N = strlen(S);

	fill(pos, pos+256, -1);
	for(int t = 0, c = 'a'; c <= 'z'; c++) {
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'w' || c == 'y') continue;
		 {
			pos[c] = t++;
		}
	}

	for(int i = 0; i+1 < N; i++) {
		int x =pos[S[i]];
		int y = pos[S[i+1]];
		if(x > y) swap(x, y);
		if(x < 0 || y < 0) continue;
		cnt[x][y] += 1;	
	}

	int ansm = 0;
	int ansc = -1;
	for(int mask = 0; mask < (1<<(26-7)); mask++) {
		for(int i = 0; i < 21; i++) now[i] = (mask >> i)  & 1;
		int cur = 0;
		for(int i = 0; i < 21; i++) {
			for(int j = i; j < 21; j++) {
				if(now[i] != now[j]) cur += cnt[i][j];
			}
		}
		if(cur > ansc) {
			ansc = cur;
			ansm = mask;
		}
	}

	for(int i = 0; i < N; i++) {
		if(pos[S[i]] >= 0 && ((ansm >> pos[S[i]]) & 1) == 1) {
			S[i] += 'A' - 'a';
		}
	}

	puts(S);


	return 0;
}
