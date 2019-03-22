#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
const int MAXT = 1050000;
using pi = pair<int, int>;

struct seg{
	int tree[MAXT], lazy[MAXT];
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
	void init() { memset(tree, 0, sizeof(tree)); }
}bit;

int n, k, a[MAXN], d1[MAXN], d2[MAXN];

struct event{
	int l, r, v;
};

vector<event> Event[MAXN];

vector<vector<event>> process(vector<pi> v){
	set<pi> s;
	vector<vector<event>> dap;
	for(auto &i : v){
		vector<event> tra;
		auto j = s.lower_bound(pi(i.first, -1));
		if(j != s.begin() && prev(j)->second >= i.second){
			// dominated
			dap.push_back(tra);
			continue; 
		}
		if(j == s.end()){
			// case 4
			int prv = (j == s.begin() ? 0 : (prev(j)->second));
			tra.push_back({i.first, n, i.second - prv});
			s.insert(i);
			dap.push_back(tra);
			continue;
		}
		if(j != s.end() && j->second > i.second){
			// not dominating
			int prv = (j == s.begin() ? 0 : (prev(j)->second));
			tra.push_back({i.first, j->first - 1, i.second - prv});
			s.insert(i);
			dap.push_back(tra);
			continue;
		}
		if(j != s.end() && j->second <= i.second){
			int sh = 0;
			if(j != s.begin()) sh = prev(j)->second;
			tra.push_back({i.first, j->first - 1, i.second - sh});
		}
		while(j != s.end() && j->second <= i.second){
			int ep = n;
			if(next(j) != s.end()) ep = next(j)->first - 1;
			if(i.second != j->second) tra.push_back({j->first, ep, i.second - j->second});
			j = s.erase(j);
		}
		s.insert(i);
		dap.push_back(tra);
	}
	return dap;
}

int main(){
	scanf("%d",&n);
	scanf("%d",&k);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++){
		d1[i] = bit.query(a[i] - 1) + 1;
		bit.add(a[i], d1[i]);
	}
	bit.init();
	for(int i=n; i; i--){
		d2[i] = bit.query(n + 1 - a[i] - 1) + 1;
		bit.add(n + 1 - a[i], d2[i]);
	}
	vector<pi> v, w;
	for(int i=1; i<=n; i++) v.emplace_back(a[i], d1[i]);
	for(int i=n; i>=1; i--) w.emplace_back(n + 1 - a[i], d2[i]);
	auto trans1 = process(v);
	auto trans2 = process(w);
	for(auto &i : trans2){
		for(auto &j : i){
			tie(j.l, j.r) = pi(n - j.r + 1, n - j.l + 1);
			j.l--;
			j.r--;
		}
	}
	for(int i=0; i<trans1.size(); i++){
		for(auto &j : trans1[i]){
			Event[i + 2].push_back(j);
		}
	}
	for(int i=0; i<trans2.size(); i++){
		for(auto &j : trans2[i]){
			Event[1].push_back(j);
		}
		for(auto &j : trans2[i]){
			Event[max(1, n - k + 1 - i)].push_back({j.l, j.r, -j.v});
		}
	}
	for(int i=1; i<=n-k+1; i++){
		for(auto &j : Event[i]){
			seg.add(j.l, j.r, 0, n + 1, 1, j.v);
		}
		printf("%d\n", seg.tree[1]);
	}
}
