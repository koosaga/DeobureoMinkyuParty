#include <bits/stdc++.h>

using llf = long double;

const llf pi = acosl(-1);

int T;

llf solve (llf y) {
	llf low = 1e-9, high = pi;
	for(int rep = 0; rep < 50; rep++) {
		llf mid = (low + high) / 2;
		if(sin(mid) / mid > y) {
			low = mid;
		}else {
			high = mid;
		}
	}
	return low;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		int K_, L_;
		llf K, L; 
		scanf("%d%d", &K_,&L_);
		K = K_; L = L_;

		llf ans = 0;
		// case 1
		{
			auto calc = [&K, &L](llf v) {
				llf R = L / 2 / (pi - v);
				return R * (L + R * sinl(2 * v)) / 2;
			};

			llf low = 0, high = pi - solve(K / L);
			for(int rep = 0; rep < 100; rep++) {
				llf m1 = (low * 2 + high) / 3;
				llf m2 = (low + 2 * high) / 3;
				if(calc(m1) < calc(m2)) {
					low = m1;
				}else {
					high = m2;
				}
			}

			llf v = calc(low);
			if(v > ans) ans = v;
		}
		printf("%.20Lf\n", ans);
	}
	return 0;
}