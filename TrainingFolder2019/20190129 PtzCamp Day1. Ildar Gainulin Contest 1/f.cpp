#include <bits/stdc++.h>
const int MAXN = 100005;
int n, m;
using namespace std;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x]== x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	int ret = 0;
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(disj.uni(s, e)) ret++;
	}
	cout << m - ret << endl;
}
