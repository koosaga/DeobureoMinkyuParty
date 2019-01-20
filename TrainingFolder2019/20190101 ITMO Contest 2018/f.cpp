#include<bits/stdc++.h>
#define sz(v) ((int)((v).size()))
using namespace std;
const int MAXN = 2050;
using lint = long long;
int n, m, mod;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

struct BBLA{
	vector<int> berlekamp_massey(vector<int> x){
		vector<int> ls, cur;
		int lf, ld;
		for(int i=0; i<x.size(); i++){
			lint t = 0;
			for(int j=0; j<cur.size(); j++){
				t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
			}
			if((t - x[i]) % mod == 0) continue;
			if(cur.empty()){
				cur.resize(i + 1);
				lf = i;
				ld = (t - x[i]) % mod;
				continue;
			}
			lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
			vector<int> c(i - lf - 1);
			c.push_back(k);
			for(auto &j : ls) c.push_back(-j * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j=0; j<cur.size(); j++) c[j] = (c[j] + cur[j]) % mod;
			if(i - lf + sz(ls) >= sz(cur)){
				tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
			}
			cur = c;
		}
		for(auto &i : cur) i = (i % mod + mod) % mod;
		return cur;
	}
	int get_nth(vector<int> rec, vector<int> dp, lint n){
		int m = rec.size();
		vector<int> s(m), t(m);
		s[0] = 1;
		if(m != 1) t[1] = 1;
		else t[0] = rec[0];
		auto mul = [&rec](vector<int> v, vector<int> w){
			int m = v.size();
			vector<int> t(2 * m);
			for(int j=0; j<m; j++){
				for(int k=0; k<m; k++){
					t[j + k] += 1ll * v[j] * w[k] % mod;
					if(t[j + k] >= mod) t[j + k] -= mod;
				}
			}
			for(int j=2*m-1; j>=m; j--){
				for(int k=1; k<=m; k++){
					t[j-k] += 1ll * t[j] * rec[k-1] % mod;
					if(t[j - k] >= mod) t[j-k] -= mod;
				}
			}
			t.resize(m);
			return t;
		};
		while(n){
			if(n & 1) s = mul(s, t);
			t = mul(t, t);
			n >>= 1;
		}
		lint ret = 0;
		for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
		return ret % mod;
	}
	int guess_nth_term(vector<int> x, lint n){
		if(n < x.size()) return x[n];
		vector<int> v = berlekamp_massey(x);
		if(v.empty()) return 0;
		return get_nth(v, x, n);
	}
}BBLA;

vector<int> cnd;
vector<pair<int, vector<int> > > state;

void generate(int msk, int n, vector<int> vect){
	if(n == 0){
		state.emplace_back(msk, vect);
		return;
	}
	int maxp = 0;
	for(int i=0; i<vect.size(); i++) maxp = max(maxp, vect[i] + 1);
	for(int j=0; j<=maxp; j++){
		vect.push_back(j);
		generate(msk, n - 1, vect);
		vect.pop_back();
	}
}

void bktk(int r, int msk){
	if(r == n){
		cnd.push_back(msk);
		int vsize = 0;
		for(int j=0; j<n; j++){
			if((msk >> j) & 1) continue;
			int e = j;
			while(e < n && ((msk >> e) & 1) == 0) e++;
			j = e;
			vsize++;
		}
		vector<int> vect;
		generate(msk, vsize, vect); 
		return;
	}
	if(r == 0 || (msk >> (r-1)) % 2 == 0){
		bktk(r + 1, msk | (1<<r));
	}
	bktk(r + 1, msk);
}

struct disj{
	int pa[20];
	void init(){
		iota(pa, pa + 20, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void uni(int p, int q){
		p = find(p); q = find(q);
		if(p > q) swap(p, q);
		pa[q] = p;
	}
}disj;

vector<int> RECONCILE(int prv, int cur, vector<int> par){
	disj.init();
	int grid[2][11] = {};
	int cnum[2][11] = {};
	for(int i=0; i<n; i++) grid[0][i] = (prv >> i) & 1;
	for(int i=0; i<n; i++) grid[1][i] = (cur >> i) & 1;
	int cmpcnt = 0;
	for(int i=0; i<n; i++){
		if(grid[0][i]) continue;
		int e = i;
		while(e < n && grid[0][e] == 0) e++;
		for(int j=i; j<e; j++){
			cnum[0][j] = par[cmpcnt];
		}
		cmpcnt++;
		i = e;
	}
	cmpcnt = par.size();
	for(int i=0; i<n; i++){
		if(grid[1][i]) continue;
		int e = i;
		while(e < n && grid[1][e] == 0) e++;
		for(int j=i; j<e; j++){
			cnum[1][j] = cmpcnt;
		}
		cmpcnt++;
		i = e;
	}
	for(int i=0; i<n; i++){
		if(grid[0][i] || grid[1][i]) continue;
		disj.uni(cnum[0][i], cnum[1][i]);
	}
	set<int> adv;
	for(int i=0; i<n; i++){
		if(!grid[0][i]) cnum[0][i] = disj.find(cnum[0][i]);
		if(!grid[1][i]){
			cnum[1][i] = disj.find(cnum[1][i]);
			adv.insert(cnum[1][i]);
		}
	}
	for(int i=0; i<n; i++){
		if(!grid[0][i] && adv.find(cnum[0][i]) == adv.end()){
			vector<int> v = {-1};
			return v;
		}
	}
	vector<int> cur_number;
	vector<int> actual_idx;
	for(int i=0; i<n; i++){
		if(grid[1][i]) continue;
		int e = i;
		while(e < n && grid[1][e] == 0) e++;
		cur_number.push_back(cnum[1][i]);
		for(int j=0; j<cur_number.size(); j++){
			if(cnum[1][i] == cur_number[j]){
				actual_idx.push_back(j);
				break;
			}
		}
		i = e;
	}
	vector<int> crd = actual_idx;
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	for(auto &i : actual_idx){
		i = lower_bound(crd.begin(), crd.end(), i) - crd.begin();
	}
	return actual_idx;
}

int dp[MAXN][4000];
vector<int> gph[4000];

void make_graph(){
	for(int i=0; i<state.size(); i++){
		int msk = state[i].first;
		vector<int> cmps = state[i].second;
		for(auto &j : cnd){
			if(msk & j) continue;
			auto nxt = RECONCILE(msk, j, cmps);
			if(nxt[0] == -1) continue;
			auto k = lower_bound(state.begin(), state.end(), make_pair(j, nxt)) - state.begin();
			assert(k != state.size() && state[k] == make_pair(j, nxt));
			gph[i].push_back(k);
		}
	}
}

int dfs(int n, int m){
	if(~dp[n][m]) return dp[n][m];
	if(n == 0){
		int msk = state[m].first;
		vector<int> cmps = state[m].second;
		return count(cmps.begin(), cmps.end(), 0) == cmps.size();
	}
	int ret = 0;
	for(auto &i : gph[m]){
		ret += dfs(n - 1, i);
		ret %= mod;
	}
	return dp[n][m] = ret;
}

int CONSTR(int msk){
	vector<int> v;
	for(int i=0; i<n; i++) v.push_back((msk >> i) & 1);
	vector<int> dap;
	for(int i=0; i<n; i++){
		if(v[i]) continue;
		int e = i;
		while(e < n && !v[e]) e++;
		int d = dap.size();
		dap.push_back(d);
		i = e;
	}
	return lower_bound(state.begin(), state.end(), make_pair(msk, dap)) - state.begin();
}

int dap[MAXN * 2];

int main(){
	int rm;
	cin >> n >> rm >> mod;
	bktk(0, 0);
	sort(state.begin(), state.end());
	make_graph();
	memset(dp, -1, sizeof(dp));
	dap[0] = 1;
	for(m = 1; m <= 2000; m++){
		int ret = 0;
		for(auto &i : cnd){
			ret += dfs(m - 1, CONSTR(i));
			ret %= mod;
		}
		dap[m] = ret;
	}
	vector<int> v(dap, dap + 2001);
	cout << BBLA.guess_nth_term(v, rm) << endl;
}
