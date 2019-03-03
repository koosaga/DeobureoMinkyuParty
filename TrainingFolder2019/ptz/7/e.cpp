#include <bits/stdc++.h>

using namespace std;

int arr[200];

int main()
{
	int n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);

	int s = 0;
	for(i=0; i<n; i++)
		s += arr[i] - 2;

	int r = n + (s + 1) / 2;
	printf("%d\n", r);
	return 0;
}