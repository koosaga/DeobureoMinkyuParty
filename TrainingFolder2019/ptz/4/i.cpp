#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40005;
const int MAXM = 40005;

namespace BPM{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int l, int r){ gph[l].push_back(r); }
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front(); que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i;
				r[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int match(int n){
		memset(l, -1, sizeof(l)); // opposite side number (none if -1)
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++) if(l[i] == -1 && dfs(i)) ret++;
		}
		return ret;
	}
};

int lr[110][110];
int dir[110][110];

int main()
{
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			char a, b;
			scanf(" %c%c", &a, &b);
			if(a == 'R')
				lr[i][j] = 1;
			if(b == '^')
				dir[i][j] = 0;
			else if(b == '>')
				dir[i][j] = 1;
			else if(b == 'v')
				dir[i][j] = 2;
			else
				dir[i][j] = 3;
		}
	}

	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			if(i != n - 1 && (lr[i][j] ^ lr[i+1][j]))
			{
				int x = i * m + j;
				int y = (i+1) * m + j;
				if(lr[i][j])
					swap(x, y);
				BPM::add_edge(x, y);
			}
			if(j != m - 1 && (lr[i][j] ^ lr[i][j+1]))
			{
				int x = i * m + j;
				int y = i * m + (j+1);
				if(lr[i][j])
					swap(x, y);
				BPM::add_edge(x, y);
			}
		}
	}
	
	int sz = BPM::match(n*m);
	if(sz * 2 < n*m)
	{
		printf("%d\n", sz);
		return 0;
	}

	int ver = 0;
	for(i=0; i<n*m; i++)
	{
		int y = BPM::l[i];
		if(y == -1)
			continue;

		if(y == i+m || y == i-m)
			ver = 1 - ver;
	}

	int sum = 0;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			sum = (sum + dir[i][j]) % 4;

	if(ver == 0 && sum == 0 || ver == 1 && sum == 2)
		printf("%d\n", sz);
	else
		printf("%d\n", sz - 1);

	return 0;
}








