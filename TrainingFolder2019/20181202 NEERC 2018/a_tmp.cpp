#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> ans[205][205];
pair<int, int> score[205][205];


vector<pair<int, int>> now;

inline int dif(pair<int, int> d) {
	return d.first - d.second;
}

inline void go(int x, int y, int a, int b) { // set x:y, score a:b
	if(a > 200 || b > 200) return;

	if(dif(score[a][b]) > x - y) {
		return;
	}

	if(dif(score[a][b]) < x - y) {
		score[a][b] = make_pair(x, y);
		ans[a][b] = now;
	}

	if(x == 3 || y == 3) return;

	int F = (x+y == 4 ? 15 : 25);

	for(int i = 0; i <= F-2 && a+F <= 200 && b+i <= 200; i++) {
		now.emplace_back(F, i);
		go(x+1, y, a+F, b+i);
		now.pop_back();
	}

	for(int i = F+1; b+i-2 <= 200 && a+i <= 200; i++) {
		now.emplace_back(i, i-2);
		go(x+1, y, a+i, b+i-2);
		now.pop_back();
	}

	for(int i = 0; i <= F-2 && a+i <= 200 && b+F <= 200; i++) {
		now.emplace_back(i, F);
		go(x, y+1, a+i, b+F);
		now.pop_back();
	}

	for(int i = F+1; i <= 200 && a+i-2 <= 200 && a+i <= 200; i++) {
		now.emplace_back(i-2, i);
		go(x, y+1, a+i-2, a+i);
		now.pop_back();
	}
}


int main() {
	for(int i = 0; i <= 200; i++) {
		for(int j =0 ; j <= 200; j++) {
			score[i][j] = make_pair(-1000, -100);
		}

	}
	go(0, 0, 0, 0);
	//printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);

	for(int i = 0; i <= 200; i++) {
		for(int j = 0; j <= 200; j++) {
			if(score[i][j].first >= 0) {
				int x, y; tie(x, y) = score[i][j];
				printf("(%d, %d): [(%d, %d)", i, j, x, y);
				for(auto it : ans[i][j]) printf(", (%d, %d)", it.first, it.second);
				printf("],\n");
			}
		}
	}
	return 0;*/

	int m; scanf("%d", &m);
	while(m--) {
		int a, b; scanf("%d%d", &a, &b);
		int x, y; tie(x, y) = score[a][b];
		if(x < 0) {
			puts("Impossible");
			continue;
		}

		printf("%d:%d\n", x, y);
		for(auto it : ans[a][b]) printf("%d:%d ", it.first, it.second);
		puts("");
	}

	return 0;
}
