#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
using pi = pair<int, int>;

struct seg{
	int tree[MAXT], lazy[MAXT];
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p] += v;
			if(lazy[p] > 0) tree[p] = (pe - ps + 1);
			else tree[p] = (ps == pe ? 0 : (tree[2*p] + tree[2*p+1]));
			return;
		}
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		if(lazy[p] == 0) tree[p] = tree[2*p] + tree[2*p+1];
	}
	int query(){ return tree[1]; }
}seg;

struct sweep{
	int pos, s, e, x;
	bool operator<(const sweep &s)const{
		return pi(pos, -x) < pi(s.pos, -s.x);
	}
};

int w, h, n, sx[MAXN], ex[MAXN], sy[MAXN], ey[MAXN];

int solve(){
	vector<sweep> swp;
	swp.push_back({1, 1, 0, 0});
	swp.push_back({w+1, 1, 0, 0});
	for(int i=0; i<n; i++){
		swp.push_back({sx[i], sy[i], ey[i], +1});
		swp.push_back({ex[i] + 1, sy[i], ey[i], -1});
	}
	sort(swp.begin(), swp.end());
	int ret = 0;
	for(int i=0; i<swp.size(); ){
		int e = i;
		while(e < swp.size() && swp[i].pos == swp[e].pos) e++;
		for(int j=i; j<e; j++){
			seg.add(swp[j].s, swp[j].e, 1, h, 1, swp[j].x);
		}
		if(e < swp.size()) ret += (swp[e].pos - swp[i].pos) * ((h - seg.query()) % 2);
		i = e;
	}
	return ret;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d %d",&w,&h,&n);
		for(int i=0; i<n; i++){
			scanf("%d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i]);
		}
		int ret = solve();
		for(int i=0; i<n; i++){
			swap(sx[i], sy[i]);
			swap(ex[i], ey[i]);
		}
		swap(w, h);
		ret = max(ret, solve());
		printf("%d\n", ret);
	}
}
