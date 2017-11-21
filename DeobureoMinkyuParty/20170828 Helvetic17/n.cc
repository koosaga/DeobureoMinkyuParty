#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

char str[MAXN];

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		memset(nord, 0, sizeof(ord));
		memset(cnt, 0, sizeof(ord));
		memset(aux, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]) pnt++;
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p <<= 1;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			if(h) h--;
		}
	}
}sfxarray;

struct rmq{
	int lim;
	pi tree[270000];
	void init(int n, int *a){
		fill(tree, tree + 270000, pi(1e9, 1e9));
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++) tree[i + lim] = pi(a[i], i);
		for(int i=lim; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq;

int n, sfx[MAXN], rev[MAXN], lcp[MAXN];#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

char str[MAXN];

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		memset(nord, 0, sizeof(ord));
		memset(cnt, 0, sizeof(ord));
		memset(aux, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]) pnt++;
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p <<= 1;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			if(h) h--;
		}
	}
}sfxarray;

struct rmq{
	int lim;
	pi tree[270000];
	void init(int n, int *a){
		fill(tree, tree + 270000, pi(1e9, 1e9));
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++) tree[i + lim] = pi(a[i], i);
		for(int i=lim; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq;

int n, sfx[MAXN], rev[MAXN], lcp[MAXN];
lint solve(int s, int e){
	if(s > e) return 0;
	auto x = rmq.query(s, e);
	lint ret = solve(s, x.second -1) + solve(x.second + 1, e);
	ret += 1ll * (e - x.second + 1) * (1 + x.second - s) * x.first;
	return ret;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> str;
		memset(sfx, 0, sizeof(sfx));
		memset(rev, 0, sizeof(sfx));
		memset(lcp, 0, sizeof(sfx));
		n = strlen(str);
		sfxarray.solve(n, str, sfx, rev, lcp);
		lint ret = 1ll * n * (n + 1) / 2;
		rmq.init(n, lcp);
		ret += 2 * solve(1, n-1);
		cout << ret << endl;
	}
}
lint solve(int s, int e){
	if(s > e) return 0;
	auto x = rmq.query(s, e);
	lint ret = solve(s, x.second -1) + solve(x.second + 1, e);
	ret += 1ll * (e - x.second + 1) * (1 + x.second - s) * x.first;
	return ret;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> str;
		memset(sfx, 0, sizeof(sfx));
		memset(rev, 0, sizeof(sfx));
		memset(lcp, 0, sizeof(sfx));
		n = strlen(str);
		sfxarray.solve(n, str, sfx, rev, lcp);
		lint ret = 1ll * n * (n + 1) / 2;
		rmq.init(n, lcp);
		ret += 2 * solve(1, n-1);
		cout << ret << endl;
	}
}
