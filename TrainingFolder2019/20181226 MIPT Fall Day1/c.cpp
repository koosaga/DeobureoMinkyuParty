#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

char s[101];

vector<int> pos[26];
bool chk[26][100];

struct state {
	int l, r, v;
	state(int l_ = 0, int r_ = 0, int v_ = 0): l(l_), r(r_), v(v_) { }
};

char t[200];

vector<state> dp[26];

int v1[55], v2[55];

int main() {
	scanf("%s", t);
	int m = strlen(t);

	s[0] = t[0];
	for(int i = 0, j = 1; j < m; j++) {
		if(s[i] != t[j]) {
			s[++i] = t[j];
		}
	}
	int n = strlen(s);

	for(int i = 0; i < n; i++) {
		pos[s[i] - 'a'].push_back(i);
		chk[s[i] - 'a'][i] = true;
	}

	int maxc = *max_element(s, s+n) - 'a';
	if(pos[maxc].size() >= 2) {
		for(int i : pos[maxc]) for(int j : pos[maxc]) {
			if(i != j) dp[maxc].emplace_back(i, j, pos[maxc].size());
		}	
	}else {
		dp[maxc].emplace_back(pos[maxc][0], pos[maxc][0], 1);
	}

	for(int c = maxc-1; c >= 0; c--) {
		if(pos[c].empty()) {
			dp[c] = dp[c+1];
		}else if(pos[c].size() == 1) {
			int i = pos[c][0];
			fill(v1, v1+n, int(1e9));
			fill(v2, v2+n, int(1e9));
			for(state s : dp[c+1]) {
				// case 1: s.l, s.r -> i, s.r
				{
					int cur = s.v;
					if(s.l - 1 != i || s.l - 1 == s.r) cur += 1;
					v1[s.r] = min(v1[s.r], cur);
				}

				// case 2: s.l, s.r -> s.l, i
				{
					int cur = s.v;
					if(s.r + 1 != i || s.r + 1 == s.l) cur += 1;
					v2[s.l] = min(v2[s.l], cur);
				}
			}

			for(int j = 0; j < n; j++) if(v1[j] < int(1e9)) {
				dp[c].emplace_back(i, j, v1[j]);
			}
			for(int j = 0; j < n; j++) if(v2[j] < int(1e9)) {
				dp[c].emplace_back(j, i, v2[j]);
			}
		}else {
			for(int i : pos[c]) {
				fill(v1, v1+n, int(1e9));
				fill(v2, v2+n, int(1e9));

				for(state s : dp[c+1]) {
					// case 1: s.l, s.r -> i, s.r
					{
						int cur = s.v + pos[c].size();
						if(chk[c][s.l - 1] && (pos[c].size() == 1 || i != s.l - 1)) {
							cur -= 1;
						}
						v1[s.r] = min(v1[s.r], cur);
					//printf(" >> %d %d %d %d %d l\n", i, s.l, s.r, s.v, cur);
					}

					// case 2: s.l, s.r -> s.l, i
					{
						int cur = s.v + pos[c].size();
						if(chk[c][s.r + 1] && (pos[c].size() == 1 || i == s.r + 1)) {
							cur -= 1;
						}
						v2[s.l] = min(v2[s.l], cur);
					//printf(" >> %d %d %d %d %d r\n", i, s.l, s.r, s.v, cur);
					}
				}

				for(int j = 0; j < n; j++) if(v1[j] < int(1e9)) {
					dp[c].emplace_back(i, j, v1[j]);
				}
				for(int j = 0; j < n; j++) if(v2[j] < int(1e9)) {
					dp[c].emplace_back(j, i, v2[j]);
				}

				for(int j : pos[c]) if(i != j) {
					int best = 1e9;
					for(state s : dp[c+1]) {
						int cur = s.v + pos[c].size();
						int ex = 0;
						int l = s.l - 1, r = s.r + 1;
						if(l == r) {
							if(chk[c][l]) cur -= 1;
						}else {
							if(chk[c][l] && l != j) cur -= 1, ex += 1;
							if(chk[c][r] && r != i) cur -= 1, ex += 1;
							if(i == l && r == j && ex == 2 && pos[c].size() > 2) cur += 1;
						}
						best = min(best, cur);
					}
					dp[c].emplace_back(i, j, best);
				}	
			}
		}
		//printf("c = %c %ld\n", c+'a', dp[c].size());
		
		
		/*
		for(state s : dp[c+1]) {
			printf("%c: %d %d %d\n", c+1+'a', s.l, s.r, s.v);
		}*/

	}

	int ans = 1e9;
	for(state s : dp[0]) {
		ans = min(ans, s.v);
	}

	printf("%d\n", ans - 1);
	return 0;
}

/*
4: 5 5 1
3: 3 5 2
3: 5 3 2
2: 4 5 3
2: 3 4 3
2: 4 3 2
2: 5 4 2
1: 1 5 4
1: 4 1 4
1: 1 4 4
1: 3 1 4
1: 1 3 3
1: 4 1 3
1: 1 4 3
1: 5 1 3
0: 0 2 4
0: 2 0 4*/