#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
const int mod = 1e9 + 7;
using pi = pair<int, int>;
using lint = long long;

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, pi(2e9, -1));
		for(int i=1; i<=n; i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i=lim-1; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(2e9, -1);
		while(s < e){
			if(s % 2 == 1) ret = min(ret, tree[s++]);
			if(e % 2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = pi(v, x - lim);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
}seg, seg2;

struct ans{
	int tak, nie;
};

vector<pi> v[MAXN];
int ptr[MAXN];
int n, m, a[MAXN], b[MAXN];

ans append(ans x, int TAK, int NIE){
	return (ans){x.tak + TAK, max(x.nie + NIE, x.tak + TAK)};
}

ans fuck(ans x, vector<pi> v){
	for(int i=0; i<v.size(); ){
		int e = i;
		int tak = 0, nie = 0;
		while(e < v.size() && v[e].first == v[i].first){
			if(v[e].second == 0) nie++;
			else tak++;
			e++;
		}
		x = append(x, tak, nie);
		i = e;
	}
	return x;
}

ans dnc(int s, int e, int h){
	vector<pi> cons;
	if(s == e){
		while(seg2.query(s, s).first < h){
			cons.push_back(v[s][ptr[s]++]);
			b[s] = (ptr[s] == v[s].size() ? 1000696969 : v[s][ptr[s]].first);
			seg2.upd(s, b[s]);
		}
		ans sol = {0, 0};
		return fuck(sol, cons);
	}
	auto l = seg.query(s, e - 1);
	l.first *= -1;
	auto L = dnc(s, l.second, l.first);
	auto R = dnc(l.second + 1, e, l.first);
	while(true){
		auto t = seg2.query(s, e);
		if(t.first >= h) break;
		int pos = t.second;
		cons.push_back(v[pos][ptr[pos]++]);
		b[pos] = (ptr[pos] == v[pos].size() ? 1000696969 : v[pos][ptr[pos]].first);
		seg2.upd(pos, b[pos]);
	}
	ans sol;
	sol.tak = L.tak + R.tak;
	sol.nie = L.nie + R.nie;
	return fuck(sol, cons);
}

int solve(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<n; i++){
		scanf("%d",&a[i]);
		a[i] *= -1;
	}
	seg.init(n, a);
	for(int i=1; i<=n; i++){
		ptr[i] = 0;
		v[i].clear();
	}
	for(int i=0; i<m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		v[x].emplace_back(y, z);
	}
	for(int i=1; i<=n; i++){
		sort(v[i].begin(), v[i].end());
		b[i] = v[i].size() ? v[i][0].first : 2e9;
	}
	seg2.init(n, b);
	auto ret = dnc(1, n, 1e9 + 12345);
	return ret.nie;
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		printf("Case #%d: %d\n", i, solve());
	}
}
