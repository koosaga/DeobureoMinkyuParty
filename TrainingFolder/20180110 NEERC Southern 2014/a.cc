#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int B = 505;
typedef pair<int, int> pi;

pi a[MAXN];
struct query{ int s, e, x; }b[MAXN];
struct event{ int t, p, v; };
int n, m, q, ret[MAXN];

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		memset(rk, 0, sizeof(rk));
	}
	int find(int x){
		if(pa[x] == x) return x;
		return find(pa[x]);
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p;
		if(rk[p] == rk[q]) rk[p]++;
	}	
	bool uni(int p, int q, vector<event> &rbk){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		rbk.push_back({1, q, pa[q]});
		pa[q] = p;	
		if(rk[p] == rk[q]){
			rbk.push_back({2, p, rk[p]});
			rk[p]++;
		}
	}
	void revert(vector<event> &v){
		reverse(v.begin(), v.end());
		for(auto &i : v){
			if(i.t == 1) pa[i.p] = i.v;
			else rk[i.p] = i.v;
		}
		v.clear();
	}
}disj;

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<m; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<q; i++){
		scanf("%d %d",&b[i].s,&b[i].e);
		b[i].s--; b[i].e--;
		b[i].x = i;
	}
	sort(b, b + q, [&](const query &a, const query &b){
		return pi(a.s / B, a.e) < pi(b.s / B, b.e);
	});
	int ptr = 0;
	for(int i=0; i<m; i+=B){
		int s = i, e = i + B;
		vector<query> w;
		while(ptr < q && b[ptr].s / B == i / B){
			w.push_back(b[ptr++]);
		}
		disj.init(2 * n);
		for(auto &j : w){
			if(j.e < i + B){
				ret[j.x] = 1;
				vector<event> rbk;
				for(int k=j.s; k<=j.e; k++){
					disj.uni(a[k].first, a[k].second + n, rbk);
					disj.uni(a[k].first + n, a[k].second, rbk);
					if(disj.find(a[k].first) == disj.find(a[k].first + n)){
						ret[j.x] = 0;
					}
				}
				disj.revert(rbk);
			}
		}
		int ptr = e;
		bool ok = 1;
		for(auto &j : w){
			if(j.e >= i + B){
				while(ptr <= j.e){
					disj.uni(a[ptr].first, a[ptr].second + n);
					disj.uni(a[ptr].first + n, a[ptr].second);
					if(disj.find(a[ptr].first) == disj.find(a[ptr].first + n)){
						ok = 0;
					}
					ptr++;
				}
				if(ok == 0){
					ret[j.x] = 0;
					continue;
				}
				vector<event> rbk;
				ret[j.x] = 1;
				for(int k=i+B-1; k>=j.s; k--){
					disj.uni(a[k].first, a[k].second + n, rbk);
					disj.uni(a[k].first + n, a[k].second, rbk);
					if(disj.find(a[k].first) == disj.find(a[k].first + n)){
						ret[j.x] = 0;
						break;
					}
				}
				disj.revert(rbk);
			}
		}
	}
	for(int i=0; i<q; i++) puts(ret[i] ? "Possible" : "Impossible");
}
