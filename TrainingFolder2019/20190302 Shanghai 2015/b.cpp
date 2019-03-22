#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n, k, i;
	scanf("%d%d", &n, &k);
	
	if(k == 1)
	{
		assert(n == 1);
		puts("1 +");
		return;
	}
	
	if(n == 1LL << k)
	{
		long long c = 0;
		for(i=0; i<k; i++)
		{
			long long x = (1LL << i);
			if(i == k - 1)
				x++;
			
			printf("%lld +\n", x);
			c += x;
		}
		assert(c == n);
		return;
	}
	
	vector<int> v;
	int t = n;
	while(t)
	{
		v.push_back(t % 2);
		t /= 2;
	}
	
	while(v.size() < k)
		v.push_back(0);
	
	long long c = 0;
	bool u = 0;
	for(i=0; i<k; i++)
	{
		long long x = (1LL << i);
		if(n % 2 == 0 && i == k - 1)
			x++;
		
		if(v[i] == 1)
			u = 1;
			
		if(n % 2 == 0 && !u)
		{
			if(v[i + 1] == 1)
			{
				printf("%lld -\n", x);
				c -= x;
			}
			else
			{
				printf("%lld +\n", x);
				c += x;
			}
			
			continue;
		}
		
		
		if(i != k - 1 && v[i + 1] == 0)
		{
			printf("%lld -\n", x);
			c -= x;
		}	
		else
		{
			printf("%lld +\n", x);
			c += x;
		}
	}
	
	assert(c == n);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
