#include <bits/stdc++.h>

using namespace std;

using lint = long long;
using real_t = double;

const int MOD = int(1e9) + 7;

const real_t PI = acos(-1);

real_t ccw (real_t x1, real_t y1, real_t x2, real_t y2, real_t x3, real_t y3) {
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

real_t s2a(real_t a, real_t b, real_t c) {
	return acos((a*a + b*b - c*c) / (2 * a * b));	
}

using point = complex<double>;

real_t ccw (point a, point b, point c) {
	return ccw(a.real(), a.imag(), b.real(), b.imag(), c.real(), c.imag());
	return ((c - a) * conj(b - a)).imag(); // TODO
}

real_t solve2(real_t px, real_t py, real_t v, real_t w, real_t theta) {
	real_t r = v / w;
	
	real_t ox = -r * sin(theta);
	real_t oy = r * cos(theta);
	point o(ox, oy);
	point p(px, py);

	if(abs(o - p) < r) return 1e18;
	
	real_t op = hypot(px - ox, py - oy);
	real_t ph = sqrt(op * op - r * r);
	real_t alpha = acos(r / op);
	
	point hs[] = {
		p + (o - p) * ph / op * exp(+point(0, PI / 2 - alpha)),
		p + (o - p) * ph / op * exp(-point(0, PI / 2 - alpha))
	};
	
	point h;
	if(ccw(p, hs[0], o) < ccw(p, hs[1], o)) {
		h = hs[0];
	}else {
		h = hs[1];
	}
	
	real_t qh = abs(h);
	real_t beta = 2 * asin(qh / (2 * r));
	
	if(ccw(h, o, point(0,0)) < -1e-7) {
		beta = 2 * PI - beta;
	}
	return beta / w + ph / v;
}

real_t solve(real_t x, real_t y, real_t v, real_t w) {
	auto f = [&x, &y, &v, &w](double theta) {
		return theta / w + solve2(x, y, v, w, theta);
	};
	
	real_t ans = 1e18;
	const int TOT = 2000;
	for(int cho = 0; cho < TOT; cho++) {
		real_t low = cho * PI / TOT;
		real_t high = (cho + 1) * PI / TOT;
		for(int rep = 0; rep < 100; rep++) {
			real_t m1 = (low * 2 + high) / 3;
			real_t m2 = (low + 2 * high) / 3;
			if(f(m1) > f(m2)) {
				low = m1;
			}else {
				high = m2;
			}
		}
		ans = min(ans, f(low));
	}
	
	return ans;
}

int main() {
	real_t x, y, v, w;
	cin >> x >> y >> v >> w;
	
	real_t ans = 1e18;
	for(int repy = 0; repy < 2; repy++) {
		auto f = [&x, &y, &v, &w](double s) {
			return s / v + solve(x - s, y, v, w);
		};
	
		real_t low = 0, high = 0;
		for(int rep = 0; rep < 1; rep++) {
			real_t m1 = (low * 2 + high) / 3;
			real_t m2 = (low + 2 * high) / 3;
			if(f(m1) > f(m2)) {
				low = m1;
			}else {
				high = m2;
			}
		}
		y = -y;
		ans = min(ans, f(low));
	}
	
	printf("%.20lf\n", ans);
	return 0;
}
