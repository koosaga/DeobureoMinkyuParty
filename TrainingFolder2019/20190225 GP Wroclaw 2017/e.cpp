#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 530000;
const int MAXM = 1000005;
using lint = long long;
using pi = pair<lint, int>;

struct seg{
	lint tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, 1e18);
	}
	void push(int s, int e, lint x){
		if(s > e) return;
		s += lim;
		e += lim;
		while(s < e){
			if(s % 2 == 1){
				tree[s] = min(tree[s], x);
				s++;
			}
			if(e % 2 == 0){
				tree[e] = min(tree[e], x);
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s] = min(tree[s], x);
	}
	lint query(int x){
		x += lim;
		lint ret = 1e18;
		while(x){
			ret = min(ret, tree[x]);
			x >>= 1;
		}
		return ret;
	}
}seg1, seg2;

struct edg{
	int cst, pos, idx;
};

vector<edg> gph[MAXN];
vector<pi> tgph[MAXN];
vector<int> tr[MAXN];
vector<tuple<int, int, int>> edg_list[MAXN];
vector<int> vtx_list[MAXN];
int n, m;
int lbl[MAXN], key[MAXN];
lint dist[MAXN], rdist[MAXN];
lint tr_dist[MAXN];
int par[MAXN], pae[MAXN];

lint exclude(int p){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(auto &i : vtx_list[p]){
		tr_dist[i] = 1e18;
		for(auto &j : gph[i]){
			if(key[lbl[j.pos]] < p){
				tr_dist[i] = min(tr_dist[i], dist[j.pos] + j.cst);
			}
		}
		pq.emplace(tr_dist[i], i);
	}
	for(auto &i : edg_list[p]){
		int s, e, x; tie(s, e, x) = i;
		tgph[s].emplace_back(x, e);
		tgph[e].emplace_back(x, s);
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(tr_dist[x.second] != x.first) continue;
		for(auto &j : tgph[x.second]){
			if(tr_dist[j.second] > x.first + j.first){
				tr_dist[j.second] = x.first + j.first;
				pq.emplace(tr_dist[j.second], j.second);
			}
		}
	}
	lint ans = 1e18;
	for(auto &i : vtx_list[p]){
		for(auto &j : gph[i]){
			if(key[lbl[j.pos]] > p){
				ans = min(ans, tr_dist[i] + rdist[j.pos] + j.cst);
			}
		}
	}
	return ans;
}

void dfs(int x){
	for(auto &i : tr[x]){
		if(!lbl[i]) lbl[i] = lbl[x];
		dfs(i);
	}
}

void dijk(lint *dist, int x){
	dist[x] = 0;
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.emplace(0, x);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.pos] > x.first + i.cst){
				dist[i.pos] = x.first + i.cst;
				par[i.pos] = x.second;
				pae[i.pos] = i.idx;
				pq.emplace(dist[i.pos], i.pos);
			}
		}
	}
}

int inside_spath[MAXM];

void solve(){
	scanf("%d %d",&n,&m);
	memset(lbl, 0, sizeof(lbl));
	memset(key, 0, sizeof(key));
	memset(dist, 0x3f, sizeof(dist));
	memset(rdist, 0x3f, sizeof(rdist));
	memset(inside_spath, 0, sizeof(inside_spath));
	vector<tuple<int, int, int>> edgs;
	for(int i=0; i<=n; i++){
		gph[i].clear();
		tr[i].clear();
		edg_list[i].clear();
		vtx_list[i].clear();
		tgph[i].clear();
	}
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back({x, e, i});
		gph[e].push_back({x, s, i});
		edgs.emplace_back(s, e, x);
	}
	dijk(rdist, n);
	dijk(dist, 1);
	for(int i=2; i<=n; i++){
		tr[par[i]].push_back(i);
	}
	vector<int> v;
	for(int i=n; i!=1; i=par[i]){
		lbl[i] = i;
		v.push_back(i);
	}
	lbl[1] = 1;
	v.push_back(1);
	dfs(1);
	reverse(v.begin(), v.end());
	for(int i=0; i<v.size(); i++) key[v[i]] = i;
	for(int i=1; i<v.size(); i++) inside_spath[pae[v[i]]] = i;
	for(int i=1; i<=n; i++){
		if(lbl[i] != i) vtx_list[key[lbl[i]]].push_back(i);
	}
	seg1.init(v.size() + 1);
	seg2.init(v.size() + 1);
	int cnt = 0;
	for(auto &i : edgs){
		cnt++;
		if(inside_spath[cnt - 1]) continue;
		int s, e, x; tie(s, e, x) = i;
		int st = key[lbl[s]];
		int ed = key[lbl[e]];
		if(st == ed){
			if(lbl[s] == s || lbl[e] == e) continue;
			edg_list[st].emplace_back(s, e, x);
			continue;
		}
		lint val = x;
		if(st < ed){
			val += dist[s] + rdist[e];
		}
		else{
			swap(st, ed);
			swap(s, e);
			val += dist[s] + rdist[e]; 
		}
		seg1.push(st + 1, ed, val - dist[n]);
		seg2.push(st + 1, ed - 1, val - dist[n]);
	}
	for(int i=1; i+1<v.size(); i++){
		seg2.push(i, i, exclude(i) - dist[n]);
	}
	for(int i=0; i<m; i++){
		if(inside_spath[i]){
			lint val = seg1.query(inside_spath[i]);
			if(val > 1e17) printf("-1 ");
			else printf("%lld ", val);
		}
		else printf("0 ");
	}
	puts("");
	for(int i=2; i<=n-1; i++){
		if(lbl[i] != i){
			printf("0 ");
			continue;
		}
		lint val = seg2.query(key[i]);
		if(val > 1e17) printf("-1 ");
		else printf("%lld ", val);
	}
	puts("");
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		solve();
	}
}
