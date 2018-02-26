#include<bits/stdc++.h>
using namespace std;

int flowN, flowM;

const int MAXN = 1010101, MAXM = 1010101;
vector<int> gph[MAXN];
int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
void clear(){ for(int i=0; i<flowN; ++i) gph[i].clear(); }
void add_edge(int l, int r){ gph[l].push_back(r);}
bool bfs(int n)
{
    queue<int> Q;
    bool ok = 0;
    for(int i=0; i<flowN; ++i) dis[i] = 0;
    for(int i=0; i<n; ++i)
    {
        if(l[i] == -1 && !dis[i])
        {
            Q.push(i);
            dis[i] = 1;
        }
    }
    while(!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for(auto& i: gph[x])
        {
            if(r[i] == -1) ok = 1;
            else if(!dis[r[i]])
            {
                dis[r[i]] = dis[x]+1;
                Q.push(r[i]);
            }
        }
    }
    return ok;
}
bool dfs(int x)
{
    for(auto &i: gph[x])
    {
        if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x]+1 && dfs(r[i])))
        {
            vis[r[i]] = 1; l[x] = i; r[i] = x;
            return 1;
        }
    }
	return 0;
}

int match(int n)
{
	for(int i=0; i<flowN; ++i){
		l[i] = -1;
	}
	for(int i=0; i<flowM; i++) r[i] = -1;
	int ret = 0;
	while(bfs(n))
	{
		for(int i=0; i<flowN; ++i) vis[i] = 0;
		for(int i=0; i<n; ++i) if(l[i] == -1 && dfs(i)) ret++;
	}
	return ret;
}


int N, M, a, b;
int u[MAXN], v[MAXN];
vector<int> conn[MAXN];
vector<int> revconn[MAXN];
bool solve() {
	if(revconn[a].size() != 0) return false;
	if(conn[a].size() == 0) return false;

	if(conn[b].size() != 0) return false;
	if(revconn[b].size() == 0) return false;

	for(int i=1; i<=N; ++i)
	{
		if( i==a || i==b ) continue;
		if( conn[i].size() == 0 ) return false;
		if( revconn[i].size() == 0 ) return false;
	}
	flowN = 2 * N;
	flowM = M;
	for(int i=1; i<=N; i++){
		for(auto &j : conn[i]){
			add_edge(i-1, j-1);
		}
		for(auto &j : revconn[i]){
			add_edge(i + N - 1, j - 1);
		}
	}
	int k = match(2 * N);
	if(k != 2 * N - 2) return false;
	puts("YES");
	for(int i=1; i<=N; i++){
		if(i != a) printf("%d ", 1 + l[i + N - 1]);
	}
	puts("");
	for(int i=1; i<=N; i++){
		if(i != b) printf("%d ", 1 + l[i - 1]);
	}
	puts("");
	return true;
}

int main()
{
	while(4==scanf("%d%d%d%d", &N, &M, &a, &b))
	{
		for(int i=1; i<=M; ++i)
		{
			scanf("%d%d", u+i, v+i);
			conn[u[i]].push_back(i);
			revconn[v[i]].push_back(i);
		}
		if(!solve()) puts("NO");
		clear();
		for(int i=1; i<=N; ++i)
			conn[i].clear(), revconn[i].clear();
	}
}



