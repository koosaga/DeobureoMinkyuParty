#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int d, s;
int vis[505][5005];
pi par[505][5005];

queue<pi> que;

int main(){
	cin >> d >> s;
	memset(vis, 0, sizeof(vis));
		for(int i=1; i<10; i++){
		if(vis[i % d][i]) continue;
		vis[i%d][i] = 1;
		par[i%d][i] = pi(0, i);
		que.emplace(i % d, i);
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(x == pi(0, s)){
			vector<int> v;
			while(x.second){
				auto ww  = par[x.first][x.second];
				v.push_back(ww.second);
				x.second -= ww.second;
				x.first = ww.first;
			}
			reverse(v.begin(), v.end());
			for(auto &i : v) printf("%d",i);
			return 0;
		}
		for(int i=0; i<10; i++){
			int nxt = (x.first * 10 + i) % d;
			if(x.second + i > s) continue;
			if(!vis[nxt][x.second + i]){
				vis[nxt][x.second + i] = 1;
				par[nxt][x.second + i] = pi(x.first, i);
				que.emplace(nxt, x.second + i); 
			}
		}
	}
	puts("-1");
}
