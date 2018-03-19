#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;

struct pi{
	int first, second, idx;
	bool operator<(const pi &p)const{
		return make_pair(first, second) < make_pair(p.first, p.second);
	}
}a[MAXN];

int n, m;
int dp[MAXN][MAXN];
bool DO[MAXN][MAXN];

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		int d, s;
		cin >> d >> s;
		d = max(d, s);
		d = m - d + s;
		a[i].first = d;
		a[i].second = s;
		a[i].idx = i+1;
	}
	sort(a, a+n);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=n; i++){
		dp[i][0] = 0;
		for(int j=1; j<=n; j++){
			dp[i][j] = dp[i-1][j];
			if(dp[i-1][j-1] + a[i-1].second <= a[i-1].first){
				if(dp[i][j] > dp[i-1][j-1] + a[i-1].second){
					DO[i][j] = 1;
					dp[i][j] = dp[i-1][j-1] + a[i-1].second;
				}
			}
		}
	}
	for(int i=n; i>=0; i--){
		if(dp[n][i] <= m){
			vector<int> v;
			int p = i;
			for(int j=n; j; j--){
				if(DO[j][p]){
					v.push_back(a[j-1].idx);
					p--;
				}
			}
			reverse(v.begin(), v.end());
			cout << v.size() << endl;
			for(auto &i : v) cout << i << " ";
			return 0;
		}
	}
}
