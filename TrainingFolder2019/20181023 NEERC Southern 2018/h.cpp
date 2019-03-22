#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> lis;
int n, q;
string a[10005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		cin >> a[i];
		string x = a[i];
		set<string> tmp;
		for(int i=0; i<x.size(); i++){
			for(int j=1; j<=x.size()-i; j++){
				tmp.insert(x.substr(i, j));
			}
		}
		for(auto &j : tmp) lis.emplace_back(j, i);
	}
	sort(lis.begin(), lis.end());
	scanf("%d",&q);
	while(q--){
		char buf[10];
		scanf("%s", buf);
		string x = buf;
		auto l = lower_bound(lis.begin(), lis.end(), make_pair(x, -1));
		auto r = upper_bound(lis.begin(), lis.end(), make_pair(x, 1241234));
		if(l == r) puts("0 -");
		else{
			printf("%d %s\n",(int)(r - l), a[l->second].c_str());
		}
	}
}
