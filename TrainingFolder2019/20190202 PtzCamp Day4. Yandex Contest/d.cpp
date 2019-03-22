#include <bits/stdc++.h>
using lint = long long;
using namespace std;
using pi = pair<int, int>;
const int MAXN = 150;

int n, m, sz;
vector<pi> indep;

vector<lint> v[MAXN];
vector<int> chk[MAXN];
vector<int> dist[MAXN];
vector<pi> par[MAXN];

vector<pi> insert_in_first(lint x){
	lint basis[66] = {};
	lint from[66] = {};
	for(int i=0; i<indep.size(); i++){
		lint x = v[indep[i].first][indep[i].second];
		lint y = (1ll << i);
		for(int j=59; j>=0; j--){
			if((x >> j) & 1){
				if(basis[j]){
					x ^= basis[j];
					y ^= from[j];
				}
				else{
					basis[j] = x;
					from[j] = y;
					break;
				}
			}
		}
	}
	lint fromv = 0;
	for(int j=59; j>=0; j--){
		if((x >> j) & 1){
			if(basis[j]){
				x ^= basis[j];
				fromv ^= from[j];
			}
			else return vector<pi>();
		}
	}
	vector<pi> v;
	for(int i=0; i<indep.size(); i++){
		if((fromv >> i) & 1) v.push_back(indep[i]);
	}
	return v;
}

vector<pi> insert_in_second(int x, int y){
	vector<pi> w;
	for(int i=0; i<v[x].size(); i++){
		if(!chk[x][i]) w.emplace_back(x, i);
	}
	return w;
}

void insert_matroid(vector<lint> w){
	queue<pi> que;
	chk[sz].resize(w.size());
	v[sz] = w;
	sz++;
	for(int i=0; i<sz; i++){
		dist[i].clear();
		par[i].clear();
		dist[i].resize(v[i].size(), 1e9);
		par[i].resize(v[i].size(), pi(-1, -1));
	}
	for(int i=0; i<v[sz-1].size(); i++){
		que.emplace(sz - 1, i);
		dist[sz - 1][i] = 0;
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(chk[x.first][x.second] == 0){ 
			auto aug = insert_in_first(v[x.first][x.second]);
			if(aug.empty()){
				for(pi i = x; i != pi(-1, -1); i = par[i.first][i.second]){
					chk[i.first][i.second] ^= 1;
					if(chk[i.first][i.second]){
						indep.push_back(i);
					}
					else{
						indep.erase(find(indep.begin(), indep.end(), i));
					}
				}
				break;
			}
			for(auto &i : aug){
				if(dist[i.first][i.second] > dist[x.first][x.second] + 1){
					dist[i.first][i.second] = dist[x.first][x.second] + 1;
					par[i.first][i.second] = x;
					que.emplace(i.first, i.second);
				}
			}
		}
		else{ // to find replacement
			auto v = insert_in_second(x.first, x.second);
			for(auto &i : v){
				if(dist[i.first][i.second] > dist[x.first][x.second] + 1){
					dist[i.first][i.second] = dist[x.first][x.second] + 1;
					par[i.first][i.second] = x;
					que.emplace(i.first, i.second);
				}
			}
		}
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		lint x;
		cin >> x;
		insert_matroid({x});
	}
	cin >> m;
	for(int i=0; i<m; i++){
		int k; cin >> k;
		vector<lint> v(k);
		for(int j=0; j<k; j++) cin >> v[j];
		insert_matroid(v);
	}
	if(indep.size() != n + m){
		puts("-1");
		return 0;
	}
	sort(indep.begin(), indep.end());
	for(int i=n; i<n+m; i++) cout << v[i][indep[i].second] << endl;
}
