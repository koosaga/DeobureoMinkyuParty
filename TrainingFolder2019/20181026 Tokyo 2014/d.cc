#include <bits/stdc++.h>

using namespace std;

using llf = long double;

int D, N, B;
int P[15], H[15];

int main() {
	scanf("%d%d%d", &D, &N, &B);
	for(int i = 0; i < N; i++) {
		scanf("%d%d", &P[i], &H[i]);
	}

	llf ans = 1e18;
	for(int jumps = 1; jumps <= B+1; jumps += 1) {
		 {
			llf l = (llf)D / jumps;
			llf m = -1;
			{
				llf low = 1e-7, high = 1e6;
				for(int rep = 0; rep < 120; rep++) {
					llf mid = (low + high) / 2.0;
					bool good = true;
					for(int i = 0; i < N; i++) {
						llf x = P[i] - floor((llf)P[i] / l + 1e-6) * l;
						llf y = -mid * x * (x - l);
						//printf(" %d %Lf %d %Lf %Lf < %d?\n", jumps, mid, i, x, y, H[i]);
						if(y < H[i] && fabs(y - H[i]) > 1e-6) {
							good = false;
						}
					}
					//printf(" mid = %Lf -> good = %d\n", mid, good);
					if(good) {
						high = mid;
					}else {
						low = mid;
					}
				}
				m = (low + high) / 2;
				//printf(" jumps = %d, m = %Lf\n", jumps, m);
			}

			if(fabs(1e6 - m) < 1e-6) continue;

			{
				auto go = [&l](llf m) {
					llf vx_squared = 1 / (2 * m);
					llf vy_squared = m * m * l * l * vx_squared;
					//printf(" m=%Lf -> vx=%Lf, vy=%Lf\n", m, vx_squared, vy_squared);
					return vx_squared + vy_squared;
				};
				llf low = m, high = 1e6;
				for(int rep = 0; rep < 120; rep++) {
					llf m1 = (low * 2 + high) / 3;
					llf v1 = go(m1);
					llf m2 = (low + 2 * high) / 3;
					llf v2 = go(m2);
					if(v1 < v2) {
						high = m2;
					}else {
						low = m1;
					}
				}

				ans = min(ans, go((low + high) / 2.0));
			}
		}
	}

	printf("%.10Lf\n", sqrt(ans));
	return 0;
}