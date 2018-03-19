#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
typedef __int128 bset;

int n;
char str[6][11][11];
int tab[6][11][11];
vector<pi> tp[6];
vector<bset> cnd[6];
bset ONE = 1;

bool ok(int x, int y){
	return max(x, y) <= n-2 && min(x, y) >= 1;
}

void Add(int x, vector<bset> &cnd){
	int mx = 1e9, my = 1e9;
	for(auto &i : tp[x]){
		mx = min(mx, i.first);
		my = min(my, i.second);
	}
	for(auto &i : tp[x]){
		i.first -= mx;
		i.second -= my;
	}
	mx = 0, my = 0;
	for(auto &i : tp[x]){
		mx = max(mx, i.first);
		my = max(my, i.second);
	}
	for(int i=0; i<n-mx; i++){
		for(int j=0; j<n-my; j++){
			int cnt = 0;
			for(auto &k : tp[x]){
				if(ok(k.first + i, k.second + j)){
					cnt++;
				}
			}
			if(cnt == (n-2)*(n-2)){
				bset b = 0;
				for(auto &k : tp[x]){
					if(!ok(k.first + i, k.second + j)){
						int v = tab[x][k.first+i][k.second+j];
						b |= (ONE << v);
					}
				}
				cnd.push_back(b);
			}
		}
	}
}

void Rotate(int x){
	for(auto &i : tp[x]){
		i = pi(n-i.second, i.first);
	}
}

void Flip(int x){
	for(auto &i : tp[x]){
		i.first = n-i.first;
	}
}

char ret[11][11][11];

void WeWillBuildAWallAndMexicoWillPayForIt(vector<int> v, vector<bset> b){
	for(int i=0; i<n*n*n; i++) ret[i/(n*n)][(i/n)%n][i%n] = '.';
	for(int it = 0; it < 6; it++){
		int idx = 0;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					int c1 = (i == 0 || i == n-1);
					int c2 = (j == 0 || j == n-1);
					int c3 = (k == 0 || k == n-1);
					if(c1 + c2 + c3 < 2) continue;
					if((b[it] >> idx) & 1){
						ret[i][j][k] = v[it] + 'A';;
					}
					idx++;
				}
			}
		}
		for(int i=1; i<n-1; i++){
			for(int j=1; j<n-1; j++){
				if(it == 0) ret[0][i][j] = v[it] + 'A';
				if(it == 2) ret[n-1][i][j] = v[it] + 'A';
				if(it == 1) ret[i][0][j] = v[it] + 'A';
				if(it == 3) ret[i][n-1][j] = v[it] + 'A';
				if(it == 4) ret[i][j][0] = v[it] + 'A';
				if(it == 5) ret[i][j][n-1] = v[it] + 'A';
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++) puts(ret[i][j]);
		puts("");
	}
}

void Do(int x, int y, int z){
	for(int i=0; i<6; i++){
		tp[i].clear();
		cnd[i].clear();
	}
	vector<int> fuck = {0, x, y, z};
	for(int i=0; i<6; i++){
		if(count(fuck.begin(), fuck.end(), i) == 0) fuck.push_back(i);
	}
	int cnt = 0;
	for(auto &v : fuck){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(str[v][j][k] != '.') tp[cnt].push_back(pi(j, k));
			}
		}
		cnt++;
	}
	bset l = 0, r = 0, totbit = 0;;
	int idx = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				int c1 = (i == 0 || i == n-1);
				int c2 = (j == 0 || j == n-1);
				int c3 = (k == 0 || k == n-1);
				if(c1 + c2 + c3 < 2) continue;
				if(i == 0) tab[0][j][k] = idx;
				if(i == n-1) tab[2][j][k] = idx;
				if(j == 0) tab[1][i][k] = idx;
				if(j == n-1) tab[3][i][k] = idx;
				if(k == 0) tab[4][i][j] = idx, l |= (ONE << idx);
				if(k == n-1) tab[5][i][j] = idx, r |= (ONE << idx);
				totbit |= (ONE << idx);
				idx++;
			}
		}
	}
	Add(0, cnd[0]);
	for(int i=0; i<6; i++){
		for(int k=0; k<2; k++){
			for(int j=0; j<4; j++){
				Rotate(i);
				Add(i, cnd[i]);
			}
			Flip(i);
		}
	}
	for(int i=0; i<6; i++){
		sort(cnd[i].begin(), cnd[i].end());
		cnd[i].resize(unique(cnd[i].begin(), cnd[i].end()) - cnd[i].begin());
	}
	for(auto &i : cnd[0]){
		for(auto &j : cnd[1]){
			for(auto &k : cnd[2]){
				for(auto &lfuck : cnd[3]){
					bset b = i | j | k | lfuck;
					bset ll = l & ~b;
					bset rr = r & ~b;
					if((b | ll | rr) != totbit) continue;
					if(binary_search(cnd[4].begin(), cnd[4].end(), ll) &&
						binary_search(cnd[5].begin(), cnd[5].end(), rr)){
						vector<bset> b = {i, j, k, lfuck, ll, rr};
						WeWillBuildAWallAndMexicoWillPayForIt(fuck, b);
						exit(0);
					}
				}
			}
		}
	}
}

int main(){
	cin >> n;
	for(int i=0; i<6; i++){
		for(int j=0; j<n; j++) cin >> str[i][j];
	}
	for(int i='B'; i<='F'; i++){
		for(int j='B'; j<='F'; j++){
			for(int k='B'; k<='F'; k++){
				if(i != j && j != k && k != i){
					Do(i - 'A', j - 'A', k - 'A');
				}
			}
		}
	}
}
