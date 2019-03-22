#include <bits/stdc++.h>

using namespace std;

int mem[1601][81][81];

void solve()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);

	mem[n * m][n][m] = 1 % k;
	for(int x = n * m - 1; x >= 0; x--)
	{
		for(int r = 0; r <= n; r++)
		{
			for(int c = 0; c <= m; c++)
			{
				mem[x][r][c] = 0;
				if(x < r * c)
					mem[x][r][c] = 1LL * (r * c - x) * mem[x+1][r][c] % k;
				if(r < n)
					mem[x][r][c] = (mem[x][r][c] + 1LL * (n - r) * c * mem[x+1][r+1][c]) % k;
				if(c < m)
					mem[x][r][c] = (mem[x][r][c] + 1LL * (m - c) * r * mem[x+1][r][c+1]) % k;

				//printf("mem %d %d %d = %d\n", x, r, c, mem[x][r][c]);
			}
		}
	}

	int res = mem[0][1][1] % k;
	printf("%d\n", res);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}