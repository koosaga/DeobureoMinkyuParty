#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, m, q;
lint ret[MAXN];

struct query{ int s, e, idx; };
vector<query> qr[MAXN];

set<pi> s;

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
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<pi> process(int l){
	vector<pi> v;
	for(auto &i : s) v.push_back(i);
	sort(qr[l].begin(), qr[l].end(), [&](const query &x, const query &y){
		return x.s < y.s;
	});
	for(int i=1; i<v.size(); i++) bit.add(i, 1ll * (v[i].first - v[i-1].first) * (1 - v[i].second));
	int ptr = 0;
	for(auto &i : qr[l]){
		while(ptr < v.size() && v[ptr].first < i.s){
			ptr++;
		}
		if(ptr == v.size() || v[ptr].second > i.e) continue;
		ret[i.idx] += 1ll * (v[ptr].first - i.s + 1) * (i.e - v[ptr].second + 1);
		int s = ptr, e = v.size() - 1;
		while(s != e){
			int m = (s+e+1)/2;
			if(v[m].second <= i.e) s = m;
			else e = m - 1;
		}
		ret[i.idx] += 1ll * i.e * (v[s].first - v[ptr].first);
		ret[i.idx] += bit.query(s) - bit.query(ptr);
	}
	for(int i=1; i<v.size(); i++) bit.flush(i);
	return v;
}

void Insert(int v){
	auto l = s.upper_bound(pi(v+1, -1));
	while(l != s.begin() && prev(l)->second >= v){
		s.erase(prev(l));
	}
	s.insert(pi(v, v));
}

vector<int> v[MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		v[x].push_back(i);
	}
	for(int i=0; i<q; i++){
		int l, r, k; scanf("%d %d %d",&l,&r,&k);
		qr[k].push_back({l, r, i});
	}
	for(int i=1; i<=m; i++){
		for(auto &j : v[i]) Insert(j);
		vector<pi> v = process(i);
		vector<pi> w;
		int ptr = 0;
		for(auto &i : v){
			while(ptr < v.size() && v[ptr].first <= i.second) ptr++;
			if(ptr == v.size()) break;
			w.emplace_back(i.first, v[ptr].second);
		}
		reverse(w.begin(), w.end());
		s.clear();
		int prv = -420;
		for(auto &i : w){
			if(prv != i.second){
				prv = i.second;
				s.insert(i);
			}
		}
	}
	for(int i=0; i<q; i++) printf("%lld\n", ret[i]);
}

