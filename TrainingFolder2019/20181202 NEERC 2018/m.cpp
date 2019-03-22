#include <bits/stdc++.h>

using namespace std;

int arr[10][10];
bool chk[10];

vector<int> scc[10];
int num[10];
int siz;

vector<int> edg[10];
int deg[10];

char res[30][3][210];
int dep[10];

int main()
{
	int n, i, j, k;
	scanf("%d", &n);
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			scanf("%d", &arr[i][j]);
	
	for(i=1; i<=n; i++)
		arr[i][i] = 1;
	
	for(k=1; k<=n; k++)
		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++)
				arr[i][j] |= arr[i][k] & arr[k][j];
	
	for(i=1; i<=n; i++)
	{
		if(chk[i])
			continue;
		
		for(j=1; j<=n; j++)
		{
			if(arr[i][j] & arr[j][i])
			{
				chk[j] = 1;
				scc[siz].push_back(j);
				num[j] = siz;
			}
		}
		siz++;
	}
	
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			if(arr[i][j] && num[i] != num[j])
			{
				deg[num[j]]++;
				edg[num[i]].push_back(num[j]);
			}
		}
	}
	
	queue<int> q;
	for(i=0; i<siz; i++)
		if(deg[i] == 0)
			q.push(i);
	
	vector<int> ord;
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		
		dep[x] = (int)ord.size();
		ord.push_back(x);
		
		for(int y : edg[x])
		{
			deg[y]--;
			if(deg[y] == 0)
				q.push(y);
		}
	}
	
	for(i=0; i<30; i++)
	{
		for(j=0; j<3; j++)
		{
			for(k=0; k<200; k++)
			{
				if(i % 3 == 2 && j != 2 || j == 1 || j == 2 && k % 2 == 1)
					res[i][j][k] = '#';
				else
					res[i][j][k] = '.';
			}
		}
	}
	
	for(i=0; i<siz; i++)
	{
		int x = ord[i];
		
		for(j=0; j<scc[x].size(); j++)
			res[3*i+1][0][j] = '0' + scc[x][j];
		
		for(int y : edg[x])
		{
			int t = 2 * (dep[x] * 10 + dep[y]);
			
			res[3*dep[x]+1][1][t] = '.';
			res[3*dep[y]+1][1][t] = '.';
			res[3*dep[y]+2][2][t] = '#';
		}
	}
	
	printf("%d %d %d\n", 200, 3, 30);
	for(i=0; i<30; i++)
	{
		for(j=0; j<3; j++)
			printf("%s\n", res[i][j]);
		puts("");
	}
	
	return 0;
}
