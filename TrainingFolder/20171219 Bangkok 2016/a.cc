#include<bits/stdc++.h>
using namespace std;

const int THRES = 100;
int N, W, Q;
int arr[50010];
int sor[50010];

set<int> bset[510];
deque<int> bdeq[510];
void solve_wbig()
{
	long long res = 0;
	int i, j;

	int maxb = (N-1)/W+1;
	for(i=1;i<=maxb;i++)
	{
		bdeq[i].clear();
	}

	for(i=1;i<=N;i++)
		arr[i] = -arr[i];

	for(i=1;i<=N;i++)
		sor[i] = arr[i];

	sort(sor + 1, sor + N + 1);

	for(i=1;i<=N;i++)
	{
		int b = (i-1)/W + 1;
		bdeq[b].push_back(sor[i]);
		res += 1LL * b * sor[i];
	}

	for(i = 0; i < Q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		y = -y;

		int t = arr[x];
		arr[x] = y;
		if(t == y){
			printf("%lld\n", -res);
			continue;
		}
		int mb = -1;
		for(j=1;j<=maxb;j++)
		{
			if(bdeq[j].front() <= t && t <= bdeq[j].back())
			{
				mb = j;
				break;
			}
		}
		auto it = lower_bound(bdeq[mb].begin(), bdeq[mb].end(), t);
		bdeq[mb].erase(it);
		if(t < y){
			res -= 1ll * t * mb;
			while(mb < maxb && bdeq[mb].back() < y){
				int x = bdeq[mb+1].front();
				bdeq[mb].push_back(x);
				bdeq[mb+1].pop_front();
				res -= x;
				mb++;
			}
			auto it = lower_bound(bdeq[mb].begin(), bdeq[mb].end(), y);
			bdeq[mb].insert(it, y);
			res += 1ll * mb * y;
		}
		else{
			res -= 1ll * t * mb;
			while(mb > 1 && bdeq[mb].front() > y){
				int x = bdeq[mb-1].back();
				bdeq[mb].push_front(x);
				bdeq[mb-1].pop_back();
				res += x;
				mb--;
			}
			auto it = lower_bound(bdeq[mb].begin(), bdeq[mb].end(), y);
			bdeq[mb].insert(it, y);
			res += 1ll * mb * y;
		}
		printf("%lld\n", -res);
	}
}

struct node{
	node *l, *r, *p;
	int sz, key, origin;
	lint sum;
	node(int k, int idx){
		l = r = p = NULL;
		sz = 1;
		key = k;
		origin = idx;
		sum = k;
	}
}*root[THRES + 5];

void push(node *p){

}

void pull(node *p){
	p->sz = 1;
	p->sum = p->key;
	if(p->l){
		p->sz += p->l->sz;
		p->sum += p->l->sum;
	}
	if(p->r){
		p->sz += p->r->sz;
		p->sum += p->r->sum;
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
	if(!x->p) root[x->origin] = x;
}

void splay(node *x){
	while(x->p){
		node *p = x->p;
		node *g = p->p;
		if(g){
			if((p->l == x)^ (g->l == p)) rotate(x);
			rotate(p);
		}
		rotate(x);
	}
}

void insert(node *x, int v){
	while(true){
		if(v <= x->key){
			if(!x->l){
				x->l = new node(v, x->origin);
				x->l->p = x;
				splay(x->l);
				return;
			}
			else x = x->l;
		}
		else{
			if(!x->r){
				x->r = new node(v, x->origin);
				x->r->p = x;
				splay(x->r);
				return;
			}
			else x = x->r;
		}
	}
}

void find(node *x, int v){
	node *y = x;
	while(x){
		if(v == x->key){
			splay(x);
			return;
		}
		y = x;
		if(v < x->key) x = x->l;
		else x = x->r;
	}
	splay(y);
}

int count_low(node *x, int v){
	find(x, v);
	if(x->key > v) return (x->l ? x->l->sz : 0);
	else return (x->l ? x->l->sz : 0) + 1;
}

void remove(node *x){ // find first done
	node *y = x;
	if(!x->l){
		root[x->origin] = x->l;
		x = root[x->origin];
		x->p = NULL;
	}
	else{
		x->l->p = NULL;
		node *p = x->l;
		while(p->r) p = p->r;
		splay(p);
		p->r = x->r;
		x->r->p = p;
		root[p->origin] = p;
	}
	delete y;
}

void kth(node *x, int k){
	while(true){
		int l = (x->l ? x->l->sz : 0);
		if(k <= l){
			x = x->l;
			continue;
		}
		if(k == l + 1){
			splay(x);
			return;
		}
		k -= l + 1;
		x = x->r;
	}
}

void solve_wsmall()
{
	for(int i=0; i<W; i++) root[i] = new node(1e9, i);
	lint res = 0;
	for(int i=0; i<N; i++) sor[i] = -arr[i+1];
	sort(sor, sor + N);
	for(int i=0; i<N; i++) insert(root[i % W], sor[i]);
	lint ans = 0;
	for(int i=0; i<N; i++) ans += 1ll * sor[i] * (i / W +1);
	for(int i = 0; i < Q; i++)
	{
		int X, Y;
		scanf("%d%d", &X, &Y);
		int a = -arr[X];
		int b = -Y;
		arr[X] = Y;
		if(a == b){
			printf("%lld\n", -ans);
			continue;
		}
		int mb = -1;
		int sidx = -1;
		for(int i=0; i<W; i++){
			find(root[i], a);
			if(root[i]->key == a){
				sidx = root[i]->sz * W + i;
				mb = i;
				break;
			}
		}
		int eidx = 0;
		for(int i=0; i<W; i++){
			eidx += count_low(root[i], b);
		}
		if(a < b){
			node *l[THRES + 5];
			node *r[THRES + 5];
			node *m[THRES + 5];
			for(int i=0; i<W; i++){
				int sps = -1;
				int eps = -1;
				if(i > sidx % W){
					sps = sidx / W;
				}
				else sps = sidx / W + 1;
				if(i < eidx % W){
					eps = eidx / W; 
				}
				else{
					eps = eidx / W - 1;
				}
				if(sps > eps){
					m[i] = NULL;
					kth(root[i], sps + 1);
					l[i] = root[i]->l;
					r[i] = root[i];
					r[i]->l = NULL;
					l[i]->p = NULL;
				}
				else{
					kth(root[i], eps + 2);
					node *aux = root[i]->l;
					aux->p = NULL;
					root[i]->l = NULL;
					r[i] = root[i];
					r[i] = aux;
					kth(aux, sps + 1);
					l[i] = aux->l;
					if(l[i]) l[i]->p = NULL;
					aux->l = NULL;
					m[i] = aux;
				}
			}
			find(l[sidx % W], a);
			remove(l[sidx % W]);
			ans -= m[i]->sum;
			int minus1 = (eidx - 1);
			insert(r[minus1 % W], b);
			rotate(m, m+1, m+W);
			for(int i=0; i<W; i++){
				node *ret = r[i];
				if(m[i]){
					node *pred = m[i];
					while(pred->r) pred = pred->r;
					splay(pred);
					pred->r = r[i];
					r[i]->p = pred;
					pull(pred);
				}
				root[i] = r[i];
				splay(
			}
		}
	}
}

void solve()
{
	scanf("%d%d", &N, &W);
	int i;
	for(i=1;i<=N;i++)
		scanf("%d", &arr[i]);
	scanf("%d", &Q);

	if(W > THRES)
		solve_wbig();
	else
		solve_wsmall();
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=1;i<=t;i++)
	{
		printf("Case %d:\n", i);
		solve();
	}
	return 0;
}
