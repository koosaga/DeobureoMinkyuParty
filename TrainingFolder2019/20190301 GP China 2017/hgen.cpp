#include <bits/stdc++.h>
using namespace std;
mt19937 rng;
int main(){
	int p[4];
	for(int i=0; i<4; i++){
		cin >> p[i];
	}
	vector<int> perm(11);
	iota(perm.begin(), perm.end(), 1);
	
	
	//return 0;
	//int rep = 100000;
	do{
		printf("%d\n", perm.size());
		for(auto &i :perm) printf("%d ", i);
		puts("");
		for(int i=0; i<4; i++) printf("%d ", p[i]);
		puts("");
		//shuffle(perm.begin(),perm.end(),rng);		
	}while(next_permutation(perm.begin(), perm.end()));
}
