#include <bits/stdc++.h>
using namespace std;

vector<int> v[4];

int main(){
	int n; scanf("%d",&n);
	for(int i=0; i<n; i++){
		int c, w;
		scanf("%d %d",&c,&w);
		if(c == 10) c = 2;
		if(c == 11) c = 3;
		v[c].push_back(w);
	}
	for(int i=0; i<4; i++) sort(v[i].rbegin(), v[i].rend());
	if(v[1].size() < v[2].size()) swap(v[1], v[2]);
	while(v[1].size() > v[2].size()){
		v[0].push_back(v[1].back());
		v[1].pop_back();
	}
	v[1].resize(v[2].size());
	sort(v[0].rbegin(), v[0].rend());
	v[0].resize(v[3].size());
	int ret = 0;
	for(int i=0; i<4; i++){
		ret = accumulate(v[i].begin(), v[i].end(), ret);
	}
	cout << ret << endl;
}

