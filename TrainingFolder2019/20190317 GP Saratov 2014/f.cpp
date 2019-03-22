#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 1000005;
using lint = long long;
using pi = pair<int, int>;

int n;
pi a[MAXN];
int par[MAXN];

void solve(){
	vector<int> v;
	for(int i=0; i<n; i++){
		v.push_back(a[i].first);
		v.push_back(a[i].second);
	}
	sort(v.begin(), v.end());
	int w = v[n];
	for(int i=0; i<n; i++){
		if(a[i].first > a[i].second) swap(a[i].first, a[i].second);
		if(a[i].second < w || a[i].first > w){
			puts("no");
			return;
		}
	}
	sort(a, a + n, [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	int p1 = 1e9, p2 = 1e9;
	int i1 = -1, i2 = -1;
	for(int i=0; i<n; i++){
		if(a[i].second <= p1){
			p1 = a[i].second;
			par[i] = i1;
			i1 = i;
		}
		else if(a[i].second <= p2){
			p2 = a[i].second;
			par[i] = i2;
			i2 = i;
		}
		else{
			puts("no");
			return;
		}
		if(p1 > p2){
			swap(p1, p2);
			swap(i1, i2);
		}
	}
	if(i1 == -1 || i2 == -1){
	}
	else{
		vector<pi> v, w;
		for(int j=i1; j!=-1; j=par[j]) v.push_back(a[j]);
		for(int j=i2; j!=-1; j=par[j]) w.push_back(a[j]);
		for(auto &i : w) swap(i.first, i.second);
		reverse(v.begin(), v.end());
		for(auto &i : w) v.push_back(i);
		for(int i=0; i<n; i++) a[i] = v[i];
	}
		puts("yes");
		for(int i=0; i<n; i++) printf("%d %d\n", a[i].first, a[i].second);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d %d",&a[i].first,&a[i].second);
		}
		solve();
	}
}
