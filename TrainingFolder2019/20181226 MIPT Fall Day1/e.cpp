#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int MAXM = 105;

struct ans{
	int x, y;
	lint wsum;
	bool operator<(const ans &c)const{
		if(wsum != c.wsum) return wsum < c.wsum;
		return pi(x, y) < pi(c.x, c.y);
	}
}ret;

int n, m;
vector<pi> gph[MAXN];
lint sum[MAXN], tot;
int dfn[MAXN], low[MAXN], piv;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.second != p){
			if(!dfn[i.second]){
				dfs(i.second, x);
				sum[x] += sum[i.second] + i.first;
				low[x] = min(low[x], low[i.second]);
				if(dfn[x] < low[i.second]){
					ret = min(ret, (ans){min(x, i.second), max(x, i.second), 
					abs(tot - 2 * sum[i.second] - i.first)});
				}
			}
			else{
				low[x] = min(low[x], dfn[i.second]);
				if(dfn[x] < dfn[i.second]) sum[x] += i.first;
			}
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	lint sum = 0;
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
		sum += x;
	}
	tot = sum;
	ret = {0, 0, (lint)1e17};
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(i < j.second){
				ret = min(ret, (ans){i, j.second, sum - j.first});
			}
		}
	}
	dfs(1, 0);
	cout << ret.x << " " << ret.y << endl;
}
