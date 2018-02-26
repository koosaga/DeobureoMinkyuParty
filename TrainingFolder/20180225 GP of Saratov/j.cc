#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 200005;
const int mod = 1e9 + 7;

int n, m, a[MAXN], ret[MAXN];
int L[MAXN][20], R[MAXN][20];

struct qry{ int s, e, idx; };

void solve(int s, int e, vector<qry> &q){
	if(s == e){
		for(auto &i : q){
			if(a[s] == 0) ret[i.idx] = 2;
			else ret[i.idx] = 1;
		}
		return;
	}
	int mi = (s+e)/2;
	vector<qry> l, r, tq;
	for(auto &i : q){
		if(i.e <= mi) l.push_back(i);
		else if(i.s >= mi + 1) r.push_back(i);
		else tq.push_back(i);
	}
	solve(s, mi, l);
	solve(mi + 1, e, r);
	memset(L[mi + 1], 0, sizeof(L[mi + 1]));
	memset(R[mi], 0, sizeof(R[mi]));
	L[mi + 1][0] = R[mi][0] = 1;
	for(int i=mi; i>=s; i--){
		for(int j=0; j<m; j++) L[i][j] = L[i+1][j];
		for(int j=0; j<m; j++){
			L[i][(j + a[i]) % m] += L[i+1][j];
		}
		for(int j=0; j<m; j++) L[i][j] %= mod;
	}
	for(int i=mi+1; i<=e; i++){
		for(int j=0; j<m; j++) R[i][j] = R[i-1][j];
		for(int j=0; j<m; j++){
			R[i][(j + a[i]) % m] += R[i-1][j];
		}
		for(int j=0; j<m; j++){
			R[i][j] %= mod;
		}
	}
	for(auto &i : tq){
		lint ans = 0;
		for(int j=0; j<m; j++){
			ans += 1ll * L[i.s][j] * R[i.e][(m - j) % m] % mod;
		}
		ret[i.idx] = ans % mod;
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] %= m;
	}
	vector<qry> q;
	int qc; scanf("%d",&qc);
	for(int i=0; i<qc; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		q.push_back({s, e, i});
	}
	solve(1, n, q);
	for(int i=0; i<qc; i++) printf("%d\n", ret[i]);
}
