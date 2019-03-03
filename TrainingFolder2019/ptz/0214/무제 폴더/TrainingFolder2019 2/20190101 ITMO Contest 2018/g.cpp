#include<bits/stdc++.h>

using namespace std;

using lint = long long ;

long long gcd(lint a, lint b) {
	return b ? gcd(b, a%b) : a;
}

int N, C;

vector<int> pos[int(1.1e6)];

lint a[int(1.1e6)], b[int(1.1e6)];

void add(int l, int r, lint p, lint q) {
	if(l > r) return;

	a[l] += p; a[r+1] += -p;
	b[l] += q; b[r+1] += -q;
	//printf("[%d, %d] %lld x + %lld\n", l, r, p, q);
}

int main() {
	scanf("%d%d", &N, &C);
	for(int i = 1; i <= N; i++) {
		int x; scanf("%d", &x);
		pos[x].push_back(i);
	}

	for(int c = 1; c <= C; c++) {
		vector<int> &xs = pos[c];

		if(pos[c].empty()) continue;
		add(1, xs[0] - 1, -1, xs[0]);
		for(int j = 1; j < xs.size(); j++) {
			int x = xs[j-1], y = xs[j];
			int m = (x + y) / 2;

			add(x, m, 1, -x);
			add(m+1, y, -1, y);
		}
		add(xs.back() + 1, N, 1, -xs.back());
	}

	lint ans = 1e18;
	for(int i = 1; i <= N; i++) {
		a[i] += a[i-1];
		b[i] += b[i-1];

		ans = min(ans, a[i] * i + b[i]);
		//printf("%d: %lld %lld\n", i, a[i], b[i]);
	}

	lint g = gcd(ans, C);
	printf("%lld/%lld\n", ans/g, C/g);


	return 0;
}