#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
using pi = pair<int, int>;

int s1, t1, s2, t2;

int n, a[MAXN];
int m, b[MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];
int gs1[MAXN][MAXN];
int gs2[MAXN][MAXN];

pi t(int l, int r){
	int ptime = t1 + gs1[l][r];
	int solved = n - (r - l) + s1;
	return pi(solved, -ptime);
}

pi u(int l, int r){
	int ptime = t2 + gs2[l][r];
	int solved = m - (r - l) + s2;
	return pi(solved, -ptime);
}

int f(int l1, int r1, int l2, int r2){
	if(dp[l1][r1][l2][r2]) return dp[l1][r1][l2][r2];
	pi cur1 = t(l1, r1);
	pi cur2 = u(l2, r2);
	int ret = 0;
	if(cur1 >= cur2){
		if(l2 == r2) return dp[l1][r1][l2][r2] = 1;
		pi cur3 = u(l2, r2 - 1);
		ret = max(ret, f(l1, r1, l2, r2 - 1) + (cur1 < cur3));
		pi cur4 = u(l2 + 1, r2);
		ret = max(ret, f(l1, r1, l2 + 1, r2) + (cur1 < cur4));
	}
	else{
		if(l1 == r1) return dp[l1][r1][l2][r2] = 1;
		pi cur3 = t(l1 + 1, r1);
		ret = max(ret, f(l1 + 1, r1, l2, r2) + (cur3 >= cur2));
		pi cur4 = t(l1, r1 - 1);
		ret = max(ret, f(l1, r1 - 1, l2, r2) + (cur4 >= cur2));
	}
	return dp[l1][r1][l2][r2] = ret;
}

int main(){
	cin >> s1 >> t1 >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	sort(a, a + n);
	cin >> s2 >> t2 >> m;
	for(int i=0; i<m; i++) cin >> b[i];
	sort(b, b + m);
	for(int i=0; i<=n; i++){
		for(int j=i; j<=n; j++){
			gs1[i][j] = accumulate(a, a + i, 0) + accumulate(a + j, a + n, 0);
		}
	}
	for(int i=0; i<=m; i++){
		for(int j=i; j<=m; j++){
			gs2[i][j] = accumulate(b, b + i, 0) + accumulate(b + j, b + m, 0);
		}
	}
	cout << f(0, n, 0, m) - 1 << endl;
}
