#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using llf = long double;
using lint = long long;
const int MAXN = 105;

bool gotcha[MAXN];
int r, c, q;
llf adj[MAXN][MAXN];
llf val[MAXN][MAXN];
llf ans[MAXN]; 
bool chk[MAXN][MAXN];

int main(){
	scanf("%d %d %d",&r,&c,&q);
	for(int i=1; i<=r; i++){
		for(int j=1; j<=r; j++){
			if(i != j) adj[i][j] = 1e9;
		}
	}
	for(int i=1; i<r; i++){
		llf rat;
		cin >> rat;
		if(rat < 0) continue;
		rat = log(rat);
		adj[i][i + 1] = rat;
		adj[i + 1][i] = -rat;
	}
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			llf x;
			cin >> x;
			if(x < 0){
				continue;
			}
			x = log(x);
			chk[i][j] = 1;
			val[i][j] = x;
		}
	}
	while(clock() < 0.9 * CLOCKS_PER_SEC){
		for(int i=1; i<=r; i++){
			for(int j=1; j<=r; j++){
				for(int k=1; k<=r; k++){
					adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
				}
			}
		}
		for(int i=1; i<=r; i++){
			for(int j=i+1; j<=r; j++){
				if(adj[i][j] > 1e7) continue;
				// propagate from new adj(i, j)
				for(int k=1; k<=c; k++){
					if(!gotcha[k] && chk[i][k] && chk[j][k]){
						llf x = val[j][k] - val[i][k] - adj[i][j];
						x /= j - i;
						ans[k] = x;
						gotcha[k] = 1;
					}
					if(gotcha[k] && chk[i][k] && !chk[j][k]){
						val[j][k] = val[i][k] + (j - i) * ans[k] + adj[i][j];
						chk[j][k] = 1;
					}
					if(gotcha[k] && !chk[i][k] && chk[j][k]){
						val[i][k] = val[j][k] - (j - i) * ans[k] + adj[j][i];
						chk[i][k] = 1;
					}
				}
			}
		}
		for(int i=1; i<=c; i++){
			if(!gotcha[i]) continue;
			// propagate from new modifier ans(i)
			for(int j=1; j<=r; j++){
				for(int k=j+1; k<=r; k++){
					if(chk[j][i] && chk[k][i]){
						llf x = val[k][i] - val[j][i] - ans[i] * (k - j);
						adj[j][k] = x;
						adj[k][j] = -x;
					}
					if(!chk[j][i] && chk[k][i] && adj[j][k] < 1e7){
						val[j][i] = val[k][i] - (k - j) * ans[i] + adj[k][j];
						chk[j][i] = 1;
					}
					if(chk[j][i] && !chk[k][i] && adj[k][j] < 1e7){
						val[k][i] = val[j][i] + (k - j) * ans[i] + adj[j][k];
						chk[k][i] = 1;
					}
				}
			}
		}
		for(int i=1; i<=c; i++){
			for(int j=1; j<=r; j++){
				for(int k=j+1; k<=r; k++){
					// propagate from pair of val(j, i), val(k, i)
					if(chk[j][i] && chk[k][i]){
						if(!gotcha[i] && adj[j][k] < 1e7){
							llf x = val[k][i] - val[j][i] - adj[j][k];
							x /= (k - j);
							ans[i] = x;
							gotcha[i] = 1;
						}
						if(gotcha[i] && adj[j][k] > 1e7){
							llf x = val[k][i] - val[j][i] - ans[i] * (k - j);
							adj[j][k] = x;
							adj[k][j] = -x;
						}
					}
				}
			}
		}
	}
	while(q--){
		int a, b; scanf("%d %d",&a,&b);
		swap(a, b);
		if(!chk[a][b]) puts("-1");
		else printf("%.10Lf\n", exp(val[a][b]));
	}
}
