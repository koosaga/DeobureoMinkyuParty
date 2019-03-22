#include <bits/stdc++.h>

using namespace std;

int hero[110];
int hp[110];

int ori[110];
int arr[110];

bool chk[110];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; i++)
	{
		int s, h;
		scanf("%d%d", &s, &h);
		hero[s] = i;
		hp[i] = h;
	}
	for(int i=1; i<=n; i++)
		scanf("%d", &ori[i]);

	for(int i=1;i<=n;i++)
	{
		memset(chk, 0, sizeof chk);
		vector<int> v1;
		for(int j=1; j<=n; j++)
			arr[j] = ori[j];

		while(1)
		{
			int now = -1;
			for(int j=1; j<i; j++)
			{
				if(!hero[j])
					continue;

				int c = hp[hero[j]];
				bool ok = 1;
				for(int k=j; k<=i; k++)
				{
					c += arr[k];
					if(c < 0)
					{
						ok = 0;
						break;
					}
				}
				if(ok)
				{
					now = j;
					break;
				}
			}
			if(now == -1)
				break;

			chk[now] = 1;
			v1.push_back(now);

			for(int j=now; j<=i; j++)
				arr[j] = 0;
		}

		memset(chk, 0, sizeof chk);
		vector<int> v2;
		for(int j=1; j<=n; j++)
			arr[j] = ori[j];

		while(1)
		{
			int now = -1;
			for(int j=n; j>=i; j--)
			{
				if(!hero[j])
					continue;

				int c = hp[hero[j]];
				bool ok = 1;
				for(int k=j; k<=i; k++)
				{
					c += arr[k];
					if(c < 0)
					{
						ok = 0;
						break;
					}
				}
				if(ok)
				{
					now = j;
					break;
				}
			}
			if(now == -1)
				break;

			chk[now] = 1;
			v1.push_back(now);

			for(int j=now; j<=i; j++)
				arr[j] = 0;
		}
	}

	// Rally = Hero
	return 0;
}