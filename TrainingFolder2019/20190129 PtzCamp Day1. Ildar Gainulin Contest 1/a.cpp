#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 20005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

struct mf{
	// 1-based Vertex index
	int vis[MAXN], par[MAXN], orig[MAXN], match[MAXN], aux[MAXN], t, N;
	vector<int> conn[MAXN];
	queue<int> Q;
	void add_edge(int u, int v) {
		u++; v++;
		conn[u].push_back(v); conn[v].push_back(u);
	}
	void init(int n) {
		N = n; t = 0;
		for(int i=0; i<=n; ++i) {
			conn[i].clear();
			match[i] = aux[i] = par[i] = 0;
		}
	}
	void augment(int u, int v) {
		int pv = v, nv;
		do {
			pv = par[v]; nv = match[pv];
			match[v] = pv; match[pv] = v;
			v = nv;
		} while(u != pv);
	}
	int lca(int v, int w) {
		++t;
		while(true) {
			if(v) {
				if(aux[v] == t) return v; aux[v] = t;
				v = orig[par[match[v]]];
			}
			swap(v, w);
		}
	}
	void blossom(int v, int w, int a) {
		while(orig[v] != a) {
			par[v] = w; w = match[v];
			if(vis[w] == 1) Q.push(w), vis[w] = 0;
			orig[v] = orig[w] = a;
			v = par[w];
		}
	}
	bool bfs(int u) {
		fill(vis+1, vis+1+N, -1); iota(orig + 1, orig + N + 1, 1);
		Q = queue<int> (); Q.push(u); vis[u] = 0;
		while(!Q.empty()) {
			int v = Q.front(); Q.pop();
			for(int x: conn[v]) {
				if(vis[x] == -1) {
					par[x] = v; vis[x] = 1;
					if(!match[x]) return augment(u, x), true;
					Q.push(match[x]); vis[match[x]] = 0;
				}
				else if(vis[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a); blossom(v, x, a);
				}
			}
		}
		return false;
	}
	int Match() {
		int ans = 0;
		// find random matching (not necessary, constant improvement)
		vector<int> V(N-1); iota(V.begin(), V.end(), 1);
		shuffle(V.begin(), V.end(), mt19937(0x94949));
		for(auto x: V) if(!match[x]){
			for(auto y: conn[x]) if(!match[y]) {
				match[x] = y, match[y] = x;
				++ans; break;
			}
		}
		for(int i=1; i<=N; ++i) if(!match[i] && bfs(i)) ++ans;
		return ans;
	}
}mf;

int n, m;
char str[105][105];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int availMask(int x, int y){
	int ans = (1<<26) - 1;
	for(int i=0; i<4; i++){
		if(x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] <= m && isalpha(str[x+dx[i]][y+dy[i]])){
			ans &= ~(1 << (str[x + dx[i]][y + dy[i]] - 'a'));
		}
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	mf.init(2 * n * m);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
	}
	int cnt = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '+'){
				cnt++;
				for(int k=0; k<4; k++){
					if(i + dx[k] >= 0 && i + dx[k] < n && j + dy[k] >= 0 && j + dy[k] < m && str[i + dx[k]][j + dy[k]] == '.'){
						int pos = (i + dx[k]) * m + j + dy[k];
						mf.add_edge(i * m + j, pos);
						mf.add_edge(i * m + j + n * m, pos);
					}
				}
				mf.add_edge(i * m + j, i * m + j + n * m);
			}
			if(str[i][j] == '*'){
				cnt++;
				for(int k=0; k<4; k++){
					if(i + dx[k] >= 0 && i + dx[k] < n && j + dy[k] >= 0 && j + dy[k] < m && str[i + dx[k]][j + dy[k]] == '.'){
						int pos = (i + dx[k]) * m + j + dy[k];
						if(k % 2) mf.add_edge(i * m + j, pos);
						else mf.add_edge(i * m + j + n * m, pos);
					}
				}
				mf.add_edge(i * m + j, i * m + j + n * m);
			}
		}
	}
	int dap = mf.Match() - cnt;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '+'){
				int np = mf.match[i * m + j + 1] - 1;
				int mp = mf.match[i * m + j + n * m + 1] - 1;
				if(np < n * m && mp < n * m && str[np / m][np % m] == '.' && str[mp / m][mp % m] == '.'){
					int msk = availMask(np / m, np % m) & availMask(mp / m, mp % m) & availMask(i, j);
					for(int v=0; v<26; v++){
						if((msk >> v) & 1){
							str[np/m][np%m] = str[mp/m][mp%m] = str[i][j] = v + 'a';
							break;
						}
					}
				}
			}
			if(str[i][j] == '*'){
				int np = mf.match[i * m + j + 1] - 1;
				int mp = mf.match[i * m + j + n * m + 1] - 1;
				if(np < n * m && mp < n * m && str[np / m][np % m] == '.' && str[mp / m][mp % m] == '.'){
					int msk = availMask(np / m, np % m) & availMask(mp / m, mp % m) & availMask(i, j);
					for(int v=0; v<26; v++){
						if((msk >> v) & 1){
							str[np/m][np%m] = str[mp/m][mp%m] = str[i][j] = v + 'a';
							break;
						}
					}
				}
			}
		}
	}
	for(int i=0; i<n; i++) cout << str[i] << endl;
}
