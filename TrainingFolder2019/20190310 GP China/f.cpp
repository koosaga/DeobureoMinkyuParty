#include <bits/stdc++.h>

using namespace std;

const long long INF = 4.5e18;
long long mem[201][201][103];

void upd(long long &x, long long v)
{
	assert(v < INF);
	x = min(x, v);
}

void solve()
{
	long long h1, h2;
	long long h3;
	long long a1, a2, a3;
	scanf("%lld%lld%lld%lld%lld%lld", &h1, &h2, &h3, &a1, &a2, &a3);
	
	if(a1 > a2)
	{
		swap(a1, a2);
		swap(h1, h2);
	}
	
	for(int i=0; i<=h1 + 100; i++)
		for(int j=0; j<=h2 + 100; j++)
			for(int k=0; k<=102; k++)
				mem[i][j][k] = INF;
	
	long long res = INF;
	
	mem[h1 + 100][h2 + 100][1] = 0;
	for(int k=1; k<=101; k++)
	{
		for(int i=0; i<=h1 + 100; i++)
		{
			for(int j=0; j<=h2 + 100; j++)
			{
				long long &x = mem[i][j][k];
				if(x == INF)
					continue;
				
				long long bosshp = h3 + (h1 + 100 - i) + (h2 + 100 - j) - (k-1) * k / 2;

				if(i > 100)
					x += a1;
				if(j > 100)
					x += a2;
				if(bosshp > 0)
					x += a3;
				
				if(i <= 100 && j <= 100 && bosshp <= 0)
				{
					upd(res, x);
					continue;
				}
				
				if(i > 100)
					upd(mem[i - k][j][k + 1], x);
					
				if(j > 100)
					upd(mem[i][j - k][k + 1], x);
				
				if(bosshp > 0)
					upd(mem[i][j][k + 1], x);
			}
		}
	}
	
	for(int i=0; i<=h1 + 100; i++)
	{
		for(int j=0; j<=h2 + 100; j++)
		{
			long long &x = mem[i][j][102];
			if(x == INF)
				continue;

			long long bosshp = h3 + (h1 + 100 - i) + (h2 + 100 - j) - 101 * 102 / 2;
			
			if(i > 100)
				x += a1;
			if(j > 100)
				x += a2;
			if(bosshp > 0)
				x += a3;
				
			if(i <= 100 && j <= 100 && bosshp <= 0)
			{
				upd(res, x);
				continue;
			}
			
			if(bosshp <= 0)
			{
				if(i > 100 && j > 100)
					upd(res, x + a1);
				else
					upd(res, x);
				continue;
			}
			
			long long s = 102;
			long long g = 1.5e9;
			while(s < g)
			{
				long long m = s + (g - s) / 2;
				if(bosshp - 1LL * (m - 1) * m / 2 + 101 * 102 / 2 <= 0)
					g = m;
				else
					s = m + 1;
			}
			
			if(i <= 100 && j <= 100)
				upd(res, x + 1LL * (s - 103) * a3);
				
			if(i > 100 && j <= 100)
				upd(res, x + 1LL * (s - 103) * (a1 + a3) + a1);
				
			if(i <= 100 && j > 100)
				upd(res, x + 1LL * (s - 103) * (a2 + a3) + a2);
				
			if(i > 100 && j > 100)
				upd(res, x + 1LL * (s - 103) * (a1 + a2 + a3) + (a1 + a2) + a1);
		}
	}
	
	printf("%lld\n", res);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}
