#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int mod = 1e9 + 7;
using pi = pair<int, int>;
using lint = long long;

int n;
pi a[MAXN];
lint bino[MAXN][MAXN], bsum[MAXN][MAXN];

int ccw(pi a, pi b){
	return a.first * b.second - a.second * b.first;
}

int gcd(int x, int y){ return y ? gcd(y, x%y) : x; }

lint weirdQuad(){
	lint ret = 0;
	for(int i=0; i<n; i++){
		vector<pi> l, r;
		for(int j=0; j<i; j++){
			l.emplace_back(a[i].first - a[j].first, a[i].second - a[j].second);
		}
		for(int j=i+1; j<n; j++){
			r.emplace_back(a[j].first - a[i].first, a[j].second - a[i].second);
		}
		sort(l.begin(), l.end(), [&](const pi &a, const pi &b){
			return ccw(a, b) > 0;
		});
		sort(r.begin(), r.end(), [&](const pi &a, const pi &b){
			return ccw(a, b) > 0;
		});
		int j = 0;
		lint sum = 0;
		for(int i=0; i<l.size(); ){
			int e = i;
			while(e < l.size() && ccw(l[i], l[e]) == 0) e++;
			while(j < r.size() && ccw(r[j], l[i]) > 0) j++;
			int k = 0;
			while(k < r.size() && ccw(r[k], l[i]) >= 0) k++;
			lint curpair = (e - i) * (k - j);
			ret += 1ll * curpair * sum % mod;
			sum += curpair;
			i = e;
			j = k;
		}
	}
	return ret;
}

lint count_collinear(int x){
	vector<pi> u, d;
	for(int i=x+1; i<n; i++){
		u.emplace_back(a[i].first - a[x].first, a[i].second - a[x].second);
	}
	for(int i=0; i<x; i++){
		d.emplace_back(a[x].first - a[i].first, a[x].second - a[i].second);
	}
	sort(u.begin(), u.end(), [&](const pi &a, const pi &b){
		return ccw(a, b) > 0;
	});
	sort(d.begin(), d.end(), [&](const pi &a, const pi &b){
		return ccw(a, b) > 0;
	});
	lint ret = 0;
	int l = 0, r = 0;
	for(int i=0; i<u.size(); ){
		int e = i;
		while(e < u.size() && ccw(u[i], u[e]) == 0) e++;
		while(l < d.size() && ccw(u[i], d[l]) < 0) l++;
		while(r < d.size() && ccw(u[i], d[r]) <= 0) r++;
		int cnt = e - i;
		int left_line = (u.size() - e) + l;
		int right_line = (d.size() - r) + i;
		if(cnt >= 2){
			ret += 1ll * left_line * right_line * bsum[cnt][2];
		}
		if(cnt >= 3){
			ret += 1ll * (left_line + right_line) * bsum[cnt][3];
		}
		if(cnt >= 4){
			ret += bsum[cnt][4];
		}
		ret %= mod;
		i = e;
	}
	ret %= mod;
	ret += mod;
	ret %= mod;
	return ret;
}


lint solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	lint ret = bino[n][1] + bino[n][2] + bino[n][3] + bino[n][4];
	sort(a, a + n);
	for(int i=0; i<n; i++) ret += count_collinear(i);
	ret += mod - weirdQuad();
	ret %= mod;
	ret += mod;
	ret %= mod;
	return ret % mod;
}

int main(){
	for(int i=0; i<MAXN; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
		}
		for(int j=MAXN-1; j>=0; j--){
			bsum[i][j] = bino[i][j] + (j + 1 < MAXN ? bsum[i][j+1] : 0);
		}
	}
	int tc;
	scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		printf("Case #%d: %lld\n", i, solve());
	}
}
