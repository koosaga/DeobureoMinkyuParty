#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
#include<set>
#include<vector>
#include<map>
#include<queue>
#define N_ 301000
#define pli pair<long long,int>
#define pii pair<int,int>
#define FI first
#define SE second
using namespace std;
priority_queue<pli>PQ;
vector<pii>E[N_];
vector<int>G[N_], L[N_];
map<pii, int>Map;
int n, m, cnt, Next[N_][20], K, U[N_];
struct Edge {
	int b, e;
}Ed[N_];
void init() {
	int i;
	Map.clear();
	for (i = 1; i <= cnt + n; i++) {
		E[i].clear();
		G[i].clear();
		L[i].clear();
	}
	cnt = 0;
}
void Add_Edge(int a, int b, int c) {
	G[a].push_back(b);
	L[a].push_back(c);
}
void Add(int a, int b, int c) {
	int be = Map[{a, b}];
	int ed = Map[{b, c}];
	Next[be][0] = ed;
	Add_Edge(be, ed, 1);
}
void Go(int b, int x, pii t) {
	pii tp = { t.FI, b };
	int pv = lower_bound(E[x].begin(), E[x].end(), tp) - E[x].begin();
	if (E[x].size() == 1) {
		Add(b, x, b);
	}
	else {
		if (!pv) {
			Add(b, x, E[x][pv + 1].SE);
		}
		else if (pv + 1 == E[x].size()) {
			Add(b, x, E[x][pv - 1].SE);
		}
		else {
			pii t1 = E[x][pv - 1], t2 = E[x][pv + 1];
			int g1 = abs(t1.FI - t.FI), g2 = abs(t2.FI - t.FI);
			int r;
			if (g1 == g2)r = min(t1.SE, t2.SE);
			else if (g1 < g2)r = t1.SE;
			else r = t2.SE;
			Add(b, x, r);
		}
	}
}
long long D[N_];
void Put(int a, long long d) {
	if (D[a] <= d)return;
	D[a] = d;
	PQ.push({ -d,a });
}
long long Dijk() {
	int i;
	while (!PQ.empty()) {
		pli tp = PQ.top();
		PQ.pop();
		int x = tp.second;
		if (D[x] != -tp.first)continue;
		for (i = 0; i < G[x].size(); i++) {
			Put(G[x][i], D[x] + L[x][i]);
		}
	}
	long long r = 1e18;
	for (i = 1; i <= cnt; i++) {
		if (Ed[i].e == n)r = min(r, D[i]);
	}
	r = min(r, D[cnt + n]);
	return r;
}
void Solve() {
	int i, a, b, c, j;
	scanf("%d%d%d", &n, &m, &K);
	for (i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		assert(a != b);
		E[a].push_back({ c,b });
		E[b].push_back({ c,a });
		Map[{a, b}] = ++cnt;
		Ed[cnt] = { a,b };
		Map[{b, a}] = ++cnt;
		Ed[cnt] = { b,a };
	}
	for (i = 1; i <= n; i++) {
		sort(E[i].begin(), E[i].end());
	}
	for (i = 1; i <= n; i++) {
		for (auto &t : E[i]) {
			int b = i, x = t.SE;
			Go(b, x, t);
		}
	}
	Map[{1, 1}] = ++cnt;
	Ed[cnt] = { 1,1 };
	Add(1, 1, E[1][0].SE);
	for (i = 0; i < 19; i++) {
		for (j = 1; j <= cnt; j++) {
			Next[j][i + 1] = Next[Next[j][i]][i];
		}
	}
	for (i = 1; i <= cnt; i++) {
		int a = i;
		for (j = 0; j < 19; j++) {
			if ((K >> j) & 1)a = Next[a][j];
		}
		U[i] = a;
	}
	int st1 = cnt;
	for (i = 1; i <= n; i++) {
		for (auto &t : E[i]) {
			int b = i, e = t.SE;
			int cur = Map[{b, e}];
			Add_Edge(cur, Ed[U[cur]].e + cnt, K);
			Add_Edge(b + cnt, cur, 1);
		}
	}
	int st2 = cnt + 1;
	long long res = 1e18;
	for (i = 1; i <= cnt + n; i++)D[i] = 1e18;
	Put(cnt + 1, 0);
	for (i = 1; i <= K + 1; i++) {
		st1 = Next[st1][0];
		Put(cnt + Ed[st1].e, i);
	}
	res = Dijk();
	if (res > 1e17)res = -1;
	printf("%lld\n", res);
	init();
}
int main() {
	int TC;
	scanf("%d", &TC);
	for (int TT = 1; TT <= TC; TT++) {
		printf("Case #%d: ", TT);
		Solve();
	}
}

