#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
using pi = pair<int, int>;
using lint = long long;
#define data SEX

struct data{
	// trivial
	lint l, r;
	int s;
	// upward
	int lc, rc;
	lint cnt;
	// downward
	int ld, rd;
	lint dnt;
};

data make(lint v){
	return (data){v, v, 1, 1, 1, 1, 1, 1, 1};
}

data merge(data a, data b){
	data c;
	// easy infos
	c.l = a.l;
	c.r = b.r;
	c.s = a.s + b.s;
	// upward merges
	c.lc = (a.lc == a.s && a.r < b.l ? (a.lc + b.lc) : a.lc);
	c.rc = (b.rc == b.s && a.r < b.l ? (b.rc + a.rc) : b.rc);
	c.cnt = a.cnt + b.cnt + (a.r < b.l ? (1ll * a.rc * b.lc) : 0ll);
	// downward merges
	c.ld = (a.ld == a.s && a.r > b.l ? (a.ld + b.ld) : a.ld);
	c.rd = (b.rd == b.s && a.r > b.l ? (a.rd + b.rd) : b.rd);
	c.dnt = a.dnt + b.dnt + (a.r > b.l ? (1ll * a.rd * b.ld) : 0ll);
	return c;
}

data reverse(data a){
	swap(a.l, a.r);
	swap(a.cnt, a.dnt);
	swap(a.lc, a.rd);
	swap(a.rc, a.ld);
	return a;
}

data increase(data a, lint k){
	a.l += k;
	a.r += k;
	return a;
}

struct node{
	node *l, *r, *p;
	int cnt, lazy;
	lint ladd;
	data myData, Data;
	node(int v){
		l = r = p = NULL;
		myData = Data = make(v);
		lazy = ladd = 0;
		cnt = 1;
	}
}*nd[MAXN], *root;

void push(node *p){
	if(p->lazy){
		swap(p->l, p->r);
		if(p->l){
			p->l->lazy ^= 1;
			p->l->Data = reverse(p->l->Data);
		}
		if(p->r){
			p->r->lazy ^= 1;
			p->r->Data = reverse(p->r->Data);
		}
		p->lazy = 0;
	}
	if(p->ladd){
		if(p->l){
			p->l->ladd += p->ladd;
			p->l->Data = increase(p->l->Data, p->ladd);
			p->l->myData = increase(p->l->myData, p->ladd);
		}
		if(p->r){
			p->r->ladd += p->ladd;
			p->r->Data = increase(p->r->Data, p->ladd);
			p->r->myData = increase(p->r->myData, p->ladd);
		}
		p->ladd = 0;
	}
}

void pull(node *x){
	x->cnt = 1;
	x->Data = x->myData;
	if(x->l){
		x->cnt += x->l->cnt;
		x->Data = merge(x->l->Data, x->Data);
	}
	if(x->r){
		x->cnt += x->r->cnt;
		x->Data = merge(x->Data, x->r->Data);
	}
}

void rotate(node *x){
	if(!x->p) return;
	push(x->p);  // if there's lazy stuff
	push(x);
	node *p = x->p;
	bool is_left = (p->l == x);
	node *b = (is_left ? x->r : x->l);
	x->p = p->p;
	if(x->p && x->p->l == p) x->p->l = x;
	if(x->p && x->p->r == p) x->p->r = x;
	if(is_left){
		if(b) b->p = p;
		p->l = b;
		p->p = x;
		x->r = p;
	} else{
		if(b) b->p = p;
		p->r = b;
		p->p = x;
		x->l = p;
	}
	pull(p); // if there's something to pull up
	pull(x);
	if(!x->p) root = x; // IF YOU ARE SPLAY TREE
}

void splay(node *x){
	while(x->p){
		node *p = x->p;
		node *g = p->p;
		if(g){
			if((p->l == x) ^ (g->l == p)) rotate(x);
			else rotate(p);
		}
		rotate(x); 
	}
}

void reroot(int k){
	node *v = root;
	while(true){
		push(v);
		if(v->l && v->l->cnt >= k){
			v = v->l;
			continue;
		}
		if(v->l) k -= v->l->cnt;
		if(k == 1){
			break;
		}
		k -= 1;
		assert(v->r);
		v = v->r;
	}
	splay(v);
}

void dfs(node *p){
	push(p);
	if(p->l){
		printf("[");
		dfs(p->l);
		printf("]");
	}
	printf("%lld", p->myData.l);
	if(p->r){
		printf("[");
		dfs(p->r);
		printf("]");
	}
	pull(p);
}
void solve(){
	int n, q;
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		nd[i] = new node(x);
	}
	nd[0] = new node(0);
	nd[n+1] = new node(0);
	for(int i=n; i>=0; i--){
		nd[i]->r = nd[i+1];
		nd[i+1]->p = nd[i];
		pull(nd[i]);
	}
	root = nd[0];
//	dfs(root); puts("");
	char buf[10];
	auto reverse_on_node = [&](node *pos){
		pos->lazy ^= 1;
		pos->Data = reverse(pos->Data);
		splay(pos);
	};
	auto add_on_node = [&](node *pos, int v){
		pos->ladd += v;
		pos->Data = increase(pos->Data, v);
		pos->myData = increase(pos->myData, v);
		splay(pos);
	};
	while(q--){
		scanf("%s", buf);
		int l, r; scanf("%d %d",&l,&r);
		if(*buf == 'R'){
			reroot(r + 2);
			auto tmp = root;
			root->l->p = NULL;
			root = root->l;
			reroot(l);
			reverse_on_node(root->r);
			tmp->l = root;
			root->p = tmp;
			root = tmp;
			pull(root);
		}
		else{
			int v; scanf("%d", &v);
			reroot(r + 2);
			auto tmp = root;
			root->l->p = NULL;
			root = root->l;
			reroot(l);
			add_on_node(root->r, v);
			tmp->l = root;
			root->p = tmp;
			root = tmp;
			pull(root);
		}
		reroot(n + 2);
		auto tmp = root;
		root->l->p = NULL;
		root = root->l;
		reroot(1);
		printf("%lld\n", root->r->Data.cnt);
			pull(root);
			tmp->l = root;
			root->p = tmp;
			root = tmp;
			pull(root);
	//		dfs(root); puts("");
	}
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		solve();
	}
}
