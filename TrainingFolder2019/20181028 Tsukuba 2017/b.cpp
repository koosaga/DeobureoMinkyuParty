#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;

int n;

struct point {
	int x, y;
	int operator* (point p) {
		return x * p.x + y * p.y;
	}
};

point points[20];

vector<pair<int, int>> dirs;
bool used[20];

int gcd(int x, int y) {
	return y ? gcd(y, x%y) : x;
}

pair<int, int> normalize(int x, int y) {
	if(x < 0) {
		x = -x;
		y = -y;
	}else if(x == 0 && y < 0) {
		y = -y;
	}
	int g = gcd(x, y);
	x /= g;
	y /= g;
	return make_pair(x, y);
}

int CNT = 0;
int ans =0;

void go(int u) {
	if(u == n) {
		auto now = dirs;
		sort(now.begin(), now.end());
		int ret = 0;
		for(int i = 0; i < now.size(); ) {
			int j = i;
			while(j < now.size() && now[i] == now[j]) j += 1;
			ret += (j - i) * (j - i - 1) / 2;
			i = j;
		}
		ans = max(ans, ret);
		CNT += 1;
		return;
	}
	if(used[u]) {
		go(u+1);
		return;
	}
	used[u] = true;
	for(int i = 0; i < n; i++) {
		if(!used[i]) {
			dirs.push_back(normalize(points[u].x - points[i].x, points[u].y - points[i].y));
			used[i] = true;
			go(u+1);
			used[i] = false;
			dirs.pop_back();
		}
	}
	used[u] = false;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &points[i].x, &points[i].y);
	}

	go(0);

	printf("%d\n",ans);

	return 0;
}