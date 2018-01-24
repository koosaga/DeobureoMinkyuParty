#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 20005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

struct pnt{
	int x, y, idx;
	bool operator<(const pnt &p)const{
		return pi(y, x) < pi(p.y, p.x);
	}
}a[MAXN], b[MAXN];

struct seg{
	pi tree[66000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 66000, pi(1e9, -1));
	}
	void update(int pos, pi val){
		pos += lim;
		tree[pos] = min(tree[pos], val);
		while(pos > 1){
			pos >>= 1;
			tree[pos] = min(tree[2*pos], tree[2*pos+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, -1);
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

int n;
vector<edg> e;

void solve(){
	vector<int> v;
	for(int i=0; i<n; i++){
		v.push_back(a[i].x - a[i].y);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	seg.init(n);
	for(int i=n-1; i>=0; i--){
		int l = lower_bound(v.begin(), v.end(), a[i].x - a[i].y) - v.begin();
		auto p = seg.query(l, n - 1);
		if(p.second != -1){
			e.push_back({(int)p.second, a[i].idx, (int)p.first - a[i].x - a[i].y});
		}
		seg.update(l, pi(a[i].x + a[i].y, a[i].idx));
	}
}


int main(){
	cin >> n;
	disj.init(n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].idx = i;
	}
	for(int i=0; i<8; i++){
		for(int j=0; j<n; j++){
			b[j] = a[j];
		}
		for(int j=0; j<n; j++){
			if(i & 1) a[j].x *= -1;
			if(i & 2) a[j].y *= -1;
			if(i & 4) swap(a[j].x, a[j].y);
		}
		sort(a, a+n);
		solve();
		for(int j=0; j<n; j++) a[j] = b[j];
	}
	sort(e.begin(), e.end());
	int ret = 0;
	for(auto &i : e){
	//	printf("%d %d %d\n", i.s, i.e, i.x);
		if(disj.uni(i.s, i.e)) ret = i.x;
	}
	cout << ret;
}
