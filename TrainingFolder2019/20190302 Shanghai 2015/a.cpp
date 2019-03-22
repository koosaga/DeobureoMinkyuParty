#include <bits/stdc++.h>
using namespace std;

using real_t = long double;

using point = complex<real_t>;

const real_t eps = 1e-8;

void solve()
{
	int ox, oy, r, ax, ay, vx, vy, bx, by;
	cin >> ox >> oy >> r >> ax >> ay >> vx >> vy >> bx >> by;
	point o(ox, oy);
	point a(ax, ay);
	point v(vx, vy);
	point b(bx, by);
	
	point c;
	
	{
		auto f = [&a, &v, &o](real_t t) {
			return norm(a + v * t - o);
		};
		
		real_t low = 0, high = 1e5;
		
		for(int rep = 0; rep < 100; rep++) {
			real_t m1 = (2 * low + high) / 3;
			real_t m2 = (low + 2 * high) / 3;
			
			if(f(m1) < f(m2)) {
				high = m2;
			}else {
				low = m1;
			}
		}
		
		bool crash;
		if(f(low) < r*r) {
			low = 0;
			for(int rep = 0; rep < 100; rep++) {
				real_t m = (low + high) / 2;
				if(f(m) > r*r) {
					low = m;
				}else {
					high = m;
				}
			}
			crash = true;
			c = a + v * high;
		} else {
			crash = false;
			high = 1e5;
		}
		
		auto g = [&a, &v, &b](real_t t) {
			return norm(a + v * t - b);
		};
		
		low = 0;
		for(int rep = 0; rep < 100; rep++) {
			real_t m1 = (2 * low + high) / 3;
			real_t m2 = (low + 2 * high) / 3;
		
			if(g(m1) < g(m2)) {
				high = m2;
			}else {
				low = m1;
			}
		}

		if(fabs(g(low)) < eps) {
			puts("Yes");
			return;
		}else if(!crash){
			puts("No");
			return;
		}
		
		assert(crash);
	}
	
	point n = c - o;
	real_t k = (v * conj(n)).real() / norm(n);
	point u = 2 * k * n - v;
	u = -u;
	{
		auto f = [&c, &u, &b](real_t t) {
			return norm(c + u * t - b);
		};
		
		real_t low = 0, high = 1e5;
		
		for(int rep = 0; rep < 100; rep++) {
			real_t m1 = (2 * low + high) / 3;
			real_t m2 = (low + 2 * high) / 3;
			
			if(f(m1) < f(m2)) {
				high = m2;
			}else {
				low = m1;
			}
		}
		
		if(fabs(f(low)) < eps) {
			puts("Yes");
		}else {
			puts("No");
		}
	}
}

int main()
{
	int t, i;
	cin >> t;
	for(i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
