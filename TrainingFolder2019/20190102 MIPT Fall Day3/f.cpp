#include <bits/stdc++.h>

using namespace std;

int N;

const int N_ = int(1e5) + 3;

using pii = pair<int,int>;

int A[N_];
vector<int> ch[N_];

vector<int> cur;

void dfs(int u) {
	cur.push_back(u);
	for(int v : ch[u]) dfs(v);
}

void solve() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}

	set<pii> heads;
	for(int i = N; i > 0; i--) {
		if(heads.empty()) {
			heads.emplace(A[i], i);
			continue;
		}
		auto it = heads.lower_bound(pii(A[i], 0));
		for(int rep = 0; rep < 2; rep++) {
			if(it == heads.end()) break;
			auto nit = it; nit++;
			ch[i].push_back(it->second);
			heads.erase(it);
			it = nit;
		}
		heads.emplace(A[i], i);
	}

	printf("%ld\n", heads.size());
	for(auto it : heads) {
		int u = it.second;
		cur.clear();
		dfs(u);
		sort(cur.begin(), cur.end());
		printf("%ld", cur.size());
		for(int x : cur) printf(" %d", x);
		puts("");
	}

	for(int i = 1; i <= N; i++) ch[i].clear();

}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		solve();
	}
	return 0;
}