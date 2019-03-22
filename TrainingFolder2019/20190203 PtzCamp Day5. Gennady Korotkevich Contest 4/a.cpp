#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXT = 66000;
const int mod = 998244353;
using lint = long long;
using pi = pair<int, int>;

inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
	unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
	asm(
		"divl %4; \n\t"
		: "=a" (d), "=d" (m)
		: "d" (xh), "a" (xl), "r" (y)
	);
#else
	__asm {
		mov edx, dword ptr[xh];
		mov eax, dword ptr[xl];
		div dword ptr[y];
		mov dword ptr[d], eax;
		mov dword ptr[m], edx;
	};
#endif
	out_d = d; out_m = m;
}

//x < 2^32 * MOD !
inline unsigned Mod(unsigned long long x){
	unsigned y = mod;
	unsigned dummy, r;
	fasterLLDivMod(x, y, dummy, r);
	return r;
}



int n, k;
lint fact[MAXN], invf[MAXN];
vector<int> gph[MAXN];
vector<pi> tdfn;
bool vis[MAXN];

lint bino(int x, int y){ return fact[x] * (invf[y] * invf[x - y] % mod) % mod; }

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

struct bit{
	lint tree[MAXN];
	void flush(int x){
		while(x < MAXN){
			tree[x] = 0;
			x += x & -x;
		}
	}
	void add(int x, lint v){
		while(x < MAXN){
			tree[x] += v;
			tree[x] %= mod;
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret % mod;
	}
}bit1, bit2;

namespace centroid{
	vector<int> dfn;
	int sz[MAXN], msz[MAXN];
	void dfs(int x, int p){
		dfn.push_back(x);
		sz[x] = 1;
		msz[x] = 0;
		for(auto &i : gph[x]){
			if(i != p && !vis[i]){
				dfs(i, x);
				sz[x] += sz[i];
				msz[x] = max(msz[x], sz[i]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, -1);
		for(auto &i : dfn){
			int w = max((int)dfn.size() - sz[i], msz[i]);
			ret = min(ret, pi(w, i));
		}
		return ret.second;
	}
}

namespace FFT{
	typedef lint base;
	void fft(vector<base> &a, bool inv){
		int n = a.size(), j = 0;
		vector<base> roots(n/2);
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		int ang = ipow(3, (mod - 1) / n);
		if(inv) ang = ipow(ang, mod - 2);
		for(int i=0; i<n/2; i++){
			roots[i] = (i ? (1ll * roots[i-1] * ang % mod) : 1);
		}
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					base u = a[j+k], v = Mod(1ll * a[j+k+i/2] * roots[step * k]);
					a[j+k] = (u+v);
					if(a[j+k] >= mod) a[j+k] -= mod;
					a[j+k+i/2] = (u-v+mod);
					if(a[j+k+i/2] >= mod) a[j+k+i/2] -= mod;
				}
			}
		}
		lint invf = ipow(n, mod - 2);
		if(inv) for(int i=0; i<n; i++) a[i] = invf * a[i] % mod;
	}

	vector<int> multiply(const vector<int> &v, const vector<int> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 2; while(n < v.size() + w.size()) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] = 1ll * fv[i] * fw[i] % mod;
		fft(fv, 1);
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = fv[i];
		return ret;
	}

	vector<int> get_inv(int n, const vector<int> &p){
		vector<int> q = {(int)ipow(p[0], mod - 2)};
		for(int i=2; i<=n; i<<=1){
			vector<int> res;
			vector<base> fq(q.begin(), q.end()); fq.resize(2*i);
			vector<base> fp(p.begin(), p.begin() + i); fp.resize(2*i);
			fft(fq, 0); fft(fp, 0);
			for(int j=0; j<2*i; j++){
				fp[j] = Mod(1ll * fp[j] * Mod(1ll * fq[j] * fq[j]));
			}
			fft(fp, 1);
			res.resize(i);
			for(int j=0; j<i; j++){
				res[j] = mod - fp[j];
				if(j < i/2){
					res[j] += q[j];
					if(res[j] >= mod) res[j] -= mod;
					res[j] += q[j];
					if(res[j] >= mod) res[j] -= mod;
				}
			}
			q = res;
		}
		return q;
	}
	vector<int> poly_divide(const vector<int> &a, const vector<int> &b){
		assert(b.back() != 0); // please trim leading zero
		int n = a.size(), m = b.size();
		if(n < m) return {};
		int k = 2; while(k < n-m+1) k <<= 1;
		vector<int> rb(k), ra(k);
		for(int i=0; i<m && i<k; ++i) rb[i] = b[m-i-1];
		for(int i=0; i<n && i<k; ++i) ra[i] = a[n-i-1];
		vector<int> rbi = get_inv(k, rb);
		vector<int> res = multiply(rbi, ra);
		res.resize(n - m + 1);
		reverse(res.begin(), res.end());
		return res;
	}
	
	vector<int> get_modulo(vector<int> a, const vector<int> &b){
		while(a.size() && a.back() == 0) a.pop_back();
		if(a.size() < b.size()) return a;
		auto div = multiply(poly_divide(a, b), b);
		assert(a.size() <= div.size());
		for(int i=0; i<a.size(); i++){
			a[i] += mod - div[i];
			if(a[i] >= mod) a[i] -= mod;
		}
		return a;
	}

	vector<int> seg[MAXT];

	void init(int s, int e, int p){
		if(s == e){
			seg[p] = vector<int>{mod - s, 1};
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m + 1, e, 2*p+1);
		seg[p] = multiply(seg[2*p], seg[2*p+1]);
		seg[p].resize(e - s + 2);
	}

	void dfs(int s, int e, int p, vector<int> poly, vector<int> &ans){
		poly = get_modulo(poly, seg[p]);
		if(s == e){
			if(poly.empty()) ans[s] = 0;
			else ans[s] = poly[0];
			return;
		}
		int m = (s + e) / 2;
		dfs(s, m, 2*p, poly, ans);
		dfs(m + 1, e, 2*p+1, poly, ans);
	}

	vector<int> interpolate(vector<int> p, int n){
		init(0, n - 1, 1);
		vector<int> v(n);
		dfs(0, n - 1, 1, p, v);
		return v;
	}

}

int sz[MAXN], par[MAXN];

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
			par[i] = x;
			sz[x] += sz[i];
		}
	}
}

int getsz(int x, int p){
	if(par[x] == p) return sz[x];
	return n - sz[p];
}

lint func[MAXN];

void dfs2(int x, int p){
	int mysz = 1; 
	func[x] = 0;
	for(auto &i : gph[x]){
		if(i != p){
			if(!vis[i]) dfs2(i, x);
			int szi = getsz(i, x);
			func[x] += mod - ipow(szi, k / 2);
			mysz += szi;
		}
	}
	func[x] += ipow(mysz, k / 2);
	func[x] %= mod;
}

lint dfs_sum(int x, int p, int d){
	d = min(x, d);
	tdfn.emplace_back(d, x);
	lint ret = d * func[x];
	for(auto &i : gph[x]){
		if(!vis[i] && i != p){
			ret += dfs_sum(i, x, d);
		}
	}
	return ret % mod;
}

int coeff[MAXN];

vector<int> pwr_nx(int m){
	vector<int> v(m + 1);
	int pwr = 1;
	for(int i=m; i>=0; i--){
		if(i % 2 == 0) v[i] = bino(m, i) * pwr % mod;
		else v[i] = mod - bino(m, i) * pwr % mod;
		pwr = (1ll * pwr * n) % mod;
	}
	return v;
}

vector<int> generate_range(int l, int r){
	if(l == r){
		vector<int> v = {coeff[l]};
		return v;
	}
	int m = (l + r) / 2;
	auto lp = generate_range(l, m);
	auto rp = generate_range(m + 1, r); 
	auto v = FFT::multiply(pwr_nx(r - m), lp);
	for(int i=0; i<r - m; i++){
		v[m+1-l+i] += rp[i];
		v[m+1-l+i] %= mod;
	}
	v.resize(r - l + 1);
	return v;
}

lint interp[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	for(int i=1; i<n; i++){
		int x, y;
		x = i, y = i + 1;
		scanf("%d %d",&x,&y);
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	dfs(1, 0);
	lint dap = 0;
	for(int i=k/2+1; i<=k; i++){
		coeff[i] = mod - bino(k, i);
	}
	vector<int> poly;
	{
		auto aux = generate_range(k / 2 + 1, k);
		poly.resize(k / 2 + 1);
		for(auto &i : aux) poly.push_back(i);
		poly.resize(k + 1);
	}
	for(int i=1; i<=n; i++){
		vector<int> v;
		for(auto &j : gph[i]) v.push_back(getsz(j, i));
		dap += i * ipow(n, k) % mod;
		dap %= mod;
		for(int j=0; j<v.size(); j++){
			interp[v[j]] += i;
			interp[v[j]] %= mod;
		}
	}
	auto ans = FFT::interpolate(poly, n);
	for(int i=1; i<n; i++){
		dap += interp[i] * ans[i] % mod;
		dap %= mod;
	}
	if(k % 2 == 0){
		for(int i=1; i<=n; i++){
			vector<int> v;
			for(auto &j : gph[i]) v.push_back(getsz(j, i));
			lint ret = 0, sum = 0;
			for(int j=0; j<v.size(); j++){
				ret += mod - (ipow(v[j], k / 2) * ipow(n - v[j], k / 2) % mod);
				ret += ipow(v[j], k / 2) * sum % mod;
				sum += ipow(v[j], k / 2);
				sum %= mod;
				ret %= mod;
			}
			ret %= mod;
			ret *= i * bino(k, k/2) % mod;
			ret %= mod;
			dap = (dap + ret) % mod;
		}
		queue<int> que;
		que.push(1);
		while(!que.empty()){
			int x = que.front();
			que.pop();
			x = centroid::get_center(x); 
			vis[x] = 1;
			vector<int> v, fl;
			for(auto &i : gph[x]) v.push_back(getsz(i, x));
			dfs2(x, -1);
			lint ret = 0;
			lint poss_all = 0;
			for(auto &i : v) poss_all += mod - ipow(i, k / 2);
			for(int i=0; i<gph[x].size(); i++){
				if(!vis[gph[x][i]]){
					lint poss = poss_all + ipow(v[i], k / 2) + ipow(n - v[i], k / 2) + mod;
					poss %= mod;
					ret += 1ll * poss * dfs_sum(gph[x][i], x, x) % mod;
					ret %= mod;
					for(auto &j : tdfn){
						ret += bit1.query(j.first) * func[j.second] % mod;
						ret += (bit2.query(MAXN - 1) - bit2.query(j.first) + mod) * (j.first * func[j.second] % mod) % mod;
						ret %= mod;
					}
					for(auto &i : tdfn){
						bit1.add(i.first, i.first * func[i.second] % mod);
						bit2.add(i.first, func[i.second]);
						fl.push_back(i.first);
					}
					tdfn.clear();
				}
			}
			for(auto &i : fl){
				bit1.flush(i);
				bit2.flush(i);
			}
			ret %= mod;
			dap += bino(k, k / 2) * ret % mod;
			dap %= mod;
			for(auto &i : gph[x]){
				if(!vis[i]){
					que.push(i);
				}
			}
		}
	}
	dap %= mod;
	cout << dap << endl;
}
/*
9 6
1 2
2 4
2 3
4 5
1 6
6 7
6 8
7 9
1361895
*/
/*
9 2
1 2
2 4
2 3
4 5
1 6
6 7
6 8
7 9
195
*/
/*
5 10
2 4
5 3
1 3
3 2
25330269
*/
/*
5 2
2 4
5 3
1 3
3 2
49
*/
/*
5 3
2 4
5 3
1 3
3 2
1413
*/

