#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

struct disj{
	int pa[MAXN], cnt[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(cnt, cnt + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p != q){
			pa[q] = p;
			cnt[p] += cnt[q];
		}
		cnt[p]++;
	}
}disj;

int n, m;
vector<int> gph[MAXN];

int dfn[MAXN], low[MAXN], piv;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			if(!dfn[i]){
				dfs(i, x);
				low[x] = min(low[x], low[i]);
				if(low[i] > dfn[x]){
					disj.uni(i, x);
				}
			}
			else low[x] = min(low[x], dfn[i]);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	disj.init(n);
	dfs(1, 0);
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(disj.find(i) == i){
			ret += disj.cnt[i] / 2;
		}
	}
	cout << ret << endl;
}
