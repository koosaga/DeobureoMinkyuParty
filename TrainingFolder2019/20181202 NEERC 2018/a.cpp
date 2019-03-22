
#include <bits/stdc++.h>

using namespace std;

using pii = pair<int ,int>;

queue<pair<int,int>> que[4][4];

pair<int, int> score[205][205], rev[4][4][205][205];
bool vis[4][4][205][205];

inline int dif(pair<int, int> d) {
	return d.first - d.second;
}

int main() {
	for(int i = 0; i <= 200; i++) {
		for(int j =0 ; j <= 200; j++) {
			score[i][j] = make_pair(-1000, -100);
		}
	}

	que[0][0].emplace(0, 0);
	score[0][0] = pii(0, 0);
	vis[0][0][0][0] = true;

	for(int x = 0; x <= 3; x++ ){
		for(int y = 0; y <= 3; y++) {
			if(x == 3 || y == 3) continue;

			while(!que[x][y].empty()) {
				int a, b; tie(a, b) = que[x][y].front(); que[x][y].pop();
				//printf("%d %d %d %d\n", x, y, a, b);

				auto go = [&a, &b, &x, &y](int nx, int ny, int na, int nb) {
					if(!vis[nx][ny][na][nb]) {
						vis[nx][ny][na][nb] = true;
						que[nx][ny].emplace(na, nb);
						rev[nx][ny][na][nb] = pii(na - a, nb - b);
					}
				};

				int F = (x+y == 4 ? 15 : 25);

				for(int i = 0; i <= F-2 && a+F <= 200 && b+i <= 200; i++) {
					go(x+1, y, a+F, b+i);
				}

				for(int i = F+1; b+i-2 <= 200 && a+i <= 200; i++) {
					go(x+1, y, a+i, b+i-2);
				}

				for(int i = 0; i <= F-2 && a+i <= 200 && b+F <= 200; i++) {
					go(x, y+1, a+i, b+F);
				}

				for(int i = F+1; i <= 200 && a+i-2 <= 200 && b+i <= 200; i++) {
					go(x, y+1, a+i-2, b+i);
				}
			}
		}
	}

	int m; scanf("%d", &m);
	while(m--) {
		int a, b; scanf("%d%d", &a, &b);
		int curx = -1, cury = 100;
		for(int x = 0; x <= 3; x++) {
			for(int y = 0; y <= 3; y++) {
				if(x == 3 || y == 3) {
					if(vis[x][y][a][b] && x - y > curx - cury) {
						curx = x;
						cury = y;
					}
				}
			}
		}
		if(curx < 0) {
			puts("Impossible");
			continue;
		}

		int x = curx, y = cury;

		printf("%d:%d\n", x, y);
		vector<pair<int, int>> ans;

		int rep = 100;
		while(x > 0 || y > 0) {
			if(rep-- == 0) {
				exit(-1);
			}
			int p, q; tie(p, q) = rev[x][y][a][b];
			//printf("%d %d / %d %d \n", a, b, p, q);
			//if(b == -205) exit(-1);
			ans.emplace_back(p, q);
			if(p > q) x -= 1; else y -= 1;
			a -= p;
			b -= q;
		}

		reverse(ans.begin(), ans.end());
		for(auto it : ans) {
			printf("%d:%d ", it.first, it.second);
		}
		puts("");
	}
	return 0;
}
