#include <bits/stdc++.h>

using namespace std;

long long h[100010];
long long x[100010];
long long y[100010];

int main()
{
	int n, t, i;
	scanf("%d%d", &n, &t);
	for(i=0;i<n;i++)
		scanf("%lld", &h[i]);

	x[0] = 0;
	y[0] = h[0];
	for(i=1;i<n;i++)
	{
		x[i] = x[i-1] + h[i-1];
		y[i] = max(h[i], y[i-1]);
	}

	for(i=0;i<n;i++)
	{
		if(t - x[i] <= 0)
			printf("1\n");
		else
		{
			if((t - x[i]) % y[i] < h[i])
				printf("%lld\n", (t - x[i]) / y[i] + 1);
			else
				printf("%lld\n", (t - x[i]) / y[i] + 2);
		}
	}

	return 0;
}