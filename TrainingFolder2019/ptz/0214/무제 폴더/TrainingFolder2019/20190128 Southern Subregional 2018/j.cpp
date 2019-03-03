#include <bits/stdc++.h>

using namespace std;

int a[110];
int b[110];
int mem[2][110][10010];

int main()
{
	int n, i, j, k;
	scanf("%d", &n);
	for(i=1; i<=n; i++)
		scanf("%d", &a[i]);
	for(i=1; i<=n; i++)
		scanf("%d", &b[i]);

	vector<int> v;
	for(i=1; i<=n; i++)
		v.push_back(b[i]);
	sort(v.rbegin(), v.rend());

	int sum = 0;
	for(i=1; i<=n; i++)
		sum += a[i];

	int cur = 0;
	int cnt = -1;
	for(i=0; i<n; i++)
	{
		cur += v[i];
		if(cur >= sum)
		{
			cnt = i + 1;
			break;
		}
	}
	assert(cnt != -1);

	memset(mem, -1, sizeof mem);
	mem[0][0][0] = 0;
	int c = 1;
	for(i=1; i<=n; i++)
	{
		for(j=0; j<=cnt; j++)
		{
			for(k=0; k<=10000; k++)
			{
				mem[c][j][k] = mem[1-c][j][k];
				if(j-1 >= 0 && k-b[i] >= 0 && mem[1-c][j-1][k-b[i]] != -1)
					mem[c][j][k] = max(mem[c][j][k], mem[1-c][j-1][k-b[i]] + a[i]);
			}
		}

		c = 1 - c;
	}

	int res = 0;
	for(i=sum; i<=10000; i++)
		res = max(res, mem[1 - c][cnt][i]);
	
	printf("%d %d\n", cnt, sum - res);
	return 0;
}






