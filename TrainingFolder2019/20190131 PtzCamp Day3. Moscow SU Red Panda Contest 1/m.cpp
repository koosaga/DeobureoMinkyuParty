#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 500005;
const int mod = 998244353;
using pi = pair<int, int>;
const int invt = (mod + 1) / 2;

int n, a[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

lint gs(lint x){
	return ((x * x + x) / 2) % mod;
}

lint histogram(pi x, pi y){
	int x1 = x.first;
	int y1 = x.second;
	int x2 = y.first;
	int y2 = y.second;
	lint dap = 1ll * y1 * (x2 - x1 + mod) % mod;
	lint slp = (y2 - y1 + mod) * ipow(x2 - x1 + mod, mod - 2) % mod;
	slp *= gs(x2 - x1);
	slp %= mod;
	return (dap + slp) % mod;
}

int main(){
	scanf("%d",&n);
	lint ret = 0;
	vector<pi> stk;
	stk.emplace_back(0, -69696969);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		while(stk.size() >= 2 && ccw(stk[stk.size()-2], stk.back(), pi(i, a[i])) >= 0){
			ret += mod - histogram(stk[stk.size()-2], stk.back());
			stk.pop_back();
		}
		if(stk.size()) ret += histogram(stk.back(), pi(i, a[i]));
		stk.emplace_back(i, a[i]);
		ret %= mod;
		printf("%lld ", ret * ipow(i, mod - 2) % mod);
	}
}
