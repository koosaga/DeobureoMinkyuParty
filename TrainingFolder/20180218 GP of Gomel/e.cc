#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

lint solution(int x){
	return 1ll * x * (x + 1) / 2;
}

struct DS{
	set<int> s;
	lint ans;
	void init(int m){
		ans = 0;
		s.clear();
		s.insert(-1);
		s.insert(m);
		ans = solution(m);
	}
	void insert(int x){
		auto l = *--s.lower_bound(x);
		auto r = *s.upper_bound(x);
		ans -= solution(r-l-1);
		ans += solution(x-l-1);
		ans += solution(r-x-1);
		s.insert(x);
	}
	lint getsum(){
		return ans;
	}
	void erase(int x){
		auto l = *--s.lower_bound(x);
		auto r = *s.upper_bound(x);
		ans -= solution(x-l-1);
		ans -= solution(r-x-1);
		ans += solution(r-l-1);
		s.erase(x);
	}
}DS;

int n, m, pr, ps;
lint k;

int a[MAXN], b[MAXN], c[MAXN];
vector<int> pth;
vector<int> gph[MAXN];

lint ret[MAXN];
int deg[MAXN], spt[17][MAXN];

int anc(int x, int y){
	for(int i=0; i<17; i++){
		if((y >> i) & 1){
			x = spt[i][x];
		}
	}
	return x;
}

int ITR;

void DFS(int x, int p, int cur_ds){
	int flag = -1;
	if(cur_ds > ITR){
		flag = anc(x, ITR);
		DS.erase(flag);
		cur_ds--;
	}
	ret[x] = DS.getsum();
	for(auto &i : gph[x]){
		if(i != p && !deg[i]){
			DS.insert(i);
			DFS(i, x, cur_ds+1);
			DS.erase(i);
		}
	}
	if(~flag) DS.insert(flag);
}

lint solve(vector<int> cnd, int itr){
	ITR = itr;
	memset(ret, 0, sizeof(ret));
	memset(deg, 0, sizeof(deg));
	for(int i=0; i<m; i++){
		gph[i].clear();
	}
	bool vis[MAXN] = {};
	for(int i=0; i<m; i++){
		deg[c[i]]++;
		gph[c[i]].push_back(i);
		spt[0][i] = c[i];
	}
	for(int i=1; i<17; i++){
		for(int j=0; j<m; j++){
			spt[i][j] = spt[i-1][spt[i-1][j]];
		}
	}
	queue<int> que;
	for(int i=0; i<m; i++){
		if(!deg[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[c[x]]--;
		if(!deg[c[x]]){
			que.push(c[x]);
		}
	}
	for(int i=0; i<m; i++){
		if(deg[i] && !vis[i]){
			DS.init(m);
			vector<int> v;
			for(int j=i; !vis[j]; j=c[j]){
				v.push_back(j);
				vis[j] = 1;
			}
			for(int j=0; j<v.size() && j<itr; j++){
				DS.insert(v[j]);
			}
			for(int j=0; j<v.size(); j++){
				DFS(v[j], -1, min(itr, (int)v.size()));
				if(itr < v.size()){
					DS.insert(v[(j + itr) % v.size()]);
					DS.erase(v[j]);
				}
			}
		}
	}

	lint ans = 0;
	for(auto &i : cnd) ans += ret[i];
	return ans;/*
	for(auto &i : cnd){
		int pos = i;
		for(int j=0; j<itr; j++){
			DS.insert(pos);
			pos = c[pos];
		}
		ans += DS.getsum();
		pos = i;
		for(int j=0; j<itr; j++){
			DS.erase(pos);
			pos = c[pos];
		}
	}
	return ans;*/
}

int vis[MAXN];

int main(){
	scanf("%d %d %lld",&n,&m,&k);
	int ar, br, as, bs;
	scanf("%d %d %d",&pr,&ar,&br);
	scanf("%d %d %d",&ps,&as,&bs);
	for(int i=0; i<n; i++){
		a[i] = (1ll * ar * i + br) % n;
	}
	for(int i=0; i<m; i++){
		b[i] = (1ll * as * i + bs) % m;
		spt[0][i] = b[i];
	}
	for(int i=1; i<17; i++){
		for(int j=0; j<m; j++){
			spt[i][j] = spt[i-1][spt[i-1][j]];
		}
	}
	int pos = pr;
	while(!vis[pos]){
		pth.push_back(pos);
		vis[pos] = 1;
		pos = a[pos];
	}
	while(!pth.empty() && pth.back() != pos){
		pth.pop_back();
	}
	pth.pop_back();
	int cc = pth.size();
	pth.clear();
	lint ans = 0;
	int left = n;
	while(k && cc){
		ans += solution(ps);
		ans += solution(m - ps - 1);
		left--;
		ps = b[ps];
		k--;
		cc--;
	}
	memset(vis, 0, sizeof(vis));
	while(!vis[pos]){
		pth.push_back(pos);
		vis[pos] = 1;
		pos = a[pos];
	}
	for(int i=0; i<m; i++){
		c[i] = i;
		for(int j=0; j<17; j++){
			if((pth.size() >> j) & 1){
				c[i] = spt[j][c[i]];
			}
		}
	}
	vector<pi> v;
	for(int i=0; i<pth.size() && i < k; i++){
		int itr = (k + pth.size() - 1 - i) / pth.size();
		int stp = ps;
		if(itr > 0) v.push_back(pi(itr, stp));
		ps = b[ps];
	}
	sort(v.begin(), v.end());
	left -= v.size();
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].first == v[i].first) e++;
		vector<int> tmp;
		for(int j=i; j<e; j++) tmp.push_back(v[j].second);
		ans += solve(tmp, v[i].first);
		i = e;
	}
	ans += solution(m) *left;
	cout << ans << endl;
}
