#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, v[MAXN], col[MAXN];

struct node{
	pi a, b;
	bool operator<(const node &n)const{
		return abs(a.first - b.first) > abs(n.a.first - n.b.first);
	}
};

map<pi, int> mp;
priority_queue<node> pq;

void add(int p, int e, int x){
	auto pv = pi(e, p);
	if(x == -1){
		mp[pv]--;
		if(mp[pv] == 0) mp.erase(pv);
	}
	else{
		mp[pv]++;
	}
	auto l = mp.lower_bound(pv);
	if(l != mp.end() && next(l) != mp.end()){
		if(l->first.second != next(l)->first.second){
			pq.push({l->first, next(l)->first});
		}
	}
	if(l != mp.begin()){
		if(l->first.second != prev(l)->first.second){
			pq.push({prev(l)->first, l->first});
		}
	}
}

int query(){
	while(!pq.empty()){
		auto l = pq.top();
		if(mp.find(l.a) != mp.end() && mp.find(l.b) != mp.end()){
			break;
		}
		pq.pop();
	}
	auto l = pq.top();
	return abs(l.a.first - l.b.first);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&v[i]);
	}
	disj.init(2*n + 2);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		disj.uni(2*s+1, 2*e);
		disj.uni(2*s, 2*e+1);
	}
	int q; scanf("%d",&q);
	for(int i=1; i<=n; i++){
		if(disj.find(2) == disj.find(2*i)) col[i] = 1;
		add(col[i], v[i], 1);
	}
	for(int i=0; i<q; i++){
		int a, b, c; scanf("%d %d %d",&a,&b,&c);
		if(a == 0){
			add(col[b], v[b], -1);
			v[b] = c;
			add(col[b], v[b], 1);
		}
		else{
			if(disj.find(2) == disj.find(3)){
				puts("0");
				continue;
			}
			if(disj.find(2*b) == disj.find(2*c)){
				puts("0");
				continue;
			}
			else printf("%d\n", query());
		}
	}
}
