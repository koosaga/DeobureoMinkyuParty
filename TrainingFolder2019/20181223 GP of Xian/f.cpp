#include<bits/stdc++.h>

int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}
using llf = long double;


struct vec {
	int x, y, z;
	vec(int x_=0, int y_=0, int z_=0):x(x_),y(y_),z(z_) { }
	void div() { int g = gcd(x, gcd(y, z)); x /= g; y /= g; z /= g; }
	int normsq() { return x*x + y*y + z*z; }
	llf norm() { return sqrt((llf)normsq()); }
	int operator* (vec v) {
		return x * v.x + y * v.y + z * v.z;
	}
	vec operator- (vec v) {
		return vec(x-v.x, y-v.y, z-v.z);
	}
	vec cross(vec v) {
		return vec(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
	}
	void scan() { scanf("%d%d%d", &x, &y, &z); }
};


llf solve() {
	int r; vec o, s, t;
	o.scan();
	scanf("%d", &r);
	s.scan();
	t.scan();

	if((s - t).normsq() == 0) {
		return 0;
	}

	vec n = (t - s).cross(o - s);
	if(n.normsq() == 0) {
		n = vec(1, 0, 0);
	}

	llf d = 1e18;
	{
		auto getdist = [&](llf l) {
			return sqrt(
				pow(o.x - (s.x + (t.x - s.x) * l), 2) +
				pow(o.y - (s.y + (t.y - s.y) * l), 2) +
				pow(o.z - (s.z + (t.z - s.z) * l), 2) 
			);
		};

		llf low = 0, high = 1;
		for(int rep = 0; rep < 60; rep++) {
			llf m1 = (low * 2 + high) / 3;
			llf m2 = (low + high * 2) / 3;

			if(getdist(m1) < getdist(m2)) {
				high = m2;
			}else {
				low = m1;
			}
		}

		d = getdist((low + high) / 2.0);
	}

	if(d > r) {
		return sqrt((t - s).normsq());
	}

	llf cos_theta = ((t - o) * (s - o)) / (t - o).norm() / (s - o).norm();
	cos_theta = std::min(cos_theta, (llf)1);
	cos_theta = std::max(cos_theta, (llf)-1);

	llf theta = acos(cos_theta);

	llf theta_s = acos(r / (s - o).norm());
	llf theta_t = acos(r / (t - o).norm());
	return sqrt((s - o).normsq() - r*r) + r * (theta - theta_s - theta_t) + sqrt((t - o).normsq() - r*r);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) printf("%.20Lf\n", solve());
	return 0;
}