#include <bits/stdc++.h>
using namespace std;

int main(){
	int n; cin >> n;
	for(int i=1; i<=n; i++){
		string s; cin >> s;
		if(isdigit(s[0])){
			int an = 0;
			for(auto &j : s){
				an = an * 10 + j - '0';
			}
			if(an != i){
				puts("something is fishy");
				return 0;
			}
		}
	}
	puts("makes sense");
}
