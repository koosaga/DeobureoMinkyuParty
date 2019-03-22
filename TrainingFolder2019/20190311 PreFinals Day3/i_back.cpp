#include <bits/stdc++.h>

using namespace std;

int P, N;

vector<int> multiply(vector<int> p, vector<int> q) {
	vector<int> ret(int(p.size()) + int(q.size()) - 1);
	for(unsigned i = 0; i < p.size(); i++) {
		for(unsigned j = 0; j < q.size(); j++) {
			(ret[i + j] += p[i] * q[j]) %= P;
		}
	}
	return ret;
}

vector<vector<int>> ans[20];

vector<vector<int>> ans2[20];

vector<vector<int>> all;
set<vector<int>> del;

void gen(vector<int> now) {
	if(now.size() == N+1) {
		ans2[N].push_back(now);
		if(del.find(now) == del.end()) {
			ans[N].push_back(now);
		}
		return;
	}
	
	if(now.size() == N) {
		now.push_back(1);
		gen(now);
		now.pop_back();
		return;
	}
	
	for(int x = 0; x < P; x++) {
		now.push_back(x);
		gen(now);
		now.pop_back();
	}
}

int main() {
	for(P = 3; P <= 13; P++) {
	 	bool good = true;
		for(int i = 2; i < P; i++) {
			if(P % i == 0) good = false;
		}
		if(!good) continue;
		
		{
			ans[1].clear();
			vector<int> p(2);
			p[1] = 1;
			for(int i = 0; i < P; i++) {
				p[0] = i;
				ans[1].push_back(p);
			}
				ans2[1] = ans[1];
		}
		
			printf("%9d", (int)ans[1].size());
		for(N = 2; N <= 5 || (N == 8 && P <= 5); N++) {
			ans[N].clear();
			ans2[N].clear();
			del.clear();
			for(int k = 1; k <= N-k; k++) {
				for(auto &v1 : ans2[k]) for(auto &v2 : ans2[N-k]) {
					del.insert(multiply(v1, v2));
				}
			}
			all.clear();
			gen(vector<int>());
			
			//printf("%9d", (int)ans[N].size());
			int c = 0, sz = ans[N].size();
			while(0 && sz % P == 0) {
				sz /= P;
				c += 1;
			}
			printf("%9d",sz);
			
			//if(!(N == 2 && P == 2)) assert(ans[N].size() % pp == 0);
			fflush(stdout);
		}
	
		for(int n = 1; n <= 7; n++) {
			continue;
			printf("p=%d n=%d -> ans=%d\n", P, n, (int)ans[n].size()); 
			for(auto it : ans[n]) {
				printf(" : ");
				for(int c : it) printf("%4d", c);
				puts("");
			}
			puts("");
		}
		puts("");
	}
	return 0;
}

