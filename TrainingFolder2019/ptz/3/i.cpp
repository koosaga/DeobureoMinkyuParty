#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	int minx = 1e9;
	int miny = 1e9;
	while(n--){
		int x, y;
		cin >> x >> y;
		minx = min(minx, x);
		miny = min(miny, y);
	}
	cout << minx <<  " " << miny << endl;
}
