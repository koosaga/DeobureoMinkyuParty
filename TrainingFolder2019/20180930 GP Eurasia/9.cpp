#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const lint MAXC = 4e11;
const lint offset = 1.1e11;

int n;

struct node{
	int l, r;
	int sum1; lint sum2;
}pool[10000000];
int piv;

int newnode(){
	return ++piv;
}

void add(lint pos, lint s, lint e, pi v, int p){
	pool[p].sum1 += v.first;
	pool[p].sum2 += v.second;
	if(s == e) return;
	lint m = (s + e) / 2;
	if(pos <= m){
		if(!pool[p].l) pool[p].l = newnode();
		add(pos, s, m, v, pool[p].l);
	}
	else{
		if(!pool[p].r) pool[p].r = newnode();
		add(pos, m+1, e, v, pool[p].r);
	}
}

pi query(lint pos, lint s, lint e, int p){
	if(p == 0) return pi(0, 0);
	if(s == e) return pi(pool[p].sum1, pool[p].sum2);
	lint m = (s + e) / 2;
	if(pos <= m) return query(pos, s, m, pool[p].l);
	auto y = query(pos, m + 1, e, pool[p].r);
	if(pool[p].l){
		y.first += pool[pool[p].l].sum1;
		y.second += pool[pool[p].l].sum2;
	}
	return y;
}

void add_segment(lint s, lint e, int i){
	s += offset;
	e += offset;
	add(s, 0, MAXC, pi(1, i), 1);
	add(e + 1, 0, MAXC, pi(-1, -i), 1);
}

pi query(lint v){
	return query(v + offset, 0, MAXC, 1);
}

lint input(lint offset){
	double v; scanf("%lf",&v);
	lint ans = (lint)round(1000000.0 * v) + offset * 1000000;
	ans %= 1000000ll * n;
	return ans;
}

int main(){
	scanf("%d",&n);
	lint sums = 0; int q = 0;
	newnode();
	for(int i=0; i<2*n; i++){
		int t; scanf("%d",&t);
		if(t == 0){
			lint s = input(sums);
			lint e = input(0);
			if(e == 0) e = 1000000ll * n;
			add_segment(s - e, s + e, q++);
		}
		else{
			lint v = input(sums);
			auto x = query(v);
			printf("%lld\n", x.first);
			sums += x.second;
			sums %= n;
		}
	}
}
