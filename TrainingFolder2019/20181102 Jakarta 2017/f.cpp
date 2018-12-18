#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;
using llf = long double;


int N, K;
int cnt[3050];

llf tb[3050][3050];


void solve() {
	scanf("%d%d", &N, &K);
	for(int i = 1; i <= N; i++) cnt[i] = 0;
	for(int i = 0; i < K; i++) {
		int x; scanf("%d", &x);
		cnt[x] = min(cnt[x]+1, 2);
	}

	int x = 0, y = 0;
	for(int i = 1; i <= N; i++) {
		if(cnt[i] == 0) x += 1;
		if(cnt[i] == 1) y += 1;
	}

	printf("%.20Lf\n", tb[x][y] * N);

}

int main(){
	for(int i = 0; i <= 3000; i++) {
		for(int j = (i == 0 ? 1 : 0); j <= 3000; j++) {
			tb[i][j] = (i * (i == 0 ? 0 : tb[i-1][j+1]) + j * (j == 0 ? 0 : tb[i][j-1]) + 1) / (i + j);
		}
	}

	int T; scanf("%d", &T);
	while(T--) {
		solve();
	}
	return 0;
}







