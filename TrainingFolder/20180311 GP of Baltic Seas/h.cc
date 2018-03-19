#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 105;
const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};

struct node{
	int x, y;
	lint z;
	bool operator<(const node &n)const{
		return z > n.z;
	}
};

lint dis[MAXN][MAXN];

int n, m, q;
int x[MAXN*MAXN], y[MAXN*MAXN], z[MAXN*MAXN];

priority_queue<node> pq;
bool ok(int x, int y){
	return min(x, y) >= 1 && max(x, y) <= n;
}

int main(){
	cin >> n >> m >> q;
	for(int i=0; i<q; i++){
		cin >> x[i] >> y[i] >> z[i];
	}
	memset(dis, 0x3f, sizeof(dis));
	for(int i=0; i<q; i++){
		for(int j=0; j<i; j++){
			int dx = abs(x[i] - x[j]) + abs(y[i] - y[j]);
			if(1ll * dx * m < 1ll * abs(z[i] - z[j])){
				puts("NO");
				return 0;
			}
		}
		dis[x[i]][y[i]] = z[i];
		pq.push({x[i], y[i], z[i]});
	}
	puts("YES");
	while(!pq.empty()){
		auto n = pq.top();
		pq.pop();
		if(dis[n.x][n.y] != n.z) continue;
		for(int i=0; i<4; i++){
			if(ok(n.x + dx[i], n.y + dy[i]) && 
				dis[n.x + dx[i]][n.y + dy[i]] > n.z + m){
				dis[n.x + dx[i]][n.y + dy[i]] = n.z + m;
				pq.push({n.x + dx[i], n.y + dy[i], n.z + m});
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			dis[i][j] = min(dis[i][j], 1000000000ll);
			printf("%lld ", dis[i][j]);
		}
		puts("");
	}
}
