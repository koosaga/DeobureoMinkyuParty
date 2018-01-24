#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 100005;

int n, k;
pi a[MAXN];
pi b[MAXN*2];

void solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		b[2*i] = pi(a[i].first, 1);
		b[2*i+1] = pi(a[i].second, -1);
	}
	sort(b, b+2*n);
	int cur = 0, ans = 0, pos = -1;
	for(int i=0; i<2*n; i++){
		cur += b[i].second;
		if(cur > ans){
			ans = cur;
			pos = b[i].first;
		}
	}
	printf("%d ", ans);
	multiset<int> ls, rs;
	vector<pi> li, ri;	
	for(int i=0; i<n; i++){
		if(a[i].first <= pos && a[i].second > pos){
			ls.insert(a[i].first);
			rs.insert(a[i].second);
		}
		if(a[i].second <= pos) li.push_back(a[i]);
		if(a[i].first > pos) ri.push_back(a[i]);
	}
	sort(li.rbegin(), li.rend(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	for(auto &j : li){
		auto s = ls.lower_bound(j.second);
		assert(s != ls.end());
		ls.erase(s);
		ls.insert(j.first);
	}
	sort(ri.begin(), ri.end());
	for(auto &j : ri){
		auto s = rs.upper_bound(j.first);
		assert(s != rs.begin());
		s--;
		rs.erase(s);
		rs.insert(j.second);
	}
	lint tot = 0;
	for(auto &j : rs) tot += j;
	for(auto &j : ls) tot -= j;
	printf("%lld\n", tot);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
