#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint dist(pi a, pi b){
	int dx = a.first - b.first;
	int dy = a.second - b.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}

pi sub(pi a, pi b){
	return pi(b.first - a.first, b.second - a.second);
}

pi h[MAXN * 2];

double solve(vector<pi> &v){
	if(v.size() <= 2) return 0.0;
	int n = v.size();
	for(int i=0; i<n; i++){
		h[i] = h[n+i] = v[i];
	}
	int ptr = 1;
	double ans = 1e9;
	for(int i=0; i<n; i++){
		while(ccw(pi(0, 0), sub(h[i+1], h[i]), sub(h[ptr], h[ptr + 1])) < 0){
			ptr++;
		}
		lint k = ccw(h[i], h[i+1], h[ptr]);
		ans = min(ans, k / sqrt(dist(h[i], h[i+1])));
	}
	return ans;
}

int n;
pi a[MAXN];

int main(){
	scanf("%d %*d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	swap(a[0],*min_element(a, a+n));
	sort(a+1, a+n, [&](const pi &p, const pi &q){
		lint k = ccw(a[0], p, q);
		if(k != 0) return k > 0;
		return dist(a[0], p) < dist(a[0], q);
	});
	vector<pi> h;
	for(int i=0; i<n; i++){
		while(h.size() >= 2 && ccw(h[h.size() - 2], h.back(), a[i]) <= 0){
			h.pop_back();
		}
		h.push_back(a[i]);
	}
	printf("%.10f\n", solve(h));
}

