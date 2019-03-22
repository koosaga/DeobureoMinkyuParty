#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 530000;
using pi = pair<int, int>;

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void init(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[min(i + p, n)]]++;
			}
			for(int i=1; i<=n||i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i + p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p <<= 1;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h = max(h - 1, 0);
		}
	}
}sfxa;

char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[MAXN], ret[MAXN];
int aux[2 * MAXN];

void solve(int n, char *str){
	for(int i=0; i<n; i++){
		aux[2*i] = str[i];
		if(i != n - 1) aux[2*i+1] = -1;
	}
	int p = 0, c = 0;
	for(int i=0; i<2*n-1; i++){
		int cur = 0;
		if(i <= p) cur = min(ret[2 * c - i], p - i);
		while(i - cur - 1 >= 0 && i + cur + 1 < 2 * n - 1 && aux[i-cur-1] == aux[i+cur+1]){
			cur++;
		}
		ret[i] = cur;
		if(i + ret[i] > p){
			p = i + ret[i];
			c = i;
		}
	}
}

struct lcpseg{
	int tree[MAXT];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, 1e9);
		for(int i=1; i<n; i++){
			tree[i + lim] = a[i];
		}
		for(int i=lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}LCPQ;

vector<pi> tree[MAXT];
int lim;
void init(int n, int *a){
	for(lim = 1; lim <= n; lim <<= 1);
	for(int i=0; i<n; i++){
		for(int j=i+lim; j; j>>=1) tree[j].emplace_back(a[i], i);
	}
	for(int i=0; i<MAXT; i++) sort(tree[i].begin(), tree[i].end());
}

int getlcp(int s, int e){
	s = rev[s]; e = rev[e];
	if(s > e) swap(s, e);
	return LCPQ.query(s + 1, e);
}

pi maxlcp(int p, int s, int e){
	if(s > e) return pi(0, 1e9);
	pi ret(0, 1e9);
	s += lim;
	e += lim;
	pi retx(1e9, 1e9);
	pi rety(-1e9, 1e9);
	auto doQ = [&](int x){
		if(tree[x].empty()) return;
		auto l = lower_bound(tree[x].begin(), tree[x].end(), pi(rev[p], -1));
		if(l != tree[x].end()) retx = min(retx, *l);
		if(l != tree[x].begin()) rety = max(rety, *prev(l));
	};
	while(s < e){
		if(s%2 == 1) doQ(s++);
		if(e%2 == 0) doQ(e--);
		s >>= 1; e >>= 1;
	}
	if(s == e) doQ(s);
	if(retx.first < 1e8) ret = max(ret, pi(getlcp(p, sfx[retx.first]), sfx[retx.first]));
	if(rety.first > -1e8) ret = max(ret, pi(getlcp(p, sfx[rety.first]), sfx[rety.first]));
	return ret;
}

struct fortheDap{
	int dap, s1, e1, s2, e2;
	bool operator<(const fortheDap &d)const{
		return dap < d.dap;
	}
};

int n;

int main(){
	scanf("%s", str);
	n = strlen(str);
	vector<pi> v;
	solve(n, str);
	for(int i=0; i<n; i++){
		str[2*n-i] = str[i];
	}
	str[n] = '#';
	sfxa.init(2 * n + 1, str, sfx, rev, lcp);
	for(int i=0; i<2*n-1; i++){
		if(i % 2 == 0){
			int s = i/2 - ret[i]/2;
			int e = i/2 + ret[i]/2;
			v.emplace_back(s, e);
		}
		else{
			int s = i/2 + 1 - (ret[i]+1)/2;
			int e = i/2 + (ret[i]+1)/2;
			if(s <= e) v.emplace_back(s, e);
		}
	}
	fortheDap dap = {-1, -1, -1, -1, -1};
	LCPQ.init(2 * n + 1, lcp);
	init(2 * n + 1, rev);
	for(auto &i : v){
		int s = i.first;
		int e = i.second;
		dap = max(dap, (fortheDap){e-s+1, 0, -1, s, e});
		if(e + 1 < n){
			auto ans = maxlcp(e + 1, 2 * n - s + 1, 2 * n);
			ans.second = 2 * n - ans.second;
			int val = e - s + 1 + 2 * ans.first;
			dap = max(dap, (fortheDap){val, ans.second - ans.first + 1, ans.second, s, e + ans.first});
		}
		if(s - 1 >= 0){
			auto ans = maxlcp(2 * n - s + 1, e + 1, n - 1);
			int val = e - s + 1 + 2 * ans.first;
			dap = max(dap, (fortheDap){val, s - ans.first, e, ans.second, ans.second + ans.first - 1});
		}
	}
	cout << dap.dap << endl;
	auto ans = dap;
	if(ans.s1 > ans.e1) puts("-1 -1");
	else printf("%d %d\n", ans.s1 + 1, ans.e1 + 1);
	if(ans.s2 > ans.e2) puts("-1 -1");
	else printf("%d %d\n", ans.s2 + 1, ans.e2 + 1);
}
