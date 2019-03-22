#include <bits/stdc++.h>

using namespace std;

using llf = long double;

const llf PI = acos((llf)-1);
const llf C = acos((llf)-1) / 180.0;
const llf T = 180.0 / acos((llf)1);

void solve() {
	llf alpha, phi;
	scanf("%Lf%Lf", &alpha, &phi);
	alpha *= C;
	phi *= C;

	llf coef1 = cos(phi) * sin(alpha);
	llf coef2 = cos(alpha)* sin(phi);
	auto get = [&coef1, &coef2](llf x) {
		return (coef1 * sin(x / (12*60*60) * PI) - coef2);
	};

	vector<llf> cand;
	cand.push_back(0);
	cand.push_back(24*60*60-1);
	if(alpha >= phi) {
		llf sin_t = tan(phi) / tan(alpha);
		cand.push_back(asin(sin_t) * (llf)12*60*60/PI);
	}

	{
		llf low = 0;
		llf high = 24*60*60;
		for(int rep = 0; rep < 50; rep++) {
			llf m1 = (low * 2 + high) / 3;
			llf m2 = (low + high * 2) / 3;
			llf v1 = get(m1);
			llf v2 = get(m2);
			if(v1 < v2) {
				high = m2;
			}else {
				low = m1;
			}
		}
		cand.push_back((low + high) / 2.0);
	}
	{
		llf low = 0;
		llf high = 24*60*60;
		for(int rep = 0; rep < 50; rep++) {
			llf m1 = (low * 2 + high) / 3;
			llf m2 = (low + high * 2) / 3;
			llf v1 = get(m1);
			llf v2 = get(m2);
			if(v1 > v2) {
				high = m2;
			}else {
				low = m1;
			}
		}
		cand.push_back((low + high) / 2.0);
	}

	llf anst = 0;
	llf ansv = 1e18;
	for(llf t : cand) {
		llf v = fabs(get(t));
		//printf("%Lf %Lf\n", t, v);
		if(ansv > v) {
			ansv = v;
			anst = t;
		}
	}

	int t = round(anst);
	/*
	llf tan_alpha = tan(alpha);
	llf tan_phi = tan(phi);
	if(alpha >= phi) {
		llf sin_t = tan(phi) / tan(alpha);
		t = asin(sin_t) * (llf)12*60*60/PI;
	}else if(fabs(cos(phi) * sin(alpha)) < fabs(cos(alpha) * sin(phi))) {
		t = 1;
	}else {
		t = 12*60*60;
	}

	*/
	int H, M, D;
	scanf("%d:%d:%d", &H, &M, &D);
	int now = H * 60 * 60 + M * 60 + D;
	now += t;
	now %= 60 * 60 * 24;
	printf("%02d:%02d:%02d\n", now /60 / 60, now / 60 % 60, now % 60);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}