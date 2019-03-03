#include <bits/stdc++.h>
using namespace std;
using llf = long double;
using pi = pair<llf, int>;
const int MAXN = 105;

int n, m, k, a[MAXN];
int adj[MAXN][MAXN];
bool vis[10*MAXN][MAXN];
bool vis2[10*MAXN][MAXN];
double cyc[MAXN][MAXN][MAXN];
llf dp[10*MAXN][MAXN];
llf dp2[10*MAXN][MAXN];
llf min_cyc[MAXN];

llf f(int x, int y){
	if(vis[x][y]) return dp[x][y];
	vis[x][y] = 1;
	llf ret = 1e9;
	if(x == 0) ret = adj[a[y]][n];
	if(x > 0){
		for(int z=1; z<=k; z++){
			if(z != y){
				ret = min(ret, f(x - 1, z) / 2 + adj[a[y]][a[z]]);
			}
		}
	}
//	printf("dynamic %d %d = %.10f\n", x, y, ret);
	return dp[x][y] = ret;
}

llf g(int x, int y){
	if(vis2[x][y]) return dp2[x][y];
	vis2[x][y] = 1;
	llf ret = min_cyc[y];
	if(x > 0){
		for(int z=1; z<=k; z++){
			if(z != y){
				ret = min(ret, g(x - 1, z) / 2 + adj[a[y]][a[z]]);
			}
		}
	}
	return dp2[x][y] = ret;
}

void solve(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			adj[i][j] = (i == j ? 0 : 1e9);
		}
	}
	for(int i=0; i<=10*n; i++){
		for(int j=0; j<=n; j++){
			vis[i][j] = 0;
			vis2[i][j] = 0;
		}
	}
	for(int i=0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d",&x,&y,&w);
		adj[x][y] = min(adj[x][y], w);
		adj[y][x] = min(adj[y][x], w);
	}
	for(int i=1; i<=k; i++){
		scanf("%d",&a[i]);
	}
	sort(a + 1, a + k + 1);
	int vvv = 0;
	if(a[k] == n){
		a[k] = 1e9;
		vvv++;
		k--;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	for(int i=1; i<=k; i++){
		for(int j=1; j<=k; j++){
			cyc[0][i][j] = (i == j ? 0 : 1e9);
		}
	}
	for(int i=1; i<=k; i++){
		for(int x=1; x<=k; x++){
			for(int y=1; y<=k; y++){
				cyc[i][x][y] = 1e9;
				for(int z=1; z<=k; z++){
					if(x != z){
						cyc[i][x][y] = min(cyc[i][x][y], cyc[i-1][z][y] / 2 + adj[a[x]][a[z]]);
					}
				}
			}
		}
	}
	pi ret(1e9, 696969);
	fill(min_cyc, min_cyc+k+1, 1e9);
	for(int i=1; i<=k; i++){
		llf x = 1;
		for(int j=0; j<i; j++) x *= 2;
		llf r = x / (x - 1);
		for(int j=1; j<=k; j++){
			min_cyc[j] = min(min_cyc[j], cyc[i][j][j] * r);
		}
	}
	for(int i=1; i<=k; i++){
		llf ans = g(10*k, i) / 2 + adj[1][a[i]] - 1e-9L;
		ret = min(ret, pi(ans, -696969));
	}
	ret = min(ret, pi(1.0 * adj[1][n], 0));
	for(int i=1; i<=k*10; i++){
		for(int j=1; j<=k; j++){
			ret = min(ret, pi((long double)f(i - 1, j) / 2 + adj[1][a[j]] - 1e-18L * i, -i));
		}
	}
	if(ret.second < -10000) printf("%.10Lf Burst!\n", ret.first);
	else printf("%.10Lf %d\n", ret.first, -ret.second + vvv);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		solve();
	}
}
