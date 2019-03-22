#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

long long n;

int main() {
	freopen("little.in", "r", stdin);
	freopen("little.out", "w", stdout);

	scanf("%lld" ,&n);

	for(int p = 0; p <= 60; p++) {
		if((1ll << p) == n) {
			puts("-1");
			return 0;
		}
	}

	vector<vector<lint>> ans;
	ans.push_back(vector<lint>(1, n));

	auto go = [&ans](long long x) {
		vector<lint> vec;
		lint t = n;
		while(t % x == 0) t /= x, vec.push_back(x);
		while(t % (x+1) == 0) t /= x+1, vec.push_back(x+1);
		if(t == 1) {
			ans.push_back(vec);
		}
	};


	for(long long x = 2; x <= (lint)1e7; x++) {
		go(x);
	}

	if(n >= (lint)1e14) {
		for(lint x = (lint)sqrt(n)-1; x * x <= n; x++) {
			go(x);
		}
	}

	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end()) -ans.begin());
	printf("%lu\n", ans.size());
	for(auto row : ans) {
		printf("%lu", row.size());
		for(lint x : row) printf(" %lld", x);
		puts("");
	}



	return 0;
}