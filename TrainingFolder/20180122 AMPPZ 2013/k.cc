#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
typedef long long lint;
typedef pair<int, int> pi;

int n, aa, b;
pi a[MAXN];
vector<int> vx;

struct seg{
	lint tree[1000005];
	void add(int x, lint v){
		while(x <= 1000004){
			tree[x] += v;
			x += x & -x;
		}
	}
	lint query(int x){
		if(x < 0) return 0;
		x = min(x, 1000004);
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}seg1, segx, segy, segxy;

int main(){
	scanf("%d %d %d",&n,&aa,&b);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second), a[i].second++;
	sort(a, a+n);
	lint cmb = 1ll * n * (n - 1) / 2;
	long double ret = 0;
	int ptr = n;
	for(int i=n-1; i>=0; i--){
		while(ptr > 0 && a[ptr-1].first - a[i].first > aa){
			ptr--;
			seg1.add(a[ptr].second, -1);
			segx.add(a[ptr].second, -a[ptr].first);
			segy.add(a[ptr].second, -a[ptr].second);
			segxy.add(a[ptr].second, -1ll * a[ptr].first * a[ptr].second);
		}
		lint q1 = seg1.query(a[i].second + b) - seg1.query(a[i].second - 1);
		lint qx = segx.query(a[i].second + b) - segx.query(a[i].second - 1);
		lint qy = segy.query(a[i].second + b) - segy.query(a[i].second - 1);
		lint qxy = segxy.query(a[i].second + b) - segxy.query(a[i].second - 1);
		lint tmp = qxy - qy * (a[i].first + aa) - qx * (a[i].second + b) + q1 * (a[i].first + aa) * (a[i].second + b); 
		q1 = seg1.query(a[i].second - 1) - seg1.query(a[i].second - b);
		qx = segx.query(a[i].second - 1) - segx.query(a[i].second - b);
		qy = segy.query(a[i].second - 1) - segy.query(a[i].second - b);
		qxy = segxy.query(a[i].second - 1) - segxy.query(a[i].second - b);
		tmp += -qxy + (a[i].first + aa) * qy + a[i].second * qx - q1 * a[i].second * (a[i].first + aa);
		tmp += q1 * b * (a[i].first + aa) - b * qx;
		seg1.add(a[i].second, 1);
		segx.add(a[i].second, a[i].first);
		segy.add(a[i].second, a[i].second);
		segxy.add(a[i].second, 1ll * a[i].first * a[i].second);
		ret += (long double)tmp / cmb;
	}
	printf("%.10Lf\n", ret);
}
