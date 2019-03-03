#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 50005;

int k, n, m, a[10][MAXN];
int p[MAXN];

bool cmp(int x, int y){
	int cnt = 0;
	for(int i=0; i<k; i++){
		if(a[i][x] < a[i][y]) cnt++;
		else cnt--;
	}
	return cnt > 0;
}

int main(){
	scanf("%d %d %d",&k,&n,&m);
	for(int i=0; i<k; i++){
		for(int j=1; j<=n; j++){
			int x; scanf("%d",&x);
			a[i][x] = j;
		}
	}
	iota(p, p + n, 1);
	sort(p, p + n, cmp);
	for(int i=0; i<m; i++) printf("%d ", p[i]);
}
