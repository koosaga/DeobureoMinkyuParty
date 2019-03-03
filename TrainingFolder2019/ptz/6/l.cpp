#include <bits/stdc++.h>

using namespace std;

int arr[100010];

int main()
{
	int n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);

	if(is_sorted(arr, arr + n) || n % 2 == 0)
		puts("Bob");
	else
		puts("Alice");
	return 0;
}