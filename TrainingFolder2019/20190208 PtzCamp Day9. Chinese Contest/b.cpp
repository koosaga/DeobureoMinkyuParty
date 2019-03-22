#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n, a[MAXN];

bool stackable(vector<pi> v){
	for(auto &i : v){
		if(i.first > i.second) swap(i.first, i.second);
	}
	sort(v.begin(), v.end());
	vector<pi> stk;
	for(int i=0; i<v.size(); i++){
		while(!stk.empty() && stk.back().second < v[i].second){
			if(stk.back().second > v[i].first) return 0;
			stk.pop_back();
		}
		stk.push_back(v[i]);
	}
	return 1;
}

int main(){
	int t;
	scanf("%d",&t);
	for(int i=0; i<t; i++){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			int x;
			scanf("%d",&x);
			a[x] = i;
		}
		vector<pi> v, w;
		for(int i=1; i+1<=n; i+=2){
			v.emplace_back(a[i], a[i+1]);
		}
		for(int i=2; i+1<=n; i+=2){
			w.emplace_back(a[i], a[i+1]);
		}
		puts(stackable(v) && stackable(w) ? "Yes" : "No");
	}
}
