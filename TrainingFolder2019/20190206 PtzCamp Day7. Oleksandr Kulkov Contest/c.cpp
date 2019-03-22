#include <bits/stdc++.h>

using lint = long long;
using namespace std;

mt19937 rng(10248);

const int N = 4, Q = 10;

lint ipow (lint a, lint b, lint mod) {
	lint ret = 1;
	while(b > 0) {
		if(b & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ret;
}


const lint MOD[2] = {lint(1e9) + 9, 999999937};


int ask (int x) {
	assert(129 <= x && x <= 512);
	printf("%d\n", x);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	if(ret < 0) {
		ret += int(2e7) - 1;
	}
	return ret;
}

int main() {
	vector<int> p;

	for(int x = 129; x <= 512; x++) {
		p.push_back(x);
	}
	shuffle(p.begin(), p.end(), rng);
	p.resize(Q);


	for(int t = 0; t <= N-1; t++) {
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < Q; j++) {
				cur[i][j] = cur[i][j] * r[i][j] % MOD[i];
			}
		}
	}

	return 0;
}