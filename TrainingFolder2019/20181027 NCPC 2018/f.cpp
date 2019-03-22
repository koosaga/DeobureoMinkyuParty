#include <bits/stdc++.h>

using namespace std;
const int MAXN = 17;
using real_t = double;
using pi = pair<real_t, real_t>;
const real_t eps = 1e-7;

int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

int n, l;
pi s[MAXN], e[MAXN];
namespace Fuck{
	using pi = pair<int, int>;
	int ccw(pi a, pi b, pi c){
		int dx1 = b.first - a.first;
		int dy1 = b.second - a.second;
		int dx2 = c.first - a.first;
		int dy2 = c.second - a.second;
		return dx1 * dy2 - dy1 * dx2;
	}

	pair<real_t, real_t> get_intercept(pi s1, pi e1, pi s2, pi e2){
		if(s2.second == e2.second){
			real_t sex = (real_t)(s2.second - s1.second) / (e1.second - s1.second);
			return make_pair(s1.first + sex * (e1.first - s1.first), s2.second);
		}
		else{
			swap(s1.first, s1.second);
			swap(e1.first, e1.second);
			swap(s2.first, s2.second);
			swap(e2.first, e2.second);
			auto sexx = get_intercept(s1, e1, s2, e2);
			return make_pair(sexx.second, sexx.first);
		}
	}

	int solve(pi x, pi y){
		vector<pair<real_t, int>> swp;
		real_t KUGGY = hypot(x.first - y.first, x.second - y.second);
		for(int i=0; i<n; i++){
			vector<pi> rect;
			rect.emplace_back(s[i].first, s[i].second);
			rect.emplace_back(s[i].first, e[i].second);
			rect.emplace_back(e[i].first, e[i].second);
			rect.emplace_back(e[i].first, s[i].second);
			int minv = 1e9, maxv = -1e9;
			for(auto &j : rect){
				minv = min(minv, ccw(x, y, j));
				maxv = max(maxv, ccw(x, y, j));
			}
			if(maxv < 0 || minv > 0) continue;
			real_t min_pos = 1e9, max_pos = -1e9;
			for(int j=0; j<rect.size(); j++){
				auto l = rect[j], r = rect[(j + 1) % 4];
				int v = ccw(x, y, l);
				int w = ccw(x, y, r);
				if(1ll * v * w <= 0 && (v != 0 || w != 0)){
					pair<real_t, real_t> ans = get_intercept(x, y, l, r);
					real_t tmp = ans.first * (y.first - x.first) + ans.second * (y.second - x.second);
					min_pos = min(min_pos, tmp);
					max_pos = max(max_pos, tmp);
				}
			}
			swp.emplace_back(min_pos, 1);
			swp.emplace_back(max_pos + (l + eps) * KUGGY, -1);
		}
		sort(swp.begin(), swp.end());
		int dx = 0, ret = 0;
		for(auto &i : swp){
			dx += i.second;
			ret = max(ret, dx);
		}
		return ret;
	}
};

real_t ccw(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

pair<real_t, real_t> get_intercept(pi s1, pi e1, pi s2, pi e2){
	auto get_line = [](pi s, pi e){
		real_t sx = e.second - s.second;
		real_t sy = s.first - e.first;
		return make_tuple(sx, sy, sx * s.first + sy * s.second);
	};
	real_t a, b, c, d, e, f;
	tie(a, b, c) = get_line(s1, e1);
	tie(d, e, f) = get_line(s2, e2);
	real_t det = a * e - b * d;
	assert(fabs(det) > 0.001);
	return make_pair((e * c - b * f) / det, (a * f - c * d) / det);
}

int solve(pi x, pi y){
	vector<pair<real_t, int>> swp;
	for(int i=0; i<n; i++){
		vector<pi> rect;
		rect.emplace_back(s[i].first, s[i].second);
		rect.emplace_back(s[i].first, e[i].second);
		rect.emplace_back(e[i].first, e[i].second);
		rect.emplace_back(e[i].first, s[i].second);
		real_t minv = 1e9, maxv = -1e9;
		for(auto &j : rect){
			minv = min(minv, ccw(x, y, j));
			maxv = max(maxv, ccw(x, y, j));
		}
		if(maxv < 0 || minv > 0) continue;
		real_t min_pos = 1e9, max_pos = -1e9;
		for(int j=0; j<rect.size(); j++){
			auto l = rect[j], r = rect[(j + 1) % 4];
			real_t v = ccw(x, y, l);
			real_t w = ccw(x, y, r);
			if(v * w <= 0 && (fabs(v) > eps || fabs(w) > eps)){
				pair<real_t, real_t> ans = get_intercept(x, y, l, r);
				real_t tmp = ans.first * (y.first - x.first) + ans.second * (y.second - x.second);
				tmp /= hypot(x.first - y.first, x.second - y.second);
				min_pos = min(min_pos, tmp);
				max_pos = max(max_pos, tmp);
			}
		}
		swp.emplace_back(min_pos, 1);
		swp.emplace_back(max_pos + l + eps, -1);
	}
	sort(swp.begin(), swp.end());
	int dx = 0, ret = 0;
	for(auto &i : swp){
		dx += i.second;
		ret = max(ret, dx);
	}
	return ret;
}

int main(){
	vector<int> vx, vy;
	cin >> n >> l;
	for(int i=0; i<n; i++){
		cin >> s[i].first >> s[i].second;
		cin >> e[i].first >> e[i].second;
		vx.push_back(s[i].first);
		vx.push_back(e[i].first);
		vy.push_back(s[i].second);
		vy.push_back(e[i].second);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	vector<pair<int, int>> punkty;
	for(int i=0; i<vx.size(); i++){
		for(int j=0; j<vy.size(); j++){
			punkty.emplace_back(vx[i], vy[j]);
		}
	}
	int ret = 1;
	vector<pi> rect;
	for(int i=0; i<n; i++){
		rect.emplace_back(s[i].first, s[i].second);
		rect.emplace_back(s[i].first, e[i].second);
		rect.emplace_back(e[i].first, e[i].second);
		rect.emplace_back(e[i].first, s[i].second);
	}
	for(auto &i : rect){
		vector<real_t> cx, cy;
		vector<real_t> coords;
		for(int j=0; j<vx.size(); j++){
			real_t v = fabs(vx[j] - i.first);
			v = pow(v, 1.0 / 3);
			cx.push_back(v);
			cx.push_back(-v);
		}
		for(int j=0; j<vy.size(); j++){
			real_t v = fabs(vy[j] - i.second);
			v = pow(v, 1.0 / 3);
			cy.push_back(v);
		}
		sort(cx.begin(), cx.end());
		sort(cy.begin(), cy.end());
		cx.resize(unique(cx.begin(), cx.end()) - cx.begin());
		cy.resize(unique(cy.begin(), cy.end()) - cy.begin());
		for(auto &j : cx){
			for(auto &k : cy){
				ret = max(ret, solve(i, pi(i.first + j, i.second + k)));
			}
		}
	}
	vector<pi> SEXPERM;
	for(int i=0; i<punkty.size(); i++){
		for(int j=0; j<i; j++) SEXPERM.emplace_back(i, j);
	}
	random_shuffle(SEXPERM.begin(), SEXPERM.end());
	int ptr = 0;
	while(clock() < 1.95 * CLOCKS_PER_SEC){
		int fucking = 1000;
		while(fucking && ptr != SEXPERM.size()){
			int j = SEXPERM[ptr].first;
			int i = SEXPERM[ptr].second;
			ptr++;
			ret = max(ret, Fuck::solve(punkty[j], punkty[i]));
			fucking--;
		}
	}
	cout << ret << endl;
}
