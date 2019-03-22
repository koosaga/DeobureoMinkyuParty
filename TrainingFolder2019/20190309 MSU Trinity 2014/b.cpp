#include <bits/stdc++.h>

using namespace std;

using real_t = long double;

const real_t PI = acosl(-1);

int K;
real_t ang[500], _sin[500], _cos[500], _cot[500];
vector<real_t> pos[500];
vector<pair<real_t, int>> vec[500];

int main() {
	scanf("%d", &K);
	
	real_t alcohol = PI / 2 / K;
	for(int i = 1; i < K + K; i++) {
		ang[i] = alcohol * i;
		_sin[i] = sinl(ang[i]);
		_cos[i] = cosl(ang[i]);
		if(i != K) _cot[i] = 1/tanl(ang[i]);
	}

	for(int alpha = 1; alpha < K + K; alpha++) {
		for(int beta = 1; alpha + beta < K + K; beta++) {
			for(int gamma = alpha + 1; gamma < K + K - beta; gamma++) {
				real_t x = _sin[beta] * _sin[gamma - alpha] / _sin[alpha + beta] / _sin[gamma];
				//printf("%Lf %Lf\n", _sin[beta] * _sin[gamma - alpha] / _sin[alpha + beta], _sin[beta] * _sin[gamma - alpha] / _sin[alpha + beta] / _sin[gamma]);
				pos[gamma].push_back(x);
			}
		}
	}


	const real_t eps = 1e-11;
	for(int gamma = 1; gamma < K+K; gamma++) {
		sort(pos[gamma].begin(), pos[gamma].end());
		for(int i = 0; i < int(pos[gamma].size()); ) {
			int j = i;
			while(j < int(pos[gamma].size()) && fabsl(pos[gamma][i] - pos[gamma][j]) < eps) {
				j += 1;
			}
			vec[gamma].emplace_back(pos[gamma][i], j - i);
			i = j;
		}
	}

	int ans = 0;
	for(int i = 1; i <= K+K; i++) {
		int j = K + K - i; 
		for(auto xi : vec[i]) {
			auto l = lower_bound(vec[j].begin(), vec[j].end(), make_pair(1 - xi.first - eps, 0));
			auto r = upper_bound(vec[j].begin(), vec[j].end(), make_pair(1 - xi.first + eps, 0));
			//assert(r - l <= 5);
			for(auto it = l; it != r; it++) {
				if(fabsl(xi.first + it->first - 1) < eps) ans += it->second * xi.second;
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}