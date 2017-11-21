#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;

int n, par[MAXN], pth[MAXN];
vector<int> gph[MAXN];
int X[MAXN], Z[MAXN];
int dep[MAXN], mxd[MAXN];

void dfs2(int x, int p){
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		dep[i] = dep[x] + 1;
		dfs2(i, x);
		mxd[x] = max(mxd[x], mxd[i]);
	}
	mxd[x] = max(mxd[x], dep[x]);
	vector<int> gs;
	int leaf = 0;
	for(auto &i : gph[x]){
		if(pth[i] || i == p) continue;
		if(mxd[i] >= mxd[x] + 2){
			gs.push_back(i);
		}
		else leaf++;
	}
	if(gs.empty()) X[x] = 1;
	if(gs.size() == 1){
		X[x] = X[gs[0]];
		Z[x] = (leaf > 0 && X[gs[0]]);
	}
	if(gs.size() == 2){
		Z[x] = (X[gs[0]] && X[gs[1]]);
	}
}

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

int in0[MAXN], in1[MAXN], out0[MAXN], out1[MAXN], ok[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	vector<int> v;
	for(int j=n; j!=1; j=par[j]) v.push_back(j);
	v.push_back(1);
	reverse(v.begin(), v.end());
	for(auto &i : v) pth[i] = 1;
	if(gph[1].size() == 1){
		out0[1] = out1[1] = 1;
	}
	else{
		out1[1] = 1;
	}
	for(int i=1; i<v.size(); i++){
		in0[v[i]] = out0[v[i-1]] || out1[v[i-1]];
		in1[v[i]] = out0[v[i-1]];
		for(auto &j : gph[v[i]]) if(!pth[j]) ok[v[i]] = 1;
		if(!ok[v[i]]){
			out0[v[i]] = out1[v[i]] = (in0[v[i]] || in1[v[i]]);
		}
		else{
			dfs2(v[i], -1);
			if(X[v[i]]) out1[v[i]] |= in0[v[i]];
			if(X[v[i]]) out0[v[i]] |= in1[v[i]];
			if(Z[v[i]]) out1[v[i]] |= in1[v[i]];
		}
	}
	if(!out0[n]){
		puts("BRAK");
	}
	else{
		puts("TAK");
	}
}
