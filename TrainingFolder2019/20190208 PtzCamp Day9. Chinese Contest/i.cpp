#include <bits/stdc++.h>

using namespace std;

char arr[1000010];

void solve()
{
	int n, i;
	scanf("%s", arr);
	n = strlen(arr);
	if(n == 1)
	{
		puts("0");
		return;
	}

	int c0 = 0, c1 = 0, c2 = 0;
	for(i=0; i<n; i++)
	{
		if(arr[i] == '0')
			c0++;
		else if(arr[i] == '1')
			c1++;
		else
			c2++;
	}

	if(max({c0, c1, c2}) > (n + 1) / 2)
	{
		puts("-1");
		return;
	}

	if(c0 == 0 || c1 == 0 || c2 == 0)
	{
		if(n % 2 == 0)
		{
			printf("%d\n", n/2 - 1);
			for(i=0; i<n/2 - 1; i++)
				printf("%d %d\n", n / 2 - i, n / 2 + 1 - i);
		}
		else
		{
			
		}
		return;
	}

	int x = n / 2 - c1;
	int y = n / 2 - (n % 2 == 0 ? c0 : c0 - 1);
	int z = n / 2 - c2;

	int cnt = x + y + z - 1;
	printf("%d\n", x + y + z - 1);

	int p = 1;
	for(i=0; i<x; i++)
	{
		cnt--;
		printf("%d %d\n", p + 1, p + c0 + c1 + c2 - 2);
		p += 2;
		c0--;
		c2--;
	}
	if(n % 2 == 1)
	{
		p += 1;
		c0--;
	}
	for(i=0; i<y - (y ? 1 : 0); i++)
	{
		cnt--;
		printf("%d %d\n", p + c0 + c1 - 1, p + c0 + c1);
		c1--;
		c2--;
	}
	for(i=0; i<z - (y ? 0 : 1); i++)
	{
		cnt--;
		printf("%d %d\n", p + c0 - 1, p + c0);
		c0--;
		c1--;
	}

	assert(cnt == 0);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}