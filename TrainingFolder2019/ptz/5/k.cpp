#include <bits/stdc++.h>

using namespace std;

long long a1[11];
long long a2[11];
long long mem[1 << 11][1 << 11][11];
long long l1[1 << 11];
long long l2[1 << 11];
long long mx1[1 << 11];
long long mx2[1 << 11];
vector<int> v1[1 << 11];
vector<int> nv1[1 << 11];
vector<int> v2[1 << 11];
vector<int> nv2[1 << 11];

int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%lld%lld", &a1[i], &a2[i]);

	int s1 = 0, s2 = 0;
	for(i=0; i<n; i++)
	{
		s1 += a1[i];
		s2 += a2[i];
	}

	for(i=0; i<n; i++)
	{
		a1[i] *= s2;
		a2[i] *= s1;
	}

	memset(mem, -1, sizeof mem);
	for(i=0; i<n; i++)
	{
		mem[1 << i][0][i] = 0;
		mem[0][1 << i][i] = 0;
	}

	for(int b1 = 0; b1 < (1 << n); b1++)
	{
		for(i=0; i<n; i++)
		{
			if(b1 & (1 << i))
			{
				v1[b1].push_back(i);
				l1[b1] += a1[i];
				mx1[b1] = max(mx1[b1], a1[i]);
			}
			else
				nv1[b1].push_back(i);
		}
	}
	for(int b2 = 0; b2 < (1 << n); b2++)
	{
		for(i=0; i<n; i++)
		{
			if(b2 & (1 << i))
			{
				v2[b2].push_back(i);
				l2[b2] += a2[i];
				mx2[b2] = max(mx2[b2], a2[i]);
			}
			else
				nv2[b2].push_back(i);
		}
	}


	for(int b1 = 0; b1 < (1 << n); b1++)
	{
		for(int b2 = 0; b2 < (1 << n); b2++)
		{
			if(l1[b1] >= l2[b2])
			{
				if(l1[b1] - l2[b2] > mx1[b1])
					continue;
			}
			else
			{
				if(l2[b2] - l1[b1] > mx2[b2])
					continue;
			}
				
			if(l1[b1] >= l2[b2])
			{
				for(int x : v1[b1])
				{
					if(mem[b1][b2][x] == -1)
						continue;
					for(int y : nv2[b2])
					{
						if(l2[b2] + a2[y] > l1[b1])
							mem[b1][b2 | (1 << y)][y] = max(mem[b1][b2 | (1 << y)][y], mem[b1][b2][x] + (x == y ? l1[b1] - l2[b2] : 0));
						else
							mem[b1][b2 | (1 << y)][x] = max(mem[b1][b2 | (1 << y)][x], mem[b1][b2][x] + (x == y ? a2[y] : 0));
					}
				}
			}
			else
			{
				for(int y : v2[b2])
				{
					if(mem[b1][b2][y] == -1)
						continue;
					for(int x : nv1[b1])
					{
						if(l1[b1] + a1[x] >= l2[b2])
							mem[b1 | (1 << x)][b2][x] = max(mem[b1 | (1 << x)][b2][x], mem[b1][b2][y] + (x == y ? l2[b2] - l1[b1] : 0));
						else
							mem[b1 | (1 << x)][b2][y] = max(mem[b1 | (1 << x)][b2][y], mem[b1][b2][y] + (x == y ? a1[x] : 0));
					}
				}
			}
		}
	}

	long long r = 0;
	for(i=0; i<n; i++)
		r = max(r, mem[(1 << n) - 1][(1 << n) - 1][i]);

	printf("%.15lf\n", 1.0 * r / (1LL * s1 * s2));
/*
	printf("r = %lld\n", r);
	for(int b1 = 0; b1 < (1 << n); b1++)
	{
		vector<int> v1, nv1;
		long long l1 = 0;
		for(i=0; i<n; i++)
		{
			if(b1 & (1 << i))
			{
				v1.push_back(i);
				l1 += a1[i];
			}
			else
				nv1.push_back(i);
		}

		for(int b2 = 0; b2 < (1 << n); b2++)
		{
			vector<int> v2, nv2;
			long long l2 = 0;
			for(i=0; i<n; i++)
			{
				if(b2 & (1 << i))
				{
					v2.push_back(i);
					l2 += a2[i];
				}
				else
					nv2.push_back(i);
			}
			if(l1 >= l2)
			{
				for(int x : v1)
				{
					printf("b1 b2 l1 l2 x m %d %d %lld %lld %d %lld\n", b1, b2, l1, l2, x, mem[b1][b2][x]);
				}
			}
			else
			{
				for(int y : v2)
				{
					printf("b1 b2 l1 l2 y m %d %d %lld %lld %d %lld\n", b1, b2, l1, l2, y, mem[b1][b2][y]);
				}
			}
		}
	}*/
	return 0;
}





