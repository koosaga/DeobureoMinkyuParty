#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

#define left asd
#define right asdf

using lint = long long;

const int sz = 20000000;

int n;

int NODES;

int left[sz], right[sz];
char state[sz], here[sz];

void upd(int nd, lint nl, lint nr, lint l, lint r, int v) {
	if(nl == l && nr == r) {
		here[nd] |= v;
		state[nd] |= v;
		if(here[nd] == 3) {
			puts("-1");
			exit(0);
		}
		return;
	}

	lint nm = (nl + nr) >> 1;
	if(l < nm) {
		if(!left[nd]) left[nd] = ++NODES;
		upd(left[nd], nl, nm, l, min(r, nm), v);
	}
	if(nm < r) {
		if(!right[nd]) right[nd] = ++NODES;
		upd(right[nd], nm, nr, max(nm, l), r, v);
	}
	state[nd] = state[left[nd]] | state[right[nd]] | here[nd];
}

vector<string> ans;

void go(int nd, lint nl, lint nr, int k, char par = 0) {
	if(nd == 0) return;

	bool has_plus = ((state[nd] | par) & 1) == 1;
	bool has_minus = ((state[nd] | par) & 2) == 2;
	
	if(!has_minus) {
		return;
	}
	if(!has_plus) {
		static char tmp[30];
		long long sz = nl;
		lint a[4];
		for(int i = 0; i < 4; i++) {
			a[i] = sz & 255;
			sz >>= 8;
		}
		sprintf(tmp, "%lld.%lld.%lld.%lld/%d", a[3], a[2], a[1], a[0], k);
		ans.push_back(tmp);
		return;
	}

	if(!left[nd] && !right[nd]) {
		puts("-1");
		exit(0);
	}

	long long nm = (nl + nr) >> 1;
	go(left[nd], nl, nm, k+1, par | here[nd]);
	go(right[nd], nm, nr, k+1, par | here[nd]);
}

int main(){

	NODES = 1;

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		static char line[50];

		scanf("%s", line);
		int len = strlen(line);
		int x = 32;
		for(int i = 0; i < len; i++) {
			if(line[i] == '/') {
				sscanf(line+i+1, "%d", &x);
				line[i] = 0;
				break;
			}
		}

		long long a, b, c, d;
		sscanf(line+1, "%lld.%lld.%lld.%lld", &a, &b, &c, &d); // TODO
		
		long long l = (a << 24) | (b << 16) | (c << 8) | d;
		long long r = l + (1ll << (32-x));

		upd(1, 0, 1ll << 32, l, r, line[0] == '+' ? 1 : 2);
	}

	go(1, 0, 1ll<<32, 0);

	printf("%u\n", ans.size());
	for(string line : ans) {
		printf("%s\n", line.c_str());
	}


	return 0;
}