#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000005;
using pi = pair<int, int>;

char str[MAXN];

bool good(string s, int n){
	string canon;
	canon.push_back(s[0]);
	for(int i=1; i<s.size(); i++){
		if(s[i] != s[i-1]) canon.push_back(s[i]);
	}
}

void solve(){
	string s;
	for(int i=0; i<n; i++){
		for(int j=0; j<str[i] - '0'; j++){
			s.push_back(j + '0');
			if(good(s)){
				maxpos = max(maxpos, pi(i, j));
			}
			s.pop_back();
		}
		s.push_back(str[i]);
	}
}

int main(){
	while(~scanf("%s", str)){
		n = strlen(str);
		if(n <= 4){
			int x; sscanf(str, "%d", &x);
			if(x <= 1010){
				puts("-1");
				continue;
			}
		}
		if(str[0] == '1' && count(str + 1, str + n, '0') >= n - 2){
			int disc = 0;
			int wrong = 0;
			for(int j=1; j<n; j++){
				if(str[j] != '0'){
					disc = 1;
					if(j == n - 1) wrong = 1;
					if(j == n - 2 && str[j] == '1' && str[j+1] == '0') wrong = 1;
					break;
				}
			}
			if(!disc) wrong = 1;
			if(wrong){
				for(int j=0; j<n-3; j++) putchar('9');
				puts("898");
				continue;
			}
		}
		solve();
	}
}
