#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int mod = 1e9 + 7;
typedef long long lint;

int n, a[MAXN];
lint dp[1<<10], nxt[1<<10];
char str[MAXN];
lint ret[11];

int main(){
	scanf("%s", str);
	n = strlen(str);
	dp[0] = 1;
	for(int i=0; i<n; i++){
		int x = str[i] - '0';
		for(int j=0; j<(1<<10); j++){
			nxt[j] += dp[j];
			int cmsk = j & (1024 - (1<<x));
			if(cmsk == 0){
				nxt[j | (1<<x)] += dp[j];
			}
			else{
				int cur = j - (cmsk & -cmsk) + (1<<x);
				nxt[cur] += dp[j];
			}
		}
		for(int j=0; j<(1<<10); j++){
			dp[j] = nxt[j] % mod;
			nxt[j] %= mod;
			nxt[j] = 0;
		}
	}
	for(int i=1; i<(1<<10); i++){
		int cnt = 0;
		for(int j=0; j<10; j++){
			if((i >> j) & 1) cnt++;
		}
		ret[cnt] += dp[i];
	}
	for(int i=1; i<=10; i++) cout << ret[i] % mod << " ";
}
