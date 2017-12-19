#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long lint;

vector<int> gph[MAXN];
int n, din[MAXN], dout[MAXN], piv;

void dfs(int x){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
	dout[x] = piv;
}

bool sub(int x, int y){
	return din[x] <= din[y] && dout[y] <= dout[x];
}

int solve(int r, int x){
	if(r == x) return n;
	if(!sub(x, r)) return dout[x] - din[x] + 1;
	auto l = --upper_bound(gph[x].begin(), gph[x].end(), r, [&](const int &a, const int &b){
		return din[a] < din[b];
	});
	return n - (dout[*l] - din[*l] + 1);
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		piv = 0;
		int q, r;
		for(int i=0; i<MAXN; i++) gph[i].clear();
		scanf("%d %d",&n,&q);
		scanf("%d",&r);
		for(int i=0; i<n-1; i++){
			int s, e;
			scanf("%d %d",&s,&e);
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		dfs(1);
		printf("Case #%d:\n", i);
		while(q--){
			int x, y;
			scanf("%d %d",&x,&y);
			if(x == 0) r = y;
			else{
				printf("%d\n", solve(r, y));
			}
		}
	}
}
