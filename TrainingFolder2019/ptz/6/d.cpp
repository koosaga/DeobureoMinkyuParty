#include <bits/stdc++.h>
using namespace std;
using lint = long long;

int flag;

struct node{
	int l, r, d;
	lint sum;
}tree[22000000];
int piv;

int newnode(int arg){
	++piv;
	tree[piv].d = arg;
	return piv;
}

queue<int> que[22];

void init(int s, int e, int p, int *a){
	if(s == e){
		tree[p].sum = a[s];
		return;
	}
	int m = (s + e) / 2;
	tree[p].l = newnode(tree[p].d - 1);
	tree[p].r = newnode(tree[p].d - 1);
	que[tree[p].d].push(p);
	init(s, m, tree[p].l, a);
	init(m+1, e, tree[p].r, a);
	tree[p].sum = tree[tree[p].l].sum + tree[tree[p].r].sum;
}

lint query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s || !p) return 0;
	if(s <= ps && pe <= e) return tree[p].sum;
	int pm = (ps + pe) / 2;
	if((flag >> tree[p].d) & 1)	return query(s, e, ps, pm, tree[p].r) + query(s, e, pm+1, pe, tree[p].l);
	return query(s, e, ps, pm, tree[p].l) + query(s, e, pm+1, pe, tree[p].r);
}

void merge_tree(int dst, int src){
	if(src == 0) return;
	if(tree[dst].l) merge_tree(tree[dst].l, tree[src].l);
	else{
		tree[dst].l = tree[src].l;
		if(tree[dst].l) que[tree[dst].d].push(dst);
	}
	if(tree[dst].r) merge_tree(tree[dst].r, tree[src].r);
	else tree[dst].r = tree[src].r;
	tree[dst].sum += tree[src].sum;
	tree[src].l = tree[src].r = tree[src].sum = 0;
}

void eliminate(int p){
	if(!tree[p].r) tree[p].r = tree[p].l;
	else merge_tree(tree[p].r, tree[p].l);
	tree[p].l = 0;
}

void add(int pos, int s, int e, int p, int v){
	tree[p].sum += v;
	if(s == e) return;
	int m = (s + e) / 2;
	int bit = (flag >> tree[p].d) & 1;
	if(pos <= m){
		if(!bit){
			if(!tree[p].l){
				que[tree[p].d].push(p);
				tree[p].l = newnode(tree[p].d - 1);
			}
			add(pos, s, m, tree[p].l, v);
		}
		else{
			if(!tree[p].r) tree[p].r = newnode(tree[p].d - 1);
			add(pos, s, m, tree[p].r, v);
		}
	}
	else{
		if(bit){
			if(!tree[p].l){
				que[tree[p].d].push(p);
				tree[p].l = newnode(tree[p].d - 1);
			}
			add(pos, m+1, e, tree[p].l, v); 
		}
		else{
			if(!tree[p].r) tree[p].r = newnode(tree[p].d - 1);
			add(pos, m+1, e, tree[p].r, v);
		}
	}
}

void dfs(int p, int d){
	if(d == -1){
		if(p == 0) printf("0");
		else printf("%lld", tree[p].sum);
	}
	else{
		int m = (flag >> d) & 1;
		if(!m){
			printf("[");
			dfs(tree[p].l, d - 1);
			printf("][");
			dfs(tree[p].r, d - 1);
			printf("]");
		}
		else{
			printf("[");
			dfs(tree[p].r, d - 1);
			printf("][");
			dfs(tree[p].l, d - 1);
			printf("]");
		}
		assert(tree[p].sum == tree[tree[p].l].sum + tree[tree[p].r].sum);
	}
}

int n, q, a[1<<19];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<(1<<n); i++) scanf("%d",&a[i]);
	int root = newnode(n - 1);
	init(0, (1<<n) - 1, root, a);
	char buf[10];
	while(q--){
		scanf("%s", buf);
		if(*buf == 's'){ // sum
			int s, e; scanf("%d %d",&s,&e);
			printf("%lld\n", query(s, e, 0, (1<<n)-1, root));
		}
		else if(*buf == 'o'){ // or
			int v; scanf("%d",&v);
			for(int i=n-1; i>=0; i--){
				if((v >> i) & 1){
					while(!que[i].empty()){
						eliminate(que[i].front());
						que[i].pop();
					}
				}
			}
			flag &= ~v;
		}
		else if(*buf == 'x'){ // xor
			int k; scanf("%d",&k); flag ^= k;
		}
		else if(buf[1] == 'n'){ // and	
			int v; scanf("%d",&v);
			v = (~v) & ((1<<n) - 1);
			for(int i=n-1; i>=0; i--){
				if((v >> i) & 1){
					while(!que[i].empty()){
						eliminate(que[i].front());
						que[i].pop();
					}
				}
			}
			flag &= ~v;
			flag ^= v;
		}
		else{ // add
			int x, v;
			scanf("%d %d",&x,&v);
			add(x, 0, (1<<n)-1, root, v);
		}
	//	dfs(root, n - 1); puts("");
	}

}


