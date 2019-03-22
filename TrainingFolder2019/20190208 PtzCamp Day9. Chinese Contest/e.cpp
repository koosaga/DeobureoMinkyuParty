#include <bits/stdc++.h>

using namespace std;

long long arr[1000010];

void solve()
{
	int n, i;
	long long m;
	scanf("%d%lld", &n, &m);
	for(i=0; i<n; i++)
		scanf("%lld", &arr[i]);

	int mxp = max_element(arr, arr + n) - arr;
	if(arr[mxp] > m)
	{
		puts("-1");
		return;
	}

	if(n % 2 == 0)
	{
		printf("%lld\n", m + arr[mxp]);
		return;
	}

	for(i=0; i<n; i++)
		arr[i] = m - arr[i];

	long long g0 = arr[mxp];
	vector<long long> v1, v2;
	for(i=1; i<=n/2; i++)
	{
		v1.push_back(arr[(mxp - i + n) % n]);
		v2.push_back(arr[(mxp + i) % n]);
	}

	/*
	printf("g0 = %lld\n", g0);
	for(auto t : v1)
		printf("v1 %lld\n", t);
	for(auto t : v2)
		printf("v2 %lld\n", t);
	*/

	long long s = m + (m - g0);
	long long g = 3 * m;
	//printf("sg %lld %lld\n", s, g);
	while(s < g)
	{
		long long x = (s + g) / 2;
		long long its = g0;
		bool ok = 1;
		for(i=0; i<n/2; i++)
		{
			long long u0 = x - (2 * m - its);
			if(u0 < 0)
			{
				ok = 0;
				break;
			}

			long long g1 = v1[i];
			long long g2 = v2[i];
			if(g2 < g1)
				swap(g1, g2);

			long long u1 = min(g2 - g1, m - its);
			long long u2 = max(0LL, min(g1, m - its - u1));
			long long u3 = max(0LL, min(m - its, g1) - u2);
			long long u4 = max(0LL, min(0LL, g1 - m) + its);
			its = min(m, u0 + u1 + 2 * u2 + u3 + u4);
		}
		if(its < m)
			ok = 0;

		if(ok)
			g = x;
		else
			s = x + 1;
	}
	printf("%lld\n", s);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}