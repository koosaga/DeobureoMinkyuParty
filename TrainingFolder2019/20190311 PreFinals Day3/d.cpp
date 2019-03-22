#include <bits/stdc++.h>

using namespace std;

double tb[1<<8][1<<8];
bool used[1<<8][1<<8];

int a[8][8];
int n1, n2, n;
int x[8],y[8];

double go (int s1, int s2) {
	if(s1 == 0 && s2 == 0) {
		return 0.5;
	}
	if(s1 == 0) {
		return 0;
	}
	if(s2 == 0) {
		return 1;
	}
	if(used[s1][s2]) {
		return tb[s1][s2];
	}
	
	double ret = 0;
	
	for(int i = 0; i < n1; i++) if((s1 >> i) & 1) {
		double worst = 1e18;
		for(int j = 0; j < n2; j++) if((s2 >> j) & 1) {
			int ns1 = s1, ns2 = s2;
			double cur = 0;
			if(x[i] == y[j]) {
				ns1 ^= 1<<i;
				ns2 ^= 1<<j;
				cur += 0;
			}else if(!A[x[i]][y[j]]) {
				ns1 ^= 1<<i;
			}else {
				ns2 ^= 1<<j;
				cur += 1;
			}
			cur += go(ns1, ns2);
			worst = min(worst, cur);
		}
		ret = max(ret, worst);
	}
	
	used[s1][s2] = true;
	tb[s1][s2] = ret;
	return ret;	
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	
	scanf("%d", &n1);
	for(int i = 0; i < n1; i++) {
		scanf("%d", &x[i]);
	}
	scanf("%d", &n2);
	for(int i = 0; i < n2; i++) {
		scanf("%d", &y[i]);
	}
	
	return 0;
}
