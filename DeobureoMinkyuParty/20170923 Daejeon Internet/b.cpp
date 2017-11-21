#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <tuple>
#include <complex>
#include <bitset>
#include <random>
#include <ctime>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;

int n, m;
vector<pi> gph[MAXN];
double dis[MAXN];
bool inque[MAXN];

bool trial(double t) {
	fill(dis + 1, dis + n + 1, 0);
	memset(inque, 0, sizeof(inque));
	queue<int> que;
	for (int i = 1; i <= n; i++) {
		for (auto &j : gph[i]) {
			if (dis[j.second] > dis[i] + j.first - t) {
				dis[j.second] = dis[i] + j.first - t;
				if (!inque[j.second]) {
					inque[j.second] = 1;
					que.push(j.second);
				}
			}
		}
	}
	int cnt = 5000000;
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		inque[x] = 0;
		for (auto &i : gph[x]) {
			cnt--;
			if (dis[i.second] > dis[x] + i.first - t) {
				dis[i.second] = dis[x] + i.first - t;
				cnt--;
				if (cnt < 0) return true;
				if (!inque[i.second]) {
					inque[i.second] = 1;
					que.push(i.second);
				}
			}
		}
   }
	return false;
}

int p[2222];

int main() {
	scanf("%d %d", &n, &m);
	iota(p + 1, p + n + 1, 1);
	mt19937 fuck(0x14004);
	shuffle(p + 1, p + n + 1, fuck);
	for (int i = 0; i < m; i++) {
		int s, e, x;
		scanf("%d %d %d", &s, &e, &x);
		s++;
		e++;
		s = p[s];
		e = p[e];
		gph[s].push_back(pi(x, e));
	}
	double s = 0, e = 1e3 + 2;	
	while (clock() < 1.9 * CLOCKS_PER_SEC){
		double m = (s + e) / 2;
		if (trial(m)) e = m;
		else s = m;
	}
	if (e > 1e3 + 1) {
		cout << "0 0";
		return 0;
	}
	for (int i = 1; i <= 1000; i++) {
		double p = i * s;
		if (fabs(p - round(p)) < 5e-4) {
			int x = (int)round(p);
			printf("%d %d\n", x, i);
			return 0;
		}
	}
}