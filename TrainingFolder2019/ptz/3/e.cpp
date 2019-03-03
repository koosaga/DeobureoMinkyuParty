#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

const int n_ = int(1.1e6);

int n;

bool vis[n_];

int t[n_];

using lint = long long;

struct modint {
	int v;
	modint(lint v_ = 0): v(v_ % mod) { }
	modint operator+(const modint m) const {
		return modint(v + m.v);
	}
	modint operator-(const modint m) const {
		return modint(v - m.v + mod);
	}
	modint operator*(const modint m) const {
		return modint((lint)v * m.v);
	}
};

modint ans[n_];

modint fac[n_], invfac[n_], inv[n_];

modint comb (int n, int r) {
	return fac[n] * invfac[n-r] * invfac[r];
}

int chain[n_];
int sz[n_], id;
int sum_sz;
int indeg[n_];


int perm[n_];
int cursum[n_];

int main() {
	fac[0] = fac[1] = 1;
	invfac[0] = invfac[1] = 1;
	inv[1] = 1;
	for(int i = 2; i < n_; i++) {
		fac[i] = fac[i-1] * i;
		inv[i] = inv[mod % i] * modint(mod - mod / i);
		assert((inv[i] * i).v == 1);
		invfac[i] = invfac[i-1] * inv[i];
	}

	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &t[i]);
		indeg[t[i]] += 1;
	}

/*
	{
		for(int i = 1; i <= n; i++) perm[i] = i;
		do {
			bool good = true;
			for(int i = 1; i <= n; i++) good &= (t[i] == 0 || t[i] == perm[i]);
			if(!good) continue;

			for(int i = 1; i <= n; i++) {
				int x = perm[i], c = 1;
				while(x != i) x = perm[x], c += 1;
				cursum[i] += c;
			}
		}while(next_permutation(perm+1, perm+n+1));

		int cc = 0;
		for(int i = 1; i <= n; i++) if(t[i] == 0) cc++;

		for(int i = 1; i <= n; i++) {
			printf("%d ", (modint(cursum[i]) * invfac[cc]).v);
		}
		puts("");
	}*/

	for(int rep = 0; rep < 2; rep++) {
		for(int i = 1; i <= n; i++) {
			if(!vis[i] && indeg[i] == rep) {
				int c = 0, x;
				vector<int> p;
				for(x = i; x > 0 && !vis[x]; x = t[x]) {
					vis[x] = true;
					c++;
					p.push_back(x);
				}
				if(x == 0) { // chain
					sz[++id] = c;
					sum_sz += c;
					for(int u : p) chain[u] = id;
				}else { // cycle
					for(int u : p) ans[u] = c;
				}
			}
		}

	}

	modint chain_ans = 0;
	modint chain_cnt = 0;
	for(int k = 1; k <= id; k++) {
		if(k > 1) chain_ans = chain_ans + (comb(id-2, k-2)) * fac[k-1] * fac[id-k] * invfac[id];
		chain_cnt = chain_cnt + (comb(id-1, k-1)) * fac[k-1] * fac[id-k] * invfac[id];
	}
	//printf("%d %d\n", chain_ans.v, chain_cnt.v);

	for(int i = 1; i <= n; i++) {
		if(chain[i]) ans[i] = chain_ans * (sum_sz - sz[chain[i]]) + chain_cnt * sz[chain[i]]; // (sum_sz - sz[chain[i]]) + sz[chain[i]];
		printf("%d%c", ans[i].v, i < n ? ' ' : '\n');
	}
	return 0;
}