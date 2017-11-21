#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<llf, llf> pi;
const int MAXN = 1005;

bool cmp(pi a, pi b){
	return a.second * b.first + b.second <
	b.second * a.first + a.second;
}

pi a[MAXN];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int m;
		scanf("%d",&m);
		vector<int> v(m);
		for(auto &j : v) scanf("%d",&j);
		sort(v.begin(), v.end());
		pi func(0, 0);
		double prob = 1;
		for(int i=0; i<v.size(); i++){
			double cur = v[i] * 0.001;
			func.first += prob * (1 - cur);
			func.second += prob * (1 - cur) * (i + 1);
			prob *= cur;
		}
		func.second += v.size() * prob;
		a[i] = func;
	}
	sort(a, a+n, cmp);
	double x = 0;
	for(int i=0; i<n; i++){
		x = a[i].first * x + a[i].second;
	}
	printf("%.10f\n", x);
}
