#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000050;
const int MAXT = 2100000;

struct seg{
	lint tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2* lim, 1e18);
	}
	void upd(int x, lint v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	lint query(int s, int e){
		s += lim; 
		e += lim;
		lint ret = 1e18;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

int n, a[MAXN];
int nxt[MAXN];
int vis[MAXN];
vector<int> v;

lint gs(int x){
	return 1ll * x * (x + 1) / 2;
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		v.clear();
		memset(vis, 0, sizeof(int) * (n + 10));
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			v.push_back(a[i]);
		}
		if(n == 1){
			puts("1");
			continue;
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		vector<int> enq;
		lint granted = 0;
		for(int i=1; i<=n; i++){
			a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
			if(vis[a[i]] == 0){
				enq.push_back(i);
				vis[a[i]] = i;
				nxt[i] = n + 1;
			}
			else{
				nxt[vis[a[i]]] = min(nxt[vis[a[i]]], i);
			}
			granted += 1ll * i * enq.size();
		}
		lint ret = granted;
		set<int> s;
		seg1.init(n);
		seg2.init(n);
		for(auto &i : enq){
			seg1.upd(a[i], v[a[i]] + gs(i - 1));
			seg2.upd(a[i], -v[a[i]] + gs(i - 1));
		}
		for(auto &i : enq){
			auto l = s.lower_bound(v[a[i]]);
			lint profit = gs(nxt[i] - 1) - gs(i - 1);
			if(l != s.end()){
				ret = min(ret, granted + abs(*l - v[a[i]]) - profit); 
			}
			if(l != s.begin()){
				ret = min(ret, granted + abs(v[a[i]] - *prev(l)) - profit);
			}
			seg1.upd(a[i], 1e18);
			seg2.upd(a[i], 1e18);
			ret = min(ret, granted + seg1.query(a[i], n) - v[a[i]] - profit - gs(i - 1));
			ret = min(ret, granted + seg2.query(0, a[i]) + v[a[i]] - profit - gs(i - 1));
			/*
			for(int j=0; j<enq.size(); j++){
				if(enq[j] > i){
			//		ret = min(ret, granted + abs(v[a[enq[j]]] - v[a[i]]) - profit + gs(enq[j] - 1) - gs(i - 1));
				}
			}*/
			s.insert(v[a[i]]);
		}
		printf("%lld\n", ret);
	}
}
