#include <bits/stdc++.h>
using namespace std;

int h, w, n;
char str[105][105];

void solve(int a, int b){
	for(int i=0; i<h; i++) fill(str[i], str[i] + w, '#');
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++) str[2*i][2*j] = '.';
	}
	for(int i=0; i<h; i++) cout << str[i] << endl;
}

int main(){
	freopen("kotlin.in", "r", stdin);
	freopen("kotlin.out", "w", stdout);
	cin >> h >> w >> n;
	int v1 = (h + 1) / 2, v2 = (w + 1) / 2;
	for(int i=1; i<=v1; i++){
		for(int j=1; j<=v2; j++){
			if(i * j == n){
				solve(i, j);
				return 0;
			}
		}
	}
	puts("Impossible");
}
