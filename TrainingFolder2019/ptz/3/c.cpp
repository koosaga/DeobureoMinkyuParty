#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using pi = pair<int, int>;

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
			}
			else low[x] = min(low[x], dfn[i]);
		}
	}
}

vector<int> cmp[MAXN], bcc[MAXN];
int c;

void color(int x, int p){
	if(p){
		cmp[x].push_back(p);
		bcc[p].push_back(x);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

bool cmpr(pi a, pi b){
	return a.first * b.second < b.first * a.second;
}

int col[MAXN];

void dfs2(int x, int c){
	if(col[x]){
		assert(col[x] == c);
		return;
	}
	col[x] = c;
	for(auto &i : gph[x]) dfs2(i, 3 - c);
}

vector<int> ans[MAXN];

void solve(int x, int B, int C){
	sort(ans[bcc[x][0]].begin(), ans[bcc[x][0]].end());
	if(bcc[x].size() % 2 == 0){
		vector<int> oddc;
		for(int j=1; j<=C; j++){
			if(!binary_search(ans[bcc[x][0]].begin(), ans[bcc[x][0]].end(), j)){
				oddc.push_back(j);
	      		if(oddc.size() == B) break;
			}
		}
		assert(oddc.size() == B);
		ans[bcc[x][1]] = oddc;
		for(int i=2; i<bcc[x].size(); i++) ans[bcc[x][i]] = ans[bcc[x][i-2]];
	}
	else{
		int V = bcc[x].size() / 2;
		vector<int> oddc;
		for(int j=1; j<=C; j++){
			if(!binary_search(ans[bcc[x][0]].begin(), ans[bcc[x][0]].end(), j)){
				oddc.push_back(j);
	      		if(oddc.size() == B) break;
			}
		}
		assert(oddc.size() == B);
		ans[bcc[x].back()] = oddc;
		for(int i=1; i<V; i++){
			vector<int> C1, C2, C3;
			bool chk1[4000 + 1] = {};
			bool chk2[4000 + 1] = {};
			for(auto &j : ans[bcc[x][i-1]]) chk1[j] = 1;
			for(auto &j : ans[bcc[x][bcc[x].size() - i]]) chk2[j] = 1;
			for(int k=1; k<=C; k++){
				if(!chk1[k] && !chk2[k]) C3.push_back(k);
				else{
					if(!chk1[k]) C1.push_back(k);
					if(!chk2[k]) C2.push_back(k);
				}
			}
			if(C3.size() > B) C3.resize(B);
			ans[bcc[x][i]] = ans[bcc[x][bcc[x].size()-i-1]] = C3;
			for(auto &j : C1){
				if(ans[bcc[x][i]].size() < B) ans[bcc[x][i]].push_back(j);
			}
			for(auto &j : C2){
				if(ans[bcc[x][bcc[x].size()-i-1]].size() < B) ans[bcc[x][bcc[x].size()-i-1]].push_back(j);
			}
			assert(ans[bcc[x][i]].size() == B);
			assert(ans[bcc[x][bcc[x].size()-i-1]].size() == B);
		}
		int mid = bcc[x].size() / 2;
		bool chk[4000 + 1] = {};
		for(auto &i : ans[bcc[x][mid-1]]) chk[i] = 1;
		for(auto &i : ans[bcc[x][mid+1]]) chk[i] = 1;
		for(int i=1; i<=C; i++){
			if(!chk[i]) ans[bcc[x][mid]].push_back(i);
			if(ans[bcc[x][mid]].size() == B) break;
		}
		assert(ans[bcc[x][mid]].size() == B);
	}
	for(auto &k : bcc[x]){
		if(k == bcc[x][0]) continue;
		for(auto &j : cmp[k]){
			if(j != x){
				solve(j, B, C);
			}
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
	dfs(1, 0);
	color(1, 0);
	pi ret(1e9, 1);
	for(int i=1; i<=1000; i++){
		int ans = 0;
		for(int j=1; j<=c; j++){
			if(bcc[j].size() % 2 == 0) continue;
			int B = i;
			int C = bcc[j].size();
			int ret = 2 * B;
			int div = C / 2;
			ret += (B + div - 1) / div;
			ans = max(ans, ret);
		}
		ret = min(ret, pi(ans, i), cmpr);
	}
	if(ret.first == 0){
		dfs2(1, 1);
		printf("2 1\n");
		for(int i=1; i<=n; i++){
			printf("%d\n", col[i]);
		}
		return 0;
	}
	cout << ret.first << " " << ret.second << endl;
	ans[1].resize(ret.second);
	iota(ans[1].begin(), ans[1].end(), 1);
	for(auto &i : cmp[1]) solve(i, ret.second, ret.first);
	for(int i=1; i<=n; i++){
		for(auto &j : ans[i]) printf("%d ", j);
		puts("");
	}
}
