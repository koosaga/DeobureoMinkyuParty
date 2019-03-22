#include <bits/stdc++.h>
using namespace std;

const double PI = acosl(-1);

int y[int(1.1e5)];
int v[int(1.1e5)];

void solve(){
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 1; i <= n; i++) scanf("%d", &y[i]);
	for(int i = 0; i <= n; i++) scanf("%d", &v[i]);
	y[n+1] = b;

	if(a == 0) {
		double ans = 0;
		for(int i = 0; i <= n; i++) {
			ans += (double)(y[i+1] - y[i]) / v[i];
		}
		printf("%.20lf\n", ans);
		return;
	}
	
	double ans = 1e18;
	
	auto f = [&n,&a,&b,&ans](double mid) {
		double x = 0, cos_ang = cos(mid);
	
		for(int i = 0; i <= n; i++) {
			double cot_ang = cos_ang / sqrt(1 - cos_ang * cos_ang);
			x += (y[i+1] - y[i]) * cot_ang;
			if(i == n) break;
			double nxt = cos_ang * v[i+1] / v[i];
			if(nxt >= 1) {
				x = 1e18;
				break;
			}
			assert(nxt > 0);
			cos_ang = nxt;
		}
		return x;
	};
	
	auto g = [&n,&a,&b,&ans](double mid) {
		double x = 0, cos_ang = cos(mid);
	
		double cur = 0;
		for(int i = 0; i <= n; i++) {
			double cot_ang = cos_ang / sqrt(1 - cos_ang * cos_ang);
			x += (y[i+1] - y[i]) * cot_ang;
			cur += (y[i+1] - y[i]) * sqrt(1 + cot_ang * cot_ang) / v[i];
		
			if(i == n) break;
			double nxt = cos_ang * v[i+1] / v[i];
			if(nxt >= 1) {
				x = 1e18;
				cur = 1e18;
				break;
			}
			assert(nxt > 0);
			cos_ang = nxt;
		}
		ans = cur;
		return x;
	};
	
	{
		double low = 0, high = PI / 2;
		for(int rep = 0; rep < 50; rep++) {
			double mid = (low + high) / 2;
		
			if(f(mid) > a) {
				low = mid;	
			}else {
				high = mid;
			}
		}
		g(low);
	}
	printf("%.20lf\n", ans);
}

int main(){
	int tc; cin >> tc;
	while(tc--){
		solve();
	}
}

/*3.53436796962887286194
18.56307374237399555883
*/
