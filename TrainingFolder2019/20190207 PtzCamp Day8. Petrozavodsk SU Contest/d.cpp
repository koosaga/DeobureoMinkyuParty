/*#include <bits/stdc++.h>

using namespace std;

long long sq(long long x)
{
	return x * x;
}

int main()
{
	long long n, k, i;
	scanf("%lld%lld", &n, &k);
	//	printf("tt = %lld\n", 4 * n * n - 4 * n - 8 * k);

	long long mn = 0;
	long long mx = n;

	{
		long long x = (2 * n - 1 - sqrt(8 * k + 1)) / 2;
		for(i = x - 5; i <= x + 5; i++)
		{
			long long t = 2 * n - 1 - 2 * i;
			if(t < 0 || 8 * k + 1 >= sq(t))
			{
				mn = max(mn, i);
				break;
			}
		}
	}
	{
		long long x = (2 * n - 1 + sqrt(8 * k + 1)) / 2;
		for(i = x + 5; i >= x - 5; i--)
		{
			long long t = 2 * i - 2 * n + 1;
			if(t < 0 || 8 * k + 1 >= sq(t))
			{
				mx = min(mx, i);
				break;
			}
		}
	}
	//printf("mn mx %lld %lld\n", mn, mx);
	{
		long long x = (1 - sqrt(4 * n * n - 4 * n - 8 * k)) / 2;
		for(i = x - 5; i <= x + 5; i++)
		{
			long long t = 1 - 2 * i;
			if(t < 0 || 4 * n * n - 4 * n - 8 * k <= sq(t))
			{
				mn = max(mn, i);
				break;
			}
		}
	}

	{
		long long x = (1 + sqrt(4 * n * n - 4 * n - 8 * k)) / 2;
		//printf("x = %lld\n", x);
		//printf("tt = %lld\n", 4 * n * n - 4 * n - 8 * k);
		for(i = x + 5; i >= x - 5; i--)
		{
			long long t = 2 * i - 1;
			if(t < 0 || 4 * n * n - 4 * n - 8 * k <= sq(t))
			{
				//printf("i = %lld\n", i);
				mx = min(mx, i);
				break;
			}
		}
	}
	//printf("mn mx %lld %lld\n", mn, mx);

	if(mx < mn)
		puts("-1");
	else
	{
		long long r = max(mx * (mx - 1) / 2 + (n - mx) * (n - mx - 1) / 2, mn * (mn - 1) / 2 + (n - mn) * (n - mn - 1) / 2);
		printf("%lld\n", r);
	}

	return 0;
}*/




#include <bits/stdc++.h>

using namespace std;

long long sq(long long x)
{
	return x * x;
}

int main()
{
	long long n, k, i;
	scanf("%lld%lld", &n, &k);
	//	printf("tt = %lld\n", 4 * n * n - 4 * n - 8 * k);


	vector<long long> v;
	v.push_back(0);
	v.push_back(n);

	{
		long long x = (2 * n - 1 - sqrt(8 * k + 1)) / 2;
		v.push_back(min(max(0LL, x), n));
	}
	{
		long long x = (2 * n - 1 + sqrt(8 * k + 1)) / 2;
		v.push_back(min(max(0LL, x), n));
	}
	//printf("mn mx %lld %lld\n", mn, mx);
	{
		long long x = (1 - sqrt(4 * n * n - 4 * n - 8 * k)) / 2;
		v.push_back(min(max(0LL, x), n));
	}

	{
		long long x = (1 + sqrt(4 * n * n - 4 * n - 8 * k)) / 2;
		v.push_back(min(max(0LL, x), n));
	}

	long long r = -1;
	for(long long x : v)
	{
		for(i = x - 100000; i <= x + 100000; i++)
		{
			if(i < 0 || i > n)
				continue;

			long long p = i;
			long long q = n - i;
			long long p2 = p * (p - 1) / 2;
			long long q2 = q * (q - 1) / 2;
			long long n2 = n * (n - 1) / 2;
			if(q2 <= k && k <= n2 - p2)
				r = max(r, p2 + q2);
		}
	}

	printf("%lld\n", r);
	return 0;
}


