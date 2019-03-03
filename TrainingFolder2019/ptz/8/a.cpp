#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int query(int x, int y){
	printf("Q %d %d\n", x, y);
	fflush(stdout);
	int z; cin >> z;
	return z;
}

void answer(int x, int y){
	printf("A %d %d\n", x, y);
	fflush(stdout);
	exit(0);
}

int dist(pi a, pi b){
	int dx = a.first - b.first;
	int dy = a.second - b.second;
	return dx * dx + dy * dy;
}

vector<pi> v;
pi wonrae[200000];

vector<pi> boom(vector<pi> v){
	vector<pi> w;
	for(auto &i : v){
		for(int j=0; j<4; j++){
			w.emplace_back(i.first + dx[j], i.second + dy[j]);
		}
	}
	sort(w.begin(), w.end());
	w.resize(unique(w.begin(), w.end()) - w.begin());
	return w;
}

int main(){
	for(int i=0; i<=100; i++) for(int j=0; j<=100; j++) v.emplace_back(i, j);
	int x = query(420, 696);
	vector<pi> w;
	for(auto &i : v){
		if(dist(pi(420, 696), i) == x){
			w.push_back(i);
		}
	}
	v = w;
	vector<vector<pi>> ff;
	ff.resize(v.size());
	srand(0x69697474);
	for(int i=0; i<v.size(); i++){
		ff[i].push_back(v[i]);
		wonrae[i] = v[i];
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<ff.size(); j++) ff[j] = boom(ff[j]);
		int x = rand() % 1000;
		int y = rand() % 1000;
		int z = query(x, y);
		for(int j=0; j<ff.size(); j++){
			vector<pi> nxt;
			for(auto &k : ff[j]){
				if(dist(k, pi(x, y)) == z) nxt.push_back(k);
			}
			ff[j] = nxt;
		}
	}
	for(int i=0; i<v.size(); i++){
		if(ff[i].size()) answer(wonrae[i].first, wonrae[i].second);
	}
}
