#include<bits/stdc++.h>
using namespace std;
typedef long long lint;

int chk[1<<15];
int n, m, s[222], e[222];
lint dp[1<<15];

lint f(int msk, int d){
	if(~dp[msk]) return dp[msk];
	if(!chk[msk]){
		lint ans = 1;
		for(int j=1; j<=d; j++) ans *= j;
		return dp[msk] = ans;
	}
	lint ans = 0;
	for(int i=0; i<n; i++){
		if((msk >> i) % 2 == 0){
			ans += f(msk | (1<<i), d - 1);
		}
	}
	return dp[msk] = ans;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i];
		s[i]--;
		e[i]--;
	}
	for(int i=0; i<(1<<n); i++){
		int arr[15] = {};
		for(int j=0; j<n; j++){
			arr[j] = (i >> j) & 1;
		}
		for(int j=0; j<m; j++){
			if(arr[s[j]] > arr[e[j]]) swap(arr[s[j]], arr[e[j]]);
		}
		chk[i] = is_sorted(arr, arr + n);
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0, n) << endl;
}
