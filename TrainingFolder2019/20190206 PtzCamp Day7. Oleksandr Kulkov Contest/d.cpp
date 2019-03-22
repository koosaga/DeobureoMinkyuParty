#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const int k_ = 150;

const int MOD = int(1e9) + 7;
const int mod = int(1e9) + 7;

mt19937 rng;
uniform_int_distribution<int> gen(1, 100000000);

int k, a[k_], b[k_];

lint f[k_];

vector<int> get_nth_and_k_more (lint n) {
	vector<int> s(k), t(k);
	s[0] = 1;
	if(k != 1) t[1] = 1;
	else t[0] = a[0];

	auto mul = [&](vector<int> v, vector<int> w) {
		int m = v.size();
		vector<int> t(2 * m);
		for(int j = 0; j < m; j++) for(int k = 0; k < m; k++) {
			t[j+k] += lint(v[j]) * lint(w[k]) % MOD;
			if(t[j+k] >= MOD) t[j+k] -= MOD;
		}
		for(int j = 2*m-1; j >= m; j--) {
			for(int i = 1; i <= m; i++) {
				t[j-i] += 1ll * t[j] * a[i-1] % MOD;
				if(t[j-i] >= MOD) t[j-i] -= mod;
			}
		}
		t.resize(m);
		return t;
	};

	while(n) {
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}

	vector<int> ret;
	for(int i = 0; i < k; i++) {
		lint cur = 0;
		for(int j = 0; j < k; j++) cur += lint(s[j]) * f[j] % mod;
		ret.push_back(cur % mod);

		vector<int> nxt(2 * k);
		for(int j = 0; j < k; j++) {
			if(k != 1) {
				(nxt[j+1] += s[j]) %= MOD;
			}else {
				(nxt[j] += (lint)(s[j]) * a[0] % MOD) %= MOD;
			}
		}
		for(int j = k+1; j >= k; j--) {
			for(int i = 1; i <= k; i++) {
				nxt[j-i] += 1ll * nxt[j] * a[i-1] % MOD;
				if(nxt[j-i] >= MOD) nxt[j-i] -= mod;
			}
		}
		nxt.resize(k);
		s = nxt;
	}

	return ret;
}

vector<int> basis[505];

lint ipow(lint a, lint b) {
	lint ret = 1;
	while(b > 0) {
		if(b & 1) (ret *= a) %= mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ret;
}

lint modinv(lint a) {
	return ipow(a, mod-2);
}

int inv;
lint gyesu = 1;

void insert(int *v) {
	for(int i = 0; i < k; i++) {
		if(basis[i].size()) inv ^= 1;
		if(v[i] && basis[i].empty()) {
			for(int j = 0; j <= k; j++) basis[i].push_back(v[j]);
			return;
		}
		if(v[i]) {
			lint minv = ipow(basis[i][i], mod - 2) * v[i] % mod;
			for(auto &j : basis[i]) {
				j = (j * minv) % mod;
			}
			gyesu *= minv;
			gyesu %= mod;
			for(int j = 0; j < basis[i].size(); j++) {
				v[j] += mod - basis[i][j];
				while(v[j] >= mod) v[j] -= mod;
			}
		}
	}
	assert(false);
}

int mat[k_][k_], col[k_];

int ans[k_];

int main() {
	scanf("%d", &k);
	for(int i = 0; i < k; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= k; i++) {
		scanf("%d", &b[i]);
	}
	for(int i = 0; i < k; i++) {
		f[i] = gen(rng);
	}

	uniform_int_distribution<lint> gen_n(lint(4e9), lint(1e10));
	lint n = gen_n(rng);

	for(int i = 0; i <= k; i++) {
		vector<int> cur = get_nth_and_k_more(n - b[i]);
		if(i == 0) {
			for(int j = 0; j < k; j++) {
				mat[j][k] = cur[j];
			}
		}else {
			for(int j = 0; j < k; j++) {
				mat[j][i-1] = cur[j];
			}
		}
	}

	for(int i = 0; i < k; i++) {
		insert(mat[i]);
	}

	for(int j = k-1; j >= 0; j-- ){
		lint cur = modinv(mat[j][j]) % mod;
		ans[j] = mat[j][k] * cur % mod;

		for(int i = j-1; i >= 0; i--) {
			lint coef = cur * mat[i][j] % mod;
			for(int jj = 0; jj <= k; jj++) {
				mat[i][jj] = (mat[i][jj] - mat[j][jj] * coef % mod + mod) % mod;
			}
		}
	}

	for(int i = 0; i < k; i++) {
		printf("%d ", ans[i]);
	}




	return 0;
}