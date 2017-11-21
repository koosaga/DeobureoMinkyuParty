#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 15;
const int MAXM = (1<<15);

int n;

int adj[MAXN][MAXN];
lint D[MAXM][MAXN];
lint E[MAXM][MAXN][MAXN];
int popcnt[MAXM];

int main(){
	cin >> n;
	for(int i=1; i<(1<<n); i++){
		popcnt[i] = popcnt[i - (i & -i)] + 1;
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			cin >> adj[i][j];
			adj[j][i] = adj[i][j];
		}
	}
	memset(D, 0x3f, sizeof(D));
	memset(E, 0x3f, sizeof(E));
	for(int i=0; i<n; i++) D[1<<i][i] = 0;
	for(int mask = 1; mask < (1<<n); mask++){
		if(mask != 1){
			for(int i=0; i<n; i++){
				if((mask >> i) & 1){
					int bmsk = (mask ^ (1<<i));
					for(int j=bmsk; j; j = (j-1) & bmsk){
						D[mask][i] = min(D[mask][i],
						E[j][i][n - popcnt[j]] + D[mask ^ j][i]);
					}
				}
			}
		}
		for(int i=0; i<n; i++){
			if((mask >> i) & 1) continue;
			for(int k=1; k<=n; k++){
				for(int j=0; j<n; j++){
					if((mask >> j) % 2 == 0) continue;
					E[mask][i][k] = min(E[mask][i][k],
					D[mask][j] + 1ll * adj[i][j] * k * popcnt[mask]);
				}
			}
		}
	}
	cout << *min_element(D[(1<<n)-1], D[(1<<n)-1] + n);
}
