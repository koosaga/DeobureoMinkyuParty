#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
#define tm aasdiasjo

int R[int(5.1e3)];

int ways[int(5.1e3)][int(5.1e3)];
bool possible[int(5.1e3)][int(5.1e3)];

int comb[int(5.1e3)][int(5.1e3)];

vector<pi> posl[int(5.1e3)], posr[int(5.1e3)];
vector<int> posx[int(5.1e3)], posy[int(5.1e3)];
int whl[int(5.1e3)], whr[int(5.1e3)];
vector<int> pos[int(5.1e3)];
int used[int(5.1e3)], tm;

void solve() {
	int N; scanf("%d", &N);
	for(int i = 1; i <= N; i++) scanf("%d", &R[i]);
	
	for(int i = 1; i <= N; i++) {
		if(i - R[i] < 1 || i + R[i] > N) {
			puts("NO");
			return;
		}
	}
	for(int i = 1; i <= N; i++) {
		posl[i - R[i]].emplace_back(i + R[i], i);
		posr[i + R[i]].emplace_back(i - R[i], i);
	}
	
	for(int i = 0; i <= N; i++) {
		possible[i][i+1] = true;
		ways[i][i+1] = 1;
	}
	for(int i = 0; i <= N; i++) {
		possible[i+1][i] = true;
		ways[i+1][i] = 1;
	}
	for(int i = 1; i <= N; i++) {
		possible[i][i] = (R[i] == 0);
		ways[i][i] = (R[i] == 0) ? 1 : 0;
		whl[i] = whr[i] = 0;
		sort(posl[i].begin(), posl[i].end());
		sort(posr[i].rbegin(), posr[i].rend());
		posl[i].emplace_back(-1, -1);
		posr[i].emplace_back(-1, -1);
		
		{
			int j = i;
			if(posl[i][whl[i]].first == j) {
				posx[i].push_back(posl[i][whl[i]].second);
				whl[i] += 1;
			}
			if(posr[j][whr[j]].first == i) {
				posy[j].push_back(posr[j][whr[j]].second);
				whr[j] += 1;
			}
		}
	}
	
	for(int len = 2; len <= N; len++) {
		for(int i = 1, j = len; j <= N; i++, j++) {
			bool cur_possible = false;
			long long cur_ways = 0;
			auto go = [&cur_possible, &cur_ways, &len, &i, &j](int k) {
				if(used[k] == tm) return;
				used[k] = tm;
				//printf("[%d, %d] %d : %d %d\n",i,j,k,ways[i][k-1],ways[k+1][j]);
				if(!possible[i][k-1] || !possible[k+1][j]) return;
				cur_possible = true;
				cur_ways += ((lint)comb[len - 1][k - i] * ways[i][k-1] % mod) * ways[k+1][j] % mod;
			};
			if(posl[i][whl[i]].first == j) {
				posx[i].push_back(posl[i][whl[i]].second);
				whl[i] += 1;
			}
			if(posr[j][whr[j]].first == i) {
				posy[j].push_back(posr[j][whr[j]].second);
				whr[j] += 1;
			}
			tm += 1;
			for(int k : posx[i]) {
				go(k);
			}
			for(int k : posy[j]) {
				go(k);
			}
			
			possible[i][j] = cur_possible;
			ways[i][j] = cur_ways % mod;
		}
	}
	
	if(!possible[1][N]) {
		puts("NO");
	}else {
		printf("%d\n", ways[1][N]);
	}
	for(int i = 0; i <= N; i++) {
		pos[i].clear();
		posl[i].clear();
		posr[i].clear();
		posx[i].clear();
		posy[i].clear();
		for(int j = 0; j <= N; j++) {
			possible[i][j] = false;
			ways[i][j] = 0;
			//printf("[%d, %d]: %d %d\n", i, j, possible[i][j], ways[i][j]);
		}
	}
}

int main(){
	comb[0][0] = 1;
	for(int n = 1; n <= 5000; n++) {
		comb[n][0] = 1;
		for(int k = 1; k <= n; k++) comb[n][k] = (comb[n-1][k] + comb[n-1][k-1]) % mod;
	}
	int tc; scanf("%d",&tc);
	while(tc--){
		solve();
	}
}


