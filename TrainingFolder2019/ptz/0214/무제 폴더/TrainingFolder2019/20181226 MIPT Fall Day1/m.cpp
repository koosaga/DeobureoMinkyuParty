#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = __float128;
using pi = pair<real_t, real_t>;
const int MAXN = 30005;

struct cht{
	vector<pi> v;
	int p;
	void clear(){
		 p = 0;
		 v.clear();
	}
	bool bad(pi x, pi y, pi z){
		real_t cr1 = (real_t) (x.second - y.second) * (z.first - y.first);
		real_t cr2 = (real_t) (y.second - z.second) * (y.first - x.first);
		return cr1 >= cr2;
	}
	void add(real_t x, real_t y){
		while(v.size() >= p + 2 && bad(v[v.size()-2], v.back(), pi(x, y))){
			v.pop_back();
		}
		v.emplace_back(x, y);
	}
	real_t query(real_t x){
		int s = 0, e = v.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(v[m].first * x + v[m].second > v[m+1].first * x + v[m+1].second){
				e = m;
			}
			else s = m + 1;
		}
		int m = s;
		return v[m].first * x + v[m].second;
	}
}cht;

int n, m;
real_t c[MAXN], h[MAXN], p[MAXN];
pi fuck[MAXN];

real_t query(real_t yint, real_t t){
	real_t inc = max((real_t)0.0L, cht.query(yint));
	return inc * m - t * yint;
}

real_t trial(real_t t){
	real_t ys = 0, ye = 1e13;
	for(int i=0; i<420; i++){
		real_t m1 = (2 * ys + ye) / 3;
		real_t m2 = (ys + 2 * ye) / 3;
		if(query(m1, t) < query(m2, t)) ye = m2;
		else ys = m1;
	}
	return t * query((ys + ye) / 2, t);
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		double fuckc, fuckh, fuckp;
		cin >> fuckc >> fuckh >> fuckp;
		c[i] = fuckc;
		h[i] = fuckh;
		p[i] = fuckp;
		fuck[i] = pi(h[i] / c[i], p[i] / c[i]);
	}
	sort(fuck, fuck + n);
	for(int i=0; i<n; i++){
		if(i < n - 1 && fuck[i].first == fuck[i+1].first) continue;
		cht.add(fuck[i].first, fuck[i].second);
	}
	real_t s = 0, e = 1e13;
	for(int i=0; i<420; i++){
		real_t m1 = (2 * s + e) / 3;
		real_t m2 = (s + 2 * e) / 3;
		if(trial(m1) > trial(m2)) e = m2;
		else s = m1;
	}
	printf("%.2f\n", (double)(1e-10 + trial((s + e) / 2)));
}
