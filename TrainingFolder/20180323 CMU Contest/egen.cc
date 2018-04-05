#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 50005;

int main(){
	int n;
	scanf("%d",&n);
	cout << n << endl;
	for(int i=0; i<n-1; i++){
		int j = i+2;
		printf("%d %d\n", j-1, j);
	}
}
