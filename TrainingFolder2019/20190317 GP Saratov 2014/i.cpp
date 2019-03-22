#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
const int MAXT = 1050000;
using lint = long long;
using pi = pair<int, int>;

mt19937 rng(12389);


int gcd (int a, int b) {
	return b ? gcd(b, a%b) : a;
}

int N, M;

const int TH = 500;

int solve (vector<int> &a) {
	assert(a.size() >= 2);
	
	if(a.size() <= TH) {
		unordered_map<int, int> cnt;
		for(int i = 0; i < (int)a.size(); i++) {
			for(int j = 0; j < (int)a.size(); j++) {
				if(i != j) {
					cnt[(a[j] - a[i] + N) % N] += 1;
				}
			}
		}	
		for(auto &it : cnt) {
			if(it.second >= int(a.size()) - 1) {
				return it.first;
			}
		}
		return -1;
	}

	uniform_int_distribution<int> gen(0, int(a.size())-1);
	while(clock() < CLOCKS_PER_SEC * 1.5) {
		int x = gen(rng);
		vector<int> c;
		for(int j = 1; j < (int)a.size(); j++) {
			c.push_back((a[(x + j) % a.size()] - a[x] + N) % N);
		}
		
		vector<int> d;
		for(int i = 0, j = int(c.size())-1; i < int(c.size()); i++) {
			while(j >= 0 && c[i] + c[j] > N) j--;
			if(j >= 0 && c[i] + c[j] == N) {
				continue;
			}
			d.push_back(c[i]);
		}
		
		if(d.size() >= 2 && d.size() <= max(TH, (int)(a.size() * 0.85))) {
			int x = solve(d);
			if(x > 0) {
				return x;
			}
		}
	}
	
	return -1;
}

int main() {
	scanf("%d%d", &N, &M);
	
	int g = N;
	vector<int> a;
	for(int i = 0; i < M; i++) {
		int x; scanf("%d", &x);
		a.push_back(x);
		if(i > 0) g = gcd(g, a[i] - a[i-1]);
	}

	if(M == 1) {
		printf("%d 1\n", a[0]);
		return 0;
	}
		
	if(M == N / g) {
		printf("%d %d\n", a[0], g);
		return 0;
	}
	
	{
		auto chk1 = [&](int i) {
			for(int j = 0; j < M; j++) {
				if((a[(i+j)%M] - a[i] + N) % N != j) {
					return;
				}
			}
			printf("%d %d\n", a[i], 1);
			exit(0);
		};
		
		
		bool good = false;
		for(int i = 1; i < M; i++) {
			if(a[i] - a[i-1] != 1) {
				chk1(i);
				good = true;
				break;
			}
		}
		if(!good) {
			chk1(0);
		}
	}
	
	int k = solve(a);
	if(k == -1) {
		printf("-1 -1\n");
		return 0;
	}
	
	int s = -1;
	for(int i = 0; i < M; i++) {
		if(binary_search(a.begin(), a.end(), (a[i] + N-k) % N)) {
			continue;
		}
		s = a[i];
		break;
	}
	
	for(int i = 0; i < M; i++) {
		if(binary_search(a.begin(), a.end(), (int)((s + (lint)i * k) % N))) {
			continue;
		}
		puts("-1 -1");
		return 0;
	}
	
	printf("%d %d\n", s, k);
	return 0;
}
