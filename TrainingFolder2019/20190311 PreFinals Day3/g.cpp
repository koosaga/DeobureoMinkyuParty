#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
using lint = long long;
using pi = pair<lint, lint>;

lint dp1[2][MAXN], s[MAXN], dp2[2][MAXN];
int n, k, a[MAXN];

struct cht{
	vector<pi> v;
	int p = 0;
	void clear() { p = 0; v.clear(); }
	bool ccw(pi a, pi b, pi c){
		return (b.second - a.second) * (b.first - c.first) >= (c.second - b.second) * (a.first - b.first);
	}
	void add(lint x, lint y){
		if(v.size() > p && v.back().first == x){
			y = min(y, v.back().second);
			v.pop_back();
		}
		pi z(x, y);
		while(v.size() >= p + 2 && ccw(v[v.size() - 2], v.back(), z)) v.pop_back();
		v.push_back(z);
	}
	lint query(int x){
		if(v.size() == p) return 1e12;
		while(p + 1 < v.size() && v[p].first * x + v[p].second > v[p+1].first * x + v[p+1].second) p++;
		return v[p].first * x + v[p].second;
	}
}cht;

void FUCK(int x){
	fill(dp1[x], dp1[x] + MAXN, 1e12);
	fill(dp2[x], dp2[x] + MAXN, 1e12);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	sort(a + 1, a + n + 1);
	for(int i=1; i<=n; i++) s[i] = s[i-1] + a[i];
	FUCK(0); FUCK(1);
	dp2[0][0] = 0;
	for(int i=1; i<=k; i++){
		FUCK(i % 2);
		cht.clear();
		for(int j=1; j<=n; j++){
			cht.add(-(j-1), dp2[(i-1)%2][j-1] + s[j-1]);
			dp1[i%2][j] = cht.query(a[j]) - s[j] + 1ll * a[j] * j;
		}
		cht.clear();
		for(int j=1; j<=n; j++){
			cht.add(-a[j], dp1[i%2][j] + 1ll * a[j] * j - s[j]);
			dp2[i%2][j] = cht.query(j) + s[j];
		}
	}
	cout << dp2[k%2][n] << endl;
}
