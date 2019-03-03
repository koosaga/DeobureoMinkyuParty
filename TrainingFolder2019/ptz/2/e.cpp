#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const double PI = acos(-1);

struct disj{
	int pa[MAXN], chk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(chk, chk + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
	void ck(int x){
		chk[find(x)] = 1;
	}
	bool haschk(int x){ return chk[find(x)]; } 
}disj;

int n, R, x[MAXN], y[MAXN], r[MAXN];

int dist(int v, int w){
	return (x[v] - x[w]) * (x[v] - x[w]) + (y[v] - y[w]) * (y[v] - y[w]);
}

bool has_outside(int v){
	int dist = x[v] * x[v] + y[v] * y[v];
	if(R - r[v] <= 0) return 1;
	return dist >= (R - r[v]) * (R - r[v]);
}

double solve(int v){
	if(!has_outside(v)) return 2 * PI * r[v];
	if(x[v] * x[v] + y[v] * y[v] >= (R + r[v]) * (R + r[v])) return 0;
	double dist = hypot(x[v], y[v]);
	double R1 = r[v];
	double R2 = R;
	double theta1 = (R1 * R1 + dist * dist - R2 * R2) / (2 * R1 * dist);
	double theta2 = (R2 * R2 + dist * dist - R1 * R1) / (2 * R2 * dist);
	theta1 = 2 * acos(theta1);
	theta2 = 2 * acos(theta2);
	return theta1 * R1 - theta2 * R2;
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&R);
		for(int i=0; i<n; i++){
			scanf("%d %d %d",&x[i],&y[i],&r[i]);
		}
		disj.init(n);
		for(int i=0; i<n; i++){
			if(has_outside(i)) disj.ck(i);
			for(int j=0; j<i; j++){
				if(dist(i, j) == (r[i] + r[j]) * (r[i] + r[j])){
					disj.uni(i, j);
				}
			}
		}
		double ret = 2 * PI * R;
		for(int i=0; i<n; i++){
			if(disj.haschk(i)){
				ret += solve(i);
			}
		}
		printf("%.10f\n", ret);
	}
}
