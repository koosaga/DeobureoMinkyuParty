#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
typedef pair<int, int> pi;
int n, cnt[MAXN];

struct seg{
	struct node{
		int sum, maxv, maxfrm;
	}tree[530000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	node merge(node a, node b){
		node ret;
		ret.sum = a.sum + b.sum;
		if(a.maxv >= a.sum + b.maxv){
			ret.maxv = a.maxv;
			ret.maxfrm = a.maxfrm;
		}
		else{
			ret.maxv = a.sum + b.maxv;
			ret.maxfrm = b.maxfrm;
		}
		return ret;
	}
	void set(int x, int v){
		x += lim;
		tree[x] = {v, max(v, 0), x - lim};
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	node query(){ return tree[1]; }
}seg;

struct intv{
	int s, e, v;
	bool operator<(const intv &i)const{
		return pi(e, v) < pi(i.e, i.v);
	}
}a[MAXN];

struct rmq{
	pi tree[530000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 530000, pi(1e9, 1e9));
	}
	void add(int x, pi v){
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
}rmq;

vector<intv> st[MAXN];
pi orv[MAXN];

bool Fuck();

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].s,&a[i].e);
		orv[i] = pi(a[i].s, a[i].e);
		a[i].v = i;
	}
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++){
		st[a[i].s].push_back(a[i]);
		cnt[i]--;
		cnt[a[i].e]++;
	}
	seg.init(n);
	rmq.init(n);
	for(int i=1; i<=n; i++) seg.set(i, cnt[i]);
	if(Fuck()){
		puts("-1");
		return 0;
	}
	for(int i=1; i<=n; i++){
		int lst = i;
		cnt[i]++;
		seg.set(i, cnt[i]);
		if(seg.query().maxv > 0) lst = seg.query().maxfrm;
		else lst = n;
		for(auto &j : st[i]){
			auto it = lower_bound(a + 1, a + n + 1, j) - a;
			rmq.add(it, pi(j.v, it));
		}
		int l = lower_bound(a + 1, a + n + 1, (intv){-1, lst, 2222222}) - a;
		auto k = rmq.query(1, l - 1);
		int ev = orv[k.first].second;
		rmq.add(k.second, pi(1e9, 1e9));
		cnt[ev]--;
		seg.set(ev, cnt[ev]);
		printf("%d ", k.first);
	}
}


bool Fuck(){
	priority_queue<int, vector<int>, greater<int> > pq;
	for(int i=1; i<=n; i++){
		for(auto &j : st[i]){
			pq.push(j.e);
		}
		if(pq.empty()) return true;
		if(pq.top() < i) return true;
		pq.pop();
	}
	return false;
}

