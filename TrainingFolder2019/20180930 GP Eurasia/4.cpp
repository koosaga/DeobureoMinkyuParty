#include <bits/stdc++.h>

using namespace std;


const int N_ = 100500;

int par[N_];
set<int> bad[N_];

int identify(int x) {
	return par[x] == x ? x : (par[x] = identify(par[x]));
}

bool identify(int a, int b) {
	a = identify(a);
	b = identify(b);
	if(a == b){
		return false;
	}
	par[a] = b;
	return true;
}

int N, M, K;

int main() {
	scanf("%d%d%d", &N, &K, &M);
	for(int i = 0; i < K; i++) {
		int a, b; scanf("%d%d", &a, &b);
		bad[a].insert(b);
		bad[b].insert(a);
	}

	for(int i = 1; i <= N; i++) {
		par[i] = i;
	}

	vector<int> ans;
	for(int i = 1; i <= M; i++) {
		int u, v; scanf("%d%d", &u, &v);

		int a = identify(u); 
		int b = identify(v);
		if(a == b) {
			ans.push_back(i);
			continue;
		}
		
		if(bad[a].find(b) != bad[a].end() ||
			bad[b].find(a) != bad[b].end()) {
			continue;
		}

		ans.push_back(i);
		if(bad[a].size() > bad[b].size()) {
			swap(a, b);
		}
		
		for(int u : bad[a]) {
			bad[u].erase(a);
			bad[u].insert(b);
			bad[b].insert(u);
		}
		bad[a].clear();
		par[a] = b;
	}

	printf("%lu\n", ans.size());
	for(int x : ans) printf("%d ", x);
	return 0;
}