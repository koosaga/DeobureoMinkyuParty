#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using pi = pair<int, int>;

struct node{
	int l, r, v;
}tree[40000000];
int piv;

int newnode(int x){
	piv++;
	tree[piv].v = x;
	return piv;
}

void lazydown(int p){
	if(!tree[p].v) return;
	tree[p].l = newnode(tree[p].v);
	tree[p].r = newnode(tree[p].v);
	tree[p].v = 0;
}

void dfs(int s, int e, int ps, int pe, int p1, int p2){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		swap(tree[p1], tree[p2]);
		return;
	}
	lazydown(p1);
	lazydown(p2);
	int pm = (ps + pe) / 2;	
	dfs(s, e, ps, pm, tree[p1].l, tree[p2].l);
	dfs(s, e, pm+1, pe, tree[p1].r, tree[p2].r);
}

int walk(int s, int e, int pos, int p){
	if(tree[p].v) return tree[p].v;
	int m = (s + e) / 2;
	if(pos <= m) return walk(s, m, pos, tree[p].l);
	else walk(m + 1, e, pos, tree[p].r);
}

int n, m;
pi a[MAXN];
char buf[5];
int root[MAXN];
int rep[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=m; i++){
		scanf("%d",&a[i].first);
	}
	int q, x;
	scanf("%d",&q);
	for(int i=1; i<=m; i++) a[i].second = q;
	for(int i=0; i<q; i++){
		scanf("%s %d",buf,&x);
		if(*buf == 'A'){
			a[x].second = i;
		}
		else{
			rep[i] = x;
		}
	}
	for(int i=1; i<=n; i++){
		root[i] = newnode(i);
	}
	for(int i=m; i; i--){
		if(a[i].second == q){
			swap(root[a[i].first], root[a[i].first + 1]);
		}
		else{
			dfs(0, a[i].second, 0, q - 1, root[a[i].first], root[a[i].first + 1]);
		}
	}
	for(int i=0; i<q; i++){
		if(rep[i]){
			printf("%d\n", walk(0, q - 1, i, root[rep[i]]));
		}
	}
}
