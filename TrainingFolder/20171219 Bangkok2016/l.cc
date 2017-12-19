#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long lint;

struct edg{ int pos, x, y; };

int n, m;
vector<edg> gph[MAXN];
vector<int> dfn;

lint d1[MAXN], d2[MAXN];
bool vis[MAXN];

void dfs(int x){
	dfn.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(!vis[i.pos]){
			d1[i.pos] = d1[x] + i.x;
			d2[i.pos] = d2[x] + i.y;
			dfs(i.pos);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e, x, y;
		scanf("%d %d %d %d",&s,&e,&x,&y);
		gph[s].push_back({e, x, y});
		gph[e].push_back({s, -x, -y});
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs(i);
			lint xm = 1e18, ym = 1e18;
			for(auto &j : dfn){
				xm = min(xm, d1[j]);
				ym = min(ym, d2[j]);
			}
			for(auto &j : dfn){
				d1[j] -= xm;
				d2[j] -= ym;
			}
		}
	}
	for(int i=1; i<=n; i++) printf("%lld %lld\n", d1[i], d2[i]);
}
