#include <bits/stdc++.h>

using namespace std;

int a[100010];
int b[100010];

bool solve()
{
	int n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	for(i=0; i<n; i++)
		scanf("%d", &b[i]);

	for(i=0; i<n; i++)
		if(a[i] == 1 && b[i] == 1)
			b[i] = 0;

	int cnt1 = 0;
	int cnt2 = 0;
	int x1, x2;
	int xsum = 0;
	for(i=0; i<n; i++)
	{
		xsum ^= a[i];
		if(b[i] == 1)
		{
			cnt1++;
			x1 = a[i];
		}
		else if(b[i] == 2)
		{
			cnt2++;
			x2 = a[i];
		}
	}

	if(xsum == 0)
		return 0;

	if(cnt1 >= 2 || cnt2 >= 2)
		return 0;

	if(cnt1 == 1 && cnt2 == 1)
		return 0;

	if(cnt2 == 1 && (x2 % 2 == 1 || (xsum ^ x2)))
		return 0;

	if(cnt1 == 1 && ((x1 % 2 == 1 && (xsum ^ x1)) || (x1 % 2 == 0 && (xsum ^ x1 ^ 1))))
		return 0;

	return 1;
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
	{
		if(solve())
			puts("Alice");
		else
			puts("Bob");
	}
}