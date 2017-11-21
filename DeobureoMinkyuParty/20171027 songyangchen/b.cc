#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int MAXM = 105;
typedef long long lint;

int n, m, q;
char s[MAXN], t[MAXM];
int CL[MAXN], CR[MAXN];
lint SCL[MAXN], SCR[MAXN];

int L[MAXN][MAXM], R[MAXN][MAXM];
int PL[MAXM][MAXN], PR[MAXM][MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&q);
	scanf("%s %s",s+1,t+1);
	L[0][0] = R[n+1][m] = 1;
	for(int i=1; i<=n; i++){
		L[i][0] = 1;
		for(int j=1; j<=m; j++){
			if(L[i-1][j-1] && s[i] == t[j]) L[i][j] = 1;
		}
		CL[i] = CL[i-1] + L[i][m];
		SCL[i] = SCL[i-1] + CL[i];
	}
	for(int i=n; i; i--){
		R[i][m] = 1;
		for(int j=m-1; j>=0; j--){
			if(R[i+1][j+1] && s[i] == t[j+1]) R[i][j] = 1;
		}
		CR[i] = CR[i+1] + R[i][0];
		SCR[i] = SCR[i+1] + CR[i];
	}
	for(int i=1; i<m; i++){
		for(int j=1; j<=n; j++){
			PL[i][j] = PL[i][j-1] + L[j][i];
		}
		for(int j=n; j>=1; j--){
			PR[i][j] = PR[i][j+1] + R[j][i];
		}
	}
	while(q--){
		int l, r;
		scanf("%d %d",&l,&r);
		lint ans = SCL[l] * (n - r + 1) + SCR[r] * l;
		for(int i=1; i<m; i++){
			ans += 1ll * PL[i][l] * PR[i][r];
		}
		printf("%lld\n", ans);
	}
}

