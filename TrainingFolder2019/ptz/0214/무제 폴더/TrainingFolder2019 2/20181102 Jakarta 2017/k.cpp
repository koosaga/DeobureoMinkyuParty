#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
using pi = pair<int, int>;
using lint = long long;

int n,q, p[MAXN], vis[MAXN];
vector<int> cyc[MAXN];

lint gcd(lint x, lint y){
	return y ? gcd(y, x%y) : x;
}

lint lcm(lint x, lint y){
	return x * (y / gcd(x, y));
}

int crt (int r1, int m1, int r2, int m2) {
	for(int i=0; i<r2;i++){
		if((r1 * i + m1) % r2 == m2){
			return i;
		}
	}
	assert(0);
}

int main(){
	cin >> n >> q;
	for(int i=1; i<=n; i++) scanf("%d",&p[i]);
	lint tot = 1;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			vector<int> v;
			for(int j=i; !vis[j]; j=p[j]){
				v.push_back(j);
				vis[j] = 1;
			}
			vector<int> w = v;
			sort(w.begin(), w.end());
			for(int j=0; j<w.size(); j++){
				int pos = find(v.begin(), v.end(), w[j]) - v.begin();
				cyc[i].push_back(pos);
			}
			tot = lcm(tot, v.size());
		}
	}
	while(q--){
		lint k; cin >> k;
		k--;
		k %= tot;
		lint A = 1, B = 0;
		for(int i=1; i<=n; i++){
			if(cyc[i].empty()) continue;
			int g = gcd(A, cyc[i].size());
			lint L = A * cyc[i].size() / g;
			int modv = B % g;
			lint nxt_possible = tot / L;
			int order_stat = k / nxt_possible;
			k %= nxt_possible;
			for(int j=0; j<cyc[i].size(); j++){
				if(cyc[i][j] % g != modv) continue;
				if(order_stat == 0){
					tie(A, B) = make_pair(L, B + A * crt(A % cyc[i].size(), B % cyc[i].size(), cyc[i].size(), cyc[i][j]));
					break;
				}
				order_stat--;
			}
		}
		if(B == 0) B += tot;
		printf("%lld\n", B);
	}
}
