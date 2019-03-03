#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(rk, rk + n + 1, 0);
	}
	int find(int x){
		return (pa[x] == x ? x : find(pa[x]));
	}
	void revert(vector<pi> &v){
		reverse(v.begin(), v.end());
		for(auto &i : v){
			if(i.second == 1) rk[i.first]--;
			else pa[i.first] = i.first;
		}
		v.clear();
	}
	bool uni(int p, int q, vector<pi> &snap){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p; 
		snap.push_back({q, 2});
		if(rk[p] == rk[q]){
			rk[p]++;
			snap.push_back({p, 1});
		}
		return 1;
	}
}disj;


int n, m, q;

int st[MAXN], ed[MAXN], cost[MAXN], chk[MAXN];
pi qr[MAXN];
bool cmp(int &a, int &b){ return pi(cost[a], a) < pi(cost[b], b); }
void contract(int s, int e, vector<int> v, vector<int> &must_mst, vector<int> &maybe_mst){
	sort(v.begin(), v.end(), cmp);
	vector<pi> snapshot;
	for(int i=s; i<=e; i++) disj.uni(st[qr[i].first], ed[qr[i].first], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) must_mst.push_back(i);
	disj.revert(snapshot);
	for(auto &i : must_mst) disj.uni(st[i], ed[i], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) maybe_mst.push_back(i);
	disj.revert(snapshot);
}

vector<lint> dap;

void solve(int s, int e, vector<int> v, lint cv){
	if(s == e){
		cost[qr[s].first] = qr[s].second;
		if(st[qr[s].first] == ed[qr[s].first]){
			dap.push_back(cv);
			return;
		}
		int minv = qr[s].second;
		for(auto &i : v) minv = min(minv, cost[i]);
		dap.push_back(cv + minv);
		return;
	}
	int m = (s+e)/2;
	vector<int> lv = v, rv = v;
	vector<int> must_mst, maybe_mst;
	for(int i=m+1; i<=e; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) lv.push_back(qr[i].first);
	}
	vector<pi> snapshot;
	contract(s, m, lv, must_mst, maybe_mst);
	lint lcv = cv;
	for(auto &i : must_mst) lcv += cost[i], disj.uni(st[i], ed[i], snapshot);
	solve(s, m, maybe_mst, lcv);
	disj.revert(snapshot);
	must_mst.clear(); maybe_mst.clear();
	for(int i=m+1; i<=e; i++) chk[qr[i].first]++;
	for(int i=s; i<=m; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) rv.push_back(qr[i].first);
	}
	lint rcv = cv;
	contract(m+1, e, rv, must_mst, maybe_mst);
	for(auto &i : must_mst) rcv += cost[i], disj.uni(st[i], ed[i], snapshot);
	solve(m+1, e, maybe_mst, rcv);
	disj.revert(snapshot);
	for(int i=s; i<=m; i++) chk[qr[i].first]++;
}

namespace CONN{
	int cmp;
	struct disj{
		int pa[MAXN], rk[MAXN];
		void init(int n){
			iota(pa, pa + n + 1, 0);
			fill(rk, rk + n + 1, 0);
		}
		int find(int x){
			return (pa[x] == x ? x : find(pa[x]));
		}
		bool uni(int p, int q){
			p = find(p);
			q = find(q);
			if(p == q) return 0;
			if(rk[p] < rk[q]) swap(p, q);
			pa[q] = p; 
			if(rk[p] == rk[q]){
				rk[p]++;
			}
			cmp--;
			return 1;
		}
	}disj;
	void init(int n){
		disj.init(n);
		cmp = n;
	}
	int query(){
		return cmp;
	}
}

void solve(){
	scanf("%d %d",&n,&m);
	CONN::init(n);
	vector<int> ve;
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&st[i],&ed[i],&cost[i]);
		CONN::disj.uni(st[i], ed[i]);
	}
	if(CONN::query() != 1){
		for(int i=0; i<m; i++) printf("FAIL\n");
		return;
	}
	q = m;
	qr[0] = pi(0, cost[0]);
	chk[0]++;
	for(int i=1; i<=q; i++){
		qr[i] = pi(i-1, 2.1e9);
		chk[qr[i].first]++;
	}
	disj.init(n);
	for(int i=0; i<m; i++) if(!chk[i]) ve.push_back(i);
	dap.clear();
	solve(0, q, ve, 0);
	bool fail = 0;
	for(int i=0; i<q; i++){
		if(i && dap[i-1] < dap[i] - 1.01e9) fail = 1;
		if(fail) puts("FAIL");
		else printf("%lld\n", dap[i]);
	}
	for(int i=0; i<m; i++) chk[i] = 0;
}

int main(){
	int tc; cin >> tc;
	for(int i=1; i<=tc; i++){
		printf("Case #%d:\n", i);
		solve();
	}
}
