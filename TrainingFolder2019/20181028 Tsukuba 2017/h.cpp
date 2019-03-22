#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

int n, m;
int st[500], en[500];

namespace max_work {
	struct interval {
		int l, r;
		bool operator< (const interval &other) const {
			return r > other.r;
		}
	};

	int solve() {
		priority_queue<interval> pq;
		int ret = 0;
		for(int t = 1; t <= 400; t++) {
			for(int i = 0; i < n; i++) {
				if(st[i] == t) pq.push(interval{st[i], en[i]});
			}
			while(!pq.empty() && pq.top().r < t) {
				pq.pop();
			}
			if(!pq.empty()) {
				interval work = pq.top(); pq.pop();
				ret += 1;
			}
		}
		return ret;
	}
};

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &st[i], &en[i]);
	}

	printf("%d\n", max_work::solve());

	return 0;
}