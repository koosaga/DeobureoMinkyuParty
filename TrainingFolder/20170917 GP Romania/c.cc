#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
char str[MAXN][MAXN];
char ret[MAXN][MAXN];
int cmp[MAXN][MAXN];
int hei[MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m && !cmp[x][y] && str[x][y] == '#';
}

queue<pi> que;

void bfs(int x, int y, int c){
	que.push(pi(x, y));
	cmp[x][y] = c;
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			if(ok(x.first + dx[i], x.second + dy[i])){
				cmp[x.first + dx[i]][x.second + dy[i]] = c;
				hei[x.first + dx[i]][x.second + dy[i]] = hei[x.first][x.second] + dx[i];
				que.push(pi(x.first + dx[i], x.second + dy[i]));
			}
		}
	}
}

vector<pi> gph[2000005];
int dis[2000005], inq[2000005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	int cnt = 0;
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<m; j++){
			if(!cmp[i][j] && str[i][j] == '#'){
				bfs(i, j, ++cnt);
			}
		}
	}
	for(int i=0; i<m; i++){
		int prv = 0, prp = 0;
		for(int j=n-1; j>=0; j--){
			if(cmp[j][i] && prv != cmp[j][i]){
				int cst = prp - hei[j][i] - 1;
				gph[prv].push_back(pi(cst, cmp[j][i]));
				prv = cmp[j][i];
			}
			if(cmp[j][i]) prp = hei[j][i];
		}
	}
	queue<int> que;
	que.push(0);
	inq[0] = 1;
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = n;
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		inq[x] = 0;
		for(auto &i : gph[x]){
			if(dis[i.second] > dis[x] + i.first){
				dis[i.second] = dis[x] + i.first;
				if(!inq[i.second]){
					inq[i.second] = 1;
					que.push(i.second);
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) ret[i][j] = '.';
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '.') continue;
			int cur = i - hei[i][j];
			cur = dis[cmp[i][j]] - cur;
			ret[i+cur][j] = '#';
		}
	}
	for(int i=0; i<n; i++) puts(ret[i]);
}
