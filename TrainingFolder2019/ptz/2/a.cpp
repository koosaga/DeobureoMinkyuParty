#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;

int tc;
int n, m;
vector<pi> gph[MAXN];
vector<int> bcc[MAXN], cmp[MAXN];
int dfn[MAXN], low[MAXN], piv, c;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		if(!dfn[i.second]){
			dfs(i.second, x);
			low[x] = min(low[x], low[i.second]);
		}
		else low[x] = min(low[x], dfn[i.second]);
	}
}

void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i.second].size()) continue;
		if(low[i.second] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i.second, c);
		}
		else color(i.second, p);
	}
}

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
};

struct disj{
	int pa[MAXN], cnt[MAXN][2];
	void init(int n, int c){
		iota(pa, pa + n + 1, 0);
		for(int i=1; i<=n; i++){
			cnt[i][0] = cnt[i][1] = 0;
			cnt[i][(i >> c) & 1]++;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int get(int x, int y){
		return cnt[find(x)][y];
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; 
		cnt[p][0] += cnt[q][0];
		cnt[p][1] += cnt[q][1];
		return 1;
	}
}disj;

int main(){
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		map<pi, int> mp;
		for(int i=0; i<m; i++){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			if(s > e) swap(s, e);
			mp[pi(s, e)] = x;
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(x, s);
		}
		piv = c = 0;
		dfs(1, 0);
		color(1, 0);
		vector<edg> drog;
		auto getW = [&](int x, int y){
			if(x > y) swap(x, y);
			return mp[pi(x, y)];
		};
		for(int i=1; i<=c; i++){
			if(bcc[i].size() == 2){
				drog.push_back({bcc[i][0], bcc[i][1], getW(bcc[i][0], bcc[i][1])});
			}
			else{
				pi ret(2e9, -1);
				for(int j=0; j<bcc[i].size(); j++){
					int tmp = getW(bcc[i][j], bcc[i][(j+1)%bcc[i].size()]);
					ret = min(ret, pi(tmp, j));
				}
				for(int j=0; j<bcc[i].size(); j++){
					if(j == ret.second) continue;
					int v = bcc[i][j];
					int w = bcc[i][(j+1)%bcc[i].size()];
					drog.push_back({v, w, ret.first + getW(v, w)});
				}
			}
		}
		sort(drog.begin(), drog.end());
		unsigned long long ret = 0;
		for(int i=0; i<31; i++){
			disj.init(n, i);
			unsigned long long tot = 0;
			for(auto &j : drog){
				int par = (j.x >> i) & 1;
				tot += 1ll * disj.get(j.s, 0) * disj.get(j.e, par ^ 1);
				tot += 1ll * disj.get(j.s, 1) * disj.get(j.e, par);
				disj.uni(j.s, j.e);
			}
			ret += (tot << i);
		}
		cout << ret << endl;
		for(int i=1; i<=n; i++){
			dfn[i] = low[i] = 0;
			bcc[i].clear();
			cmp[i].clear();
			gph[i].clear();
		}
	}
}
