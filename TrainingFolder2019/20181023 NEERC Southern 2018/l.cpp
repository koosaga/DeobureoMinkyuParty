#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n, m;
vector<int> gph[MAXN];
bitset<MAXN> bs[MAXN];
int col[MAXN], active[MAXN];

void upload(bitset<MAXN> v, int c){
	for(int i=0; i<n; i++){
		if(v[i]){
			if(!active[i]){
				active[i] = 1;
				col[i] = c;
				bs[i] = v;
				return;
			}
			v ^= bs[i];
			c ^= col[i];
		}
	}
}

void solve(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	bool two = 0;
	for(int i=1; i<=n; i++){
		if(gph[i].size() & 1) two = 1;
	}
	if(!two){
		puts("1");
		for(int i=1; i<=n; i++) printf("1 ");
		puts("");
		return;
	}
	for(int i=1; i<=n; i++){
		bitset<MAXN> bs;
		for(auto &j : gph[i]) bs[j-1] = 1;
		if(gph[i].size() & 1) bs[i-1] = 1;
		upload(bs, gph[i].size() & 1);
	}
	for(int i=n-1; i>=0; i--){
		for(int j=i+1; j<n; j++){
			if(bs[i][j]) col[i] ^= col[j];
		}
	}
	puts("2");
	for(int i=0; i<n; i++) printf("%d ", col[i] + 1);
	puts("");
}

int main(){
	int tc; cin >> tc;
	for(int i=0; i<tc; i++){
		solve();
		for(int j=0; j<MAXN; j++) gph[j].clear();
		memset(active, 0, sizeof(active));
		memset(col, 0, sizeof(col));
		for(int j=0; j<n; j++) bs[j] = 0;
	}
}
