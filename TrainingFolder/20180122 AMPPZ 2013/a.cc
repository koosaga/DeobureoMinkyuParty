#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[MAXN];
int s[MAXN], e[MAXN];

bool trial1(double x){ 
	// lower bound
	double mxp = -1e18;
	for(int j=n; j>=0; j--){
		if(j - s[j] * x < mxp) return 0;
		mxp = max(mxp, j - e[j] * x);
	}
	return true;
}
bool trial2(double x){ 
	// upper bound
	double mnp = -1e18;
	for(int j=0; j<=n; j++){
		if(j - s[j] * x < mnp) return 0;
		mnp = max(mnp, j - e[j] * x);
	}
	return true;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<=n; i++) s[i] = a[i], e[i] = a[i+1];
	s[0] = -1e9 - 100;
	e[n] = 2e9 + 100;
	double s = 0, e = 1e9;
	for(int i=0; i<100; i++){
		double m = (s+e)/2;
		if(trial1(m)) e = m;
		else s = m;
	}
	double ts = 0, te = 1e9;
	for(int i=0; i<100; i++){
		double m = (ts+te)/2;
		if(trial2(m)) ts = m;
		else te = m;
	}
	printf("%.10f %.10f\n", 1 / ts, 1 / s);
}
