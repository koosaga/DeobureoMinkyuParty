#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;

lint getsum(lint x){
	x %= mod;
	x *= (x + 1 + mod);
	x %= mod;
	x *= (mod + 1) / 2;
	x %= mod;
	return x;
}

map<lint, int> mp;
lint f(lint x){
	if(x == 0) return 0;
	if(mp.find(x) != mp.end()) return mp[x];
	if(x % 2 == 1) return mp[x] = (f(x / 2) * 2 + x) % mod;
	return mp[x] = (f(x / 2) + f((x - 1) / 2) + x) % mod;
}

lint g(lint x){
	if(x == 0) return 0;
	if(x % 2 == 1) return (4 * g(x / 2) + getsum(x) - f(x / 2) + mod) % mod;
	return (g(x - 1) + f(x)) % mod;
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		lint s, e; scanf("%lld %lld",&s,&e);
		printf("%lld\n", (g(e) - g(s-1) + mod) % mod);
	}
}
