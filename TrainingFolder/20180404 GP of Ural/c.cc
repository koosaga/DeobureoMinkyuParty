#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

int n, lit[MAXN], ans;
vector<pi> gph[MAXN];

vector<pi> hvs[MAXN];
int hv[MAXN], ds[MAXN], sum[MAXN];

void init_ds(){
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(hv[i] && hv[j.second]){
				hvs[i].push_back(j);
			}
			if(hv[i] && !hv[j.second]){
			    sum[i] += j.first;
			}
		}
	}
}

void flip(int x){
	if(!hv[x]){
		for(auto &j : gph[x]){
			if(lit[x] == lit[j.second]){
				ans += j.first;
				if(hv[j.second]) ds[j.second] += j.first;
			}
			else{
				ans -= j.first;
				if(hv[j.second]) ds[j.second] -= j.first;
			}
		}
	}
	else{
		ans -= ds[x];
		ds[x] = sum[x] - ds[x];
		ans += ds[x];
		for(auto &j : hvs[x]){
			if(lit[x] == lit[j.second]) ans += j.first;
			else ans -= j.first;
		}
	}
	lit[x] ^= 1;
}

int query(){
	return ans;
}

int lcnt[MAXN], a[MAXN], m, q;

int main(){
	int curlit = 0;
	scanf("%d %d %d",&m,&n,&q);
	for(int i=1; i<=m; i++){
		scanf("%d",&a[i]);
		lcnt[a[i]]++;
	}
	vector<pi> v;
	for(int i=2; i<=m; i++){
		int l = a[i-1], r = a[i];
		if(l > r) swap(l, r);
		if(l != r) v.push_back(pi(l, r));
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i] == v[e]) e++;
		gph[v[i].first].push_back(pi(e - i, v[i].second));
		gph[v[i].second].push_back(pi(e - i, v[i].first));
		i = e;
	}
	for(int i=1; i<=n; i++) if(gph[i].size() > 500) hv[i] = 1;
	init_ds();
	while(q--){
		int x;
		scanf("%d",&x);
		if(lit[x] == 0) curlit += lcnt[x];
		else curlit -= lcnt[x];
		flip(x);
		int ans = query();
		if(lit[a[1]]) ans++;
		if(lit[a[m]]) ans++;
		assert(ans % 2 == 0);
		printf("%d\n", ans / 2);
	}
}
