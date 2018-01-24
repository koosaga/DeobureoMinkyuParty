#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int n, a[2005];
lint dp[2005][2005];

struct seg{
	lint tree[4100];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
	}
	void update(int x, lint v){
		x += lim;
		while(x){
			tree[x] = min(tree[x], v);
			x >>= 1;
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = 1e18;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}segl[2005], segr[2005];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		segl[i].init(n+1);
		segr[i].init(n+1);
	}
	for(int i=1; i<=n; i++){
		dp[i][i] = a[i];
		segl[i].update(i+1, dp[i][i] + a[i+1]);
		segl[i].update(i, dp[i][i-1] + a[i]);
		segr[i].update(i-1, dp[i][i] + a[i-1]);
		segr[i].update(i, dp[i+1][i] + a[i]);
	}
	for(int i=1; i<n; i++){
		for(int j=1; j+i<=n; j++){
			int s = j, e = j + i;
			while(s != e){
				int m = (s+e)/2;
				lint left_cost = dp[j][m-1];
				lint right_cost = dp[m+1][j+i];
				if(left_cost <= right_cost) s = m+1;
				else e = m;
			}
			dp[j][j+i] = min(segl[j].query(s, j+i), segr[j+i].query(j, s-1));
			/*for(int k=s; k<=j+i; k++){
			
				dp[j][j+i] = min(dp[j][j+i], dp[j][k-1] + a[k]);
			}
			for(int k=j; k<s; k++){
				dp[j][j+i] = min(dp[j][j+i], a[k] + dp[k+1][j+i]);
			}*/
			segr[j+i].update(j - 1, dp[j][j + i] + a[j-1]);
			segl[j].update(j + i + 1, dp[j][j+i] + a[j+i+1]);
		}
	}
	cout << dp[1][n];
}
