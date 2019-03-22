#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 50505;

int n, q, a[MAXN];
int PC, NC;
pi P[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pi operator+(const pi &a, const pi &b){
	return pi(a.first + b.first, a.second + b.second);
}

const int B = 200;
vector<pair<pi, int>> hull[255];
pi offset[255];

void query(){
	pair<lint, int> ret(5e18, 1);
	for(int j=0; j<n; j+=B){
		for(auto &k : hull[j / B]){
			auto v = make_pair(ccw(pi(0, 0), pi(PC, NC), k.first + offset[j / B]), k.second);
			ret = min(ret, v);
		}
	}
	printf("%d\n", ret.second);
}

void build(int x){
	int s = x * B, e = (x + 1) * B;
	e = min(e, n);
	for(int i=s; i<e; i++){
		P[i + 1] = P[i + 1] + offset[x];
	}
	offset[x] = pi(0, 0);
	hull[x].clear();
	for(int i=s; i<e; i++){
		while(hull[x].size() >= 2 && ccw(hull[x][hull[x].size()-2].first, hull[x].back().first, P[i + 1]) <= 0){
			hull[x].pop_back();
		}
		hull[x].emplace_back(P[i + 1], i + 1);
	}
}

int main(){
	freopen("joker.in", "r", stdin);
	freopen("joker.out", "w", stdout);
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(a[i] < 0) NC -= a[i];
		else PC += a[i];
	}
	for(int i=1; i<=n; i++){
		P[i] = P[i-1];
		if(a[i] < 0) P[i].second -= a[i];
		else P[i].first += a[i];
	}
	for(int i=0; i<n; i+=B){
		build(i / B);
	}
	query();
	while(q--){
		int x, v; scanf("%d %d",&x,&v);
		pi D = pi(0, 0);
		if(a[x] < 0){
			NC += a[x];
			D.second += a[x];
		}
		else{
			PC -= a[x];
			D.first -= a[x];
		}
		a[x] = v;
		if(a[x] < 0){
			NC -= a[x];
			D.second -= a[x];
		}
		else{
			PC += a[x];
			D.first += a[x];
		}
		for(int j=x-1; j % B != 0; j++){
			P[j + 1].first += D.first;
			P[j + 1].second += D.second;
		}
		for(int j=(x - 1) / B + 1; j*B<n ; j++){
			offset[j].first += D.first;
			offset[j].second += D.second;
		}
		build((x - 1) / B);
		query();
	}
}
