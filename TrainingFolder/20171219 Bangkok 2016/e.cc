#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int MAXC = 100000;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	node *l, *r;
	int sum;
	node(){
		l = r = NULL;
		sum = 0;
	}
}*nd[MAXN];

void init(node *p, int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	p->l = new node();
	p->r = new node();
	init(p->l, s, m);
	init(p->r, m+1, e);
}

void update(int s, int e, int x, node *p, node *c){
	if(s == e){
		c->sum = p->sum + 1;
		return;
	}
	int m = (s+e)/2;
	if(x <= m){
		c->l = new node();
		c->r = p->r;
		update(s, m, x, p->l, c->l);
	}
	else{
		c->l = p->l;
		c->r = new node();
		update(m+1, e, x, p->r, c->r);
	}
	c->sum = c->l->sum + c->r->sum;
}

vector<pi> gph[MAXN];
int n, dep[MAXN], par[16][MAXN];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dep[i.second] = dep[x] + 1;
		par[0][i.second] = x;
		update(1, MAXC, i.first, nd[x], nd[i.second]);
		dfs(i.second, x);
	}
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<16; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=15; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int bs(node *a, node *b, node *c, int s, int e, int k){
	if(s == e) return s;
	int m = (s+e)/2;
	int leftsum = a->l->sum + b->l->sum - 2 * c->l->sum;
	if(k <= leftsum) return bs(a->l, b->l, c->l, s, m, k);
	return bs(a->r, b->r, c->r, m+1, e, k - leftsum);
}


int solve(int s, int e, int l, int x){
	return bs(nd[s], nd[e], nd[l], 1, MAXC, x);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		for(int i=0; i<MAXN; i++) gph[i].clear();
		scanf("%d",&n);
		for(int i=2; i<=n; i++){
			int u, v, w;
			scanf("%d %d %d",&u,&v,&w);
			gph[u].push_back(pi(w, v));
			gph[v].push_back(pi(w, u));
		}
		for(int i=1; i<=n; i++){
			nd[i] = new node();
		}
		init(nd[1], 1, MAXC);
		dfs(1, -1);
		for(int i=1; i<16; i++){
			for(int j=1; j<=n; j++){
				par[i][j] = par[i-1][par[i-1][j]];
			}
		}
		int q; scanf("%d",&q);
		while(q--){
			int s, e;
			scanf("%d %d",&s,&e);
			int l = lca(s, e);
			int d = dep[s] + dep[e] - 2 * dep[l];
			if(d % 2 == 1){
				printf("%d.0\n", solve(s, e, l, d/2 + 1));
			}
			else{
				int sum = solve(s, e, l, d/2)+ solve(s, e, l, d/2+1);
				printf("%d.%d\n", sum / 2, 5 * (sum % 2));
			}
		}
	}
}
