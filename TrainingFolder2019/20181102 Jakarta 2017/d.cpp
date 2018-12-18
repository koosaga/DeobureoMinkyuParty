
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;

int n, m;
int s[MAXN], e[MAXN], x[MAXN];
vector<int> in[MAXN], out[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	vector<int> crd;
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		crd.push_back(s[i]);
		crd.push_back(e[i]);
	}
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	for(int i=0; i<n; i++){
		s[i] = lower_bound(crd.begin(), crd.end(), s[i]) - crd.begin();
		e[i] = lower_bound(crd.begin(), crd.end(), e[i]) - crd.begin();
		in[e[i]].push_back(x[i]);
		out[s[i]].push_back(x[i]);
	}
	int ret = n;
	for(int i=0; i<crd.size(); i++){
		sort(in[i].rbegin(), in[i].rend());
		sort(out[i].rbegin(), out[i].rend());
		int cursatisfy = 0;
		int p = 0;
		for(auto &j : in[i]){
			while(p < out[i].size() && out[i][p] > j){
				p++;
			}
			int nxt = min(cursatisfy + m, p);
			ret -= (nxt - cursatisfy);
			cursatisfy = nxt;
		}
		p = out[i].size();
		while(cursatisfy < p){
			int nxt = min(cursatisfy + m, p);
			ret -= (nxt - cursatisfy) - 1;
			cursatisfy = nxt;
		}
	}
	cout << ret << endl;
}
