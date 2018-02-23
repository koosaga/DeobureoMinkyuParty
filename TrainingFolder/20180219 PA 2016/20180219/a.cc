#include <bits/stdc++.h>
using namespace std;
const int MAXD = 205;
const int MAXN = 5005;
typedef unsigned long long hash_t;

int vect[MAXN][MAXD];
hash_t hv[MAXN], magic[MAXD];

map<hash_t, int> mp;
int ans;

void update(int p, int x, int y){
	ans -= mp[hv[x]] - 1;
	mp[hv[x]]--;
	if(mp[hv[x]] == 0) mp.erase(hv[x]);
	hv[x] -= vect[x][p] * magic[p];
	vect[x][p] = y;
	hv[x] += vect[x][p] * magic[p];
	ans += mp[hv[x]];
	mp[hv[x]]++;
}

int d, n, m;
struct disj{
	int pa[MAXN];
	vector<int> incomp[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		for(int i=1; i<=n; i++) incomp[i].push_back(i);
	}
	bool uni(int p, int q, int d){
		if(pa[p] == pa[q]) return 0;
		p = pa[p];
		q = pa[q];
		if(incomp[p].size() > incomp[q].size()) swap(p, q);
		for(auto &i : incomp[p]){
			incomp[q].push_back(i);
			update(d, i, q);
			pa[i] = q;
		}
		return 1;
	}
}disj[MAXD];


int main(){
	scanf("%d %d %d",&d,&n,&m);
	mt19937 rng(0x14004);
	for(int i=1; i<=d; i++){
		disj[i].init(n);
		magic[i] = uniform_int_distribution<hash_t>(0,~0ull)(rng);
	}
	ans = n * (n - 1) / 2;
	mp[0] = n;
	for(int i=1; i<=d; i++){
		for(int j=1; j<=n; j++){
			update(i, j, j);
		}
	}
	while(m--){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		disj[x].uni(s, e, x);
		printf("%d\n", ans * 2 + n);
	}
}
