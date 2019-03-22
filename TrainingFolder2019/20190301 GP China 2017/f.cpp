#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using lint = long long;
using pi = pair<lint, int>;

struct rect{
	int l, r, v, h, type;
	bool operator<(const rect &r)const{
		return l < r.l;
	}
}a[MAXN];

bool insec(rect a, rect b){
	return max(a.l, b.l) < min(a.r, b.r);
}

int n, w;
int dp[MAXN][MAXN];
int L[MAXN][MAXN];
int R[MAXN][MAXN];
int nxt[MAXN];

int main(){
	while(~scanf("%d %d",&n,&w)){
		for(int i=1; i<=n; i++){
			scanf("%d %d %d %d %d",&a[i].type,&a[i].h,&a[i].l,&a[i].r,&a[i].v);
		}
		a[n+1] = {-1000001, -1000002, 0, 1, 0};
		a[n+2] = {-1000003, -1000004, 0, 1, 1};
		n += 2;
		sort(a + 1, a + n + 1);
		for(int i=0; i<=n+2; i++){
			for(int j=0; j<=n+2; j++){
				L[i][j] = R[i][j] = -2e9;
			}
		}
		for(int i=1; i<=n; i++){
			nxt[i] = n + 1;
			for(int j=i+1; j<=n; j++){
				if(a[j].type == a[i].type && a[j].l >= a[i].r){
					nxt[i] = j;
					break;
				}
			}
		}
		int ret = 0;
		for(int i=n; i; i--){
			for(int j=n; j; j--){
				if(a[i].type == 0 && a[j].type == 1){
					int ni = max(nxt[i], max(i, j) + 1);
					int nj = max(nxt[j], max(i, j) + 1);
					dp[i][j] = max({0, L[ni][j], R[i][nj]});
					if(insec(a[i], a[j]) && a[i].h + a[j].h > w){
						dp[i][j] = -2e9;
					}
					ret = max(ret, dp[i][j] + a[i].v + a[j].v);
				}
				else dp[i][j] = -2e9;
				L[i][j] = max(L[i+1][j], dp[i][j] + a[i].v);
				R[i][j] = max(R[i][j+1], dp[i][j] + a[j].v);
			}
		}
		cout << ret << endl;
	}
}

