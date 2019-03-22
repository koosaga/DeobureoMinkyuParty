#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;
using pi = pair<lint, int>;

int n;
int a[MAXN], b[MAXN], c[MAXN];
lint dist[MAXN];
vector<pi> gph[MAXN];

void add_edge(int s, int e, int x){
	gph[s].emplace_back(x, e);
	gph[e].emplace_back(x, s);
}

lint solve(){
	for(int i=1; i<=n; i++){
		int l = 2 * i, r = 2 * i + 1;
		add_edge(0, l, a[i]);
		add_edge(r, 1, b[i]);
		add_edge(l, r, c[2*i]);
		if(i < n) add_edge(l, r + 2, c[2*i+1]);
	}
	add_edge(1, 3, c[1]);
	add_edge(0, 2*n, c[2*n+1]);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	dist[0] = 0;
	pq.emplace(0, 0);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		if(x.second == 1) return x.first;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > x.first + i.first){
				dist[i.second] = x.first + i.first;
				pq.emplace(dist[i.second], i.second);
			}
		}
	}
	assert(0);
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		for(int i=1; i<=n; i++) scanf("%d",&b[i]);
		for(int i=1; i<=n+n+1; i++) scanf("%d",&c[i]);
		for(int i=0; i<=2*n+3; i++){
			gph[i].clear(); dist[i] = 1e18;
		}
		printf("%lld\n", solve());
	}
}
