#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;
const int MAXN = 100005;

int n;
pi a[MAXN];
lint dp[MAXN];

struct cht{
	vector<pi> stk;
	using real_t = long double;
	real_t cross(pi a, pi b){
		return (real_t)(b.second - a.second) / (a.first - b.first);
	}
	void add(int x, lint v){
		while(stk.size() >= 2 && cross(stk[stk.size()-2], stk.back()) >= cross(stk.back(), pi(x, v))){
			stk.pop_back();
		}
		stk.emplace_back(x, v);
	}
	lint query(lint x){
		if(stk.empty()) return -1e18;
		int s = 0, e = stk.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(stk[m].first * x + stk[m].second < stk[m+1].first * x + stk[m+1].second) s = m+1;
			else e = m;
		}
		return stk[s].first * x + stk[s].second;
	}
	void clear(){ stk.clear(); }
}cht;

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	vector<pi> L, R;
	for(int i=s; i<=m; i++) L.push_back(pi(a[i].second, a[i].first));
	for(int i=m+1; i<=e; i++) R.push_back(pi(a[i].second, a[i].first));
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	int ptr = 0;
	cht.clear();
	for(auto &i : R){
		while(ptr < L.size() && L[ptr].first <= i.first){
			auto ins = L[ptr++];
			cht.add(ins.first * 2 + 1, -1ll * ins.first * (ins.first + 1) + dp[ins.first]);
		}
		dp[i.first] = max(dp[i.first], cht.query(i.first) - 1ll * i.first * i.first + i.second);
	}
	solve(m+1, e);
}

int main(){
	scanf("%d",&n);
	a[0].first = -2e9 - 1000;
	a[n+1].first = 2e9 + 1000;
	a[n+1].second = n+1;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i].first);
		a[i].first <<= 1;
		a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	fill(dp + 1, dp + n + 2, -1e15);
	solve(0, n + 1);
	assert(dp[n+1] % 2 == 0);
	cout << dp[n+1] / 2 - a[n+1].first / 2 << endl;
}
