#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXE = 2000005;
using pi = pair<int, int>;
using lint = long long;

struct disj{
	int pa[MAXE];
	lint areaSum[MAXE];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){ return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; 
		areaSum[p] += areaSum[q];
		return 1;
	}
	void append(int x, lint v){
		x = find(x);
		areaSum[x] += v;
	}
	lint getarea(int x){ return areaSum[find(x)]; }
}disj;

struct query{ int t, a, b; }qr[MAXE];

int n, q;
pi a[MAXN];
vector<pi> gph[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	scanf("%d",&q);
	disj.init(2 * q);
	vector<tuple<int, int, int>> EE;
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&qr[i].t,&qr[i].a,&qr[i].b);
		if(qr[i].t == 1){
			EE.emplace_back(qr[i].a, qr[i].b, 2 * i);
			EE.emplace_back(qr[i].b, qr[i].a, 2 * i + 1);
			gph[qr[i].a].emplace_back(2*i, qr[i].b);
			gph[qr[i].b].emplace_back(2*i+1, qr[i].a);
			disj.append(2 * i, ccw(pi(0, 0), a[qr[i].a], a[qr[i].b]));
			disj.append(2 * i + 1, ccw(pi(0, 0), a[qr[i].b], a[qr[i].a]));
		}
	}
	for(int i=0; i<n; i++){
		sort(gph[i].begin(), gph[i].end(), [&](const pi &x, const pi &y){
			bool mode1 = (a[i] > a[x.second]);
			bool mode2 = (a[i] > a[y.second]);
			if(mode1 != mode2) return mode1 < mode2;
			return ccw(a[i], a[x.second], a[y.second]) > 0;
		});
		for(int j=0; j<gph[i].size(); j++){
			int out = gph[i][j].first;
			int in = gph[i][(j+1)%gph[i].size()].first ^ 1;
			disj.uni(in, out);
		}
	}
	sort(EE.begin(), EE.end());
	int minpos = min_element(a, a + n) - a;
	int dir = gph[minpos][0].first ^ 1;
	disj.append(dir, -69696969ll);
	vector<lint> seq;
	for(int i=q-1; i>=0; i--){
		if(qr[i].t == 0){
			auto lb = lower_bound(EE.begin(), EE.end(), make_tuple(qr[i].a, qr[i].b, -1));
			seq.push_back(disj.getarea(get<2>(*lb)));
		}
		else{
			disj.uni(2 * i, 2 * i + 1);
		}
	}
	reverse(seq.begin(), seq.end());
	for(auto &i : seq) printf("%lld\n", max(i, -1ll));
}
