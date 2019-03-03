#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using lint = long long;
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
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m;
set<int> gph[MAXN];
int cnt[MAXN];
vector<pi> E;

int main(){
	scanf("%d %d",&n,&m);
	if(n <= 5){
		puts("0");
		return 0;
	}
	for(int i=0; i<m; i++){
		int x, y; scanf("%d %d",&x,&y);
		x--;
		y--;
		if(x > y) swap(x, y);
		E.emplace_back(x, y);
		gph[x].insert(y);
		gph[y].insert(x);
	}
	sort(E.begin(), E.end());
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<n; i++){
		pq.push(pi(gph[i].size(), i));
	}
	vector<tuple<int, int, int>> tup;
	auto detect_triangle = [&](int x, int y, int z){
		if(!binary_search(E.begin(), E.end(), pi(y, z))) return;
		if(x > y) swap(x, y);
		if(y > z) swap(y, z);
		if(x > y) swap(x, y);
		if(y > z) swap(y, z);
		tup.emplace_back(x, y, z);
		tup.emplace_back(x, z, y);
		tup.emplace_back(y, z, x);
	};
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(gph[x.second].size() != x.first) continue;
		for(auto &v : gph[x.second]){
			for(auto &w : gph[x.second]){
				if(v == w) break;
				detect_triangle(x.second, w, v);
			}
		}
		for(auto &v : gph[x.second]){
			gph[v].erase(x.second);
			pq.push(pi(gph[v].size(), v));
		}
		gph[x.second].clear();
	}
	sort(tup.begin(), tup.end());
	disj.init(n);
	for(int i=1; i<tup.size(); i++){
		int x1, y1, z1, x2, y2, z2;
		tie(x1, y1, z1) = tup[i-1];
		tie(x2, y2, z2) = tup[i];
		if(x1 == x2 && y1 == y2) disj.uni(z1, z2);
	}
	int cmp = 0;
	for(int i=0; i<n; i++){
		cnt[disj.find(i)]++;
		if(disj.find(i) == i){
			cmp++;
		}
	}
	for(auto &i : E){
		if(disj.find(i.first) == disj.find(i.second)){
			puts("0");
			return 0;
		}
	}
	if(cmp != 3){
		puts("0");
		return 0;
	}
	vector<lint> v;
	for(int i=0; i<n; i++) if(cnt[i]) v.push_back(cnt[i]);
	lint ret = v[0] * v[1] + v[1] * v[2] + v[0] * v[2] - m;
	cout << ret << endl;
}
