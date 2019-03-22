#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;

const int n_ = 1050;

int n, m, k;
vector<pii> gph[n_];

lint dst[n_][n_];

const int K_ = 1050;
int U[K_];
lint S[K_], T[K_];

long long dp[n_];

int main() {
	scanf("%d%d", &n, &m);
	for(int rep = 0; rep < m; rep++) {
		int u, v, d; scanf("%d%d%d", &u, &v, &d);
		gph[u].emplace_back(v, d);
		gph[v].emplace_back(u, d);
	}

	for(int st = 1; st <= n; st++) {
		priority_queue<pli, vector<pli>, greater<pli>> pq;
		fill(dst[st], dst[st]+n+1, (lint)1e18);
		dst[st][st] = 0;
		pq.emplace(0, st);
		while(!pq.empty()) {
			lint d; int u;
			tie(d, u) = pq.top(); pq.pop();
			for(auto e : gph[u]) {
				int v = e.first;
				if(dst[st][v] > dst[st][u] + e.second) {
					dst[st][v] = dst[st][u] + e.second;
					pq.emplace(dst[st][v], v);
				}
			}
		}
	}	

	scanf("%d", &k);
	for(int rep = 1; rep <= k; rep++) {
		int s, u, t; scanf("%d%d%d", &s, &u, &t);
		S[rep] = s;
		U[rep] = u;
		T[rep] = t;
	}

	lint low = 0, high = (lint)1e15, ans = (lint)1e15;
	while(low <= high) {
		lint mid = (low + high) >> 1;
		fill(dp, dp+k+1, (lint)1e18);
		dp[0] = 0;
		for(int i = 1; i <= k; i++) {
			long long cur_max = -(lint)1e18;
			long long dsum = 0;
			for(int j = i; j <= k; j++) {
				dsum += dst[(j == i) ? 1 : U[j-1]][U[j]];
				cur_max = max(cur_max, dsum - S[j]);
				if(cur_max + max(T[j], dp[i-1]) <= mid) 
					dp[j] = min(dp[j], max(T[j], dp[i-1]) + dsum + dst[U[j]][1]);
			}
		}
		if(dp[k] < (lint)1e18) {
			ans = mid;
			high = mid-1;
		}else {
			low = mid+1;
		}
	}

	printf("%lld\n" , ans);
	return 0;

}