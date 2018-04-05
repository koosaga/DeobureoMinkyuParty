#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m;
vector<int> gph[MAXN];
int ndeg[MAXN];
int trace[MAXN];

void query(int l, int r){
	gph[l].erase(find(gph[l].begin(), gph[l].end(), r));
	gph[r].erase(find(gph[r].begin(), gph[r].end(), l));
	memset(ndeg, 0, sizeof(ndeg));
	memset(trace, 0, sizeof(trace));
	for(int i=1; i<=n; i++) ndeg[i] = gph[i].size();
	bool fuck = false;
	for(int i=1; i<=n; i++) if(ndeg[i] == 0) fuck = true;
	for(int i=1; i<=n; i++){
		if(ndeg[i] == 1){
			int pos = i;
			while(ndeg[pos] == 1){
				ndeg[pos]--;
				trace[pos]++;
				int nxt = -1;
				for(auto &j : gph[pos]){
					if(ndeg[j]){
						ndeg[j]--;
						nxt = j;
						break;
					}
				}
				if(nxt == -1) break;
				pos = nxt;
			}
			trace[pos]++;
		}
	}
	for(int i=1; i<=n; i++){
		if(trace[i] > 1) fuck = true;
		if(ndeg[i] && ndeg[i] != 2) fuck = true;
	}
	if(fuck){
		gph[l].push_back(r);
		gph[r].push_back(l);
		return;
	}
	printf("%d %d\n", l, r);
	exit(0);
}

int dfn[MAXN], low[MAXN], bridge[MAXN], piv;
int deg[MAXN], chk[MAXN];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			if(!dfn[i]){
				dfs(i, x);
				low[x] = min(low[x], low[i]);
				if(low[i] > dfn[x] && deg[i] && deg[x]){
					bridge[x]++;
					bridge[i]++;
				}
			}
			else low[x] = min(low[x], dfn[i]);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
		deg[s]++; deg[e]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(deg[i] == 1) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(deg[i]){
				deg[x]--;
				deg[i]--;
				if(deg[i] == 1) que.push(i);
				else chk[i] = 1;
			}
		}
	}
	vector<pi> QR;
	auto GAZUA = [&](){
		if(!QR.empty()){
			for(auto &i : QR){
				if(i.first > i.second) swap(i.first, i.second);
			}
			sort(QR.begin(), QR.end());
			QR.resize(unique(QR.begin(), QR.end()) - QR.begin());
			for(auto &i : QR) query(i.first, i.second);
			assert(false);
		}
	};
	for(int i=1; i<=n; i++){
		if(deg[i] == 4){
			for(auto &j : gph[i]){
				if(deg[j]) QR.push_back(pi(i, j));
			}
		}
	}
	GAZUA();
	dfs(1, -1);
	for(int i=1; i<=n; i++){
		if(bridge[i] == 1){
			for(auto &j : gph[i]){
				if(deg[j] && !bridge[j]) QR.push_back(pi(i, j));
			}
		}
	}
	GAZUA();
	int l = -1, r = -1;
	for(int i=1; i<=n; i++){
		if(deg[i] == 3){
			for(auto &j : gph[i]){
				if(deg[j]) QR.push_back(pi(i, j));
			}
			if(l == -1) l = i;
			else if(r == -1) r = i;
			else assert(false);
		}
	}
	assert(l != -1 && r != -1);
	vector<vector<int>> paths;
	int i = l;
	for(auto j : gph[l]){
		if(deg[j]){
			set<int> s;
			s.insert(i);
			s.insert(j);
			deg[i]--;
			deg[j]--;
			vector<int> v = {i, j};
			while(j != r){
				for(auto &k : gph[j]){
					if(deg[k] && s.find(k) == s.end()){
						deg[j]--;
						deg[k]--;
						j = k;
						break;
					}
				}
				s.insert(j);
				v.push_back(j);
			}
			paths.push_back(v);
		}
	}
	auto func = [&](const vector<int> &v){
		int ans = 0;
		for(auto &i : v) ans += chk[i];
		return ans;
	};
	sort(paths.begin(), paths.end(), [&](const vector<int> &a, const vector<int> &b){
		return func(a) < func(b);
	});
	for(auto &i : paths){
		if(func(i) > 2) continue;
		for(int j=0; j<i.size(); j++){
			if(chk[i[j]]){
				if(j + 1 < i.size()){
					QR.push_back(pi(i[j], i[j+1]));
				}
				if(j > 0){
					QR.push_back(pi(i[j], i[j-1]));
				}
			}
		}
	}
	GAZUA();
}

