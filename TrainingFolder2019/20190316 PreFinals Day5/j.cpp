#include <bits/stdc++.h>
using namespace std;

using lint = long long;


vector<lint> divisors (lint n) {
	vector<lint> ret;
	lint i;
	for(i = 1; i * i <= n; i++) {
		if(n % i == 0) {
			ret.push_back(i);
			if(i != n / i) ret.push_back(n / i);
		}
	}
	sort(ret.begin(), ret.end());
	return ret;
}

vector<lint> prime_divisors (lint n) {
	vector<lint> ret;
	lint v = n;
	for(lint p = 2; p * p <= n; p++) {
		if(v % p == 0) {
			ret.push_back(p);
			while(v % p == 0) v /= p;
		}
	}
	if(v > 1) {
		ret.push_back(v);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

lint n, m, k;

lint modpow (lint a, lint b) {
	lint ret = 1;
	while(b > 0) {
		if(b & 1) ret = ((__int128)a * ret) % k;
		b >>= 1;
		a = ((__int128)a * a) % k;
	}
	return ret;
}

lint gcd (lint a, lint b) {
	return b ? gcd(b,a%b) : a;
}


int main(){
	cin >> n >> m;
	if(n == 1 && m == 1) {
		puts("1");
		return 0;
	}
	
	k = n * m - 1;
	
	vector<lint> div_k = divisors(k);
	vector<lint> pri_k = prime_divisors(k);
	
	auto phi = [&pri_k](lint x) {
		lint ret = 1;
		assert(k % x == 0);
		for(lint p : pri_k) {
			int c = 0;
			while(x % p == 0) {
				c += 1;
				if(c == 1) ret *= p-1;
				else ret *= p;
				x /= p;
			}
		}
		return ret;
	};
	
	lint phi_k = phi(k);
	vector<lint> div_phi_k = divisors(phi_k);
	unordered_map<lint, lint> f;
	for(lint d : div_phi_k) {
		f[d] = k / gcd(k, modpow(n, d)-1);
	}
	
	lint ans = 1;
	for(lint e : div_k) {
		for(lint d : div_phi_k) {
			if(e % f[d] == 0) {
				ans += phi(k / e) / d;
				break;
			}
		}
	}
	
	printf("%lld\n", ans);
	return 0;
}
