#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
const double pi = acos(-1);

struct wrapper{
	multiset<int> s;
	int largest;
	void rollback(int x, vector<int> &list){
		for(auto &i : list){
			s.erase(s.find(i));
		}
		largest = x;
	}
	int query(){ return largest; }
	void insert(int x){
		if(!s.empty()){
		    auto l = s.lower_bound((x + 180000) % 360000);
		    if(l != s.end()){
			    int d = *l - x + 360000;
			    d %= 360000;
			    if(d > 180000) d = 360000 - d;
			    largest = max(largest, d);
		    }
		    else{
			    int d = *s.begin() - x + 360000;
			    d %= 360000;
			    if(d > 180000) d = 360000 - d;
			    largest = max(largest, d);
		    }
		    if(l != s.begin()){
			    l--;
			    int d = *l - x + 360000;
			    d %= 360000;
			    if(d > 180000) d = 360000 - d;
			    largest = max(largest, d);
		    }
		    else{
		    	int d = *--s.end() - x + 360000;
			    d %= 360000;
			    if(d > 180000) d = 360000 - d;
			    largest = max(largest, d);
		    }
	    }
		s.insert(x);
	}
	void insert(vector<int> &list){
		for(auto &i : list) insert(i);
	}
}wrap;

int R, r, n;

double func(int x){
	double theta = 0.5 * pi * abs(180000 - x) / 180000.0;
	double ang = asin(1.0 * r / R);
	if(ang <= theta) return 2 * R * cos(theta);
	else return 2 * sqrt(1.0 * R * R - 1.0 * r * r) + 2 * r * (ang - theta);
}

bool insec(int s1, int e1, int s2, int e2){
	return max(s1, s2) <= min(e1, e2);
}

struct intv{
	int s, e, x;
};

int alive[360000];
int start[360000];
int ret[100005];

void solve(int s, int e, vector<intv> &v){
	if(s == e){
		int k = wrap.query();
		vector<int> x;
		for(auto &i : v) x.push_back(i.x);
		wrap.insert(x);
		ret[s] = wrap.query();
		wrap.rollback(k, x);
		return;
	}
	int m = (s+e)/2;
	vector<int> x;
	vector<intv> l, r;
	for(auto &i : v){
		if(i.s <= s && e <= i.e) x.push_back(i.x);
		else{
			if(insec(s, m, i.s, i.e)) l.push_back(i);
			if(insec(m+1, e, i.s, i.e)) r.push_back(i);
		}
	}
	int k = wrap.query();
	wrap.insert(x);
	solve(s, m, l);
	solve(m+1, e, r);
	wrap.rollback(k, x);
}

int main(){
	vector<intv> proc;
	scanf("%d %d",&R,&r);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		alive[x] = 1;
	}
	int q;
	scanf("%d",&q);
	for(int i=1; i<=q; i++){
		int x, v;
		scanf("%d %d",&x,&v);
		if(x == 1){
			assert(!alive[v]);
			start[v] = i;
		}
		else{
			assert(alive[v]);
			proc.push_back({start[v], i - 1, v});
		}
		alive[v] ^= 1;
	}
	for(int i=0; i<360000; i++){
		if(alive[i]){
			proc.push_back({start[i], q, i});
		}
	}
	solve(0, q, proc);
	for(int i=0; i<=q; i++) printf("%.10f\n", func(ret[i]));
}
