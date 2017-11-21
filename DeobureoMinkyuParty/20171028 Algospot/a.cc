#include <bits/stdc++.h>
using namespace std;

string s;

int main(){
	cin >> s;
	for(int i=0; i<8; i++){
		for(int j=0; j<i; j++){
			if(s[i] + s[j] == '5' + '5'){
				cout << "Yes";
				return 0;
			}
		}
	}
	cout << "No";
}
