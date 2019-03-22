#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, m, q;
pi edg[MAXN];
int from[MAXN];

struct disj{
	int pa[MAXN], rk[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q, vector<int> &trace){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p;
		sz[p] += sz[q];
		trace.push_back(q);
		if(rk[p] == rk[q]){
			rk[p]++;
			trace.push_back(-p);
		}
		return 1;
	}
	void revert(vector<int> &trace){
		reverse(trace.begin(), trace.end());
		for(auto &i : trace){
			if(i < 0){
				rk[-i]--;
			}
			else{
				sz[pa[i]] -= sz[i];
				pa[i] = i;
			}
		}
	}
}disj;

struct edges{ int s, e, x, y; };
vector<int> v[MAXN];
bool ans[MAXN];
int cnt[MAXN];

void solve(int s, int e, vector<edges> &vv){
	int m = (s + e) / 2;
	vector<edges> l, r;
	vector<int> trace;
	for(auto &i : vv){
		if(i.s <= s && e <= i.e){
			disj.uni(i.x, i.y, trace);
			continue;
		}
		if(i.s <= m) l.push_back(i);
		if(i.e >= m + 1) r.push_back(i);
	}
	if(s == e){
		int cur = disj.find(v[s][0]);
		for(auto &i : v[s]){
			i = disj.find(i);
			cnt[i]++;
		}
		ans[s] = 1;
		for(auto &i : v[s]){
			if(cnt[i] > 0 && cnt[i] != disj.sz[i]){
				ans[s] = 0;
				break;
			}
		}
		for(auto &i : v[s]) cnt[i]--;
	}
	else{
		solve(s, m, l);
		solve(m + 1, e, r);
	}
	disj.revert(trace);
}
int main(){
	vector<edges> qr;
	scanf("%d %d",&n,&q);
	int fuck = 0;
	disj.init(n);
	for(int i=1; i<=q; i++){
		int t; scanf("%d",&t);
		if(t == 3){
			int x;
			scanf("%d",&x);
			v[++m].resize(x);
			for(auto &i : v[m]){
				scanf("%d",&i);
			}
		}
		if(t == 1){
			int u, v; scanf("%d %d",&u,&v);
			edg[++fuck] = pi(u, v);
			from[fuck] = m + 1;
		}
		if(t == 2){
			int x; scanf("%d",&x);
			if(from[x] <= m){
				qr.push_back({from[x], m, edg[x].first, edg[x].second});
			}
			from[x] = 0;
		}	
	}
	for(int i=1; i<=fuck; i++){
		if(from[i] && from[i] <= m){
			qr.push_back({from[i], m, edg[i].first, edg[i].second});
		}
	}
	if(m == 0) return 0;
	solve(1, m, qr);
	for(int i=1; i<=m; i++){
		puts(ans[i] ? "YES" : "NO");
	}
}
