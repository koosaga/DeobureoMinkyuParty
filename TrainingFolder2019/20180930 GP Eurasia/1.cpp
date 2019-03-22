#include <bits/stdc++.h>
using namespace std;

int n, m, a[105][105];
string s;
int dx[256], dy[256];

int query(int x, int y){
	int ans = 0;
	for(int i=0; i<s.size(); i++){
		ans += a[x][y];
		x += dx[s[i]];
		y += dy[s[i]];
		if(x < 0 || y < 0 || x >= n || y >= m) return 0;
	}
	return ans + a[x][y];
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int tc;  cin >> tc;
	dx['U'] = -1;
	dx['D'] = 1;
	dy['L'] = -1;
	dy['R'] = 1;
	while(tc--){
		cin >> n >> m >> s;
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				cin >> a[i][j];
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				printf("%d ", query(i, j));
			}
			puts("");
		}
	}
}
