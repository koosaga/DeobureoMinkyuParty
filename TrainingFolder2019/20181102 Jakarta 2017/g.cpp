#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int xs, ys, xe, ye, n;
int fx[MAXN], fy[MAXN], r[MAXN];

int main(){
	cin >> xs >> ys >> xe >> ye >> n;
	for(int i=0; i<n; i++){
		cin >> fx[i] >> fy[i] >> r[i];
	}
	disj.init(n + 2);
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			int dx = fx[i] - fx[j];
			int dy = fy[i] - fy[j];
			int dr = r[i] + r[j];
			if(1ll * dx * dx + 1ll * dy * dy < 1ll * dr * dr){
				disj.uni(i, j);
			}
		}
		if(fx[i] - r[i] < xs) disj.uni(i, n + 0);
		if(fx[i] + r[i] > xe) disj.uni(i, n + 1);
		if(fy[i] - r[i] < ys) disj.uni(i, n + 1);
		if(fy[i] + r[i] > ye) disj.uni(i, n + 0);
	}
	if(disj.uni(n, n + 1)) puts("YES");
	else puts("NO");
}
