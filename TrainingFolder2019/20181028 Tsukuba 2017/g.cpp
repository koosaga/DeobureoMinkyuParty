#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

vector<char> go() {
	static char tmp[3];
	int d, l;
	scanf("%s%d%d", tmp, &d, &l);

	int angle = d;
	switch(*tmp) {
		case 'D': break;
		case 'B': angle += 60; break;
		case 'C': angle += 120; break;
	}
	angle = -angle;

	llf x = l * cos(angle * PI / 180.0);
	llf y = l * sin(angle * PI / 180.0);

	llf a = x + y / sqrt((llf)3);
	llf b = -2 * y / sqrt((llf)3);

	const char mp[2][5] = {"AB", "DC"};
	vector<char> ret;

	for(int q = 0; q < 100; q += 1) {
		for(int p = -100; p <= 100; p += 1) {
			if(p < a && a < p+1 && q < b && b < q+1) {
				ret.push_back(mp[~p&1][q&1]);
				ret.push_back(mp[p&1][~q&1]);
				if(a + b < p + q + 1) {
					ret.push_back(mp[p&1][q&1]);
				}else {
					ret.push_back(mp[~p&1][~q&1]);
				}
			}
		}
	}

	assert(ret.size() % 3 == 0);
	sort(ret.begin(), ret.end());

//	for(char c : ret) putchar(c); puts("");

	return ret;
}

int main() {
	set<vector<char>> cur;
	for(int rep = 0; rep < 2; rep++) {
		cur.insert(go());
	}
	puts(cur.size() == 1 ? "YES" : "NO");
	return 0;
}