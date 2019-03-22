#include <bits/stdc++.h>

using namespace std;

int W, H;

struct point {
	int x, y;
	point(int x_ = 0, int y_ = 0): x(x_), y(y_) { }
	bool valid() { return 0 <= x && x < W && 0 <= y && y < H;}
	point operator+(point p) { return point(x+p.x, y+p.y); }
	point operator-(point p) { return point(x-p.x, y-p.y); }
	bool operator== (const point &p) const { return p.x == x && p.y == y; }
	bool operator!= (const point &p) const { return p.x != x || p.y != y; }
};

const point adj[6] = {
	point(-1, -1),
	point(0, -1),
	point(1, 0),
	point(1, 1),
	point(0, 1),
	point(-1, 0),
};

char A[105][105], B[105][105];
bool RV[105][105][6];
int R;
int M;

struct state {
	point p;
	int x, y;
	int m;
	state(point p_ = point(), int m_ = 0): p(p_), m(m_ ), x(p.x), y(p.y) { }
	bool operator< (const state &s) const {
		return m < s.m;
	};
	char a() { return A[p.x][p.y]; }
	char b() { return B[p.x][p.y]; }
};

int tb[105][105];
int tim[105][105];
int min_turns[105][105];
int max_mp[105][105];
int add[105][105];
point rev[105][105];

int main() {
	scanf("%d%d", &W, &H);
	for(int j = 0; j < H; j++) {
		for(int i = 0; i < W; i++) {
			char s[3]; scanf("%s", s);
			A[i][j] = s[0];
			B[i][j] = s[1];
			tim[i][j] = -1;
			min_turns[i][j] = 1e9;
			max_mp[i][j] = -1;
		}
	}

	scanf("%d", &R);
	for(int i = 0; i < R; i++) {
		int xa, ya, xb, yb;
		scanf("%d%d%d%d", &xa,&ya,&xb,&yb);
		point a(xa, ya);
		point b(xb, yb);
		for(int rep=0;rep<2;rep++) {
			RV[a.x][a.y][find(adj, adj+6, b-a) - adj] = true;
			swap(a, b);
		}
	}

	scanf("%d", &M);

	point st, en;
	scanf("%d%d", &st.x, &st.y);
	scanf("%d%d", &en.x, &en.y);

	priority_queue<state> pq[2];
	pq[0].emplace(st, M);
	tim[st.x][st.y] = 0;
	max_mp[st.x][st.y] = M;
	min_turns[st.x][st.y] = 0;

	for(int turns = 0; ; turns++) {
		auto &nxt = pq[~turns & 1];
		while(!nxt.empty()) {
			nxt.pop();
		}

		auto &now = pq[turns & 1];
		while(!now.empty()) {
			state s = now.top(); now.pop();
			if(min_turns[s.x][s.y] < turns) {
				continue;
			}
			if(max_mp[s.x][s.y] > s.m) {
				continue;
			}
			for(int di = 0; di < 6; di++) {
				point d = adj[di];
				state t(s.p + d, s.m);
				if(!t.p.valid()) {
					continue;
				}

				if(t.a() == 'm') {
					continue;
				}
				t.m -= 1;
				if(RV[s.x][s.y][di]) {
					t.m = 0;
				}
				if(s.a() == 'p' && t.a() == 'h') {
					t.m -= 1;
				}
				if(t.b() == 'f' || t.b() == 'm') {
					t.m -= 1;
				}

				if(tim[t.x][t.y] < turns) {
					tim[t.x][t.y] = turns;
				}

				if(t.m <= 0 && min_turns[t.x][t.y] > turns+1) {
					nxt.emplace(t.p, M);
					min_turns[t.x][t.y] = turns+1;
					max_mp[t.x][t.y] = M;
					add[t.x][t.y] = -1;
					rev[t.x][t.y] = s.p;
				}

				if(t.m > 0 && 
					(min_turns[t.x][t.y] > turns
					|| (min_turns[t.x][t.y] == turns && max_mp[t.x][t.y] < t.m))) {
					min_turns[t.x][t.y] = turns;
					max_mp[t.x][t.y] = t.m;
					rev[t.x][t.y] = s.p;
					now.push(t);
				}
			}
		}

		if(min_turns[en.x][en.y] < int(1e9)) {
			puts("Come this way");
			printf("%d\n", min_turns[en.x][en.y] + add[en.x][en.y] + 1);
			//printf( " > > %d\n", max_mp[en.x][en.y]);
			vector<point> path;
			for(point p = en; p != st; p = rev[p.x][p.y]) {
				//printf(" >> %d %d\n", p.x, p.y);
				path.push_back(p);
			}
			path.push_back(st);
			reverse(path.begin(), path.end());
			printf("%lu\n", path.size());
			for(point p : path) {
				printf("%d %d\n", p.x, p.y);
				//printf("%d %d ( %d %d\n", p.y, p.x, min_turns[p.x][p.y], max_mp[p.x][p.y ]);
			}
			return 0;
		}

		if(nxt.empty()) {
			break;
		}
	}

	puts("They shall not pass");
	return 0;
}