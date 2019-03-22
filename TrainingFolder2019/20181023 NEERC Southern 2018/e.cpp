#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

using ll = long long;

int n, m; long long t;
int p[int(2.1e5)];

void solve() {
	scanf("%d%d%lld", &n, &m, &t);
	for(int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}

	auto go = [&](long long d) {
		long long tot = 0;
		long long used = 0;
		int cnt = 0;
		for(int i = 0; i < n; i++) {
			if(p[i] <= d) {
				used += p[i];
				cnt += 1;
				tot += p[i];
				if(cnt % m == 0) {
					used += tot;
					tot = 0;
				}
			}
		}
		return make_pair(cnt, used);
	};

	int low = 1, high = 200000, best = -1;
	if(high > t) high = t;
	while(low <= high) {
		int mid = (low + high) >> 1;
		if(go(mid).second <= t) {
			best = mid;
			low = mid + 1;
		}else {
			high = mid - 1;
		}
	}

	pair<int, int> ans(-1, -1);
	for(int d = best-2; d <= best+2; d++) {
		if(d < 1 || d > 200001 || d > t) continue;
		long long tot = 0, used = 0;
		int cnt = 0;
		for(int i = 0; i < n; i++) if(p[i] <= d) {
			tot += p[i];
			cnt += 1;
			used += p[i];
			if(used > t) {
				cnt -= 1;
				break;
			}
			if(cnt % m == 0) {
				used += tot;
				tot = 0;
			}
			if(used > t) {
				break;
			}
		}
		ans = max(ans, make_pair(cnt, d));
	}

	printf("%d %d\n", ans.first, ans.second);

}

int main(){
	int t; scanf("%d", &t);
	while(t--) { solve() ;}
	return 0;
}