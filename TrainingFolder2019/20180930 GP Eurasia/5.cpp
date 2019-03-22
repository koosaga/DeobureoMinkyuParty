#include <bits/stdc++.h>

using namespace std;


const int N_ = 100500;

long long albs(long long x) {
	return x < 0? -x : x;
}

int T;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	for(scanf("%d", &T); T--; ){
		long long y; scanf("%lld", &y);
		bool good = !true;
		for(long long x = -100; x <= 100; x++) {
			long long a = 1; // (t - x) (t - y);
			long long b = -(x + y);
			long long c = x * y;
			if(b != 0 && c != 0 && albs(b) <= 1000000 && albs(c) <= 1000000) {
				printf("%lld %lld %lld\n", a, b, c);
				good = true;
				break;
			}
		}
		assert(good);
	}
	return 0;
}