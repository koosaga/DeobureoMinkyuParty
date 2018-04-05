#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;
const int MAXN = 52;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const char chr[5] = "DRUL";

struct node{ int sx, sy, ex, ey; };
queue<node> que;

int n, m;
char str[MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN][MAXN];
int dis[MAXN][MAXN][MAXN][MAXN];
int par[MAXN][MAXN][MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#';
}

void enqueue(int sx, int sy, int ex, int ey, int d, int p = -1){
	if(!ok(sx, sy) || !ok(ex, ey)) return;
	if(vis[sx][sy][ex][ey]) return;
	if(d > 100) return;
	vis[sx][sy][ex][ey] = 1;
	dis[sx][sy][ex][ey] = d;
	par[sx][sy][ex][ey] = p;
	que.push({sx, sy, ex, ey});
}

void bfs(){
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			node nd = {x.sx - dx[i], x.sy - dy[i], x.ex + dx[i], x.ey + dy[i]};
			enqueue(nd.sx, nd.sy, nd.ex, nd.ey, dis[x.sx][x.sy][x.ex][x.ey] + 2, i);
		}
	}
}

string trace(pi s, pi e){
	if(s == e) return "";
	if(dis[s.first][s.second][e.first][e.second] == 1){
		string ret;
		for(int j=0; j<4; j++){
			if(s.first + dx[j] == e.first && s.second + dy[j] == e.second){
				ret.push_back(chr[j]);
			}
		}
		return ret;
	}
	int val = par[s.first][s.second][e.first][e.second];;
	string tmp = trace(pi(s.first + dx[val], s.second + dy[val]), pi(e.first - dx[val], e.second - dy[val]));
	string x; x.push_back(chr[val]);
	return x + tmp + x;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] != '#'){
				enqueue(i, j, i, j, 0);
			}
			if(j+1 < m && str[i][j] != '#' && str[i][j+1] != '#'){
				enqueue(i, j, i, j+1, 1);
			}
			if(i+1 < n && str[i][j] != '#' && str[i+1][j] != '#'){
				enqueue(i, j, i+1, j, 1);
			}
		}
	}
	bfs();
	queue<pi> que;
	int nd[MAXN][MAXN];
	pi np[MAXN][MAXN];
	memset(nd, 0x3f, sizeof(nd));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'S'){
				que.push(pi(i, j));
				nd[i][j] = 0;
			}
		}
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(vis[x.first][x.second][i][j] && nd[i][j] > nd[x.first][x.second] + 1){
					nd[i][j] = nd[x.first][x.second] + 1;
					np[i][j] = x;
					que.push(pi(i, j));
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'F' && nd[i][j] < 20000){
				vector<pi> pth;
				for(pi p = pi(i, j); ; p = np[p.first][p.second]){
					pth.push_back(p);
					if(str[p.first][p.second] == 'S') break;
				}
				reverse(pth.begin(), pth.end());
				vector<string> ret;
				for(int i=1; i<pth.size(); i++) ret.push_back(trace(pth[i-1], pth[i]));
				cout << ret.size() << endl;
				for(auto &i : ret) cout << i << endl;
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}

