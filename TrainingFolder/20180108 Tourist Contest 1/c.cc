#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 1005;
const int MAXM = 100005;
const int mod = 1e9 + 7;

int n, m, c[10];
char str[MAXM];
lint bino[MAXN][MAXN];
lint f[6][MAXN], g[6][MAXN];

int lis[5][2] = {{0, 9}, {1, 8}, {2, 7}, {3, 6}, {4, 5}};

int ok(int p, int a, int b, int x, int y){
	a += c[lis[p][0]];
	b += c[lis[p][1]];
	if(lis[p][0] == x) a--;
	if(lis[p][0] == y) a--;
	if(lis[p][1] == x) b--;
	if(lis[p][1] == y) b--;
	if(a < 0 || b < 0) return 0;
	if(p == 0){
		return a >= b && a % 2 == b % 2;
	}
	else return a == b;
}

lint solve(int x, int y){
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	for(int i=0; i<5; i++){
		for(int j=0; j<=m; j++){
			for(int k=0; k<=j; k++){
				if(ok(i, j-k, k, x, y)) g[i][j] += bino[j][k];
			}
			g[i][j] %= mod;
		}
	}
	f[0][0] = 1;
	for(int i=1; i<=5; i++){
		for(int j=0; j<=m; j++){
			for(int k=0; k<=j; k++) f[i][j] += f[i-1][k] * (bino[j][k] * g[i-1][j-k] % mod) % mod;
			f[i][j] %= mod;
		}
	}
	return f[5][m];
}

int main(){
	freopen("can.in", "r", stdin);
	freopen("can.out", "w", stdout);
	for(int i=0; i<MAXN; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % mod;
		}
	}
	scanf("%s", str);
	n = strlen(str);
	m = count(str, str + n, '?');
	for(int i=0; i<10; i++) c[i] = count(str, str + n, i + '0');
	lint ans = solve(1, 9) + solve(2, 8) + solve(3, 7) + solve(4, 6) + solve(5, 5);
	cout << ans % mod;
}
