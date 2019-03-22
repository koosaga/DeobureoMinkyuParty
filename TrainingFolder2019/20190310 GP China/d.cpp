#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 3005;

int n, mod;
lint bino[MAXN][MAXN];
lint func[MAXN], fuck[MAXN];
lint E[MAXN];
lint EXP[MAXN], WAY[MAXN];
lint CEX[MAXN], CWA[MAXN];

int main(){
	int tc;
	cin >> tc >> mod;
	int n = 3001;
	for(int i=0; i<MAXN; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
		}
		func[i] = 1;
		for(int j=0; j<i-2; j++) func[i] = func[i] * i % mod;
	}
	fuck[3] = 1;
	for(int i=4; i<=n; i++) fuck[i] = fuck[i-1] * (i - 1) % mod;
	for(int j=3; j<=n; j++){
		lint poss = 1;
		for(int i=j; i>=3; i--){
			lint dij = poss * bino[j-1][i-1] % mod;
			poss *= j;
			poss %= mod;
			dij *= fuck[i];
			dij %= mod;
			EXP[j] += i * dij % mod;
			WAY[j] += dij;
			EXP[j] %= mod;
			WAY[j] %= mod;
		}
	}
	CEX[0] = 0;
	CWA[0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=0; j<i; j++){
			CEX[i] += bino[i-1][j] * 
			((CEX[j] * WAY[i-j] % mod) + (EXP[i-j] * CWA[j] % mod));
			CEX[i] %= mod;
			CWA[i] += bino[i-1][j] * (CWA[j] * WAY[i-j] % mod) % mod;
			CWA[i] %= mod;
		}
	}
	E[0] = 1;
	for(int j=0; j<=n; j++){
		for(int k=0; k<j; k++){
			E[j] += (E[k] * func[j-k] % mod) * bino[j-1][k] % mod;
			E[j] %= mod;
		}
	}
	while(tc--){
		int n; cin >> n;
		lint ret= 0;
		for(int i=1; i<=n; i++){
			ret += (CEX[i] * E[n - i] % mod) * bino[n][i] % mod;
		}
		ret %= mod;
		cout << ret << endl;
	}
}

