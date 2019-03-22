#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int n;
pi a[1005];
int sx = 1e9, ex = -1e9, sy = 1e9, ey = -1e9;

int dist(pi a, pi b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(){
	freopen("intel.in", "r", stdin);
	freopen("intel.out", "w", stdout);
	cin >> n;
	int ret = 0;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		sx = min(sx, a[i].first);
		ex = max(ex, a[i].first);
		sy = min(sy, a[i].second);
		ey = max(ey, a[i].second);
	}
	for(int i=0; i<n; i++) ret += dist(a[i], a[(i+1)%n]);
	ret -= 2 * (ex - sx) + 2 * (ey - sy);
	cout << ret << endl;
}
