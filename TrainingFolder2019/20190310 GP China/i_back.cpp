#include <bits/stdc++.h>

using namespace std;

const int MAXN = int(1e7);

const int MOD = int(1e9) + 7;

using lint = long long;

set<vector<int>> ans,ext;

vector<int> cur;


int N, M;
void go (int x, int sum) {
	if(x == M) {
		vector<int> p = cur;
		vector<int> q = cur;
		for(int i = 0; i < M; i++) {
			q = min(q, p);
			reverse(p.begin(), p.end());
			q = min(q, p);
			reverse(p.begin(), p.end());
			rotate(p.begin(), p.begin()+1, p.end());
		}
		if(*max_element(q.begin(),q.end()) < (N+1)/2) {
			ans.insert(q);
		
		}else {
			ext.insert(q);	
		}
		return;
	}
	if(x == M-1) {
		cur.push_back(N - sum);
		go(x + 1, sum + cur.back());
		cur.pop_back();
		return;
	}
	
	for(int v = 1; v + sum + (M - x - 1) <= N; v++) {
		cur.push_back(v);
		go(x + 1, sum + v);
		cur.pop_back();
	}
}


int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		ans.clear();ext.clear();
		go(0, 0);
		printf("%ld\n", ans.size());
		printf("- tot=%ld, ext=%ld\n", ext.size()+ans.size(),ext.size());
		/*printf("ans:\n");
		for(auto it : ans ){
		for(int x : it)printf("%d ",x);
		puts("");
		}*/
		printf("Ext:\n");
		for(auto it : ext ){
		for(int x : it)printf("%d ",x-1);
		puts("");
		}
		assert(cur.empty());
	}
	
	return 0;
}
