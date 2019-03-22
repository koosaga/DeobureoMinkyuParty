#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;

int n, m, s;
int a[MAXN], b[MAXN], c[MAXN];

bool trial(double T){
	double ret = 0;
	for(int i=1; i<=n; i++){
		if(b[i] == 0) continue;
		double x = max(0.0, T * b[i] - a[i]);
		ret += x * c[i];
		if(ret > s) return false;
	}
	return true;
}

int main(){
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int tc;  cin >> tc;
	while(tc--){
		memset(b, 0, sizeof(b));
		cin >> n >> m >> s;
		for(int i=0; i<m; i++){
			int x;
			scanf("%d",&x);
			b[x]++;
		}
		for(int i=1; i<=n; i++){
			scanf("%d %d",&a[i],&c[i]);
		}
		double s = 0, e = 2e9;
		for(int i=0; i<100; i++){
			double m = (s+e)/2;
			if(trial(m)) s = m;
			else e = m;
		}
		printf("%.10f\n", s);
	}
}
