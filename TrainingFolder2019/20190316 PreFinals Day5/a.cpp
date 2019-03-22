#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
const int MAXT = 270000;
using pi = pair<int, int>;

struct SA{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(1){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				aux[--cnt[ord[min(i+p, n)]]] = i;
			memset(cnt, 0, sizeof cnt);
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p *= 2;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h  = max(h - 1, 0);
		}
	}
}sfxarray;

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(1e9, 1e9));
		for(int i=0; i<n; i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i=lim-1; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
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
}sfxmin, seg;


int n;
char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[MAXN];
vector<tuple<int, int, int>> edg;

void add_edge(int s, int e, int x){
	edg.emplace_back(s + 1, x, e + 1);
	assert(s < e);
}

void solve(int s, int e, int depth){
	if(s == e) return;
	int min_val = seg.query(s + 1, e).first;
	int min_sfx = sfxmin.query(s, e).first;
	while(s <= e){
		auto x = seg.query(s + 1, e);
		if(x.first != min_val){
			x.first = min_val;
			x.second = e + 1;
		}
		int nxt_sfx = sfxmin.query(s, x.second - 1).first;
		if(min_sfx != nxt_sfx && nxt_sfx + min_val != n){
			add_edge(min_sfx + min_val, nxt_sfx + min_val + 1, str[nxt_sfx + min_val]);
		}
		solve(s, x.second - 1, min_val);
		s = x.second;
	}
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	sfxarray.solve(n, str, sfx, rev, lcp);
	for(int i=0; i<n; i++){
		add_edge(i, i + 1, str[i]);
	}
	sfxmin.init(n, sfx);
	seg.init(n, lcp);
	solve(0, n - 1, 0);
	sort(edg.begin(), edg.end());
	edg.resize(unique(edg.begin(), edg.end()) - edg.begin());
	vector<tuple<int, int, int>> fuck = edg;
	edg.clear();
	edg.push_back(fuck[0]);
	for(int i=1; i<fuck.size(); i++){
		int ps, pe, px;
		int ns, ne, nx;
		tie(ps, pe, px) = fuck[i-1];
		tie(ns, ne, nx) = fuck[i];
		if(ps == ns && pe == ne) continue;
		else edg.push_back(fuck[i]);
	}

	printf("%d %d\n", n + 1, edg.size());
	for(auto &i : edg){
		int s, e, x;
		tie(s, x, e) = i;
		printf("%d %d %c\n", s, e, (char)x);
	}
}
