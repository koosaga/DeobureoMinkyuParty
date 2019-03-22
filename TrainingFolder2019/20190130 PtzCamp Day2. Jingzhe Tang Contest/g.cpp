#include <bits/stdc++.h>
using namespace std;
using lint = long long;

namespace Fuck{
	unsigned int X, Y, Z;
	void start(){
		cin >> X >> Y >> Z;
	}
	unsigned int fuck(){
		X = X ^ (X << 11);
		X = X ^ (X >> 4);
		X = X ^ (X << 5);
		X = X ^ (X >> 14);
		auto W = X ^ Y ^ Z;
		X = Y;
		Y = Z;
		Z = W;
		return Z;
	}
}

const int MAXN = 100005;

struct intv{ 
	int l, r, x;
	bool operator<(const intv &i)const{
		return x > i.x;
	}
};

const int X = 12;

vector<intv> bucket[1<<X];
int pa[MAXN], val[MAXN];

int trv(int x, int y, int v){
	if(pa[x] != x) return pa[x] = trv(pa[x], y, v);
	if(x >= y) return x;
	if(!val[x]) val[x] = v;
	return pa[x] = trv(pa[x + 1], y, v);
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		int n, m;
		scanf("%d %d",&n,&m);
		Fuck::start();
		int B = (1<<X);
		for(int i=0; i<B; i++) bucket[i].clear();
		for(int i=0; i<m; i++){
			int l = (Fuck::fuck() % (1u * n)) + 1;
			int r = (Fuck::fuck() % (1u * n)) + 1;
			int v = (Fuck::fuck() & ((1u << 30) - 1));
			if(v == 0){
				m--;
				i--;
				continue;
			}
			if(l > r) swap(l, r);
			bucket[v >> (30 - X)].push_back({l, r, v});
		}
		for(int i=1; i<=n+1; i++){
			pa[i] = i;
			val[i] = 0;
		}
		for(int i=B - 1; i>=0; i--){
			if(bucket[i].empty()) continue;
			vector<intv> cut;
			for(auto &j : bucket[i]){
				if(j.x && pa[j.l] <= j.r){
					cut.push_back(j);
				}
			}
			sort(cut.begin(), cut.end());
			for(auto &j : cut){
				if(j.x && pa[j.l] <= j.r) trv(j.l, j.r + 1, j.x);
			}
		}
		lint dap = 0;
		for(int i=1; i<=n; i++) dap ^= 1ll * i * val[i];
		printf("%lld\n", dap);
	}
}
