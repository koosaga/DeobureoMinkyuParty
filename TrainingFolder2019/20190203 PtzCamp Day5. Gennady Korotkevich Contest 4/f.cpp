#include <bits/stdc++.h>
using lint = long long;
using namespace std;
using pi = pair<int, int>;
const int MAXN = 500005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
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
}disj;

int deg[MAXN], hasSpan[MAXN];
int n, m;
pi a[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=m; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		deg[a[i].first]++;
		deg[a[i].second]++;
	}
	lint ret = 0;
	disj.init(n);
	for(int i=1; i<=m; i++){
		int x, y; tie(x, y) = a[i];
		if(disj.uni(x, y)){
			if(hasSpan[x]) ret += i;
			if(hasSpan[y]) ret += i;
			ret += 1ll * (deg[x] + deg[y] - 3) * i;
			hasSpan[x] = hasSpan[y] = 1;
		}
		else{
			ret += 1ll * (deg[x] + deg[y] - 2) * i;
		}
		deg[x]--;
		deg[y]--;
	}
	cout << ret << endl;
}
