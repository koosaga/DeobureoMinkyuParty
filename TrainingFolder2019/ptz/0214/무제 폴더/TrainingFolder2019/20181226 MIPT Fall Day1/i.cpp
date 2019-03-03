#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
using real_t = lint;
const int MAXN = 200005;
const int MAXM = 105;

struct cht{
	vector<pi> v;
	int p;
	void clear(){
		 p = 0;
		 v.clear();
	}
	bool bad(pi x, pi y, pi z){
		real_t cr1 = (real_t) (x.second - y.second) * (z.first - y.first);
		real_t cr2 = (real_t) (y.second - z.second) * (y.first - x.first);
		return cr1 >= cr2;
	}
	void add(int x, lint y){
		while(v.size() >= p + 2 && bad(v[v.size()-2], v.back(), pi(x, y))){
			v.pop_back();
		}
		v.emplace_back(x, y);
	}
	lint query(int x){
		while(p + 1 < v.size() && v[p].first * x + v[p].second < v[p+1].first * x + v[p+1].second){
			p++;
		}
		return v[p].first * x + v[p].second;
	}
}cht;

int n, m, k, a[MAXN];
int pos[MAXN], sum[MAXN][MAXM];
lint cost[MAXM][MAXN];
lint dp[MAXM][MAXN];

int gs(int sx, int ex, int sy, int ey){
	return sum[ex][ey] - sum[sx-1][ey] - sum[ex][sy-1] + sum[sx-1][sy-1];
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(a[i] == 0) pos[++k] = i;
		else sum[i][a[i]]++;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	for(int i=1; i<=m; i++){
		for(int j=1; j<=k; j++){
			cost[i][j] = gs(1, pos[j], i + 1, m) + gs(pos[j], n, 1, i - 1);
			cost[i][j] += cost[i][j-1];
		}
	}
	for(int i=1;i<=k; i++) dp[m+1][i] = -1e12;
	for(int i=m; i; i--){
		cht.clear();
		for(int j=0; j<=k; j++){
			cht.add(j, dp[i+1][j] - cost[i][j] - 1ll * j * j);
			dp[i][j] = cht.query(j) + cost[i][j];
		}
	}
	lint dap = dp[1][k];
	for(int i=1; i<=n; i++){
		if(a[i]) dap += gs(1, i,  a[i] + 1, m);
	}
	cout << dap << endl;
}
