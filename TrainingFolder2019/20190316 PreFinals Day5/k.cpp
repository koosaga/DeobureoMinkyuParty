#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char str[MAXN][MAXN];
int idx[MAXN][MAXN];
int adj[MAXN][MAXN];
int col[MAXN], deg[MAXN];

pi nxt(pi x){
	if(x.first % 2 == 0){
		if(x.second == m - 1) return pi(x.first + 1, m - 1);
		else return pi(x.first, x.second + 1);
	}
	else{
		if(x.second == 0) return pi(x.first + 1, 0);
		else return pi(x.first, x.second - 1);
	}
}

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

int main(){
	scanf("%d %d",&n,&m);
	vector<int> v;
	for(int i=1; i*(i+1)/2<=n*m; i++){
		v.push_back(i);
	}
	v.back() += n * m - accumulate(v.begin(), v.end(), 0);
	pi ptr(0, 0);
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v[i]; j++){
			idx[ptr.first][ptr.second] = i + 1;
			ptr = nxt(ptr);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<4; k++){
				if(ok(i + dx[k], j + dy[k])){
					adj[idx[i][j]][idx[i+dx[k]][j+dy[k]]] = 1;
				}
			}
		}
	}
	for(int i=1; i<=v.size(); i++) adj[i][i] = 0;
	for(int i=1; i<=v.size(); i++){
		for(int j=1; j<=v.size(); j++){
			deg[i] += adj[i][j];
		}
	}
	for(int i=1; i<=v.size(); i++){
		int cur = 1e9, pos = -1;
		for(int j=1; j<=v.size(); j++){
			if(!col[j] && deg[j] < cur){
				cur = deg[j];
				pos = j;
			}
		}
		bool used[30] = {};
		for(int j=1; j<=v.size(); j++){
			if(!adj[i][j]) continue;
			if(col[j]){
				used[col[j]] = 1;
			}
			else{
				deg[j]--;
			}
		}
		for(int j=1; j<=26; j++){
			if(!used[j]){
				col[i] = j;
				break;
			}
		}
	}
	cout << v.size() << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int val = col[idx[i][j]] - 1;
			putchar(val + 'A');
		}
		puts("");
	}
}
