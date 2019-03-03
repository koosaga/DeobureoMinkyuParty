#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint , int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

lint ipow(int x, int p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

bool cmp(pi a, pi b){
	return (__int128) a.first * b.second < (__int128) b.first * a.second;
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n; scanf("%d",&n);
		double aans = n + 1 - sqrt((1ll * n * n + n) / 2);
		int s = (int)round(aans) - 8;
		int e = (int)round(aans) + 8;
		s = max(s, 1);
		e = min(e, n - 1);
		pi ret(0, 1);
		auto sig = [&](int i){
			pair<lint, int> frac = make_pair(1ll * n * (n + 1) / 2 - 1ll * i * (i + 1), 2 * n - 2 * i);
			return frac;
		};
		for(int i=s; i<=e; i++) ret = max(ret, sig(i), cmp);
		ret = max(ret, sig(1), cmp);
		ret = max(ret, sig(n - 1), cmp);
		lint ans = (ret.first % mod) * ipow(ret.second, mod - 2) % mod;
		printf("%lld\n", ans);
	}
}
