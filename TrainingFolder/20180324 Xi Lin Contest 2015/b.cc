#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

static char buf[1<<19];
static int idx = 0;
static int bytes = 0;
static inline int _read()
{
	if(!bytes || idx == bytes)
	{
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt()
{
	int x = 0, s = 1;
	int c = _read();
	while(c<=32) c= _read();
	while(c>32) x = 10*x+(c-'0'), c = _read();
	return x;
}

int n, m;
pi E[MAXN];
char str[MAXN*2];

namespace seg{
	struct disj{
		int pa[2*MAXN];
		int rk[2*MAXN];
		void init(int n){
			iota(pa, pa + n + 1, 0);
		}
		int find(int x){
			return pa[x] == x ? x : find(pa[x]);
		}
		void uni(int p, int q, vector<int> &undoes){
			p = find(p);
			q = find(q);
			if(p == q) return; 
			if(rk[p] > rk[q]) swap(p, q);
			undoes.push_back(-p-1);
			pa[p] = q;
			if(rk[p] == rk[q]){
				rk[q]++;
				undoes.push_back(q);
			}
		}
		void undo(vector<int> &v){
			reverse(v.begin(), v.end());
			for(auto &i : v){
				if(i >= 0) rk[i]--;
				else pa[-i-1] = -i-1;
			}
		}
	}disj;
	int lim;
	vector<pi> tree[270000];
	void init(int n){
		disj.init(n*2);
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=2*lim; i++) tree[i].clear();
	}
	void add(int s, int e, pi v){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) tree[s++].push_back(v);
			if(e%2 == 0) tree[e--].push_back(v);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s].push_back(v);
	}
	void dfs(int s, int e, int p){
		bool FUCK = false;
		vector<int> undoes;
		for(auto &i : tree[p]){
			disj.uni(i.first + n, i.second, undoes);
			disj.uni(i.first, i.second + n, undoes);
			if(disj.find(i.first + n) ==
					disj.find(i.first)){
				FUCK = true;
				break;
			}
		}
		if(!FUCK){
			if(s == e){
				str[s] = '1';
			}
			else{
				int m = (s+e)/2;
				dfs(s, m, 2*p);
				dfs(m+1, e, 2*p+1);
			}
		}
		disj.undo(undoes);
	}
};

int main(){
	int tc = _readInt();
	for(int i=0; i<tc; i++){
		n = _readInt();
		m = _readInt();
		for(int i=0; i<m; i++){
			E[i].first = _readInt();
			E[i].second = _readInt();
			if(E[i].first > E[i].second) swap(E[i].first, E[i].second);
			E[i].first--;
			E[i].second--;
		}
		sort(E, E+m);
		m = unique(E, E+m) - E;
		for(int i=0; i<n; i++) str[i] = '0';
		seg::init(n);
		for(int i=0; i<m; i++){
			seg::add(0, E[i].first - 1, E[i]);
			seg::add(E[i].first + 1, E[i].second - 1, E[i]);
			seg::add(E[i].second + 1, n-1, E[i]);
		}
		seg::dfs(0, seg::lim-1, 1);
		str[n] = 0;
		puts(str);
	}
}
