#include <bits/stdc++.h>
using namespace std;

int query(int x, int y){
	printf("? %d %d\n", x + 1, y + 1);
	fflush(stdout);
	string s; cin >> s;
	if(s == "<") return -1;
	if(s == ">") return 1;
	if(s == "=") return x < y ? -1 : 1;
	assert(0);
}

void report(int x, int y){
	printf("! %d %d\n", x + 1, y + 1);
	fflush(stdout);
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<int> l, r;
		for(int i=0; i+1<n; i+=2){
			int x = query(i, i + 1);
			if(x < 0){
				l.push_back(i);
				r.push_back(i + 1);
			}
			else{
				l.push_back(i + 1);
				r.push_back(i);
			}
		}
		if(n % 2 == 1){
			l.push_back(n - 1);
			r.push_back(n - 1);
		}
		int rmin = l[0];
		int rmax = r[0];
		for(int i=1; i<l.size(); i++){
			if(query(rmin, l[i]) > 0){
				rmin = l[i];
			}
		}
		for(int i=1; i<r.size(); i++){
			if(query(rmax, r[i]) < 0){
				rmax = r[i];
			}
		}
		report(rmin, rmax);
	}
}
