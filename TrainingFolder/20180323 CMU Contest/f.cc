#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct seg{
	int sx, ex, pos, buho, idx;
};

struct bit{
	int tree[3000005];
	void add(int x, int v){
		while(x < 3000004){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<pi> v;
vector<seg> qry;
int n, q, ans[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		v.push_back(pi(x-y, x+y));
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x, y, d;
		scanf("%d %d %d",&x,&y,&d);
		qry.push_back({x+y-d, x+y+d, x-y-d-1, -1, i});
		qry.push_back({x+y-d, x+y+d, x-y+d, 1, i});
	}
	sort(qry.begin(), qry.end(), [&](const seg &a, const seg &b){
		return a.pos < b.pos;
	});
	int ptr = 0;
	sort(v.begin(), v.end());
	for(auto &i : qry){
		while(ptr < v.size() && v[ptr].first <= i.pos){
			bit.add(v[ptr++].second, 1);
		}
		ans[i.idx] += i.buho * (bit.query(i.ex) - bit.query(max(0, i.sx - 1)));
	}
	for(int i=0; i<q; i++) printf("%d\n", ans[i]);
}
