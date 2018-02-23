#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int inf = 2e9 + 10;

lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct intv{
	lint s, e;
	pi p;
	bool operator<(const intv &i)const{
		return s < i.s;
	}
};

vector<intv> il, ir;
vector<pi> l, r;
int n;

lint mfloor(pi a, pi b){
	lint A = b.second - a.second;
	lint B = b.first - a.first;
	if(A >= 0) return A / B;
	return (A - B + 1) / B;
}

lint mceil(pi a, pi b){
	lint A = b.second - a.second;
	lint B = b.first - a.first;
	if(A >= 0) return (A + B - 1) / B;
	return A / B;
}

lint sum(lint s, lint e){
	if(s > e) return 0;
	return (1ll * (s + e) * (e - s + 1)) / 2;
}

lint solve(lint s, lint e, pi p, pi q){
	s = max(s, -1000000000 - 5ll);
	e = min(e, 1000000000 + 5ll);
	if(q.first == p.first){
		return max(1ll + q.second - p.second, 0ll) * (e - s + 1);
	}
	lint ans = 0;
	if(q.first - p.first < 0){
		s = max(s, mceil(pi(0, 0), pi(p.first - q.first, -1 - q.second + p.second)));
		if(s > e) return 0;
		ans = (1 + q.second - p.second) * (e - s + 1);
		ans += (p.first - q.first) * sum(s, e);
	}
	else{
		lint limiting_factor = mfloor(pi(0, 0), pi(q.first - p.first, 1 + q.second - p.second));
		e = min(e, limiting_factor);
		if(s > e) return 0;
		ans += 1ll * (1 + q.second - p.second) * ( e - s + 1);
		ans -= sum(s, e) * (q.first - p.first);
	}
//	printf("%d %d %lld\n", s, e, ans);
	return ans;
}

int main(){
	scanf("%d",&n);
	l.push_back(pi(0, -inf));
	r.push_back(pi(0, inf));
	for(int i=1; i<=n; i++){
		int p, q;
		scanf("%d %d",&p,&q);
		while(l.size() >= 2 && ccw(l[l.size()-2], l.back(), pi(i, p)) >= 0){
			l.pop_back();
		}
		while(r.size() >= 2 && ccw(r[r.size()-2], r.back(), pi(i, q)) <= 0){
			r.pop_back();
		}
		l.push_back(pi(i, p));
		r.push_back(pi(i, q));
	}
	l.push_back(pi(n+1, -inf));
	r.push_back(pi(n+1, inf));
	for(int i=1; i+1<l.size(); i++){
		lint st = mceil(l[i], l[i+1]);
		lint ed = mfloor(l[i-1], l[i]);
		il.push_back({st, ed, l[i]});
	}
	for(int i=1; i+1<r.size(); i++){
		lint st = mceil(r[i-1], r[i]);
		lint ed = mfloor(r[i], r[i+1]);
		ir.push_back({st, ed, r[i]});
	}
	sort(il.begin(), il.end());
	sort(ir.begin(), ir.end());
	for(int i=1; i<il.size(); i++){
		if(il[i-1].e == il[i].s) il[i].s++;
	}
	for(int i=1; i<ir.size(); i++){
		if(ir[i-1].e == ir[i].s) ir[i].s++;
	}
	lint ans = 0;
	for(auto &p : il){
		auto l = lower_bound(ir.begin(), ir.end(), (intv){p.s + 1, -1, pi(-1, -1)});
		if(l != ir.begin()) l--;
		while(l != ir.end()){
			lint st = max(p.s, l->s);
			lint ed = min(p.e, l->e);
			if(st > ed) break;
			ans += solve(st, ed, p.p, l->p);
			l++;
		}
	}
	cout << ans << endl;
}
