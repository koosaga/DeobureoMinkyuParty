#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
vector<pi> grp[250005];
priority_queue<pi, vector<pi>, greater<pi> > pq;

lint dis(pi a, pi b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pi vect(pi a, pi b){
	return pi(b.first - a.first, b.second - a.second);
}

vector<pi> ch(int x){
	swap(grp[x][0], *min_element(grp[x].begin(), grp[x].end()));
	sort(grp[x].begin() + 1, grp[x].end(), [&](const pi &a, const pi &b){
		lint k = ccw(grp[x][0], a, b);
		if(k != 0) return k > 0;
		return dis(grp[x][0], a) < dis(grp[x][0], b);
	});
	vector<pi> ret;
	for(auto &i : grp[x]){
		while(ret.size() >= 2 && ccw(ret[ret.size() - 2], ret.back(), i) <= 0){
			ret.pop_back();
		}
		ret.push_back(i);
	}
	return ret;
}

lint solve(int x, int y){
	auto a = ch(x);
	auto b = ch(y);
	int ptr = 0;
	lint ret = 0;
	if(a.size() <= 2 || b.size() <= 2){
		for(auto &i : a) for(auto &j : b) ret = max(ret, dis(i, j));
		return ret;
	}
	for(int i=0; i<a.size(); i++){
		pi v1 = vect(a[i], a[(i+a.size()-1)%a.size()]);
		pi v2 = vect(a[(i+1)%a.size()], a[i]);
		while(ccw(pi(0, 0), v1, vect(b[ptr], b[(ptr+1)%b.size()])) < 0){
			ptr = (ptr + 1) % b.size();
		}
		ret = max(ret, dis(a[i], b[ptr]));
		while(ccw(pi(0, 0), vect(b[ptr], b[(ptr+1)%b.size()]), v2) >= 0){
			ret = max(ret, dis(a[i], b[ptr]));
			ptr = (ptr + 1) % b.size();
			ret = max(ret, dis(a[i], b[ptr]));
		}
		ptr = (ptr + b.size() - 1) % b.size();
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x, y, t;
		scanf("%d %d %d",&x,&y,&t);
		grp[t].push_back(pi(x, y));
	}
	for(int i=1; i<=n; i++){
		if(!grp[i].empty()){
			pq.push(pi((int)grp[i].size(), i));
		}
	}
	lint ans = 0;
	while(pq.size() > 1){
		auto x = pq.top();
		pq.pop();
		auto y = pq.top();
		pq.pop();
		ans = max(ans, solve(x.second, y.second));
		for(auto &i : grp[x.second]){
			grp[y.second].push_back(i);
		}
		pq.push(pi((int)grp[y.second].size(), y.second));
	}
	cout << ans;
}
