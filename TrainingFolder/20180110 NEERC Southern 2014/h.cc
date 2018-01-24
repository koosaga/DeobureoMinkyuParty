#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int n, a[MAXN];

struct node{
	node *p, *l, *r;
	int val, minv, size, mincnt, idx;
	node(int x, int idxv){
		val = x;
		minv = x;
		size = 1;
		mincnt = 1;
		idx = idxv;
		p = l = r = NULL;
	}
}*root;

void push(node *p){}

void pull(node *p){
	p->size = 1;
	p->minv = p->val;
	p->mincnt = 1;
	if(p->l){
		p->size += p->l->size;
		if(p->minv > p->l->minv){
			p->minv = p->l->minv;
			p->mincnt = 0;
		}
		if(p->minv == p->l->minv) p->mincnt += p->l->mincnt;
	}
	if(p->r){
		p->size += p->r->size;
		if(p->minv > p->r->minv){
			p->minv = p->r->minv;
			p->mincnt = 0;
		}
		if(p->minv == p->r->minv) p->mincnt += p->r->mincnt;
	}
}

void rotate(node *x){
	if(!x->p) return;
	push(x->p);
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
	}
	else{
		if(b) b->p = p;
		p->r = b;
		p->p = x;
		x->l = p;
	}
	pull(p);
	pull(x);
}

void splay(node *x){
	while(x->p){
		node *p = x->p;
		node *g = p->p;
		if(g){
			if((p->l == x) ^ (g->l == p))rotate(x);
			else rotate(p);
		}
		rotate(x);
	}
}

void get_minv(node *p){
	while(true){
		if(p->l && p->l->minv == p->minv) p = p->l;
		else if(p->minv == p->val) break;
		else p = p->r;
	}
	splay(p);
}

node *pad(node *p, int L, int R){
	if(p == NULL){
		node *x = new node(a[L], L);
		x->r = new node(a[R], R);
		x->r->p = x;
		pull(x);
		return x;
	}
	else{
		node *lx = p;
		while(lx->l) lx = lx->l;
		splay(lx);
		lx->l = new node(a[L], L);
		lx->l->p = lx;
		pull(lx);
		node *rx = lx;
		while(rx->r) rx = rx->r;
		splay(rx);
		rx->r = new node(a[R], R);
		rx->r->p = rx;
		pull(rx);
		return rx;
	}
}
void getallminv(node *p, vector<node*>& x)
{
	if(!p) return;
	if(p->l && p->l->minv == p->minv) getallminv(p->l, x);
	if(p->minv == p->val) x.push_back(p);
	if(p->r && p->r->minv == p->minv) getallminv(p->r, x);
	return;
}


node *merge(node *l, node *r){
	if(l == NULL) return r;
	if(r == NULL) return l;
	splay(r);
	splay(l);
	node *rr = l;
	while(rr->r) rr = rr->r;
	splay(rr);
	rr->r = r;
	r->p = rr;
	pull(rr);
	return rr;
}

vector<tuple<int, int, int>> ans;

void solve(node *p);

void do_some_shit(vector<node*> &v, int FIRSTMIN, int SECONDMIN){
	if(v.empty()) return;
	vector<int> seq;
	seq.push_back(FIRSTMIN);
	for(int i=0; i<v.size(); i++){
		seq.push_back(v[i]->idx);
	}
	seq.push_back(SECONDMIN);
	node *nxt = NULL;
	for(int i=0; i<v.size(); i++){
		splay(v[i]);
		node *x = v[i]->l;
		if(x) x->p = NULL;
		v[i]->l = NULL;
		nxt = v[i]->r;
		v[i]->r = NULL;
		if(nxt) nxt->p = NULL;
		pad(x, seq[i], seq[i+1]);
		solve(x);
	}
	pad(nxt, seq[seq.size()-2], seq.back());
	if(a[FIRSTMIN] <= a[SECONDMIN]){
		for(int i=1; i<seq.size()-1; i++){
			ans.emplace_back(FIRSTMIN, seq[i], seq[i+1]);
		}	
	}
	else{
		for(int i=1; i<seq.size()-1; i++){
			ans.emplace_back(seq[i-1], seq[i], SECONDMIN);
		}
	}
	solve(nxt);
}

void solve(node *p){
	fprintf(stderr, "%d\n", p->size);
	if(p->size == 2) return;
	get_minv(p);
	if(p->mincnt == 1){
		if(p->l) p->l->p = NULL;
		if(p->r) p->r->p = NULL;
		node *x = merge(p->r, p->l);
		if(x->mincnt == 1){
			get_minv(x);
			if(x->l) x->l->p = NULL;
			if(x->r) x->r->p = NULL;
			vector<node*> v;
			getallminv(x->l, v);
			do_some_shit(v, p->idx, x->idx);
			v.clear();
			getallminv(x->r, v);
			do_some_shit(v, x->idx, p->idx);
		}
		else{
			vector<node*> v;
			getallminv(x, v);
			do_some_shit(v, x->idx, x->idx);
		}
	}
	else if(p->mincnt == 2){
		if(p->r) p->r->p = NULL;
		if(p->l) p->l->p = NULL;
		pull(p);
		get_minv(p->r);
		int FIRSTMIN = p->idx;
		int SECONDMIN = p->r->idx;
		node *t1 = p->l;
		node *t2 = p->r->l;
		node *t3 = p->r->r;
		if(t1) t1->p = NULL;
		if(t2) t2->p = NULL;
		if(t3) t3->p = NULL;
		vector<node*> v;
		getallminv(t2, v);
		if(!v.empty()) do_some_shit(v, FIRSTMIN, SECONDMIN);
		node *x = merge(t3, t1);
		v.clear();
		getallminv(x, v);
		if(!v.empty()) do_some_shit(v, SECONDMIN, FIRSTMIN);
	}
	else{
		vector<node*> v;
		get_minv(p);
		if(p->r) p->r->p = NULL;
		if(p->l) p->l->p = NULL;
		node *x = merge(p->r, p->l);
		getallminv(x, v);
		do_some_shit(v, p->idx, p->idx);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	node *ptr = new node(a[n], n);
	for(int i=n-1; i; i--){
		node *nxt = new node(a[i], i);
		nxt->r = ptr;
		ptr->p = nxt;
		pull(nxt);
		ptr = nxt;
	}
	solve(ptr);
	for(auto &i : ans){
		int x[3];
		tie(x[0], x[1], x[2]) = i;
		sort(x, x+3, [&](const int &p, const int &q){
			return a[p] < a[q];
		});
		i = make_tuple(x[0], x[1], x[2]);
	}
	sort(ans.begin(), ans.end(), [&](const tuple<int, int, int> &fu, const tuple<int, int, int> &ck){
		pair<pair<int, int>, int> x, y;
		tie(x.first.first, x.first.second, x.second) = fu;
		tie(y.first.first, y.first.second, y.second) = ck;
		x.first.first = a[x.first.first];
		x.first.second = a[x.first.second];
		x.second = a[x.second];
		y.first.first = a[y.first.first];
		y.first.second = a[y.first.second];
		y.second = a[y.second];
		return x < y;
	});
	for(auto &i : ans){
		int x, y, z;
		tie(x, y, z) = i;
		printf("%d %d %d\n", x, y, z);
	}
}
