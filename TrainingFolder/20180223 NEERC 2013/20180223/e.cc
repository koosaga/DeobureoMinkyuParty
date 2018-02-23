#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
typedef pair<int, int> pi;
typedef long long lint;

int n;
pi a[MAXN];

struct rect{
	double sx, ex, sy, ey;
	bool operator<(const rect &r)const{
		return (ex - sx) * (ey - sy) < (r.ex - r.sx) * (r.ey - r.sy);
	}
};

struct line{
	pi s, e;
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

rect solve(){
	lint ans = 0;
	for(int i=2; i<n; i++) ans += ccw(a[0], a[i-1], a[i]);
	if(ans < 0) reverse(a, a+n);
	rotate(a, *min_element(a, a+n), a+n);
	a[n] = a[0];
	vector<pi> l, r;
	for(int i=0; i<n; i++){
		if(a[i].first < a[i+1].first){
			if(l.empty()) l.push_back(a[i]);
			l.push_back(a[i+1]);
		}
		if(a[i].first > a[i+1].first){
			if(r.empty()) r.push_back(a[i]);
			r.push_back(a[i+1]);
		}
	}
	reverse(r.begin(), r.end());
	int mxp = max_element(l.begin(), l.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	if(mxp < l.size() - 1 && l[mxp].second == l[mxp+1].second){
		// this rectangle
	}
	int l = mxp, r = mxp;
	while(l > 0 && r < l.size()){
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	auto x = solve();
	for(int i=0; i<n; i++){
		a[i].first *= -1;
	}
	auto y = solve();
	tie(y.sx, y.ex) = make_pair(-y.ex, -y.sx);
	x = max(x, y);
	for(int i=0; i<n; i++){
		a[i].first *= -1;
		swap(a[i].first, a[i].second);
	}
	y = solve();
	swap(y.sx, y.sy);
	swap(y.ex, y.ey);
	x = max(x, y);
	for(int i=0; i<n; i++){
		a[i].first *= -1;
	}
	y = solve();
	tie(y.sx, y.ex) = make_pair(-y.ex, -y.sx);
	swap(y.sx, y.sy);
	swap(y.ex, y.ey);
	x = max(x, y);
	printf("%.10f %.10f %.10f %.10f\n", x.sx, x.sy, x.ex, x.ey);
}
