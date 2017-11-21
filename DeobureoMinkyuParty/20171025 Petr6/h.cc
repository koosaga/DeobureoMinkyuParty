#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct edg{
	int stt, pos, cost, idx;
};

int n, m;
int s[MAXN], e[MAXN], x[MAXN];
vector<int> vtx;
vector<edg> gph[MAXN];
lint dist[MAXN];

void dijkstra(int x){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, x));
	memset(dist, 0x3f, sizeof(dist));
	dist[x] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.pos] > i.cost + x.first){
				dist[i.pos] = i.cost + x.first;
				pq.push(pi(dist[i.pos], i.pos));
			}
		}
	}
}

bool in_interval(edg E, int s, int e){
	int fst = dist[E.stt];
	int snd = dist[E.pos];
	return s <= fst && snd <= e;
}

lint dist2[MAXN];
int par[MAXN], pae[MAXN];
vector<edg> gph2[MAXN];

vector<int> Do(int s, int e, vector<edg> v){
	dist2[s] = dist2[e] = 2e9;
	for(auto &i : v){
		dist2[i.stt] = dist2[i.pos] = 2e9;
		gph2[i.stt].clear();
		gph2[i.pos].clear();
	}
	for(auto &i : v){
		gph2[i.stt].push_back(i);
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, s));
	dist2[s] = 0;
	while(!pq.empty()){
		auto i = pq.top();
		pq.pop();
		if(dist2[i.second] != i.first) continue;
		for(auto &j : gph2[i.second]){
			if(dist2[j.pos] > i.first + j.cost){
				dist2[j.pos] = i.first + j.cost;
				par[j.pos] = i.second;
				pae[j.pos] = j.idx;
				pq.push(pi(dist2[j.pos],j.pos));
			}
		}
	}
	if(dist2[e] > 2e9 - 100){
		vector<int> ans = {-1};
		return ans;
	}
	vector<int> ans;
	for(int j=e; j!=s; j=par[j]){
		ans.push_back(pae[j]);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

void solve(int x){
	dijkstra(x);
	vector<pi> nxt;
	vector<edg> lis;
	for(auto &i : vtx) nxt.push_back(pi(dist[i], i));
	sort(nxt.begin(), nxt.end());
	for(int i=1; i<nxt.size(); i++){
		if(nxt[i-1].first == nxt[i].first){
			return;
		}
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(dist[i] + j.cost == dist[j.pos]){
				lis.push_back(j);
			}
		}
	}
	sort(lis.begin(), lis.end(), [&](const edg &a, const edg &b){
		return dist[a.pos] < dist[b.pos];
	}); // shortest path dag
	int p = 0;
	vector<int> ans;
	for(int i=0; i<nxt.size()-1; i++){
		vector<edg> edgs;
		while(p < lis.size() && dist[lis[p].pos] <= nxt[i+1].first){
			if(in_interval(lis[p], nxt[i].first, nxt[i+1].first)){
				edgs.push_back(lis[p]);
			}
			p++;
		}
		/*
		fprintf(stderr, "%d %d\n", nxt[i].second, nxt[i+1].second);
		fprintf(stderr, "in interval %d %d = \n", nxt[i].first, 
		nxt[i+1].first);
		for(auto &j : edgs) fprintf(stderr, "%d %d %d\n", j.stt, j.pos, j.cost);

*/
		auto v = Do(nxt[i].second, nxt[i+1].second, edgs);
		if(v[0] == -1) return;
		int tmp = nxt[i+1].first - nxt[i].first;
		for(auto &j : v){
			tmp -= ::x[j];
		}
		if(tmp != 0) return;
		for(auto &j : v) ans.push_back(j);
	}
	printf("%d\n", ans.size());
	for(auto &i : ans) printf("%d ", i);
	puts("");
	exit(0);
}

int main(){
	freopen("recover.in", "r", stdin);
	freopen("recover.out", "w", stdout);
	cin >> n >> m;
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		::s[i] = s;
		::e[i] = e;
		::x[i] = x;
		gph[s].push_back({s, e, x, i});
		gph[e].push_back({e, s, x, i});
	}
	int k;
	scanf("%d",&k);
	vtx.resize(k);
	for(auto &i : vtx) scanf("%d",&i);
	dijkstra(vtx[0]);
	int cur = 0;
	for(int i=1; i<vtx.size(); i++){
		if(dist[vtx[i]] > dist[vtx[cur]]){
			cur = i;
		}
	}
	int x = vtx[0];
	int y = vtx[cur];
	solve(x);
	solve(y);
	assert(0);
}
