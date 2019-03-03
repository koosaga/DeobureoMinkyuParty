#include <bits/stdc++.h>
using namespace std;
using real_t = double;
using pi = complex<real_t>;
const real_t eps = 1e-2;
const int MAXN = 205;

int n, m;
real_t R;
pi a[MAXN];

bool parallel(int x, int y){
	auto v = a[x+1] - a[x];
	auto w = a[y+1] - a[y];
	return fabs((conj(v) * w).imag()) < eps;
}

struct line{
	real_t a, b, c;
};

pi move(pi a, pi b, pi targ, real_t R){
	pi bangVec = (b - a);
	bangVec /= abs(bangVec);
	bangVec *= pi(0, 1);
	bangVec *= R;
	return targ + bangVec;
}

line construct(pi ia, pi ib, real_t R){
	auto a = move(ia, ib, ia, R);
	auto b = move(ia, ib, ib, R);
	line l = {(a - b).imag(), (b - a).real(), -1};
	l.c = l.a * a.real() + l.b * a.imag();
	return l;
}

pi cross(line x, line y){
	long double xv = (long double)y.b * x.c - (long double)x.b * y.c;
	long double yv = (long double)x.a * y.c - (long double)y.a * x.c;
	long double det = (long double)x.a * y.b - (long double)x.b * y.a;
	return pi(xv / det, yv / det);
}

int ccw(pi a, pi b, pi c){
	real_t val = (conj(b - a) * (c - a)).imag();
	if(fabs(val) > eps) return val > 0 ? 1 : -1;
	return 0;
}

real_t dot(pi a, pi b, pi c){
	return (conj(b - a) * (c - a)).real();
}

bool insec(pi a, pi b, pi c, pi d){
	if(ccw(a, b, c) * ccw(a, b, d) >= 0) return 0;
	if(ccw(c, d, a) * ccw(c, d, b) >= 0) return 0;
	return 1;
}

real_t segdist(pi a, pi b, pi c){
	if(dot(a, b, c) < 0 || dot(b, a, c) < 0) return min(abs(a - c), abs(b - c));
	return fabs((conj(b - a) * (c - a)).imag()) / abs(a - b);
}

bool sane(pi p){
	pi amujeom(6969696, 4204204);
	int cnt = 0;
	for(int i=0; i<n; i++){
		if(insec(p, amujeom, a[i], a[i + 1])) cnt++;
	}
	if(cnt % 2 == 0) return 0;
	for(int i=0; i<n; i++){
		if(segdist(a[i], a[i+1], p) < R - eps) return 0;
	}
	return 1;
}

pi suseon(pi a, pi b, pi c){
	real_t segdist = ((conj(b - a) * (c - a)).imag()) / abs(b - a);
	c = move(a, b, c, -segdist);
	return c;
}

void solve(){
	cin >> n >> m >> R;
	for(int i=0; i<n; i++){
		int x, y;
		cin >> x >> y;
		a[i] = pi(x, y);
	}
	a[n] = a[0];
	vector<pi> cnd;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(parallel(i, j)) continue;
			line x = construct(a[i], a[i + 1], R);
			line y = construct(a[j], a[j + 1], R);
			pi p = cross(x, y);
			if(sane(p)){
				cnd.push_back(p);
			}
		}
	}
	while(m--){
		int p, q; cin >> p >> q;
		pi x(p, q);
		if(sane(x)){
			puts("0");
			continue;
		}
		real_t ret = 1e10;
		for(auto &i : cnd){
			ret = min(ret, abs(x - i));
		}
		for(int i=0; i<n; i++){
			pi lp = move(a[i], a[i+1], a[i], R);
			pi rp = move(a[i], a[i+1], a[i+1], R);
			pi p = suseon(lp, rp, x);
			assert(ccw(lp, rp, p) == 0);
			if(sane(p)) ret = min(ret, abs(x - p));
		}
		printf("%d\n", (int)round(ret));
	}
}
int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		solve();
	}
}
