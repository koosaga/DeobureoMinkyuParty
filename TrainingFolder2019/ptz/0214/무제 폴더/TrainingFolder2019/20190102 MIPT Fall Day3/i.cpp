#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 105;
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

int n;
int dap[MAXN][MAXN];
int pa[MAXN];

int main(){
	dap[1][1] = 1;
	for(n = 2; n <= 100; n+=2){
		fprintf(stderr, "done %d\n", n);
		map<pair<int, vector<int>>, int> mp1, mp2;
		{
			vector<int> v(n);
			iota(v.begin(), v.end(), 0);
			mp1[make_pair(0, v)] = 1;
		}
		for(int i = n / 2; i; i--){
			mp2.clear();
			auto new_norm = [&](int &v1, vector<int> &v2){	
				if(v2.back() != 2 * i - 1) v1++;
				v2.pop_back();
				if(v2.back() != 2 * i - 2) v1++;
				v2.pop_back();
			};
			for(auto &j : mp1){
				int v1; 
				vector<int> v2;
				tie(v1, v2) = j.first;
				new_norm(v1, v2);
				int val = mp2[make_pair(v1, v2)] + j.second;
				while(val >= mod) val -= mod;
				mp2[make_pair(v1, v2)] = val;
			}
			for(auto &j : mp1){
				int v1; 
				vector<int> v2;
				tie(v1, v2) = j.first;
				for(int i=0; i<v2.size()/2; i++){
					int pos = min(v2[i], v2[i + v2.size() / 2]);
					for(auto &j : v2){
						if(j == v2[i] || j == v2[i + v2.size() / 2]){
							j = pos;
						}
					}
				}
				new_norm(v1, v2);
				int val = mp2[make_pair(v1, v2)] + mod - j.second;
				while(val >= mod) val -= mod;
				mp2[make_pair(v1, v2)] = val;
			}
			mp1 = mp2;
		}
		for(auto &i : mp1){
			int l = i.first.first;
			int r = i.second;
			assert(l < n && l >= 0);
			dap[n][n-l] += r;
			if(dap[n][n-l] >= mod) dap[n][n-l] -= mod;
			dap[n+1][n+1-l] += r;
			if(dap[n+1][n+1-l] >= mod) dap[n+1][n+1-l] -= mod;
		}
	}
	return 0;*/
	printf("int arr[100][100] = {");
	for(int i=1; i<=100; i++){
		printf("{");
		for(int j=1; j<=i; j++){
			printf("%d", dap[i][j]);
			if(j != i) putchar(',');
			else putchar('}');
		}
		if(i != n) printf(",");
		else printf("}");
	}
}
