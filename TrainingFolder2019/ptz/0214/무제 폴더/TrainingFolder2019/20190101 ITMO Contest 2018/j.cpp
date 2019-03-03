#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;
const int rt = 316;

int a[100010];
int mem[100010];
int sum[rt + 1][100010];

int main()
{
	int n, h0, i, j;
	scanf("%d%d", &n, &h0);
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]);

	mem[n] = 1;
	for(i=1; i <= rt; i++)
		sum[i][n] = 1;

	for(i=n-1; i>=1; i--)
	{
		if(a[i] <= rt)
		{
			if(i + a[i] <= n)
				mem[i] = (mem[i] + sum[a[i]][i + a[i]]) % mod;
		}
		else
		{
			int t = i + a[i];
			while(t <= n)
			{
				mem[i] = (mem[i] + mem[t]) % mod;
				if(a[t] == a[i])
					break;
				t += a[i];
			}
		}

		for(j = 1; j <= rt; j++)
		{
			if(a[i] != j && i + j <= n)
				sum[j][i] = (mem[i] + sum[j][i + j]) % mod;
			else
				sum[j][i] = mem[i];
		}
	}

	int res = mem[1];
	if(h0 != a[1])
	{	
		int t = 1 + h0;
		while(t <= n)
		{
			res = (res + mem[t]) % mod;
			if(a[t] == h0)
				break;
			t += h0;
		}
	}

	printf("%d\n", res);
	return 0;
}