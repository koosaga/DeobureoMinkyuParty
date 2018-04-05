#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 530000;
const int MAXM = 530000;

struct seg{
	int l, r, p, idx, c;
	bool operator<(const seg &s)const{
		return p < s.p;
	}
}a[MAXN];

struct str_conn{
	vector<int> gph[MAXM];
	vector<int> rev[MAXM];
	vector<int> dfn;
	int vis[MAXN], comp[MAXN];
	void add_edge(int s, int e){
		gph[s].push_back(e);
		rev[e].push_back(s);
	}
	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		for(auto &i : gph[x]) dfs(i);
		dfn.push_back(x);
	}
	void rdfs(int x, int p){
		if(comp[x]) return;
		comp[x] = p;
		for(auto &i : rev[x]) rdfs(i, p);
	}
	int solve(int n){
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		int piv = 0;
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
		return piv;
	}
}scc;

int n, q;

struct segtree{
	int tree[530000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<lim; i++) tree[i] = i + n;
		for(int i=0; i<n; i++) tree[i + lim] = i;
		for(int i=2; i<n+lim; i++){
			scc.add_edge(tree[i/2], tree[i]);
		}
	}
	void add(int s, int e, int pos){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) scc.add_edge(pos, tree[s++]);
			if(e%2 == 0) scc.add_edge(pos, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) scc.add_edge(pos, tree[s]);
	}
}segfuck;

int rev[MAXN];
int blk[MAXN];

int indeg[MAXM];
vector<int> gph[MAXM];
multiset<int> s[MAXM];
lint ans = 0;

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i].p);
		int r;
		scanf("%d",&r);
		a[i].l = a[i].p - r;
		a[i].r = a[i].p + r;
		a[i].idx = i + 1;
		scanf("%d",&a[i].c);
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		seg x = {-1, -1, a[i].l, -1, -1};
		seg y = {-1, -1, a[i].r, -1, -1};
		a[i].l = lower_bound(a, a+n, x) - a;
		a[i].r = upper_bound(a, a+n, y) - a - 1;
		rev[a[i].idx] = i;
	}
	segfuck.init(n);
	for(int i=0; i<n; i++){
		segfuck.add(a[i].l, a[i].r, i);
	}
	int k = scc.solve(530000-2);
	for(int i=0; i<n; i++) blk[scc.comp[i]] = 1;
	for(int i=0; i<530000-2; i++){
		for(auto &j : scc.gph[i]){
			if(scc.comp[i] != scc.comp[j]){
				gph[scc.comp[i]].push_back(scc.comp[j]);
				indeg[scc.comp[j]]++;
			}
		}
	}
	queue<int> que;
	for(int i=1; i<=k; i++){
		if(indeg[i] == 0 && !blk[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &j : gph[x]){
			indeg[j]--;
			if(indeg[j] == 0 && !blk[j]) que.push(j);
		}
	}
	for(int i=0; i<n; i++){
		if(indeg[scc.comp[i]] == 0){
			s[scc.comp[i]].insert(a[i].c);
		}
	}
	lint ans = 0;
	for(int i=0; i<MAXM; i++){
		if(s[i].size()) ans += *s[i].begin();
	}
	while(q--){
		int x, v;
		scanf("%d %d",&x,&v);
		x = rev[x];
		if(indeg[scc.comp[x]] == 0){
			ans -= *s[scc.comp[x]].begin();
			s[scc.comp[x]].erase(s[scc.comp[x]].find(a[x].c));
			s[scc.comp[x]].insert(a[x].c = v);
			ans += *s[scc.comp[x]].begin();
		}
		printf("%lld\n", ans);
	}
}
