#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

struct bit{
	int tree[MAXN];
	int szz;
	int sz(){ return szz; }
	vector<int> v;
	void add(int x, int y){
		szz += y;
		v.push_back(x);
		while(x < MAXN){
			tree[x] += y;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
	int sum(int l, int r){ return query(r) - query(l - 1); }
	void flush(){
		szz = 0;
		for(auto &i : v){
			for(int j=i; j<MAXN; j+=j&-j){
				tree[j] = 0;
			}
		}
		v.clear();
	}
}bitUp, bitDn, tBitUp, tBitDn;

int n, a[MAXN];
vector<int> gph[MAXN];
vector<int> dfn2;
bool vis[MAXN];

int segUp[MAXN], segDn[MAXN];
int tSegUp[MAXN], tSegDn[MAXN];

void doUp(int x, int p, int stk1, int stk2){
	dfn2.push_back(x);
	if(stk2 == 0){
		if(stk1 <= a[x]) stk1 = a[x];
		else stk2 = a[x];
	}
	else{
		if(stk2 <= a[x]) stk2 = a[x];
		else stk2 = 1e9;
	}
	if(stk2 < 1e8){
		if(stk2 == 0) segUp[x] = stk1;
		else tSegUp[x] = stk2;
	}
	for(auto &i : gph[x]){
		if(!vis[i] && i != p){
			doUp(i, x, stk1, stk2);
		}
	}
}

void doDn(int x, int p, int stk1, int stk2){
	if(stk2 == 0){
		if(stk1 >= a[x]) stk1 = a[x];
		else stk2 = a[x];
	}
	else{
		if(stk2 >= a[x]) stk2 = a[x];
		else stk2 = -1e9;
	}
	if(stk2 > -1e8){
		if(stk2 == 0) segDn[x] = stk1;
		else tSegDn[x] = stk2;
	}
	for(auto &i : gph[x]){
		if(!vis[i] && i != p){
			doDn(i, x, stk1, stk2);
		}
	}
}

lint solve(int r){
	lint ret = 1;
	int good = 0;
	int PleaseStopCreatingProblems = 0;
//	printf("cent %d\n", r);
	for(auto &i : gph[r]){
		if(vis[i]) continue;
		doUp(i, r, a[r], 0);
		doDn(i, r, a[r], 0);
		int new_good = 0;
		int new_PleaseStopCreatingProblems = 0;
		for(auto &j : dfn2){
			if(tSegUp[j] > a[r]) tSegUp[j] = 0;
			if(tSegDn[j] < a[r]) tSegDn[j] = 0;
			printf("%d %d %d %d\n", segUp[j], segDn[j], tSegUp[j], tSegDn[j]);
			new_good++;
			if(segUp[j] && segDn[j]){
				assert(segUp[j] == a[r] && segDn[j] == a[r]);
				new_PleaseStopCreatingProblems++;
				ret += good;
				// case 5
			}
			else if(segUp[j] && tSegDn[j]){
				ret += bitDn.sz();
				ret += tBitDn.sum(segUp[j], 1e5);
				ret += bitUp.sum(a[r] + 1, segUp[j]);
				// case 6
			}
			else if(tSegUp[j] && segDn[j]){
				// case 7
				ret += bitDn.sum(segDn[j], a[r] - 1);
				ret += bitUp.sz();
				ret += tBitUp.sum(1, segDn[j]);
			}
			else if(tSegUp[j] && tSegDn[j]){
				ret += PleaseStopCreatingProblems;
				cout << PleaseStopCreatingProblems << endl;
				}
			else{
				int cnt = 0;
				if(segUp[j]){
					cnt++;
					ret += bitDn.sz();
					ret += tBitDn.sum(segUp[j], 1e5);
				}
				if(segDn[j]){
					cnt++;
					ret += bitUp.sz();
					ret += tBitUp.sum(1, segDn[j]);
				}
				if(tSegUp[j]){
					cnt++;
					ret += bitDn.sum(tSegUp[j], a[r]);
				}
				if(tSegDn[j]){
					cnt++;
					ret += bitUp.sum(a[r], tSegDn[j]);
				}
				assert(cnt <= 1);

				if(cnt == 0) new_good--;
			}
		}
		good += new_good;
		PleaseStopCreatingProblems += new_PleaseStopCreatingProblems;
		for(auto &j : dfn2){
			if(segUp[j]) bitUp.add(segUp[j], 1);
			if(segDn[j]) bitDn.add(segDn[j], 1);
			if(tSegUp[j]) tBitUp.add(tSegUp[j], 1);
			if(tSegDn[j]) tBitDn.add(tSegDn[j], 1);
			tSegUp[j] = tSegDn[j] = segUp[j] = segDn[j] = 0;
		}
		dfn2.clear();
	}
	bitUp.flush();
	bitDn.flush();
	tBitUp.flush();
	tBitDn.flush();
	ret += good;
 cout << ret << endl;
	return ret;
}

vector<int> dfn;
int sz[MAXN], msz[MAXN];

void dfs(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(vis[i] || i == p) continue;
		dfs(i, x);
		sz[x] += sz[i];
		msz[x] = max(msz[x], sz[i]);
	}
}

int get_center(int x){
	dfn.clear();
	dfs(x, -1);
	pi ret(1e9, -1);
	for(auto &i : dfn){
		int szv = max((int)dfn.size() - sz[i], msz[i]);
		ret = min(ret, pi(szv, i));
	}
	return ret.second;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		for(int i=1; i<n; i++){
			int s, e; scanf("%d %d",&s,&e);
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		queue<int> que;
		que.push(1);
		lint ret = 0;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			x = get_center(x);
			ret += solve(x);
			vis[x] = 1;
			for(auto &i : gph[x]){
				if(!vis[i]){
					que.push(i);
				}
			}
		}
		printf("%lld\n", ret);
		for(int i=0; i<=n; i++){
			vis[i] = 0;
			gph[i].clear();
		}
	}
}
