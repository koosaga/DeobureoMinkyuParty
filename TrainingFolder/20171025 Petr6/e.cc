#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n;
pi a[MAXN];

lint merge(vector<pi> &p, vector<pi> &q){
	for(auto &i : p) swap(i.first, i.second);
	for(auto &i : q) swap(i.first, i.second);
	sort(p.begin(), p.end());
	sort(q.begin(), q.end());
	reverse(p.begin(), p.end());
	reverse(q.begin(), q.end());
	int pnt = 0;
	lint ans = 0;
	stack<pi> pv;
	vector<pi> stk;
	int curmax = -2e9;
	for(int i=0; i<p.size(); ){
		int e = i;
		while(e < p.size() && p[i].first == p[e].first) e++;
		while(!pv.empty() && pv.top().second < p[i].second) pv.pop();
		int upv = 2e9;
		if(!pv.empty()) upv = pv.top().first;
		pv.push(p[i]);
		while(pnt < q.size() && q[pnt] > p[i]){
			while(!stk.empty() && stk.back().second >= q[pnt].second){
				stk.pop_back();
			}
			stk.push_back(q[pnt]);
			pnt++;
		}
		if(!stk.empty()){
			auto l = lower_bound(stk.begin(), stk.end(), pi(upv, -2e9),
			[&](const pi &a, const pi &b){
				return a > b;
			});
			ans += stk.end() - l;
		}
		i = e;
	}
	return ans;
}

lint solve(int s, int e){
	if(s == e) return 0;
	int m = (s+e)/2;
	lint ans = solve(s, m) + solve(m+1, e);
	vector<pi> vl, vr;
	for(int i=s; i<=m; i++) vl.push_back(a[i]);
	for(int i=m+1; i<=e; i++) vr.push_back(a[i]);
	ans += merge(vl, vr);
	return ans;
}


int main(){
	freopen("friends.in", "r", stdin);
	freopen("friends.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	sort(a, a+n);
	lint ans = solve(0, n-1);
//	cout << ans << endl;
	for(int i=0; i<n; i++) a[i].second = -a[i].second;
	sort(a, a+n);
	ans += solve(0, n-1);
	//cout << ans << endl;
	sort(a, a+n);
	for(int i=1; i<n; i++){
		if(a[i].first == a[i-1].first) ans--;
	}
	for(int i=0; i<n; i++) swap(a[i].first, a[i].second);
	sort(a, a+n);
	for(int i=1; i<n; i++){
		if(a[i].first == a[i-1].first) ans--;
	}
	cout << ans;
}
