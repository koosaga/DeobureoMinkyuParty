#include <bits/stdc++.h>
using namespace std;

int n, q, p;
int lazy;

set<int> s;

int main(){
	scanf("%d %d %d",&n,&q,&p);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		s.insert(x);
	}
	while(q--){
		int x;
		scanf("%d",&x);
		if(x == 1){
			scanf("%d",&x);
			s.insert(x + lazy);
		}
		else{
			auto k = *s.begin();
			s.erase(k);
			lazy++;
			s.insert(p - 1 + lazy);
		}
	}
	for(auto &i : s) printf("%d ", i - lazy);

}
