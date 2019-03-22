#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,  int>;
const int MAXN = 100005;

int n;
vector<int> gph[MAXN];
vector<int> holes[MAXN];
int dp[MAXN][2], sz[MAXN];

void dfs(int x){
	dp[x][0] = 0;
	dp[x][1] = 0;
	sz[x] = 1;
	int upd = 0;
	for(auto &i : gph[x]){
		dfs(i);
		sz[x] += sz[i];
		dp[x][1] += dp[i][0];
		dp[x][0] += dp[i][0];
		upd = max(upd, dp[i][1] - dp[i][0] + 1);
	}
	dp[x][0] += upd;
}

void trace(int x, int d, vector<int> &v){
	if(d == 0){
		pi ret(0, -1);
		for(auto &i : gph[x]){
			ret = max(ret, pi(dp[i][1] - dp[i][0] + 1, i));
		}
		if(ret.second == -1){
			v.push_back(x);
		}
		for(auto &i : gph[x]){
			trace(i, i == ret.second, v);
		}
	}
	else{
		for(auto &i : gph[x]){
			trace(i, 0, v);
		}
	}
}

int p[MAXN];
int main(){
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	scanf("%d",&n);
	for(int i=2; i<=n; i++){
		scanf("%d",&p[i]);
		if(p[i]) gph[p[i]].push_back(i);
	}
	int ret = 0;
	vector<pi> v;
	vector<int> tothol;
	for(int i=1; i<=n; i++){
		if(p[i] == 0){
			dfs(i);	
			int no_par = 0;
			int mtch = dp[i][0];
			ret += mtch;
			for(auto &j : gph[i]){
				no_par += dp[j][0];
			}
			if(no_par != mtch || i == 1){
				p[i] = 1;
				vector<int> vhol;
				trace(i, 0, vhol);
				for(auto &j : vhol) tothol.push_back(j);
				assert(vhol.size() + 2 * mtch == sz[i]);
			}
			else{
				p[i] = -1;
				vector<int> vhol;
				for(auto &j : gph[i]){
					trace(j, 0, vhol);
				}
				vhol.push_back(i);
				holes[i] = vhol;
				v.emplace_back(vhol.size(), i);
				assert(vhol.size() + 2 * mtch == sz[i]);
			}
		}
	}
	sort(v.rbegin(), v.rend());
	for(auto &i : v){
		if(tothol.empty()){
			p[i.second] = 1;
			for(auto &j : holes[i.second]){
				tothol.push_back(j);
			}
		}
		else{
			ret++;
			p[i.second] = tothol.back();
			tothol.pop_back();
			for(auto &j : holes[i.second]){
				if(j != i.second) tothol.push_back(j);
			}
		}
	}
	cout << ret << endl;
	for(int i=2; i<=n; i++) printf("%d ", p[i]);
}
