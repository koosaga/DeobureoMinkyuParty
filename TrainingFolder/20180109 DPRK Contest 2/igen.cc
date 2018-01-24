#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 3005;

int main(){
	vector<int> q;
	for(int i=0; i<2700; i++) q.push_back(rand() % 999999999 + 1);
	sort(q.begin(), q.end());
	q.resize(unique(q.begin(), q.end()) - q.begin());
	set<pi> s;
	s.insert(pi(0, 0));
	while(s.size() < 3000){
		auto x = pi(rand() % 201, rand() % 201);
		x.first -= 100;
		x.second -= 100;
		s.insert(x);
	}
	cout << 3000 << endl;
	for(auto &i : s) printf("%d %d\n", i.first, i.second);
	printf("2700\n");
	for(auto &i : q) cout << i << endl;
}

