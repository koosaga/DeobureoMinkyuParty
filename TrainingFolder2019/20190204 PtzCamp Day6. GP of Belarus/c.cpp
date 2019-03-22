#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<int, lint>;

int n;
lint a[MAXN];
double l[MAXN], r[MAXN], m[MAXN], minVal[MAXN], maxVal[MAXN];

double ccw(pi a, pi b, pi c){
	double dx1 = b.first - a.first;
	double dy1 = b.second - a.second;
	double dx2 = c.first - a.first;
	double dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		a[i] = a[i-1] + x;
	}
	fill(r + 1, r + n + 1, 1e9);
	for(int i=0; i<60; i++){
		for(int j=1; j<=n; j++){
			m[j] = (l[j] + r[j]) / 2;
		}
		vector<pi> stk;
		for(int j=0; j<=n; j++){
			while(stk.size() >= 2 && ccw(stk[stk.size()-2], stk.back(), pi(j, a[j])) <= 0){
				stk.pop_back();
			}
			stk.push_back(pi(j, a[j]));
			int s = 0, e = stk.size() - 1;
			double grad = m[j + 1];
			while(s != e){
				int m = (s + e) / 2;
				if(stk[m].second - stk[m].first * grad < stk[m+1].second - stk[m+1].first * grad){
					e = m;
				}
				else s = m + 1;
			}
			minVal[j] = stk[s].second - stk[s].first * grad;
		}
		stk.clear();
		for(int j=n; j>=0; j--){
			while(stk.size() >= 2 && ccw(stk[stk.size()-2], stk.back(), pi(j, a[j])) <= 0){
				stk.pop_back();
			}
			stk.push_back(pi(j, a[j]));
			int s = 0, e = stk.size() - 1;
			double grad = m[j];
			while(s != e){
				int m = (s + e) / 2;
				if(stk[m].second - stk[m].first * grad > stk[m+1].second - stk[m+1].first * grad){
					e = m;
				}
				else s = m + 1;
			}
			maxVal[j] = stk[s].second - stk[s].first * grad;
		}
		for(int j=1; j<=n; j++){
			if(minVal[j - 1] <= maxVal[j]) l[j] = m[j];
			else r[j] = m[j];
		}
	}
	for(int i=1; i<=n; i++) printf("%.10f\n", l[i]);
}
