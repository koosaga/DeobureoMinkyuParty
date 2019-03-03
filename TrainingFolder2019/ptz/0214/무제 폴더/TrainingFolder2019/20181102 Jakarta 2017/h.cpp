#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
int n, a[MAXN];
int dep[MAXN], par[17][MAXN], din[MAXN], dout[MAXN], piv;

vector<int> gph[MAXN];
vector<pi> g2[MAXN];
int sub[MAXN], smax[MAXN];
int chk[MAXN];

int dfs2(int x, int p, int c){
	sub[x] = chk[x];
	int ret = 0;
	for(auto &i : g2[x]){
		if(i.second != p){
			ret += dfs2(i.second, x, c);
			sub[x] += sub[i.second];
			ret += min(sub[i.second], c - sub[i.second]) * i.first;
		}
	}
	return ret;
}

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

bool in(int s, int e){ return din[s] <= din[e] && dout[e] <= dout[s]; }

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; 
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	int q; scanf("%d",&q);
	while(q--){
		int c; scanf("%d",&c);
		vector<int> vect(c);
		for(auto &i : vect){
			scanf("%d",&i);
			chk[i]++;
		}
		sort(vect.begin(), vect.end(), [&](int &a, int &b){
			return din[a] < din[b];
		});
		for(int i=0; i<c-1; i++) vect.push_back(lca(vect[i], vect[i + 1]));
		sort(vect.begin(), vect.end(), [&](int &a, int &b){
			return din[a] < din[b];
		});
		vect.resize(unique(vect.begin(), vect.end()) - vect.begin());
		vector<int> stk;
		for(auto &i : vect){
			while(!stk.empty() && !in(stk.back(), i)) stk.pop_back();
			if(!stk.empty()){
				int s = stk.back();
				int e = i;
				int x = dep[e] - dep[s];
				g2[s].emplace_back(x, e);
				g2[e].emplace_back(x, s);
			}
			stk.push_back(i);
		}
		printf("%d\n", dfs2(vect[0], -1, c));
		for(auto &i : vect){
			g2[i].clear();
			chk[i] = 0;
		}
	}
}
