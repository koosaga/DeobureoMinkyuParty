#include <bits/stdc++.h>

using namespace std;

using real_t = long double;
using point = complex<real_t>;

const real_t PI = acosl(-1);

int main() {
	int n; cin >> n;
	for(int N = 1; N <= n; N++) {
		real_t w, h, xc, yc, x0, y0; int _alpha; real_t s;
		cin >> w >> h >> xc >> yc >> x0 >> y0 >> _alpha >> s;
		real_t alpha = _alpha * PI / 180;
		
		real_t W, H, L, T, A;
		
		W = w * s;
		xc *= s;
		H = h * s;
		yc *= s;
		
		point rect[] = {
			point(0, 0), point(W, 0), point(0, H), point(W, H)
		};
		for(point &p : rect) {
			p += point(-xc, -yc);
			p *= polar(real_t(1), alpha);
		}
		point mid = accumulate(rect, rect+4, point(0,0)) * point(0.25,0);
		
		for(point &p : rect) {
			p += point(x0,y0);
		}
		mid = accumulate(rect, rect+4, point(0,0)) * point(0.25,0);
		L = mid.real() - W / 2;
		T = mid.imag() - H / 2;
		
		point p0 (L, T); p0 -= mid;
		point p1 = rect[0]; p1 -= mid;
		p0 /= abs(p0);
		p1 /= abs(p1);
		A = arg(p1 / p0); // p1 = p0 * exp(i theta)
		if(A < 0) {
			A += 2 * PI;
		}
		A *= 180 / PI;
		
		
		printf(".item%d { width: %.1Lfpx; height: %.1Lfpx; left: %.1Lfpx; top: %.1Lfpx; transform: rotate(%d.0deg); }\n", N, W, H, L, T, _alpha);
	}
	return 0;
}
