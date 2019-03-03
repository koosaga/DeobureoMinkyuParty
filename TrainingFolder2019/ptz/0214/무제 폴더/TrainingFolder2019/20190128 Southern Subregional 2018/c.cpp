#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
using lint = long long;

int n, m, w;
vector<int> gph[MAXN];
int adj[MAXN][MAXN];

struct item{
	int vtx, num, price;
}a[MAXN];

void bfs(int *dist, int v){
	queue<int> que;
	que.push(v);
	dist[v] = 0;
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(dist[i] > dist[x] + 1){
				que.push(i);
				dist[i] = dist[x] + 1;
			}
		}
	}
}

lint query(int v, int need, int limit){
	lint ret = 0;
	for(int i=0; i<w; i++){
		if(adj[v][a[i].vtx] <= limit){
			ret += 1ll * a[i].price * min(need, a[i].num);
			need -= min(need, a[i].num);
		}
	}
	if(need > 0) return 1e18;
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	memset(adj, 0x3f, sizeof(adj));
	for(int i=1; i<=n; i++) bfs(adj[i], i);
	scanf("%d",&w);
	for(int i=0; i<w; i++){
		scanf("%d %d %d",&a[i].vtx, &a[i].num, &a[i].price);
	}
	sort(a, a + w, [&](const item &a, const item &b){
		return a.price < b.price;
	});
	int q; scanf("%d",&q);
	while(q--){
		int v, r, a;
		scanf("%d %d %d",&v,&r,&a);
		int s = 0, e = n;
		while(s != e){
			int m = (s+e)/2;
			if(query(v, r, m) <= a) e = m;
			else s = m + 1;
		}
		if(s == n) s = -1;
		printf("%d\n", s);
	}
}
