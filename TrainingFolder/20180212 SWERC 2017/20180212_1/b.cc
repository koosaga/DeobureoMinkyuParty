#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, a[MAXN][MAXN];
int t[MAXN];

struct seg{
	pi tree[4100];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 4100, pi(1e9, -1));
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
		pi ret(1e9, -1);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

lint ans[MAXN][MAXN];

void solve(int s, int e){
	if(s > e) return;
	pi m = seg.query(s, e);
	solve(s, m.second - 1);
	solve(m.second + 1, e);
	int l = m.second - s, r = e - m.second;
	if(l > r) swap(l, r);
	ans[1][1] += 1;
	ans[1][1 + l + 1] -= 1;
	ans[1][r + 2] -= 1;
	ans[1][l + r + 3] += 1;
	ans[m.first+1][1] -= 1;
	ans[m.first+1][1+l+1] += 1;
	ans[m.first+1][r+2] += 1;
	ans[m.first+1][l+r+3] -= 1;
}

int main(){
	int k, q;
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i=0; i<k; i++){
		int sx, ex, sy, ey;
		scanf("%d %d %d %d",&sx,&ex,&sy,&ey);
		for(int i=sx; i<ex; i++){
			for(int j=sy; j<ey; j++){
				a[i][j] = 1;
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j]) t[j] = 0;
			else t[j]++;
		}
		seg.init(m, t);
		solve(0, m-1);
	}
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++) ans[j][i] += ans[j-1][i];
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			ans[i][j] += ans[i][j-1];
		}
		for(int j=1; j<=m; j++){
			ans[i][j] += ans[i][j-1];
		}
	}
	// preprocess
	while(q--){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%lld\n", ans[x][y]);
	}
}
