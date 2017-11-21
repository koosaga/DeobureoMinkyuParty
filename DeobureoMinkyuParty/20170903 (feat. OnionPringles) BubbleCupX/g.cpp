#include <bits/stdc++.h>
using namespace std;

char buf[55];
int trie[5000005][5], piv;
int term[5000005];
int n, q;

vector<int> v;
int chk[5000005];

void bktk(int x, int p){
	if(buf[x] == 0){
		v.push_back(p);
		return;
	}
	if(buf[x] != '?'){
		p = trie[p][buf[x] - 'a'];
		if(p == 0) return;
		bktk(x +1, p);
		return;
	}
	bktk(x + 1, p);
	for(int i=0; i<5; i++){
		if(trie[p][i]) bktk(x + 1, trie[p][i]);
	}
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		int p = 0;
		for(int j=0; buf[j]; j++){
			if(!trie[p][buf[j] - 'a']){
				trie[p][buf[j] - 'a'] = ++piv;
			}
			p = trie[p][buf[j] - 'a'];
		}
		term[p]++;
	}
	while(q--){
		scanf("%s", buf);
		bktk(0, 0);
		int ret = 0;
		for(auto &i : v){
			if(chk[i]) continue;
			chk[i] = 1;
			ret += term[i];
		}
		printf("%d\n", ret);
		for(auto &i : v) chk[i] = 0;
		v.clear();
	}
}

