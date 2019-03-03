#include <bits/stdc++.h>
const int MAXN = 300005;
const int MAXT = 1050000;
using namespace std;
using lint = long long;

struct seg1{
	lint tree[MAXT], lazy[MAXT];
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void init(int s, int e, int p, lint *x){
		if(s == e){
			tree[p] = x[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, x);
		init(m+1, e, 2*p+1, x);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg1, seg2;

int n, m;
int l[MAXN], r[MAXN], p[MAXN];
lint F[MAXN], G[MAXN], sum[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=m; i++){
		scanf("%lld",&sum[i]);
		sum[i] += sum[i-1];
	}
	for(int i=1; i<=n; i++){
		scanf("%d %d %d",&l[i],&r[i],&p[i]);
		G[i] = sum[r[i]];
		F[i - 1] = -sum[l[i] - 1];
	}
	seg1.init(0, n, 1, F);
	seg2.init(0, n, 1, G);
	vector<int> v(n);
	iota(v.begin(), v.end(), 1);
	sort(v.begin(), v.end(), [&](const int &a, const int &b){
		return p[a] > p[b];
	});
	lint ret = 0;
	for(auto &i : v){
		if(seg1.query(0, i - 1, 0, n, 1) == -seg2.query(i, n, 0, n, 1)){
			continue;
		}
		else{
			ret += p[i];
			seg1.add(i, n, 0, n, 1, 1);
			seg2.add(i, n, 0, n, 1, -1);
		}
	}
	cout << ret << endl;
}
