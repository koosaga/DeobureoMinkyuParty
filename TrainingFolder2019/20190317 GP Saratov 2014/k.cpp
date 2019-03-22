#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
const int MAXT = 1050000;
using lint = long long;
using pi = pair<int, int>;


const int N_ = int(2.1e5);

int N,FT,FC;
struct prob { int a,b; lint t; int i; };
prob P[N_];

vector<int> pos;

bool good (lint X) {
	pos.clear();
	pos.push_back(1);
	lint cur = 0;
	for(int i = 1; i <= N; ) {
		int j = i;
		lint delta = 1e18, sumb = 0;
		cur += FT;
		for(; j <= N; j++) {
			delta = min(delta, (X + P[j].t) - FC - P[j].b - sumb);
			if(cur + P[j].a > delta) {
				break;
			}
			cur += P[j].a;
			sumb += P[j].b;
		}
		if(i == j) return false;
		cur += FC + sumb;
		pos.push_back(j);
		i = j;
	}
	return true;
}


int main(){
	scanf("%d%d%d", &N,&FT,&FC);
	for(int i = 1; i <= N; i++) {
		scanf("%d%d%lld", &P[i].a, &P[i].b, &P[i].t);
		P[i].i = i;
	}
	
	sort(P+1, P+N+1, [&](const prob &p1, const prob &p2) {
		return p1.t < p2.t;
	});
	
	lint low = 0, high = 1e18, ans = 1e18;
	while(low <= high) {
		lint mid = (low + high) / 2;
		if(good(mid)) {
			ans = mid;
			high = mid - 1;
		}else {
			low = mid + 1;
		}
	}
	good(ans);
	
	printf("%lld\n", ans);
	for(int i = 0; i+1 < int(pos.size()); i++) {
		for(int x = pos[i]; x < pos[i+1]; x++) {
			printf("%d ", -P[x].i);
		}
		for(int x = pos[i]; x < pos[i+1]; x++) {
			printf("%d ", P[x].i);
		}
	}
	return 0;
}
