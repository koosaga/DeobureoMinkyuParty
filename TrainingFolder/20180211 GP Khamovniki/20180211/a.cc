#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int n, s, a[44], p1[44], p2[44];
int n1, n2;

int dp[44][1<<10], pcnt[1<<10];
int must[44];

int f(int x, int msk){
	if(a[x] == -1) return 0;
	if(~dp[x][msk]) return dp[x][msk];
	int popcnt = pcnt[msk];
	int ret;
	if(a[x] >= n){
		ret = 1e9;
		if(!must[x] || (msk >> a[x]) % 2 == 1){
			ret = f(x + 1, msk) - p1[x - popcnt];
		}
		if((msk >> a[x]) % 2 == 0){
			ret = min(ret, f(x + 1, msk | (1 << a[x])) - p2[popcnt]);
		}
	}
	else{
		ret = -1e9;
		if(!must[x] || (msk >> a[x]) % 2 == 1){
			ret = f(x + 1, msk) + p1[x - popcnt];
		}
		if((msk >> a[x]) % 2 == 0){
			ret = max(ret, f(x + 1, msk | (1 << a[x])) + p2[popcnt]);
		}
	}
	return dp[x][msk] = ret;
}

int main(){
	cin >> n >> s;
	int seq = 2 * n * (s+1);
	for(int i=0; i<seq; i++){
		cin >> a[i];
		a[i]--;
	}
	for(int i=0; i<2*n; i++){
		for(int j=seq-1; j>=0; j--){
			if(a[j] == i){
				must[j] = 1;
				break;
			}
		}
	}
	a[seq] = -1;
	for(int i=1; i<1024; i++){
		pcnt[i] = pcnt[i-(i&-i)]+1;
	}
	cin >> n1;
	for(int i=0; i<n1; i++) cin >> p1[i];
	cin >> n2;
	for(int i=0; i<n2; i++) cin >> p2[i];
	sort(p1, p1 + n1);
	sort(p2, p2 + n2);
	reverse(p1, p1 + n1);
	reverse(p2, p2 + n2);
	memset(dp, -1, sizeof(dp));
	cout << f(0, 0) << endl;
}
