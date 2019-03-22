#include <bits/stdc++.h>

using namespace std;

vector<int> edg[510];
bool chk[510];

int tow[510][510];

int f(int x, vector<int> &v)
{
	
}

char buf[10];

int main()
{
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	for(i=0; i<m; i++)
	{
		int k;
		scanf("%d", &k);
		
		int p;
		for(j=0; j<k; j++)
		{
			int x;
			scanf("%d", &x);
			
			if(j != 0)
			{
				edg[x].push_back(p);
				edg[p].push_back(x);
			}
			
			p = x;
		}
	}
	
	for(i=1; i<=n; i++)
	{
		memset(chk, 0, sizeof chk);
		
		queue<int> q;
		chk[i] = 1;
		tow[i][i] = i;
		for(int y : edg[i])
		{
			chk[y] = 1;
			tow[i][y] = y;
			q.push(y);
		}
		
		while(!q.empty())
		{
			int sz = q.size();
			for(j=0; j<sz; j++)
			{
				int x = q.front();
				q.pop();
				
				for(int y : edg[x])
				{
					if(chk[y])
						continue;
					
					chk[y] = 1;
					tow[i][y] = tow[i][x];
					q.push(y);
				}
			}
		}
	}
	
	vector<int> v;
	for(i=1; i<=n; i++)
		v.push_back(i);
	
	for(i=0; i<10; i++)
	{
		int mn = 1e9;
		int nxt = -1;
		for(int x : v)
		{
			int t = f(x, v);
			if(t < mn)
			{
				mn = t;
				nxt = x;
			}
		}
		
		printf("%d\n", nxt);
		fflush(stdout);
		
		scanf("%s", buf);
		if(buf[0] == 'F')
			return 0;
	}
	
	return 0;
}





