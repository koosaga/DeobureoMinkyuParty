#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 1000005;
using lint = long long;
using pi = pair<int, int>;

int n;
string s[MAXN];
char buf[MAXT];
int trie[MAXT][4], piv;
vector<int> term[MAXT];

lint dap;
vector<pi> ans;

int dfs(int x, int d){
	vector<int> v = term[x];
	for(int i=0; i<4; i++){
		if(!trie[x][i]) continue;
		int w = dfs(trie[x][i], d + 1);
		if(w) v.push_back(w);
	}
	for(int i=1; i<v.size(); i+=2){
		dap += d;
		ans.emplace_back(v[i-1], v[i]);
	}
	if(v.size() % 2) return v.back();
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		s[i] = buf;
		int p = 0;
		for(auto &j : s[i]){
			if(j == 'G') j = 'B';
			if(j == 'T') j = 'D';
			if(!trie[p][j - 'A']){
				trie[p][j - 'A'] = ++piv;
			}
			p = trie[p][j - 'A'];
		}
		term[p].push_back(i + 1);
	}
	dfs(0, 0);
	cout << dap << endl;
	for(auto &i : ans) printf("%d %d\n", i.first, i.second);
}
