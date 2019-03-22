#include <bits/stdc++.h>
using namespace std;

using lint = long long;

int x, p, k, m; lint d;
vector<int> interesting;
int period;

lint go (int f, lint v) {
	if(f == 1) {
		return v;
	}
	lint w = 0;
	if(v >= period) {
		w += interesting.size() * (v / period);
		v %= period;
	}
	auto it = upper_bound(interesting.begin(), interesting.end(), v);
	w += distance(interesting.begin(), it);
	return go(f - 1, w);
}

int main(){
	cin >> x >> p >> k >> m >> d;
	
	for(int i = 0, beauty = 1, tot = 0; ; i++, beauty = ((lint)beauty * (lint)x) % p) {
		if(i > 0 && tot == 0 && beauty == 1) {
			period = i; // TODO too large
			break;
		}
		(tot += beauty % m) %= m;
		if(tot == 0) {
			interesting.push_back(i);
		}
	}
	
	lint low = 0, high = 1e18, ans = 1e18;
	while(low <= high) {
		lint mid = (low + high) >> 1;
		lint now = mid - go(k, mid);
		if(now >= d) {
			ans = mid;
			high = mid - 1;
		}else {
			low = mid + 1;
		}
	}
	
	printf("%lld\n", ans);
	/*
	for(lint mid=ans-5;mid<=ans+5;mid++){
		lint g = go(k, mid);
		lint now = mid - go(k, mid);
		printf(" > %lld %lld %lld\n",mid,g,now);
	}*/

	
	
	return 0;
}
