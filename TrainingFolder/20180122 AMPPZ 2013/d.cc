#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
typedef long long lint;
typedef pair<int, int> pi;

struct ev{
	int pos, idx, mode;
	bool operator<(const ev &e)const{
		return pos < e.pos;
	}
};

set<int> s;
int n;
pi a[MAXN];
vector<ev> evnt;
int r1[MAXN];
map<pi, int> r2;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		evnt.push_back({a[i].first, i, 1});
		evnt.push_back({a[i].second, i, 2});
	}
	sort(evnt.begin(), evnt.end());
	lint tot = 0;
	for(int i=0; i<evnt.size(); ){
		int e = i;
		while(e < evnt.size() && evnt[i].pos == evnt[e].pos) e++;
		for(int j=i; j<e; j++){
			if(evnt[j].mode == 1) s.insert(evnt[j].idx);
			else s.erase(evnt[j].idx);
		}
		if(e == evnt.size()) break;
		if(s.size()) tot += evnt[e].pos - evnt[i].pos;
		if(s.size() == 1) r1[*s.begin()] += evnt[e].pos - evnt[i].pos;
		if(s.size() == 2) r2[pi(*s.begin(),*s.rbegin())] += evnt[e].pos - evnt[i].pos;
		i = e;
	}
	int ans = 0;
	for(auto &i : r2){
		ans = max(ans, i.second + r1[i.first.first] + r1[i.first.second]);
	}
	sort(r1, r1 + n);
	reverse(r1, r1 + n);
	ans = max(ans, r1[0] + r1[1]);
	cout << ans << endl;
}
