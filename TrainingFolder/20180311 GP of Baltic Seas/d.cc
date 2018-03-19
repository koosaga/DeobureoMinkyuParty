#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, s, t, l, hv[11];
string name[11];
int cur_health[1<<10];
bool vis[1<<10][1<<10];
pi trk[1<<10][1<<10];

int Move(int H1, int L1, int L2){
	int v = (H1 * L2) / L1;
	int w = (H1 * L2) % L1;
	if(w * 2 < L1){
		return v;
	}
	if(w * 2 > L1){
		return v + 1;
	}
	if(w * 2 == L1){
		return v + v%2;
	}
}

int main(){
	scanf("%d %d %d %d\n",&n,&s,&t,&l);
	int msk = 0;
	if(s == t){
		puts("0");
		printf("%d / %d\n", s, l);
		return 0;
	}
	for(int i=0; i<n; i++){
		int x;
		char buf1[50], buf2[50];
		scanf("%s %d ",buf1, &x);
		fgets(buf2, 50, stdin);
		name[i] = buf2;
		hv[i] = x;
		if(*buf1 == '+'){
			msk |= (1<<i);
			l -= x;
		}
	}
	for(int i=0; i<(1<<n); i++){
		cur_health[i] = l;
		for(int j=0; j<n; j++){
			if((i >> j) & 1) cur_health[i] += hv[j];
		}
	}
	queue<pi> que;
	que.push(pi(msk, s));
	while(!que.empty()){
		int msk = que.front().first;
		int cur = que.front().second;
		que.pop();
		for(int i=0; i<n; i++){
			int nxt_health = Move(cur, cur_health[msk], cur_health[msk ^ (1<<i)]);
			if(nxt_health > 0 && !vis[msk ^ (1<<i)][nxt_health]){
				vis[msk ^ (1<<i)][nxt_health] = 1;
				trk[msk ^ (1<<i)][nxt_health] = pi(msk, cur);
				que.push(pi(msk ^ (1<<i), nxt_health));
			}
		}
	}
	for(int i=t; i<=1000; i++){
		if(vis[msk][i]){
			vector<pi> state;
			for(pi j = pi(msk, i); j != pi(msk, s); j = trk[j.first][j.second]){
				state.push_back(j);
			}
			state.push_back(pi(msk, s));
			printf("%d\n", state.size() - 1);
			reverse(state.begin(), state.end());
			for(int i=0; i<state.size(); i++){
				printf("%d / %d\n", state[i].second, cur_health[state[i].first]);
				if(i + 1 != state.size()){
					int flg = state[i].first ^ state[i+1].first;
					if((state[i].first & flg)) printf("- ");
					else printf("+ ");
					for(int j=0; j<n; j++){
						if(flg == (1<<j)) printf(name[j].c_str());
					}
				}
			}
			return 0;
		}
	}
	puts("-1");
}
