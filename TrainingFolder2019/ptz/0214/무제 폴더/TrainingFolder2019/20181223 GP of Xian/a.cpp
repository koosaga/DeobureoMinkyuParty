#include <bits/stdc++.h>
using namespace std;

lint mst[MAXN], tot;

int n, k, m;

int main(){
	scanf("%d %d %d",&n,&k,&m);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		v.push_back({s, e + n, x});
		v.push_back({s + n, e + n + n, x});
	}
}
