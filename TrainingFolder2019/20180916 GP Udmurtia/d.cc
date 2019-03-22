#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1050;
const int MAXG = 35;
const int mod = 1e9 + 7;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, E, route[MAXN], num[MAXN];
pi edge[MAXG];
vector<pi> Graph;
lint state_adj[MAXG][MAXG];

int generate_iso(int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			edge[E++] = pi(j, i);
		}	
	}
	disj.init(1 << E);
	for(int i=0; i<(1<<E); i++){
		int p[5], adj[5][5] = {};
		iota(p, p + n, 0);
		int piv = 0;
		for(int j=0; j<E; j++){
			if((i >> j) & 1){
				adj[edge[j].first][edge[j].second] = 1;
				adj[edge[j].second][edge[j].first] = 1;
			}
		}
		do{
			int piv = 0;
			int new_msk = 0;
			for(int j=0; j<E; j++){
				int l = p[edge[j].first];
				int r = p[edge[j].second];
				if(adj[l][r]) new_msk |= (1<<j);
			}
			disj.uni(i, new_msk);
		}while(next_permutation(p, p + n));
	}
	for(int i=0; i<(1<<E); i++){
		route[i] = disj.find(i);
		if(route[i] == i){
			int adj[5][5] = {};
			int itr = 0;
			for(int j=0; j<E; j++){
				if((i >> j) & 1){
					adj[edge[j].first][edge[j].second] = 1;
					adj[edge[j].second][edge[j].first] = 1;
				}
			}
			for(int i=0; i<n; i++) adj[i][i] = 1;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					for(int k=0; k<n; k++){
						adj[j][k] |= (adj[j][i] & adj[i][k]);
					}
				}
			}
			bool is_conn = true;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					if(!adj[i][j]) is_conn = false;
				}
			}
			num[i] = Graph.size();
			Graph.push_back(pi(i, is_conn));
		}
	}
	for(int i=0; i<Graph.size(); i++){
		int adj[5][5] = {};
		for(int j=0; j<E; j++){
			if((Graph[i].first >> j) & 1){
				adj[edge[j].first][edge[j].second] = 1;
				adj[edge[j].second][edge[j].first] = 1;
			}
		}
		int rev = ipow(E, mod - 2);
		for(int j=0; j<E; j++){
			int nbit = Graph[i].first ^ (1 << j);
			nbit = route[nbit];
			nbit = num[nbit];
			state_adj[i][nbit] += rev;
			state_adj[i][nbit] %= mod;
		}
	}
	return Graph.size();
}

struct matrix{
	lint A[35][35];
	matrix operator*(const matrix &m)const{
		matrix ret;
		memset(ret.A, 0, sizeof(ret.A));
		for(int i=0; i<Graph.size(); i++){
			for(int j=0; j<Graph.size(); j++){
				for(int k=0; k<Graph.size(); k++){
					ret.A[j][k] += A[j][i] * m.A[i][k];
					ret.A[j][k] %= mod;
				}
			}
		}
		return ret;
	}
}POW_D[51], POW_E[51];

vector<lint> vect_mult(vector<lint> V, matrix M){
	vector<lint> W(V.size());
	for(int i=0; i<Graph.size(); i++){
		for(int j=0; j<Graph.size(); j++){
			W[j] += V[i] * M.A[i][j];
			W[j] %= mod;
		}
	}
	return W;
}

int main(){
	cin >> n >> m;
	generate_iso(n); // <= 34
	int day0_msk = 0;
	for(int i=0; i<m; i++){
		int l, r; scanf("%d %d",&l,&r);
		l--, r--;
		if(l > r) swap(l, r);
		for(int j=0; j<E; j++){
			if(edge[j] == pi(l, r)) day0_msk |= (1<<j);
		}
	}
	day0_msk = route[day0_msk];
	day0_msk = num[day0_msk];
	for(int i=0; i<Graph.size(); i++){
		for(int j=0; j<Graph.size(); j++){
			POW_D[0].A[i][j] = state_adj[i][j];
			if(Graph[i].second == 0 &&
				Graph[j].second == 0){
				POW_E[0].A[i][j] = state_adj[i][j];
			}
		}
	}
	for(int i=1; i<51; i++){
		POW_D[i] = POW_D[i-1] * POW_D[i-1];
		POW_E[i] = POW_E[i-1] * POW_E[i-1];
	}
	int q; scanf("%d",&q);
	while(q--){
		lint l, r;
		scanf("%lld %lld",&l,&r);
		vector<lint> ans_vector(Graph.size());
		ans_vector[day0_msk] = 1;
		for(int i=0; i<50; i++){
			if((l >> i) & 1){
				ans_vector = vect_mult(ans_vector, POW_D[i]);
			}
		}
		for(int i=0; i<Graph.size(); i++){
			if(Graph[i].second) ans_vector[i] = 0;
		}
		for(int i=0; i<50; i++){
			if(((r - l) >> i) & 1){
				ans_vector = vect_mult(ans_vector, POW_E[i]);
			}
		}
		lint dap = 1;
		for(auto &i : ans_vector){
			dap += mod - i;
		}
		dap %= mod;
		printf("%lld\n", dap);
	}
}

