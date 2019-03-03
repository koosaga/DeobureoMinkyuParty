#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using base = lint;
using vi = vector<int>;
const int mod = 998244353;
const int prr = 3;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

void fft(vector<base> &a, bool inv){
	int n = a.size(), j = 0;
	vector<base> roots(n / 2);
	for(int i=1; i<n; i++){
		int bit = (n >> 1);
		while(j >= bit){
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}
	int ang = ipow(prr, (mod - 1) / n);
	if(inv) ang = ipow(ang, mod - 2);
	for(int i=0; i<n/2; i++){
		roots[i] = (i ? (1ll * roots[i-1] * ang % mod) : 1);
	}
	for(int i=2; i<=n; i<<=1){
		int step = n / i;
		for(int j=0; j<n; j+=i){
			for(int k=0; k<i/2; k++){
				base u = a[j+k], v = a[j+k+i/2] * roots[step * k] % mod;
				a[j+k] = (u + v) % mod;
				a[j+k+i/2] = (u-v+mod) % mod;
			}
		}
	}
	if(inv){
		for(int i=0; i<n; i++) a[i] = a[i] * ipow(n, mod - 2) % mod;
	}
}

vector<int> multiply(vector<int> x, vector<int> y){
	vector<base> fv(x.begin(), x.end());
	vector<base> fw(y.begin(), y.end());
	int n = 2; while(n < x.size() + y.size()) n <<= 1;
	fv.resize(n);
	fw.resize(n);
	fft(fv, 0);
	fft(fw, 0);
	for(int i=0; i<n; i++) fv[i] = (fv[i] * fw[i] % mod);
	fft(fv, 1);
	vector<int> ret(n);
	for(int i=0; i<n; i++) ret[i] = fv[i];
	return ret;
}

auto cmp = [](vi &a, vi &b){ return a.size() > b.size(); };
int n;

int main(){
	scanf("%d",&n);
	priority_queue<vi, vector<vi>, decltype(cmp)> pq(cmp);
//	pq.push({0, 1});
	int minv = 1e9;
	lint inv = 1;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		minv = min(minv, x);
		inv = inv * x % mod;
		vector<int> v = {x, mod - 1};
		pq.push(v);
	}
	while(pq.size() > 1){
		auto x = pq.top();
		pq.pop();
		auto y = pq.top();
		pq.pop();
		auto z = multiply(x, y);
		z.resize(x.size() + y.size() - 1);
		pq.push(z);
	}
	auto x = pq.top();
	lint ret = 0;
	for(int i=0; i<x.size(); i++){
		ret += x[i] * (ipow(minv, i + 1) * ipow(i + 1, mod - 2) % mod) % mod;
	}
	ret %= mod;
	ret *= ipow(inv, mod - 2);
	ret %= mod;
	cout << ret % mod << endl;
}
