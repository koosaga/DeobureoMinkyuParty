#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 15555;

struct node{
	int val;
	node *l, *r;
	node(int v){
		val = v;
	}
	node(node *vl, node *vr){
		val = -1;
		l = vl;
		r = vr;
	}
};

struct rect{
	node *n0, *n1, *n2, *n3;
	rect(node *v0, node *v1, node *v2, node *v3){
		n0 = v0;
		n1 = v1;
		n2 = v2;
		n3 = v3;
	}
};

struct disj{
	int pa[MAXN];
	void init(){
		iota(pa, pa + MAXN, 0);
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

vector<int> v;

void Compare(node *l, node *r){
	if(l->val == -1 && r->val == -1){
		Compare(l->l, r->l);
		Compare(l->r, r->r);
	}
	if(l->val != -1 && r->val == -1){
		Compare(l, r->l);
		Compare(l, r->r);
	}
	if(l->val == -1 && r->val != -1){
		Compare(l->l, r);
		Compare(l->r, r);
	}
	if(l->val != -1 && r->val != -1){
		if(v[l->val] && v[r->val]) disj.uni(l->val, r->val);
	}
}

rect DFS(){
	int x;
	scanf("%d",&x);
	if(x != 2){
		v.push_back(x);
		node *t = new node(v.size() - 1);
		return rect(t, t, t, t);
	}
	else{
		auto l1 = DFS();
		auto l2 = DFS();
		auto l4 = DFS();
		auto l3 = DFS();
		rect ret(new node(l1.n0, l2.n0),
				 new node(l1.n1, l3.n1),
				 new node(l2.n2, l4.n2),
				 new node(l3.n3, l4.n3));
		Compare(l1.n2, l2.n1);
		Compare(l1.n3, l3.n0);
		Compare(l2.n3, l4.n0);
		Compare(l3.n2, l4.n1);
		return ret;
	}
}

int main(){
	disj.init();
	DFS();
	vector<int> pos;
	int ans = 0;
	for(int i=0; i<v.size(); i++) if(v[i]) pos.push_back(i);
	for(int i=0; i<pos.size(); i++){
		if(disj.find(pos[i]) == pos[i]) ans++;
	}
	cout << ans << endl;
}
