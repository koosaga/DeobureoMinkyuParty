#include <bits/stdc++.h>

using namespace std;

char res[400010];
long long a, b, c, d;

bool f(int u, int v)
{
	long long i;
	long long p = -1;
	for(i=0; i*(i-1)/2 <= a; i++)
		if(i*(i-1)/2 == a)
			p = i;
	
	if(p == 1 && u)
		p = 0;
			
	long long q = -1;
	for(i=0; i*(i-1)/2 <= d; i++)
		if(i*(i-1)/2 == d)
			q = i;
	
	if(q == 1 && v)
		q = 0;
	
	if(p == -1 || q == -1)
		return 0;
	
	long long n = p + q;
	if(n*(n-1)/2 != a + b + c + d)
		return 0;
	
	if(b > 1LL * p * q)
		return 0;
	
	if(p == 0)
	{
		for(i=0; i<q; i++)
			res[i] = '1';
	}
	else
	{
	
		long long x = b / p;
		long long y = b % p;
	
		if(x + (y == 0 ? 0 : 1) > q)
			return 0;
	
		long long sz = 0;
		if(y == 0)
		{
			for(i=0; i<q-x; i++)
				res[sz++] = '1';
			for(i=0; i<p; i++)
				res[sz++] = '0';
			for(i=0; i<x; i++)
				res[sz++] = '1';
		}
		else
		{
			for(i=0; i<q-x-1; i++)
				res[sz++] = '1';
			for(i=0; i<y; i++)
				res[sz++] = '0';
			res[sz++] = '1';
			for(i=0; i<p-y; i++)
				res[sz++] = '0';
			for(i=0; i<x; i++)
				res[sz++] = '1';
		}
	
		assert(sz == n);
	}
	
	long long cnt = 0;
	long long tmp = 0;
	for(i=0; i<n; i++)
	{
		if(res[i] == '1')
			cnt++;
		else
			tmp += cnt;
	}
	
	if(tmp != c)
		return 0;
	
	res[n] = '\0';
	return 1;
}

int main()
{
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	
	if(f(0, 0))
	{
		printf("%s\n", res);
		return 0;
	}
	if(f(0, 1))
	{
		printf("%s\n", res);
		return 0;
	}
	if(f(1, 0))
	{
		printf("%s\n", res);
		return 0;
	}
	if(f(1, 1))
	{
		printf("%s\n", res);
		return 0;
	}
	
	puts("impossible");
	return 0;
}



















