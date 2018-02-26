#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 105;

int n;

int Ask(vector<int> &v){
	printf("? %d", (int)v.size());
	for(auto &i : v) printf(" %d", i);
	puts("");
	fflush(stdout);
	int x;
	scanf("%d",&x);
	return x;
}

#define list hanpil_jazzi

vector<int> gph[MAXN];
vector<int> list[MAXN];
vector<int> L, T;

int mallocc(vector<int> x){
	int cnt[MAXN] = {};
	for(int i=0; i<x.size(); i++){
		for(auto &j : list[x[i]]) cnt[j]++;
	}
	return max_element(cnt, cnt + n + 1) - cnt;
}

void dfs(int cur, vector<int> v){
	for(auto &i : v){
		list[i].erase(find(list[i].begin(),list[i].end(), cur));
	}
	vector<int> nv;
	for(auto &i : v){
		if(list[i].empty()){
			gph[cur].push_back(i);
			gph[i].push_back(cur);
		}
		else nv.push_back(i);
	}
	while(nv.size()){
		int son = mallocc(nv);
		gph[cur].push_back(son);
		gph[son].push_back(cur);
		vector<int> l, r;
		for(auto &i : nv){
			bool fnd = 0;
			for(auto &j : list[i]) if(j == son) fnd = 1;
			if(fnd) l.push_back(i);
			else r.push_back(i);
		}
		dfs(son, l);
		nv = r;
	}
}

int par[MAXN];

void rdfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			rdfs(i, x);
		}
	}
}


void solve(){
	vector<int> X;
	for(int i=1; i<L.size(); i++) X.push_back(L[i]);
	int r = mallocc(X);
	gph[L[0]].push_back(r);
	gph[r].push_back(L[0]);
	dfs(r, X);
}

int main(){
	scanf("%d",&n);
	if(n == 2){
		printf("! 1\n");
		return 0;
	}
	for(int i=1; i<=n; i++){
		vector<int> v;
		for(int j=1; j<=n; j++){
			if(i != j) v.push_back(j);
		}
		int c = Ask(v);
		if(c == n-1){
			L.push_back(i);
		}
		else{
			T.push_back(i);
		}
	}
	for(int i=1; i<L.size(); i++){
		for(int j=0; j<T.size(); j++){
			vector<int> F = {L[0], L[i], T[j]};
			if(Ask(F) == 3) list[L[i]].push_back(T[j]);
		}
	}
	solve();
	rdfs(1, -1);
	printf("!");
	for(int i=2; i<=n; i++) printf(" %d", par[i]);
	puts("");
	fflush(stdout);
}
