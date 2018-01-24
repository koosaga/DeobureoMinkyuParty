#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 2005;
typedef pair<int, int> pi;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct rect{double sx, ex, sy, ey;};
rect merge(rect a, rect b){ 
	return (rect){max(a.sx, b.sx), min(a.ex, b.ex), max(a.sy, b.sy), min(a.ey, b.ey)};
}

int n, k;
double t;
pi a[MAXN];

double tri_rect(pi a, pi b, pi c, rect r){
	if(ccw(a, b, c) == 0) return 0;
	if(ccw(a, b, c) < 0) return tri_rect(a, c, b, r);
	// TODO
}

double single_rectangle_cover(rect r){
	double ret = 0;
	for(int i=2; i<n; i++){
		ret += tri_rect(a[0], a[i-1], a[i], r);
	}
	return ret;
}

bool rectangle_cover_check(vector<rect> v){
	double ans = 0;
	double area = 0;
	for(int i=2; i<n; i++) area += ccw(a[0], a[i-1], a[i]);
	for(int i=1; i<(1<<v.size()); i++){
		int cnt = 0;
		rect r = {-1e9, 1e9, -1e9, 1e9};
		for(int j=0; j<v.size(); j++){
			if((i >> j) & 1){
				cnt++;
				r = merge(r, v[j]);
			}
		}
		if(r.sx <= r.ex && r.sy <= r.ey){
			ans += single_rectangle_cover(r) * (cnt % 2 ? 1 : -1);
		}
	}
	return fabs(area - ans) < 1e-4;
}

bool solve(){
	lint arrr = 0;
	for(int i=2; i<n; i++) arrr += ccw(a[0], a[i-1], a[i]);
	if(arrr < 0) reverse(a, a+n);
	// TODO
}

bool trial(double x){
	t = x;
	if(solve()) return true;
	for(int i=0; i<n; i++) a[i].second *= -1;
	if(solve()) return true;
	for(int i=0; i<n; i++) a[i].first *= -1;
	if(solve()) return true;
	for(int i=0; i<n; i++) a[i].second *= -1;
	if(solve()) return true;
	return false;
}

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	double s = 0, e = 1e5;
	while(e - s < 1e-4){
		double m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m;
	}
	printf("%.10f\n", s);
}
