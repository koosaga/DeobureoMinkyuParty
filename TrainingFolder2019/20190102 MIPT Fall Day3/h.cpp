#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 500005;

int n, f[MAXN], l[MAXN], r[MAXN];
int a[MAXN];
vector<int> v[MAXN];

void solve(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&f[i]);
		v[f[i]].push_back(i);
	}
	for(int i=1; i<=n; i++) scanf("%d %d",&l[i],&r[i]);
	int maxl = *max_element(f + 1, f + n + 1);
	for(int i=1; i<=maxl; i++){
		if(v[i].empty()){
			puts("-1");
			return;
		}
		for(auto &j : v[i]) a[j] = l[j];
		if(i > 1){
			int prv = 0;
			for(auto &j : v[i]){
				while(prv < v[i-1].size() && v[i-1][prv] < j){
					prv++;
				}
				if(prv == 0){
					puts("-1");
					return;
				}
				a[j] = max(a[j], a[v[i-1][prv-1]] + 1);
			}
		}
		for(int j=sz(v[i]) - 2; j>=0; j--) a[v[i][j]] = max(a[v[i][j]], a[v[i][j+1]]);
	}
	for(int i=1; i<=n; i++){
		if(r[i] < a[i]){
			puts("-1");
			return;
		}
	}
	for(int i=1; i<=n; i++) printf("%d ", a[i]);
	puts("");
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		solve();
		for(int i=1; i<=n; i++) v[i].clear();
	}
}
