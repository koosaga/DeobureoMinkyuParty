#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1505;
using lint = long long;
using pi = pair<lint, int>;

namespace FIO{
	static char buf[1 << 19];
	static int idx = 0;
	static int bytes = 0;
	static inline int _read(){
		if(!bytes || idx == bytes){
			bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
			idx = 0;
		}
		return buf[idx++];
	}
	static inline int _readInt(){
		int x = 0, s = 1;
		int c = _read();
		while(c <= 32) c = _read();
		if(c == '-') s = -1, c = _read();
		while(c > 32) x = 10 * x + (c - '0'), c = _read();
		if(s < 0) x = -x;
		return x;
	}
}

int n, m, k;
int a[MAXN][MAXN];
lint T[4][MAXN][MAXN];
lint aux1[MAXN], aux2[MAXN];

void FX(){
	for(int i=1; i<=n-k+1; i++){
		memcpy(aux1, T[0][i], sizeof(T[0][i]));
		memcpy(aux2, T[1][i], sizeof(T[1][i]));
		reverse(aux1 + 1, aux1 + (m - k + 2));
		reverse(aux2 + 1, aux2 + (m - k + 2));
		memcpy(T[0][i], aux2, sizeof(T[0][i]));
		memcpy(T[1][i], aux1,  sizeof(T[1][i]));

		memcpy(aux1, T[2][i], sizeof(T[2][i]));
		memcpy(aux2, T[3][i], sizeof(T[3][i]));
		reverse(aux1 + 1, aux1 + (m - k + 2));
		reverse(aux2 + 1, aux2 + (m - k + 2));
		memcpy(T[2][i], aux2, sizeof(T[2][i]));
		memcpy(T[3][i], aux1,  sizeof(T[3][i]));
	}
}

void FY(){
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n-k+1; j++){
			aux1[j] = T[0][j][i];
			aux2[j] = T[2][j][i];
		}
		reverse(aux1 + 1, aux1 + (n - k + 2));
		reverse(aux2 + 1, aux2 + (n - k + 2));
		for(int j=1; j<=n-k+1; j++){
			T[2][j][i] = aux1[j];
			T[0][j][i] = aux2[j];
		}

		for(int j=1; j<=n-k+1; j++){
			aux1[j] = T[1][j][i];
			aux2[j] = T[3][j][i];
		}
		reverse(aux1 + 1, aux1 + (n - k + 2));
		reverse(aux2 + 1, aux2 + (n - k + 2));
		for(int j=1; j<=n-k+1; j++){
			T[3][j][i] = aux1[j];
			T[1][j][i] = aux2[j];
		}
	}
}

lint inLeft[MAXN], inUp[MAXN], inDown[MAXN], inRight[MAXN], inDiagDown[MAXN * 2], samDiagDown[MAXN * 2];

lint solve(){
	fill(inLeft, inLeft + MAXN, -1e18);
	fill(inUp, inUp + MAXN, -1e18);
	fill(inDown, inDown + MAXN, -1e18);
	fill(inRight, inRight + MAXN, -1e18);
	fill(inDiagDown, inDiagDown + 2 * MAXN, -1e18);
	fill(samDiagDown, samDiagDown + 2 * MAXN, -1e18);
	lint ret = -1e18;
	for(int i=1; i<=n-k+1; i++){
		for(int j=1; j<=m-k+1; j++){
			lint rectify = max({T[0][i][j], T[1][i][j], T[2][i][j], T[3][i][j]});
			inLeft[j + k - 1] = max(inLeft[j + k - 1], rectify);
			inUp[i + k - 1] = max(inUp[i + k - 1], rectify);
			inDown[i] = max(inDown[i], rectify);
			inRight[j] = max(inRight[j], rectify);
			inDiagDown[i + j] = max({inDiagDown[i + j], T[0][i][j], T[1][i][j], T[2][i][j]});
			samDiagDown[i + j + 2 * k - 2] = max({samDiagDown[i + j + 2 * k - 2], T[3][i][j]});
		}
	}
	for(int i=1; i<MAXN; i++){
		inLeft[i] = max(inLeft[i], inLeft[i-1]);
		inUp[i] = max(inUp[i], inUp[i-1]);
	}
	for(int i=MAXN-2; i>=0; i--){
		inRight[i] = max(inRight[i], inRight[i+1]);
		inDown[i] = max(inDown[i], inDown[i+1]);
	}
	for(int i=MAXN*2-2; i>=0; i--){
		inDiagDown[i] = max(inDiagDown[i], inDiagDown[i + 1]);
		samDiagDown[i] = max(samDiagDown[i], samDiagDown[i + 1]);
	}
	for(int i=1; i<=n-k+1; i++){
		for(int j=1; j<=m-k+1; j++){
			lint lprpv = max({inLeft[j - 1], inUp[i - 1], inDown[i + k], inRight[j + k], 
			inDiagDown[i + j + k],  // diag down strictly 
			samDiagDown[i + j + 2 * k - 1]}); // opposite vertex based
			ret = max(ret, T[0][i][j] + lprpv);
		}
	}
	return ret;
}

lint strip[MAXN][MAXN];
lint up[MAXN][MAXN];

void Make(int arg){
	for(int i=1; i<=n+1; i++){
		for(int j=1; j<=m; j++){
			strip[i][j] = strip[i-1][j] + a[i][j];
		}
	}
	for(int i=1; i<=n+1; i++){
		for(int j=1; j<=m; j++){
			up[i][j] = up[i-1][j+1] + a[i][j] - (i >= k+1 && j+k+1 <= m + 1 ? a[i-k-1][j+k+1] : 0);
		}
	}
	for(int i=1; i<=n-k+1; i++){
		for(int x = 0; x < k; x++){
			T[arg][i][m-k+1] += strip[i+k-1-x][m-k+1+x] - strip[i-1][m-k+1+x];
		}
		for(int j=m-k; j>=1; j--){
			T[arg][i][j] = T[arg][i][j+1] + strip[i+k][j] - strip[i-1][j];
			T[arg][i][j] -= up[i+k][j];
		}
	}
	/*
	puts("given array ");
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) printf("%d ", a[i][j]);
		puts("");
	}
	puts("the answer is = ");
	for(int i=1; i<=n-k+1; i++){
		for(int j=1; j<=m-k+1; j++) printf("%lld ", T[arg][i][j]);
		puts("");
	}*/
}

int main(){
	n = FIO::_readInt();
	m = FIO::_readInt();
	k = FIO::_readInt();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			a[i][j] = FIO::_readInt();
		}
	}
	{
		Make(0);
		for(int i=1; i<=n; i++) reverse(a[i] + 1, a[i] + m + 1);
		Make(1);
		for(int i=1; i<=n; i++){
			reverse(a[i] + 1, a[i] + m + 1);
			reverse(T[1][i] + 1, T[1][i] + (m - k + 2));
		}
	}
	{
		for(int i=1; i<=m; i++){
			for(int j=1; j<n+1-j; j++){
				swap(a[j][i], a[n+1-j][i]);
			}
		}
		Make(2);
		for(int i=1; i<=n; i++) reverse(a[i] + 1, a[i] + m + 1);
		Make(3);
		for(int i=1; i<=n; i++){
			reverse(a[i] + 1, a[i] + m + 1);
			reverse(T[3][i] + 1, T[3][i] + (m - k + 2));
		}
		for(int i=1; i<=m; i++){
			for(int j=1; j<n+1-j; j++){
				swap(a[j][i], a[n+1-j][i]);
			}
			for(int j=1; j<n-k+2-j; j++){
				swap(T[2][j][i], T[2][n-k+2-j][i]);
				swap(T[3][j][i], T[3][n-k+2-j][i]);
			}
		}
	}
	lint ret = solve();
	FX();
	ret = max(ret, solve());
	FY();
	ret = max(ret, solve());
	FX();
	ret = max(ret, solve());
	cout << ret << endl;
}
