#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

char str[MAXN], aux[2 * MAXN];
int n, dp[MAXN * 2];
int q, s[MAXN], e[MAXN], m[MAXN];
lint ret[MAXN];

void solve(){
	for(int i=0; i<n; i++) m[i+1] = dp[2*i] + 1;
	for(int i=0; i<q; i++){
		int st = s[i];
		int ed = e[i];
		int mi = (s[i] + e[i]) / 2;
		for(int j=st; j<=mi; j++){
			ret[i] += min(m[j], j - st + 1);
		}
		for(int j=mi+1; j<=ed; j++){
			ret[i] += min(m[j], -j + ed + 1);
		}
	}
	for(int i=0; i<n; i++) m[i+1] = dp[2*i+1];
	for(int i=0; i<q; i++){
		int st = s[i];
		int ed = e[i];
		int mi = (s[i] + e[i] - 1) / 2;
		for(int j=st; j<=mi; j++){
			ret[i] += min(m[j], j - st + 1);
		}
		for(int j=mi+1; j<=ed-1; j++){
			ret[i] += min(m[j], ed - j);
		}
	}
}

int main(){
	scanf("%s",str);
	n = strlen(str);
	for(int i=0; i<n; i++){
		aux[2*i] = str[i];
		if(i != n-1) aux[2*i+1] = '$';
	}
	int p = 0, c = 0;
	for(int i=0; i<2*n-1; i++){
		int cur = 0;
		if(i <= p) cur = min(dp[2 * c - i], p - i);
		while(i - cur - 1 >= 0 && i + cur + 1 < 2 * n - 1 && aux[i-cur-1] == aux[i+cur+1]) cur++;
		dp[i] = cur;
		if(i + dp[i] > p){
			p = i + dp[i];
			c = i;
		}
		printf("%d", dp[i]);
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d",&s[i],&e[i]);
	}
	solve();
	for(int i=0; i<q; i++) printf("%lld\n", ret[i]);
}
