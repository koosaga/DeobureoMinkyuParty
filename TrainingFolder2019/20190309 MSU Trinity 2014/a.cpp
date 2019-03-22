#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int MAXT = 2100000;
using pi = pair<int, int>;

struct segm{
	int s, e, x;
	bool operator<(const segm &v)const{
		return pi(s, e) < pi(v.s, v.e);
	}
}a[MAXN];

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n, segm *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(1e9, 1e9));
		for(int i=0; i<n; i++){
			tree[i + lim] = pi(a[i].e, i);
		}
		for(int i=lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n, q;
int dap[MAXN];

void respond(int s, int e, int x){
	if(s > e) return;
	auto l = lower_bound(a, a + q, (segm){s, -1, -1}) - a;
	auto r = lower_bound(a, a + q, (segm){e + 1, -1, -1}) - a;
	if(l == r) return;
	while(true){
		auto ans = seg.query(l, r - 1);
		if(ans.first > e) break;
		dap[a[ans.second].x] = x;
		seg.upd(ans.second, pi(1e9, 1e9));
	}
}

vector<int> v[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		v[x].push_back(i);
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int l, r; scanf("%d %d",&l,&r);
		a[i] = {l, r, i};
	}
	sort(a, a + q);
	seg.init(q, a);
	for(int i=0; i<MAXN; i++){
		if(v[i].empty()){
			respond(1, n, i);
			break;
		}
		if(v[i][0] > 1) respond(1, v[i][0] - 1, i);
		if(v[i].back() < n) respond(v[i].back() + 1, n, i);
		for(int j=1; j<v[i].size(); j++) respond(v[i][j-1] + 1, v[i][j] - 1, i);
	}
	for(int i=0; i<q; i++) printf("%d\n", dap[i]);
}
