#include <bits/stdc++.h>
using namespace std;
const int MAXC = 1000000000;
using lint = long long;
using pi = pair<int, int>;

struct node{
	int l, r, sum, minsuf;
}tree[23000000];
int piv;
int newnode(){ return ++piv; }

void merge(int p){
	if(tree[p].l == 0){
		tree[p].sum = tree[tree[p].r].sum;
		tree[p].minsuf = tree[tree[p].r].minsuf;
	}
	else if(tree[p].r == 0){	
		tree[p].sum = tree[tree[p].l].sum;
		tree[p].minsuf = tree[tree[p].l].minsuf;
	}
	else{
		int x = tree[p].l;
		int y = tree[p].r;
		tree[p].sum = tree[x].sum + tree[y].sum;
		tree[p].minsuf = min(tree[y].minsuf, tree[y].sum + tree[x].minsuf);
	}
}

void add_node(int x, int s, int e, int p, int v){
	if(s == e){
		tree[p].sum += v;
		tree[p].minsuf = min(0, tree[p].sum);
		return;
	}
	int m = (s + e) / 2;
	if(x <= m){
		if(!tree[p].l) tree[p].l = newnode();
		add_node(x, s, m, tree[p].l, v);
	}
	else{
		if(!tree[p].r) tree[p].r = newnode();
		add_node(x, m+1, e, tree[p].r, v);
	}
	merge(p);
}

int query_sum(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return 0;
	if(s <= ps && pe <= e) return tree[p].sum;
	int pm = (ps + pe) / 2;
	int ret = 0;
	if(tree[p].l) ret += query_sum(s, e, ps, pm, tree[p].l);
	if(tree[p].r) ret += query_sum(s, e, pm+1, pe, tree[p].r);
	return ret;
}

pi query_min(int s, int e, int ps, int pe, int p){
	if(p == 0) return pi(0, 0);;
	if(e < ps || pe < s) return pi(0, 0);
	if(s <= ps && pe <= e) return pi(tree[p].minsuf, tree[p].sum);
	int pm = (ps + pe) / 2;
	auto l = query_min(s, e, ps, pm, tree[p].l);
	auto r = query_min(s, e, pm+1, pe, tree[p].r);
	return pi(min(r.first, l.first + r.second), l.second + r.second);
}

int left_min_pos(int pos, int ps, int pe, int p, int v){
	int s = 0, e = pos;
	while(s != e){
		int m = (s+e+1)/2;
		if(query_min(m, pos, 1, MAXC, p).first <= v) s = m;
		else e = m - 1;
	}
	return s;
}

int root1, root2;
char buf[50];
map<int, int> mp, ty;

int main(){
	int q;
	scanf("%d",&q);
	root1 = newnode();
	root2 = newnode();
	auto REM = [&](int x){
		if(ty[x] == 1) add_node(x, 1, MAXC, root1, +1);
		if(ty[x] == 2) add_node(x, 1, MAXC, root2, +1);
		if(ty[x] == 3) add_node(x, 1, MAXC, root1, -1);
		if(ty[x] == 4) add_node(x, 1, MAXC, root2, -1); 
		mp.erase(x);
		ty.erase(x);
	};
	while(q--){
		int x; scanf("%d %s",&x,buf);
		if(*buf == '-'){
			REM(x);
			puts("0 0");
		}
		else if(*buf == '?'){
			int sum = query_sum(1, x, 1, MAXC, root1) + query_sum(1, x, 1, MAXC, root2);
			assert(sum <= 0);
			if(sum < 0) sum = -sum;
			if(sum == 0) puts("-1 -1");
			else{
				auto itr = mp.upper_bound(x);
				int ansf = -1, ansb = -1;
				{
					int q1 = left_min_pos(x, 1, MAXC, root1, -1);
					int q2 = left_min_pos(x, 1, MAXC, root2, -sum);
					ansf = mp[max(q1, q2)];
				}
				{
					int q1 = left_min_pos(x, 1, MAXC, root1, -sum);
					int q2 = left_min_pos(x, 1, MAXC, root2, -1);
					ansb = mp[max(q1, q2)];
				}
				printf("%d %d\n", ansf, ansb);
			}
		}
		else{
			string s = buf;
			if(s == "push_front"){
				int v; scanf("%d",&v);
				mp[x] = v;
				ty[x] = 1;
				add_node(x, 1, MAXC, root1, -1);
			}
			if(s == "push_back"){
				int v; scanf("%d",&v);
				mp[x] = v;
				ty[x] = 2;
				add_node(x, 1, MAXC, root2, -1);
			}
			if(s == "pop_front"){
				mp[x] = -1;
				ty[x] = 3;
				add_node(x, 1, MAXC, root1, +1);
			}
			if(s == "pop_back"){
				mp[x] = -1;
				ty[x] = 4;
				add_node(x, 1, MAXC, root2, +1);
			}
			puts("0 0");
		}
		fflush(stdout);
	}
}
