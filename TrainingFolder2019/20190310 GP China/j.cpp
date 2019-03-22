#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 600005;

struct sfxa{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, int *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(int) * (n + 3));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(int) * (n + 3));
			for(int i=0; i<n; i++){
				cnt[ord[min(i+p, n)]]++;
			}
			for(int i=1; i<=n; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i + p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(int) * (n + 3));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] ||
					ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
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
			h = max(h - 1, 0);
		}
	}
}sfxarray;

int n, a[MAXN];
int lg[MAXN];
int sfx[MAXN], rev[MAXN], lcp[20][MAXN];

int glcp(int x, int y){
	x = rev[x];
	y = rev[y];
	if(x > y) swap(x, y);
	int l = lg[y - x];
	return min(lcp[l][x + (1<<l)], lcp[l][y]);
}

int glcp_rev(int x, int y){
	return glcp(2 * n - x, 2 * n - y);
}

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

vector<edg> lis[20];

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa+ n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

void Union(int sx, int sy, int l, int w){
	for(int i=0; i<20; i++){
		if((l >> i) & 1){
			lis[i].push_back({sx, sy, w});
			sx += (1<<i);
			sy += (1<<i);
		}
	}
}

int lcpp[MAXN];
int main(){
	int tc;
	scanf("%d",&tc);
	for(int i=1; i<MAXN; i++){
		lg[i] = lg[i-1];
		while((2 << lg[i]) <= i) lg[i]++;
	}
	while(tc--){
		for(int i=0; i<20; i++) lis[i].clear();
		scanf("%d",&n);
		for(int i=0; i<n; i++) scanf("%d",&a[i]);
		for(int i=n; i<2*n; i++){
			a[i] = a[2*n-1-i];
		}
		a[2*n] = 0;
		sfxarray.solve(2*n, a, sfx, rev, lcpp);
		for(int i=0; i<2*n; i++) lcp[0][i] = lcpp[i];
		lcp[0][2*n] = 0;
		for(int i=1; i<20; i++){
			for(int j=1; j<=n*2; j++){
				lcp[i][j] = lcp[i-1][j];
				if(j - (1<<(i-1)) >= 0) lcp[i][j] = min(lcp[i][j], lcp[i-1][j - (1<<(i-1))]);
			}
		}
		for(int i=1; i<=n/2; i++){
			int w; scanf("%d",&w);
			vector<pi> v;
			for(int j=0; j<n; j+=i){
				if(j + i <= n) v.emplace_back(j, j + i);
			}
			for(int j=0; j<v.size(); ){
				int e = j + 1;
				while(e < v.size() && glcp(v[j].first, v[e].first) >= i) e++;
				int endv = v[e-1].second + glcp(v[j].first, v[e-1].second);
				int stav = v[j].first - glcp_rev(v[j].first, v[j].first + i);
				stav = max(stav, 0);
				endv = min(endv, n);
				if(endv - stav >= 2 * i){
					Union(stav, stav + i, endv - stav - i, w);
				}
				j = e;
			}
		}
		lint ret = 0;
		for(int i=19; i>=0; i--){
			sort(lis[i].begin(), lis[i].end());
			disj.init(n);
			for(auto &j : lis[i]){
				if(disj.uni(j.s, j.e)){
					if(i > 0){
						lis[i-1].push_back({j.s, j.e, j.x});
						lis[i-1].push_back({j.s + (1<<(i-1)), j.e + (1<<(i-1)), j.x});
					}
					else ret += j.x;
				}
			}
		}
		printf("%lld\n", ret);
	}
}
