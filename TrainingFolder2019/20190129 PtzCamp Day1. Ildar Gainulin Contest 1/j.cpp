#include <bits/stdc++.h>
const int MAXN = 100005;
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<llf, int>;

struct cht{
	struct line{ llf x, y; int cnt, idx; };
	bool bad(line a, line b, line c){
		llf crs1 = (b.y - a.y) / (a.x - b.x);
		llf crs2 = (c.y - b.y) / (b.x - c.x);
		return crs1 >= crs2;
	}
	vector<line> v;
	int p;
	void clear(){ v.clear(); p = 0; }
	void add(llf x, llf y, int cnt, int idx){
		line l = {x, y, cnt, idx};
		if(v.size() > p && (lint)round(v.back().x) == (lint)round(x)){
			if(l.y < v.back().y) l = v.back();
			v.pop_back();
		}
		while(v.size() >= p + 2 && bad(v[v.size()-2], v.back(), l)) v.pop_back();
		v.push_back(l);
	}
	tuple<llf, int, int> query(lint x){
		while(p + 1 < v.size() && v[p].x * x + v[p].y < v[p+1].x * x + v[p+1].y) p++;
		return make_tuple(v[p].x * x + v[p].y, v[p].cnt, v[p].idx);
	}
}cht;

int n, k;
lint a[MAXN];
pi dp[MAXN];

int trk[MAXN];

pi trial(llf l){
	cht.clear();
	for(int i=1; i<=n; i++){
		cht.add(a[i-1], -(llf)a[i-1] * a[i-1] - dp[i-1].first, dp[i-1].second, i-1);
		llf x; int y, z;
		tie(x, y, z) = cht.query(2 * a[i]);
		dp[i] = make_pair(-x + (llf)a[i] * a[i] + l, y + 1);
		trk[i] = z;
	}
	return dp[n];
}


vector<int> trace(llf l){
	trial(l);
	vector<int> v;
	for(int i=n; i; i=trk[i]) v.push_back(i);
	v.push_back(0);
	return vector<int>(v.rbegin(), v.rend());
}

int get_max(int l, int r){
	lint ret = 0;
	for(int i=l; i<=r; i++) ret = max(ret, a[i] - a[i-1]);
	return ret;
}

void report(vector<int> v){
	vector<lint> s, m;
	for(int i=0; i+1<v.size(); i++){
		s.push_back(a[v[i+1]] - a[v[i]]);
		m.push_back(get_max(v[i] + 1, v[i+1]));
	}
	for(int i=0; i+1<s.size(); i++){
		if(abs(s[i+1] - s[i]) > max(m[i], m[i+1])){
			puts("No");
			exit(0);
		}
	}
	puts("Yes");
	for(int i=1; i+1<v.size(); i++) printf("%d ", v[i]);
	exit(0);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		int x = 0;
//		scanf("%d",&x);
		a[i] = a[i-1] + x;
	}
	lint s = 0, e = 4e18;
	while(s != e){
		lint m = (s + e) / 2;
		if(trial(m + 0.5L).second <= k) e = m;
		else s = m + 1;
	}
	vector<int> l = trace(s + 0.5L); // small
	vector<int> r = trace(s - 0.5L); // large
	if(l.size() == k + 1) report(l);
	if(r.size() == k + 1) report(r);
	assert(l.size() < k + 1);
	assert(r.size() > k + 1);
	for(int i=0; i+1<r.size(); i++){
		int idx = upper_bound(l.begin(), l.end(), r[i]) - l.begin();
		if(l[idx] >= r[i+1] && (i + 1) + (l.size() - idx) == k + 1){
			vector<int> v;
			for(int j=0; j<=i; j++) v.push_back(r[j]);
			for(int j=idx; j<l.size(); j++) v.push_back(l[j]);
			report(v);
		}
	}
	puts("No");
}
