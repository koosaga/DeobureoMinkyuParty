#include <bits/stdc++.h>

using namespace std;

const int N_ = int(1.1e5);

using lint = long long;
using llf = double;

struct frac {
	// warning: m > 0
	lint j, m;
	frac(lint j_ = 0, lint m_ = 1) { 
		if(m_ < 0) j = -j_, m = -m_;
		else j = j_, m = m_;
	}
	int comp(const frac &f) const {
		__int128 v = (__int128)j * f.m - (__int128)m * f.j;
		if(v > 0) return +1;
		if(v < 0) return -1;
		return 0;
	}
	bool operator< (const frac &f) const {
		return comp(f) < 0;
	}
	bool operator> (const frac &f) const {
		return comp(f) > 0;
	}
	bool operator<= (const frac &f) const {
		return comp(f) <= 0;
	}
	bool operator>= (const frac &f) const {
		return comp(f) >= 0;
	}
	llf get_real_diff(const frac &f) const {
		__int128 v = (__int128)j * f.m - (__int128)m * f.j;
		return (llf)(v / f.m / m);
	}
	llf to_real() const {
		return (llf)j / m;
	}
};

int N, L, R;
int A[N_], X[N_];

const int LEAF = 1<<18;

struct fun {
	int a, x;
	int i;
	int t;
	fun(int a_ = 0, int x_ = 0, int i_ = 0, int t_ = 0): a(a_), x(x_), i(i_), t(t_) { }
	frac calc(int m) { 
		if(t == 0) return frac(a * m + R * x, m);
		else return frac(R * (R - x) + a * (R - m), R - m);
	}
	llf calc_real(llf m) {
		if(t == 0) return a + R * x / m;
		else return R * (R - x) / (R - m) + a;
	}
	frac intercept(fun f) {
		assert(t == f.t);
		if(t == 0) {
			return frac(R * (x - f.x), f.a - a);
		}else {
			return frac(R * (f.a - a) - R * (x - f.x), f.a - a);
		}
	}
	llf intercept_2(fun f) {
		assert(t != f.t);
		if(t == 1) return f.intercept_2(*this);

		llf aa = a - f.a;
		llf bb = R * x - (a - f.a) * R + R * (R - f.x);
		llf cc = -R * R * (x);

		return (-bb + sqrt(bb * bb - 4 * aa * cc)) / 2 / aa;
	}
};

struct lichao {
	fun tree[LEAF+LEAF];
	vector<fun> leaves[LEAF];

	void upd (int nd, int nl, int nr, int l, int r, fun f) {
		if(nl == l && nr == r) {
			if(tree[nd].i == 0) {
				tree[nd] = f;
				return;
			}

			if(nr - nl == 1) {
				leaves[nl].push_back(f);
				return;
			}

			frac tl = tree[nd].calc(X[nl]);
			frac tr = tree[nd].calc(X[nr]);
			frac fl = f.calc(X[nl]);
			frac fr = f.calc(X[nr]);

			int lc = tl.comp(fl);
			int rc = tr.comp(fr);
			if(lc * rc < 0) {
			}else if(lc > 0 || rc > 0) {
				return;
			}else if(lc < 0 || rc < 0) {
				tree[nd] = f;
				return;
			}else {
				assert(lc == 0 && rc == 0);
				return;
			}
		}
		{
			int nm = (nl + nr) / 2;
			if(l < nm) upd(nd * 2, nl, nm, l, min(nm, r), f);
			if(nm < r) upd(nd * 2 + 1, nm, nr, max(nm, l), r, f);
		}
	}
} seg[2];

vector<fun> par[2];
int used[2][N_];

struct event {
	frac t;
	fun f;

	bool operator< (const event &e) const {
		return t < e.t;
	}
};

llf ans[N_];

void go (int nd, int nl, int nr) {
	for(int s = 0; s < 2; s++) {
		fun &f = seg[s].tree[nd];
		if(++used[s][f.i] == 1) par[s].push_back(f);
	}


	if(nr - nl == 1) {
		vector<event> events;

		for(int s = 0; s < 2; s++) {
			vector<fun> &cur = seg[s].leaves[nl];
			for(fun &f : par[s]) cur.push_back(f);

			// TODO check here
			sort(cur.begin(), cur.end(), [&](const fun &f1, const fun &f2) {
				return f1.x < f2.x;
			});

			vector<fun> stk; int sz = 0;
			// TODO check here
			for(fun &f : cur) {
				while(sz >= 2 && stk[sz-2].intercept(f).comp(stk[sz-2].intercept(stk[sz-1])) * (s == 0 ? -1 : +1) >= 0) {
					stk.pop_back();
					sz -= 1;
				}
				stk.push_back(f);
				sz += 1;
			}

			if(s == 1) {
				reverse(cur.begin(), cur.end());
			}

			bool first = true;
			for(int i = 0; i+1 < stk.size(); i++) {
				event e = {stk[i].intercept(stk[i+1]), stk[i+1]};
				if(e.t >= frac(X[nl], 1)) {
					if(first) events.push_back({frac(X[nl],1), stk[i]});
					events.push_back(e);
				}
			}
		}

		events.push_back({frac(X[nr],1), fun()});
		sort(events.begin(), events.end());

		for(int i = 1; i < events.size(); i++) {
			event e0 = events[i-1];
			event e1 = events[i];
			if(e0.t < frac(0,1) || e1.t > frac(R,1)) continue;

			llf e0l = e0.f.calc_real(e0.t.to_real());
			llf e0r = e0.f.calc_real(e1.t.to_real());
			llf e1l = e1.f.calc_real(e0.t.to_real());
			llf e1r = e1.f.calc_real(e1.t.to_real());
			int cl = (e0l < e1l) ? -1 : (e0l > e1l) ? 1 : 0;
			int cr = (e0r < e1r) ? -1 : (e0r > e1r) ? 1 : 0;

			if(cl >= 0 && cr >= 0) {
				ans[e0.f.i] += e1.t.get_real_diff(e0.t);
			}else if(cl <= 0 && cr <= 0) {
				ans[e1.f.i] += e1.t.get_real_diff(e0.t);
			}else {
				assert(e0.f.t != e1.f.t);
				llf x = e0.f.intercept_2(e1.f);
				if(cl >= 0) {
					ans[e0.f.i] += x - e0.f.t.to_real();
				}
			}
		}
	}else {
		int nm = (nl + nr) / 2;
		go(nd * 2, nl, nm);
		go(nd * 2 + 1, nm, nr);
	}

	for(int s = 0; s < 2; s++) {
		fun &f = seg[s].tree[nd];
		if(used[s][f.i]-- == 1) par[s].pop_back();
	}
}

int main() {
	scanf("%d%d%d", &N, &L, &R);
	R -= L;
	X[0] = 0;
	X[N+1] = R;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &X[i]);
		X[i] -= L;
	}
	for(int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}

	for(int i = 1; i <= N; i++) {
		seg[0].upd(1, 0, N+1, i, N+1, fun(A[i], X[i], i, 0));
		seg[1].upd(1, 0, N+1, 0,   i, fun(A[i], X[i], i, 1));
	}

	used[0][0] = used[1][0] = 1;
	go(1, 0, N+1);

	for(int i = 1; i <= N; i++) {
		printf("%.20lf\n", ans[i] / R);
	}
	return 0;
}