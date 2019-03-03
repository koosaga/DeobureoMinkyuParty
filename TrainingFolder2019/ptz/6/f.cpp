#include <bits/stdc++.h>

using namespace std;

using lint = long long;


lint gcd (lint a, lint b) {
	return b ? gcd(b, a%b) : a;
}

struct frac {
	lint j, m;
	lint n;
	int offset;

	vector<int> b;
	int p;

	frac(lint j_ = 0, lint m_ = 1, lint n_ = 0) {
		offset = 0;
		n = j_ / m_ + n_;
		j = j_ % m_; m = m_;
		lint g = gcd(j, m);
		j /= g; m /= g;
		assert(j >= 0);
		assert(m > 0);

		vector<int> used(m * 2 + 1, -1);
		for(lint x = j; ; ){
			if(x >= m) {
				b.push_back(1);
				x -= m;
			}else {
				b.push_back(0);
			}
			if(used[x] >= 0) {
				p = used[x];
				break;
			}
			used[x] = b.size();
			x = x * 2;
		}
	}

	lint floor() {
		return n;
	}

	lint ceil() {
		return n + (j == 0 ? 0 : 1);
	}

	int jari (int x) {
		x -= offset;

		if(x >= 0) {
			return (n >> x) & 1;
		}

		x = -x;
		if(x < p) {
			return b[x];
		}

		x -= p;
		x %= int(b.size()) - p;
		x += p;
		return b[x];
	}
	
	int period() {
		return int(b.size()) - p;
	}

	inline bool is_integer() {
		return j == 0;
	}

	frac sosu() {
		return frac(j, m);
	}

	frac operator+ (const frac &f) const {
		return frac(j * f.m + m * f.j, m * f.m, n + f.n);
	}

	bool operator== (const frac &f) const {
		return n == f.n && j * f.m == m * f.j;
	}

	bool operator< (const frac &f) const {
		if(n != f.n) return n < f.n;
		return j * f.m < m * f.j;
	}
};

lint solve_int (lint a, lint b, lint c, lint d) {
	if(a > b || c > d) return 0;

	// [a, b] [c, d]
	lint ret = 0;
	for(int x = 60; x >= 0; x--) {
		lint low[2] = {ret, ret | (1ll << x)};
		lint high[2] = {ret | (((1ll << x) - 1)), ret | (((1ll << (x+1)) - 1))};

		int p = 0, q = 0;
		for(int bit = 0; bit < 2; bit++) {
			if(max(a, low[bit]) <= min(b, high[bit])) p |= 1<<bit;
			if(max(c, low[bit]) <= min(d, high[bit])) q |= 1<<bit;
		}

		if(((p & 1) && (q & 2)) || ((p & 2) && (q & 1))) {
			ret |= 1 << x;
		}
	}
	return ret;
}

frac ONE(1, 1);

const int BOUND = 60;
frac _pow2[BOUND * 2 + 1];
frac *pow2 = _pow2 + BOUND;

frac solve_sosu (frac a, frac b, frac c, frac d, int offset) {
	frac ret = 0;

	vector<int> digits;

	int jugi = 1000;
	for(int i = offset; i >= offset-jugi; i--) {
		int ai = a.jari(i), bi = b.jari(i), ci = c.jari(i), di = d.jari(i);

		if(ai == 0 && bi == 1) {
			if(ci == 0 && di == 1) {
				return ret + pow2[i] + max({
					solve_sosu(a, ONE, 0, d, i+1),
					solve_sosu(0, b, c, ONE, i+1)
				});
			}else {
				assert(ci == di);
				if(ci != 0) { // -> bi = 0, 11111111
					if(a == 0) return ret + pow2[i+1];
					return ret + pow2[i] + solve_sosu(a, ONE, c, d, i+1);
				}else { // -> ai = 1
					if(b == 1) return ret + pow2[i+1];
					return ret + pow2[i] + solve_sosu(0, b, c, d, i+1);
				}
			}
		}
		else {
			if(ci == 0 && di == 1) {
				return solve_sosu(c, d, a, b, offset); // TODO time check
			}else {
				assert(ci == di);
				if((ai ^ ci) == 1)
					ret = ret + pow2[i];

				// TODO infinite loop possible when everything is same
				digits.push_back(ai ^ ci);

			}
		}
	}

	reverse(digits.begin(), digits.end());

	for(int i = digits.size(); --i >= 0; ) {
		bool good = true;
		for(int j = i; j < i + i; j++) {
			if(digits[j-i] != digits[i]) good = false;
		}

		if(good) {
			reverse(digits.begin(), digits.end());

			break;
		}
	}

	return ret;
}


int main() {
	ONE.b.clear();
	ONE.b.resize(1, 1);
	ONE.p = 0;

	for(int i = 0; i <= BOUND; i++) {
		pow2[-i] = frac(1, 1ll<<i);
		pow2[i] = frac(1ll<<i, i);
	}

	int t;  cin>>t;
	while(t--) {
		lint aj,am,bj,bm,cj,cm,dj,dm;
		cin>>aj>>am>>bj>>bm>>cj>>cm>>dj>>dm;

		frac a(aj,am);
		frac b(bj,bm);
		frac c(cj,cm);
		frac d(dj,dm);

		frac ans = 0;

		auto upd = [&ans](frac cur) {
			if(ans < cur) ans = cur;
		};

		upd(solve_int(a.ceil(), b.floor(), c.ceil(), d.floor()));

		for(int rep = 0; rep < 2; rep++) {
			if(!a.is_integer()) {
				upd(solve_int(a.floor(), a.floor(), c.ceil(), d.floor()) + 1); // 0.1111111 = 1
			}
			if(!b.is_integer()) {
				upd(b.sosu() + solve_int(b.floor(), b.floor(), c.ceil(), d.floor()));
			}
			swap(a, c); swap(b, d);
		}

		{
			vector<tuple<frac, frac, lint>> p, q;

			if(a.n < b.n) {
				p.emplace_back(a.sosu(), ONE, a.n);
				p.emplace_back(0, b.sosu(), b.n);
			}else {
				p.emplace_back(a.sosu(), b.sosu(), a.n);
			}

			if(c.n < d.n) {
				q.emplace_back(c.sosu(), ONE, c.n);
				q.emplace_back(0, d.sosu(), d.n);
			}else {
				q.emplace_back(c.sosu(), d.sosu(), c.n);
			}

			for(auto it1 : p) {
				for(auto it2 : q) {
					upd(solve_sosu(get<0>(it1), get<1>(it1), get<0>(it2), get<1>(it2), -1) + frac(get<2>(it1) ^ get<2>(it2), 1));
				}
			}
		}

		printf("%lld %lld\n", ans.n * ans.m + ans.j, ans.m);
	}

	return 0;
}