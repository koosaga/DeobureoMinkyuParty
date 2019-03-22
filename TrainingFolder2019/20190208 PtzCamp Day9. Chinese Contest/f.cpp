#include <bits/stdc++.h>

using lint = long long;

using namespace std;


unordered_map<int, int> wh;

const int Q_ = 10050;

int Q, N[Q_], M[Q_], S[Q_];
int ans[Q_];

vector<int> pos[int(8e3)];

const int MOD = int(1e9) + 7;

int main() {
	scanf("%d", &Q);
	for(int i = 0; i < Q; i++) {
		scanf("%d%d%d",N+i,M+i,S+i);

		auto go = [&i](int d) {
			int p = -1;
			auto it = wh.find(d);
			if(it == wh.end()) {
				p = wh.size();
				wh[d] = p;
			}else {
				p = it->second;
			}
			pos[p].push_back(i);
		};

		for(int d = 1; d * d <= S[i]; d++) {
			if(S[i] % d == 0) {
				go(d);
				if(d * d != S[i]) go(S[i] / d);
			}
		}
	}


	for(int a = 0; a * a <= int(1e8); a++) {
		for(int b = 0; b <= a && a * a + b * b <= int(1e8); b++) {
			int z = a * a + b * b;
			if(wh.find(z) != wh.end()) {
				for(int q : pos[wh[z]]) {
					int n = N[q], m = M[q], s = S[q];
					int k = s / z;

					int coef = ((a == b && k == 1) || (b == 0)) ? 1 : 2;

					{
						{
						int x = n - max(b, a * k) + 1;
						int y = m - (a + b * k) + 1;
						if(x > 0 && y > 0) {
							ans[q] += lint(x) * y * coef % MOD;
							if(ans[q] >= MOD) ans[q] -= MOD;
						}}
						{
						int x = m - max(a, b * k) + 1;
						int y = n - (b + a * k) + 1;
						if(x > 0 && y > 0) {
							ans[q] += lint(x) * y * coef % MOD;
							if(ans[q] >= MOD) ans[q] -= MOD;
						}}
					}

					if(a != b && (b != 0)) {
						{
						int x = m - max(b, a * k) + 1;
						int y = n - (a + b * k) + 1;
						if(x > 0 && y > 0) {
							ans[q] += lint(x) * y * coef % MOD;
							if(ans[q] >= MOD) ans[q] -= MOD;
						}}
						{
						int x = n - max(a, b * k) + 1;
						int y = m - (b + a * k) + 1;
						if(x > 0 && y > 0) {
							ans[q] += lint(x) * y * coef % MOD;
							if(ans[q] >= MOD) ans[q] -= MOD;
						}}
					} 
				}
			}
		}
	}

	for(int q = 0; q < Q; q++) {
		printf("%lld\n", ((lint)ans[q] * 2) % MOD);
	}

	return 0;
}
	/*
	for(int a = 0; a * a <= int(1e8); a++) {
		for(int b = 0; b < a && a * a + b * b <= int(1e8); b++) {
			freq[a*a + b*b] += 1;
		}
	}

	long long ans = 0;
	for(int n = 1; n <= int(1e8); n++) {
		long long ret = 0, cnt = 0;
		for(int i = 1; i * i <= n; i++) {
			if(n % i == 0) {
				cnt += 1;
				ret += freq[i];
				if(i * i != n) ret += freq[n / i], cnt += 1;
			}
		}
		if(ans < ret) {
			ans = ret;
			printf("%d %lld\n", n, ans);
		}
	}
	printf("%lld\n", ans);*/
