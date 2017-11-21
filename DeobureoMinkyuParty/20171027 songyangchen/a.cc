#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
#define real fuck
const int MAXN = 131072;
const int prr = 10;
const int mod = 786433;

int k, n, m;
char str[9][15000];
lint ply[9][MAXN];
lint trf[9][MAXN];
lint roots[MAXN], iroots[MAXN];
int rev[MAXN], sex;

lint ipow(int x, int p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p & 1) ret = ret * piv;
		piv = piv * piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret;
}

void fft(lint *b, int n, bool inv){
	for(int i=1; i<n; i++) if(i < rev[i]) swap(b[i], b[rev[i]]);
	lint *r = (inv ? iroots : roots);
	for(int i=2; i<=n; i<<=1){
		int step = n / i;
		for(int j=0; j<n; j+=i){
			for(int k=0; k<i/2; k++){
				lint u = b[j+k], v = b[j+k+i/2] * r[step * k] % mod;
				b[j+k] = (u + v);
				b[j+k+i/2] = (u - v + mod);
			}
		}
	}
	if(inv){
		for(int i=0; i<n; i++) b[i] = (b[i] * sex) % mod;
	}
	else{
		for(int i=0; i<n; i++) b[i] %= mod;
	}
}

void getpoly(int x){
	memcpy(trf[x], ply[x], sizeof(ply[x]));
	fft(trf[x], MAXN, 0);
}

lint ans[MAXN];
lint fact[MAXN], invf[MAXN];
lint real[MAXN];

void solve(){
	fill(ans, ans + MAXN, 1);
	for(int i=0; i<k; i++){
		for(int j=0; j<MAXN; j++){
			ans[j] *= trf[i][j];
			ans[j] %= mod;
		}
	}
	for(int i=0; i<MAXN; i++) real[i] += ans[i];
}

void hellchosun(){
	int j = 0, n = MAXN;
	for(int i=1; i<n; i++){
		int bit = (n >> 1);
		while(j >= bit){
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		rev[i] = j;
	}
	int ang = ipow(prr, (mod - 1) / n);
	int rang = ipow(ang, mod - 2);
	sex = ipow(n, mod - 2);
	for(int i=0; i<n/2; i++){
		iroots[i] = (i ? (iroots[i-1] * rang % mod) : 1);
		roots[i] = (i ? (roots[i-1] * ang % mod) : 1);
	}
}

int main(){
	scanf("%d %d %d",&k,&n,&m);
	hellchosun();
	fact[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
	}
	invf[MAXN - 1] = ipow(fact[MAXN - 1], mod - 2);
	for(int i=MAXN-2; i>=0; i--){
		invf[i] = invf[i+1] * (i+1) % mod;
	}
	k--;
	for(int i=0; i<k; i++){
		scanf("%s", str[i]);
		for(int j=0; j<=n; j++){
			if(str[i][j] == '1') ply[i][j] = invf[j];
		}
		getpoly(i);
	}
	solve();
	while(m--){
		int u, v;
		scanf("%d %d",&u,&v);
		u--;
		str[u][v] ^= 1;
		if(str[u][v] == '1') ply[u][v] = invf[v];
		else ply[u][v] = 0;
		getpoly(u);
		solve();
	}
	for(int i=0; i<MAXN; i++) real[i] %= mod;
	fft(real, MAXN, 1);
	lint ans = 0;
	for(int i=1; i<MAXN; i++) ans += real[i] * fact[i] % mod;
	cout << ans % mod;
}
