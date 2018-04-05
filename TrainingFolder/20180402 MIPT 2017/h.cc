#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;
typedef long long lint;

struct seg{
	int tree[270000];
	int lazy[270000];
	void lazydown(int p, int s, int e){
		if(!lazy[p]) return;
		int m = (s+e)/2;
		tree[2*p] = m - s + 1 - tree[2*p];
		lazy[2*p] ^= 1;
		tree[2*p+1] = e - m - tree[2*p+1];
		lazy[2*p+1] ^= 1;
		lazy[p] = 0;
	}
	void flip(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] = pe - ps + 1 - tree[p];
			lazy[p] ^= 1;
			return;
		}
		lazydown(p, ps, pe);
		int pm = (ps+pe)/2;
		flip(s, e, ps, pm, 2*p);
		flip(s, e, pm+1, pe, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

int n, m, q;
int sx[MAXN], sy[MAXN], ex[MAXN], ey[MAXN];
int xv[MAXN], yv[MAXN];

vector<pi> swp[MAXN];

lint sweep(){
	for(int i=0; i<q; i++){
		swp[sx[i]].push_back(pi(sy[i], ey[i]));
		swp[ex[i] + 1].push_back(pi(sy[i], ey[i]));
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		for(auto &j : swp[i]){
			seg.flip(j.first, j.second, 1, m, 1);
		}
		ret += seg.tree[1];
	}
	return ret;
}

lint f(int x, int y, int n, int m){
	if(n%2==0 && m%2==0)
	{
		return 1LL*(n-x)*y+1LL*(m-y)*x;
	}
	if(n%2==1 && m%2==1)
	{
		if(x==n && y==m) return 0;
		if(x==0 && y==0) return 0;
		return -1;
	}
	else
	{
		if(m%2==0)
		{
			swap(n, m);
			swap(x, y);
		}
		if(x%2==1) return -1;
		else
		{
			if(x==0) return 1LL*(n-x)*y+1LL*(m-y)*x;
			else return -1;
		}
	}
	return 0;
}

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<q; i++){
		scanf("%d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i]);
		if(sx[i] % 2 == ex[i] % 2){
			yv[sy[i]] ^= 1;
			yv[ey[i] + 1] ^= 1;
		}
		if(sy[i] % 2 == ey[i] % 2){
			xv[sx[i]] ^= 1;
			xv[ex[i] + 1] ^= 1;
		}
	}
	for(int i=1; i<=n; i++) xv[i] ^= xv[i-1];
	for(int i=1; i<=m; i++) yv[i] ^= yv[i-1];
	int rowCount = count(xv + 1, xv + n + 1, 1);
	int colCount = count(yv + 1, yv + m + 1, 1);
	lint ret = f(rowCount, colCount, n, m);
	if(ret == -1) cout << -1 << endl;
	else cout << ret + sweep() << endl;
}
