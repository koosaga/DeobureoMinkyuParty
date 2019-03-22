#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

using ll = long long;
int n, m; ll K;

struct query {
	int c, p;
};

const int N_ = int(1e6) + 10;

vector<query> queries[N_];


const int leaf = 1<<20;

long long cnt[leaf + leaf + 10];
long long sum[leaf + leaf + 10];

void upd (int x, int v) {
	ll w = (ll)x * v;
	for(x += leaf; x > 0; x >>= 1) {
		cnt[x] += v;
		sum[x] += w;
	}
}


int main(){
	scanf("%d%lld%d", &n, &K, &m);
	for(int i = 1; i <= m; i++) {
		int l, r, c, p; scanf("%d%d%d%d", &l, &r, &c, &p);
		queries[l].push_back({c, p});
		queries[r+1].push_back({-c, p});
	}

	long long ans = 0;
	for(int x = 1; x <= n; x++) {
		for(query q : queries[x]) {
			upd(q.p, q.c);
		}

		long long k = K;
		int u = 1;
		while(u < leaf) {
			if(k <= cnt[u*2]) {
				u = u * 2;
			}else {
				k -= cnt[u*2];
				ans += sum[u*2];
				u = u * 2 + 1;
			}
		}
		ans += min(cnt[u], k) * (u - leaf);
	}

	printf("%lld\n", ans);
	return 0;
}