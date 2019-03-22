#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 50005;

int n, q, a[MAXN];
int PC, NC;
pi P[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int main(){
	printf("5000 5000\n");
	for(int i=1; i<=5000; i++){
		a[i] = rand() % 100 + 1;
		if(rand() & 1) a[i] = -a[i];
		printf("%d ", a[i]);
	}
	puts("");
	for(int i=0; i<5000; i++){
		int v = rand() % 100 + 1;
		if(rand() & 1) v = -v;
		printf("%d %d\n", rand()%5000+1, v);
	}
}

