#include <bits/stdc++.h>

using namespace std;

int arr[510][510];

int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			scanf("%d", &arr[i][j]);

	int mx = 0;
	for(i=0; i<n; i++)
	{
		int mn = 100;
		for(j=0; j<n; j++)
			mn = min(mn, arr[i][j]);
		mx = max(mx, mn);
	}

	printf("%d\n", mx);
	return 0;
}