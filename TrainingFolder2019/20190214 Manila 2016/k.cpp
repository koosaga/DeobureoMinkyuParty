#include <bits/stdc++.h>
using namespace std;

int n;
double c, x[1005], y[1005];
double xs[1005], ys[1005], xys[1005], xxs[1005], yys[1005];
double dp[1005];

double getvar(vector<double> v){
	double sum = 0;
	double sumsq = 0;
	for(auto &i : v){
		sum += i;
		sumsq += i * i;
	}
	sum /= v.size();
	sumsq /= v.size();
	return sumsq - sum * sum;
}

double cost(int l, int r){
	if(l == r) return c;
	vector<double> vx;
	double sumx = xs[r] - xs[l-1];
	double sumy = ys[r] - ys[l-1];
	double sumxy = xys[r] - xys[l-1];
	double sumxx = xxs[r] - xxs[l-1];
	sumxy /= r - l + 1;
	sumx /= r - l + 1;
	sumy /= r - l + 1;
	sumxx /= r - l + 1;
	double varx = sumxx - sumx * sumx;
	double alp = (sumxy - sumx * sumy) / varx;
	double sum = (ys[r] - ys[l-1]) - alp * (xs[r] - xs[l-1]);
	double sumsq = (yys[r] - yys[l-1]) - 2 * alp * (xys[r] - xys[l-1]) + alp * alp * (xxs[r] - xxs[l-1]);
	sum /= r - l + 1;
	sumsq /= r - l + 1;
	double varvar = sumsq - sum * sum;
	return varvar * (r - l + 1) + c;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		cin >> n >> c;
		for(int i=1; i<=n; i++){
			int xv, yv;
			scanf("%d %d",&xv,&yv);
			x[i] = xv;
			y[i] = yv;
			xs[i] = xs[i-1] + x[i];
			ys[i] = ys[i-1] + y[i];
			xys[i] = xys[i-1] + x[i] * y[i];
			xxs[i] = xxs[i-1] + x[i] * x[i];
			yys[i] = yys[i-1] + y[i] * y[i];
		}
		for(int i=1; i<=n; i++){
			dp[i] = 1e9;
			for(int j=0; j<i; j++){
				dp[i] = min(dp[j] + cost(j + 1, i), dp[i]);
			}
		}
		printf("%.10f\n", dp[n]);
	}

}
